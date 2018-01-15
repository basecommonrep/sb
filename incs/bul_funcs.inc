<?
   
function saveFieldValues( $dbn, $P, &$searchDbsValues )
{
	$PTC = $GLOBALS['params_table_content'];
	$currPTC = $PTC[$dbn];	
	
	$fnames = array_keys( $currPTC );
	
	while( list( $fname, $fvalue ) = each( $P ) )
		if ( in_array( $fname, $fnames ) )
			$searchDbsValues[$dbn][$fname] = ltrim(rtrim($fvalue));
} // end saveFieldValues

function getFieldValues( $dbn, &$P, $searchDbsValues )
{
	$postFnames = array_keys( $P );
	
	while( list( $fname, $fvalue ) = each( $searchDbsValues[$dbn] ) )
		if ( in_array( $fname, $postFnames ) )
			$P[$fname] = $fvalue;
		else
			$P += array( $fname => $fvalue );
} // end getFieldValues

function getSearchFieldsValues($dbn, $valuesFromUser)
{
	$PTC = $GLOBALS['params_table_content'];
	$currPTC = $PTC[$dbn];	
	
	$fnames = array_keys( $currPTC );
	$values = array();
	
	while( list( $fname, $fvalue ) = each( $valuesFromUser ) )
		if ( in_array( $fname, $fnames ) )
			$values += array( $fname => $fvalue );
	
	return $values;	
} // end getSearchFieldsFalues


function parseFieldsExpr($dbn, $currSearchDbsValues)
{
	$PTC = $GLOBALS['params_table_content'];
	$currPTC = $PTC[$dbn];	
	
	$parsedValues = array();
	
	
	while( list( $fname, $fieldValue ) = each( $currSearchDbsValues ) )
	{	
		$ftype = $currPTC[$fname][0];
		$fieldValue = trim( ltrim( $fieldValue ) );
		
		$fieldElements = array();
	
		if ( !empty( $fieldValue ) )
		{
			$p = new ExpressionParser( $fieldValue, $ftype, '' );		

			while( $p->GetPos() < $p->GetLen() )
			{
				$fieldElement = $p->Scan();
				
				//print("|".$fieldElement.'|<BR>');
				
				$fieldElement = strtoupper( $fieldElement );
				$fieldElement = trim( ltrim( $fieldElement ) );
				
				

				if ( !empty( $fieldElement ) )
					array_push( $fieldElements, $fieldElement );

			} // end while

		} // if !empty( $fieldValue )
		
		$parsedValues += array( $fname => $fieldElements );
	} // end while
//	print_r ($parsedValues);
	return $parsedValues;
} // end parseFieldsExpr

function verifyFieldValues( $dbn, $parsedValues )
{
	$LANG_SETTINGS = $GLOBALS['LANG_SETTINGS'];

	$parser_errors = $GLOBALS['parser_errors'];
	$PTC = $GLOBALS['params_table_content'];
	$currPTC = $PTC[$dbn];	
	
	$error = '';
	while( list( $fname, $fieldElements ) = each( $parsedValues ) )
	{
		$ftype = $currPTC[$fname][0];
		$ftitle = $currPTC[$fname][3];

		if ( count( $fieldElements ) > 0 )
		{
			//print_r( $fieldElements);
			$p = new ExpressionParser( '', $ftype, $fieldElements );
			
			if (!$p->Parse($expr))
			{
				$e = $p->errorstr;
				$error .= $LANG_SETTINGS['errors']['header'].': <b>&lt;'.$ftitle.'&gt;</b>. '.$parser_errors[$e].'<br>';
			}
		} // end if
	} // while

	return $error;
} // end verifyFieldValues


function castSearchValuesToFormat($dbn, &$parsedValues)
{
	$logicals = $GLOBALS['form_logical_operation_replacement'];
	$logicalsEngNames = array_flip( $GLOBALS['form_logical_operation_replacement'] );
	$logicalsNames = array_keys( $logicals );
	$logicalsEngNamesOnly = array_keys( $logicalsEngNames );

	$PTC = $GLOBALS['params_table_content'];
	$currPTC = $PTC[$dbn];	

	$pv = $parsedValues;
	
	$specialWords = array('(', ')', '<', '>', '=');
	$opers = array('<', '>', '=');
	while( list( $fname, $fieldElements ) = each( $pv ) )	
	{
		$ftype = $currPTC[$fname][0];
		//$ftype=1;

		$i = 0;
		// Замена1. Заменяем все укр, рус, анг логические операторы на AND, OR, NOT
		while( $i < count( $fieldElements ) )
		{
			$word = $fieldElements[$i];
			
			if ( in_array( $word, $logicalsNames ) )
				$fieldElements[$i] = $logicals[$word];

			$i++;
		} // while			

		
		// ===========================================================================================
		// ===========================================================================================
		// ===========================================================================================

		$i = 0;
		// Замена2. Заменяем "пустоту" между операндами на AND (напр: ФТ ОТ; ФЫВ (ДЫВД); ФТ НЕ ОТ; ( GH ) ( SD );)
		while( $i < count( $fieldElements ) )
		{
			$word = $fieldElements[$i];
			
			$nextWord = ( ( $i + 1 ) < count( $fieldElements ) ) ? $fieldElements[$i+1] : '';
			$prevWord = ( ( $i - 1 ) >= 0 ) ? $fieldElements[$i-1] : '';
			

			if( ( in_array($word, $opers) && !empty($prevWord) && !in_array($prevWord, $logicalsEngNamesOnly) && $prevWord != '(' && !in_array($prevWord, $opers)) ||
					( $word == 'NOT' && !empty($prevWord) && !in_array($prevWord, $logicalsEngNamesOnly) && $prevWord != '(' ) ||
					( $word == '(' && $prevWord == ')' ) || 
					( $word == '(' && !empty($prevWord) && !in_array($prevWord, $logicalsEngNamesOnly) && !in_array($prevWord, $specialWords) ) ||
					( !in_array($word, $specialWords) && !in_array($word, $logicalsEngNamesOnly) && !empty($prevWord) && !in_array($prevWord, $logicalsEngNamesOnly) && !in_array($prevWord, $specialWords) ) ||
					( !in_array($word, $specialWords) && !in_array($word, $logicalsEngNamesOnly) && $prevWord == ')' )
 				)
			{
				//print('---'.$word.'<br>');
				$a = array_splice($fieldElements, $i);

				array_push( $fieldElements, 'AND' );
				$fieldElements = array_merge($fieldElements, $a);
				
				$i++;
			}

			$i++;
		} // while			
		

		// ===========================================================================================
		// ===========================================================================================
		// ===========================================================================================

		//(01.01.2001 01.01.2001) не >01.01.2001
		$i = 0;
		// Замена3. Для полей целого типа и даты перед операндом (если нужно) ставим равно
		while( $i < count( $fieldElements ) )
		{
			$word = $fieldElements[$i];

			$nextWord = ( ( $i + 1 ) < count( $fieldElements ) ) ? $fieldElements[$i+1] : '';
			$prevWord = ( ( $i - 1 ) >= 0 ) ? $fieldElements[$i-1] : '';
			
			if ( ( $ftype == 1 || $ftype == 3) && !in_array($word, $specialWords) && !in_array($word, $logicalsEngNamesOnly) &&
				!in_array($prevWord, $opers)
				)
			{
				$a = array_splice($fieldElements, $i);

				array_push( $fieldElements, '=' );
				$fieldElements = array_merge($fieldElements, $a);
				
				$i++;
			}
			
			$i++;
		} // while			
		
		$parsedValues[$fname] = $fieldElements;

	} // end while
	
} // end castSearchValuesToFromat


function castSearchValuesToSqlFormat($dbn, &$parsedValues, $isDict)
{
	$logicals = $GLOBALS['form_logical_operation_replacement'];
	$logicalsEngNamesOnly = array_values( $logicals );

	$PTC = $GLOBALS['params_table_content'];
	$currPTC = $PTC[$dbn];	

	$pv = $parsedValues;
	
	$specialWords = array('(', ')', '<', '>', '=', 'like');
	$opers = array('<', '>', '=');
	while( list( $fname, $fieldElements ) = each( $pv ) )	
	{
		$ftype = $currPTC[$fname][0];
		$fsqltable = 't_'.$fname;
		$fsqlfield = $currPTC[$fname][2];
		$sqlalias = strtolower($fsqltable.'.'.$fsqlfield);
		$isOneToMany = $currPTC[$fname][6]; // признак поля, которое дял одной заявки может содержать несколько значений (мпк, заявитель, изобретатель...)
		
		// для словарика
		// =============
		if ( $isDict == true )
		{
			$type_mapping = array(
				1 => 'valueInt',
				2 => 'valueStr',
				3 => 'valueDate'
			);
			
			$sqlalias = strtolower('d.'.$type_mapping[$ftype]);
			$isOneToMany = 0;
		}
		// =============

		$i = 0;
		// Замена1. Для даты заменяем дату на convert()
		// 			Для строкового типа апостроф заменяем двумя апострофами, знак "?" - на "_"

		while( $i < count( $fieldElements ) )
		{
			$word = $fieldElements[$i];

			$nextWord = ( ( $i + 1 ) < count( $fieldElements ) ) ? $fieldElements[$i+1] : '';
			$prevWord = ( ( $i - 1 ) >= 0 ) ? $fieldElements[$i-1] : '';

			if ( $ftype === 1 ) // целый тип
			{
				
			} // ftype=1
			elseif ( $ftype === 2 ) // строковый тип
			{
				$isOneWordQuoted = false;
				
				if ( !in_array($word, $logicalsEngNamesOnly) && !in_array($word, $specialWords) )
				{

					$word = str_replace("[", "[[]", $word); // open

					if ( $word[0] == '"' && $word[strlen($word)-1] == '"' )
					{
						$word = substr($word, 1, strlen($word)-2);
						
						$word = str_replace("\\'", "'", $word);
						$word = str_replace("'", "''", $word);
						$word = str_replace("\\\"", "\"", $word);

						if (count(explode(' ', ltrim(rtrim($word)))) === 1)
						{
							$isOneWordQuoted = true;
							
							$word = ltrim(rtrim($word));

							$fieldElements[$i] = '\'% '.$word.'\'';
								
							$a = array_splice($fieldElements, $i);
							
							if ( !in_array($fieldElements[$i-1], $logicalsEngNamesOnly) && $i > 0)
							{
								array_push($fieldElements, 'OR');
								$i++;
							}
								
							array_push($fieldElements, 'like' );
							array_push($fieldElements, '\''.$word.' %\'');
		
							array_push($fieldElements, 'OR');
							array_push($fieldElements, 'like');
							array_push($fieldElements, '\''.$word.'\'');

							array_push($fieldElements, 'OR');
							array_push($fieldElements, 'like');
							array_push($fieldElements, '\'% '.$word.' %\'');
		
							array_push($fieldElements, 'OR');
							array_push($fieldElements, 'like');
		
							$fieldElements = array_merge($fieldElements, $a);
		
							$i = $i + 10;
						}
						else
						{
							if (count(explode(' ', ltrim(rtrim($word)))) == 2 && $fname == 'MPK' )
							{
								$p = explode(' ', ltrim(rtrim($word)));
								
								$part1 = $p[0];
								$part2 = ltrim($p[1]);
								$l1 = substr($part2, 0, strpos($part2, '/'));
								$l2 = substr($part2, strpos($part2, '/'));
								
								// довводим по стандарту ст.8 до 4 символов
								$l1 = str_pad($l1, 4, " ", STR_PAD_LEFT); 
								$word = $part1.$l1.$l2;
							}


							$word = '\'%'.$word.'%\'';
							
							//print($word);
							
							//exit;
						} // end else
							
					} // if "..."
					else
					{
						$fieldsNotLeftStar = array('NC', 'NPRIOR', 'PCTN', 'NCERT', 'PARISN', 'NREG', 'DPUBLN', 'NBUL');
						
						$word = str_replace("\\'", "'", $word);
						$word = str_replace("'", "''", $word);
						$word = str_replace("\\\"", "\"", $word);
						$word = str_replace("?", "_", $word);
					
						if ( $word[0] == '*' )
							$word[0] = '%';
						else
						{
							if ( !in_array($fname, $fieldsNotLeftStar) )
								$word = '%'.$word;
						}
							
						if ( $word[strlen($word)-1] == '*' )
							$word[strlen($word)-1] = '%';
						elseif ( $isOneToMany || $word[strlen($word)-1] != '*' )
							$word = $word.'%';

						$word = '\''.$word.'\'';

						//print($word);


					} // not "..."


					if ( !$isOneWordQuoted )
					{
						$fieldElements[$i] = $word;
							
						$a = array_splice($fieldElements, $i);
						array_push( $fieldElements, 'like' );
						$fieldElements = array_merge($fieldElements, $a);
	
						$i++;
					}

				}
				
			} // ftype=2
			elseif ( $ftype === 3 ) // дата
			{
				if ( !in_array($word, $logicalsEngNamesOnly) && !in_array($word, $specialWords) )
				{
					$word = 'convert(datetime,\''.$word.'\',104)';
					$fieldElements[$i] = $word;
				}

			} // ftype=3

			$i++;
		} // while			


		
		// ===========================================================================================
		// ===========================================================================================
		// ===========================================================================================

		$i = 0;
		
		// Замена2. Вставляем имена переменных (алиастаблицы<.>имяпеременной)
		while( $i < count( $fieldElements ) )
		{
			$word = $fieldElements[$i];

			//print('---'.$word.'<br>');
			
			$nextWord = ( ( $i + 1 ) < count( $fieldElements ) ) ? $fieldElements[$i+1] : '';
			$prevWord = ( ( $i - 1 ) >= 0 ) ? $fieldElements[$i-1] : '';

			if ( $ftype === 2 ) // строковый тип
			{
				if ( $word == 'like' )
				{
					$a = array_splice($fieldElements, $i);
	
					array_push( $fieldElements, $sqlalias );
					$fieldElements = array_merge($fieldElements, $a);
					$i++;

				}
			} // ftype=2
			elseif ( $ftype === 3 || $ftype === 1 ) // дата, целое число
			{
				if ( $word == '>' || $word == '<' || ( $word == '=' && !in_array($prevWord, $opers) ) )
				{
					$a = array_splice($fieldElements, $i);
	
					array_push( $fieldElements, $sqlalias );
					$fieldElements = array_merge($fieldElements, $a);
					$i++;
				}
			} // ftype=3

			$i++;
		} // while			


		// ===========================================================================================
		// ===========================================================================================
		// ===========================================================================================
				
		$i = 0;
		$newFieldElements = array();
		$accWord = '';

		// Замена3. Объединяем алиасы таблиц со значениемяи для поиска
		while( $i < count( $fieldElements ) )
		{
			$word = $fieldElements[$i];
			
			if ( ($word == '(' || $word == ')' || in_array($word, $logicalsEngNamesOnly)) && $isOneToMany)
			{
				if ( !empty( $accWord ) )
					array_push( $newFieldElements, $accWord );
				
				array_push( $newFieldElements, $word );
					
				$accWord = '';
			}
			else
				$accWord .= ' '.$word;

			$i++;
		} // while
		
		
		if ( !empty( $accWord ) )
			array_push( $newFieldElements, $accWord );


		$parsedValues[$fname] = $newFieldElements;

	} // end while
	if ((count ($parsedValues[DAUSSR]) > 0) && ((count ($parsedValues[TUSSR]) == 0) && (count ($parsedValues[TUSSR]) == 0)))
		$parsedValues[DAUSSR][0] = '('.$parsedValues[DAUSSR][0].') and t_DAUSSR.i_200n <> \'*\'';

	// Точный поиск по номеру свидетельства на знак для товаров и услуг
	if (isset($parsedValues['NCERT']) and isset($parsedValues['NCERT'][0])) {
        $parsedValues['NCERT'][0] = str_replace('like', '=', $parsedValues['NCERT'][0]);
        $parsedValues['NCERT'][0] = str_replace('%', '', $parsedValues['NCERT'][0]);
    }
	
} // end castSearchValuesToSqlFormat



function buildGetIdsQuery($dbn, $parsedValues, $lastSearchQuery, $addDbName)
{
	// подключение таблицы описания полей всех баз данных (тип данных, имя таблицы, имя поля, заголовок поля)
	$PTC = $GLOBALS['params_table_content'];

	// подключение таблицы описания полей конкретной базы данных
	$currPTC = $PTC[$dbn];	
	
	// подключение таблицы описания специальных запросов для всех баз данных
	$special_queries_all = $GLOBALS['special_queries'];
	
	// подключение таблицы описания специальных запросов для опеределенной базы данных
	$special_queries = $special_queries_all[$dbn];
	
	// имя полей, для которых есть специальные запросы
	$special_queries_fields = array_keys($special_queries);
	
	// подключение таблицы названий ключевых полей баз данных (например idclaim, idmain)
	$search_idfield_names = $GLOBALS['search_idfield_names'];
	$idFieldName = $search_idfield_names[$dbn];
	
	// получаем набор логических операторов: AND, OR, NOT 
	$logicals = $GLOBALS['form_logical_operation_replacement'];
	$logicalsEngNamesOnly = array_values( $logicals );



	$query = '';
	$countFields = 0;

	while( list( $fname, $fieldElements ) = each( $parsedValues ) )	
	{
		if ( count( $fieldElements ) > 0 ) // если поле с запросом не пустое
		{
			$realTableName = $currPTC[$fname][1];
			$isOneToMany = $currPTC[$fname][6]; 		// признак поля, которое дял одной заявки может содержать несколько значений (мпк, заявитель, изобретатель...)
			$specQuery = $special_queries[$fname]; 		// если у поля есть спецзапрос, он окажется в $specQuery
			$fsqlTableAlias = 't_'.$fname;
//			$fsqlTableAlias = ( empty($realTableName) ) ? 't_'.$fname : $realTableName;
			
			$fsqlField = $fname;
			$sqlAlias = $fsqlTableAlias.'.'.$fsqlField;

			$countFields++; // кол-во не пустых полей поиска
			
			$queryOneToManyField = '';
			
			// если такое поле как мпк, заявитель, изобретатель, ..., строим обратную польскую форму
			// а за тем по ней строим специальный запрос
			
		
			if ( $isOneToMany )
			{
				
				$poliz = new poliz();
				$polizForm = $poliz->getPoliz($fieldElements);
				
				//print_r($polizForm);
				
				//exit;
				
				//print('---------------------------------------------------------<br>');				
				
				// пробегаем по выражениям в польской форме и строим на их основе запросы
				for($i = 0; $i < count( $polizForm ); $i++)
				{
					if ( !in_array($polizForm[$i], $logicalsEngNamesOnly) )
					{
						if ( !empty( $specQuery ) ) // если у поля есть спецзапрос
						$polizQuery = str_replace("###WHEREEXPR###", '('.$polizForm[$i].')', $specQuery);
						else
						$polizQuery = 'select distinct '.$fsqlTableAlias.'.'.$idFieldName.
									  ' from '.$realTableName.' '.$fsqlTableAlias.
								   	  ' ###JOINQUERY### '.
									  ' where('.$polizForm[$i].')';

						$polizForm[$i] = $polizQuery;
					}
				} // for list poliz

				//print($fname.'<br>');								
				//print_r($polizForm);
				//print('<br><br>');
				
				$poliz->clear();
				// делаем разбор обратной польской формы
				for($i = 0; $i < count( $polizForm ); $i++)
				{
					$expr = $polizForm[$i];
					
					//print('==dump==<br>');
					//$poliz->dump();
					//print('<br>==dump==<br>');
					
					if ( !in_array($expr, $logicalsEngNamesOnly) )
					{
						$poliz->push($expr);
						//print('----'.$poliz->first().'<br>');
					}

					elseif ( $expr == 'AND' )
					{
						$polizQuery1 = $poliz->pop();
						$polizQuery2 = $poliz->pop();

						//print('----'.$poliz->first().'<br>');
						$polizQuery2 = str_replace("###JOINQUERY###", '', $polizQuery2);						

						//print('----'.$polizQuery1.'<br>');
						//print('----'.$polizQuery2.'<br>');
												
						$polizQuery = str_replace("###JOINQUERY###", 
							' inner join ('.$polizQuery2.') join_'.$fname.' on join_'.$fname.'.'.$idFieldName.'='.$fsqlTableAlias.'.'.$idFieldName.
							' ###JOINQUERY### ',
							$polizQuery1
						);
						
						$poliz->push($polizQuery);
						
					} // AND
 
					elseif ( $expr == 'OR' )
					{
						$polizQuery2 = $poliz->pop();
						$polizQuery1 = $poliz->pop();
						
						$polizQuery1 = str_replace("###JOINQUERY###", '', $polizQuery1);
						$polizQuery2 = str_replace("###JOINQUERY###", '', $polizQuery2);
						
						$polizQuery = 'select distinct '.$fsqlTableAlias.'.'.$idFieldName.
									' from '.$realTableName.' '.$fsqlTableAlias.
									' ###JOINQUERY###'.
									' where ' .$fsqlTableAlias.'.'.$idFieldName.' in ('.$polizQuery1.' union '.$polizQuery2.')';

						$poliz->push($polizQuery);						

					} // OR
					elseif ( $expr == 'NOT' )
					{
						$polizQuery1 = $poliz->pop();
						
						$polizQuery1 = str_replace("###JOINQUERY###", '', $polizQuery1);
						
						$polizQuery = 'select distinct '.$fsqlTableAlias.'.'.$idFieldName.
									' from '.$realTableName.' '.$fsqlTableAlias.
									' ###JOINQUERY###'.
									' where ' .$fsqlTableAlias.'.'.$idFieldName.' not in ('.$polizQuery1.')';

						$poliz->push($polizQuery);						
						
					} // NOT
					
				} // for list poliz

				$polizQuery = $poliz->pop();
				$polizQuery = str_replace("###JOINQUERY###", '', $polizQuery);
				
				$currQuery = 'select distinct '.$fsqlTableAlias.'.'.$idFieldName.
							' from '.$realTableName.' '.$fsqlTableAlias.
							' ###JOINQUERY###'.
							' where ' .$fsqlTableAlias.'.'.$idFieldName.' in ('.$polizQuery.')';


				//print('<br><br>');

				//print('==POLIZQUERY==<br>');
				//echo $polizQuery;
				//print('<br><br>');

				//print('---------------------------------------------------------<br>');								
				
			} // end if isOneToMany
			else
			{
				//print_r($fieldElements);
				//print('<BR><BR>');
				if ( !empty( $specQuery ) ) // если у поля есть спецзапрос
				$currQuery = str_replace("###WHEREEXPR###", '('.$fieldElements[0].')', $specQuery);
				else
				$currQuery = 'select distinct '.$fsqlTableAlias.'.'.$idFieldName.
							' from '.$realTableName.' '.$fsqlTableAlias.
							' ###JOINQUERY###'.
							' where('.$fieldElements[0].')';

			} // end else not isOneToMany
			
			//print('==CURRQUERY==!!!=');			
			//print($currQuery);
			//print('<br><br>');
			//print('==QUERY==!!!=');			
			//print($query);
			//print('<br><br>');

			if ( $countFields === 1 )
			{
				$currQuery = str_replace("###JOINQUERY###", '', $currQuery);
				$query = $currQuery;
			}
			else
			{
				$currQuery = str_replace("###JOINQUERY###", 
					' inner join ('.$query.') join_'.$fname.' on join_'.$fname.'.'.$idFieldName.'='.$fsqlTableAlias.'.'.$idFieldName,
					$currQuery);
				$query = $currQuery;
				
			} // end else if $countFields > 1
					
		} // end if count( $fieldElements ) > 0
		
		
	} // end while
	

	
	//print('<br><br>');
	//print('==RESULTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTQUERY==<br>');
	//echo $query;
	//print('<br><br>');
	//print('---------------------------------------------------------<br>');
	
	// берем из файла ключевой запрос

	if ( !empty( $query ) )
	{
		if ( empty( $addDbName ) )
			$fpath = 'incs/queries/search_'.$dbn.'_ids.txt';
		else
			$fpath = 'incs/queries/search_'.$dbn.'_add_ids.txt';
			
		$handle = fopen($fpath, "r");
		$mainQuery = fread($handle, filesize($fpath));
		fclose($handle);
	
		$mainQuery = str_replace('$$$SUBQUERY$$$', $query, $mainQuery);
		$mainQuery = str_replace('$$$VIEWBULWHERE$$$', '', $mainQuery); // заменяем часть, которая относится к просмотру бюлетеня
		
		
		// строем запрос для поичка в найденном
		if ( !empty( $lastSearchQuery ) )
		{
			$sortOrderTable = $GLOBALS['sortordertable'];
			$sortOrders = $GLOBALS['sortOrderTypes'];
			$currSortOrderTable = $sortOrderTable[$dbn];	
			
			$mainQuery = str_replace('$$$ORDERCLAUSE$$$', '', $mainQuery);
			if ( $dbn == 'wkm' )
				$mainQuery = substr($mainQuery, 0, strpos($mainQuery, 'order by'));

			$lastSearchQuery = substr($lastSearchQuery, 0, strpos($lastSearchQuery, 'order by'));
			
			$mainQuery = 'select infound.'.$idFieldName.
						' from ('.
							$lastSearchQuery.
						' ) as infound '.
						'inner join ('.
							$mainQuery.
						' ) as main on infound.'.$idFieldName.'=main.'.$idFieldName;
			
			if ( $dbn == 'wkm' )
				$mainQuery = str_replace('idClaim', 'idmark', $mainQuery);
				
			//print($mainQuery);
			
			// підключаємо таблиці для сортування
			while(list($sortFName, $sortSet) = each($currSortOrderTable))
				if ( !empty($sortSet['join']) )
					$mainQuery .= ' '.$sortSet['join'];
				
			if ( $dbn == 'wkm' )
				$mainQuery .= ' order by infound.idmark';
			else
				$mainQuery .= ' $$$ORDERCLAUSE$$$';
			
						
		} // end if $lastSearchQuery											
	} // !empty($query)

/*
	print('<br><br>');
	print('========================MAINQUERY====================<br>');
	echo $mainQuery;
	print('<br><br>');
	print('---------------------------------------------------------<br>');
*/
	return $mainQuery;
} // end buildGetIdsQiery

function buildGetShortBiblioQuery($dbn, $ids, $currSecName)
{
	$idsStr = '';
	
	while(list($n, $val) = each($ids))
		$idsStr .= $val.',';
		
	if ( $idsStr[strlen($idsStr)-1] == ',' )
		$idsStr[strlen($idsStr)-1] = '';
		
	$idsStr = trim(ltrim($idsStr));
	
	if ( !in_array($currSecName, array('syst', 'numc', 'nump', 'numpussr', 'numcert')) )
	{
		
		if ( substr($dbn, 0, 3) == 'inv' )
			$dbn = 'invall';
		elseif ( substr($dbn, 0, 2) == 'pp' )
			$dbn = 'pp';
		elseif ( substr($dbn, 0, 2) == 'tm' )
			$dbn = 'tm';
		elseif ( $dbn == 'madrid' || ( substr($dbn, 0, 6) == 'madrid' && $dbn != 'madridall') )
			$dbn = 'madrid';
		
	
		
		$fpath = 'incs/queries/search_'.$dbn.'_short_biblio.txt';
		//print($fpath);
	}
	else
		$fpath = 'incs/queries/view_'.$dbn.'_'.$currSecName.'_biblio.txt';
		
	$handle = fopen($fpath, "r");
	$query = fread($handle, filesize($fpath));
	fclose($handle);
	
	$query = str_replace('$$$IDS$$$', $idsStr, $query);
		
	return $query;

} // end buildGetShortBiblioQuery

function buildGetFullBiblioQuery($dbn, $idClaim)
{
	if ( substr($dbn, 0, 3) == 'inv' )
		$dbn = 'invall';
	elseif ( substr($dbn, 0, 2) == 'pp' )
		$dbn = 'pp';
	elseif ( substr($dbn, 0, 2) == 'tm' )
		$dbn = 'tm';
	elseif ( $dbn == 'madrid' )
		$dbn = 'madrid';
	elseif ( $dbn == 'madridall' )
		$dbn = 'madridall';

	$fpath = 'incs/queries/search_'.$dbn.'_full_biblio.txt';

	$handle = fopen($fpath, "r");
	$query = fread($handle, filesize($fpath));
	fclose($handle);
	
	$query = str_replace(':$$$IDCLAIM$$$', $idClaim, $query);

	return $query;	
} // end buildGetFullBiblioQuery

function executeGetIdsQuery($dbn, $query, $mssql)
{
	$connSettings = $GLOBALS['connection'];
	$currDbConnSettings = $connSettings[$dbn];
	
	$host = $currDbConnSettings['host'];
	$login = $currDbConnSettings['login'];
	$password = $currDbConnSettings['pass'];
	$database = $currDbConnSettings['dbname'];
	
	$mssql->selectDb($database);
	$err = (int)$mssql->executeQuery($query);

	if ( $err != -1 )
	{
		$resIds = array();
	
		while ( $data = $mssql->getRow('num') )
			array_push( $resIds, $data[0] );
	
		return $resIds;		
	}
	else
		; 

	return -1;
} // end executeGetIdsQuery


function executeGetShortBiblioQuery($dbn, $query, $mssql)
{
	$connSettings = $GLOBALS['connection'];
	$currDbConnSettings = $connSettings[$dbn];
	
	$host = $currDbConnSettings['host'];
	$login = $currDbConnSettings['login'];
	$password = $currDbConnSettings['pass'];
	$database = $currDbConnSettings['dbname'];
	
	$mssql->selectDb($database);
	$err = (int)$mssql->executeQuery($query);

	if ( $err != -1 )
	{
		$shortBiblioSet = array();
	
		$i = 0;
		while ( $data = $mssql->getRow('assoc') )
		{
			$shortBiblioSet += array($i => $data);

			$i++;
		}

        // Правильные МПК на дату бюлетеня
        if (in_array($dbn, array('inv', 'invc', 'invd', 'invdu'))) {
            foreach ($shortBiblioSet as &$item) {
                if ($dbn == 'invc') {
                    if ( !empty($item['claimBullDate']) ) {
                        $publication = $item['claimBullDate'];
                    }
                    else {
                        $publication = 0;
                    }
                }
                else {
                    $publication = $item['fi_46'];
                }

                //$item['mpk'] = getIPC($dbn, $mssql, $item['fi_21'], $publication);
            }
        }


	
		return $shortBiblioSet;		
	}
	else
		;

	return -1;
} // end executeGetShortBiblioQuery

function executeGetFullBiblioQuery($dbn, $query, $mssql)
{
	$connSettings = $GLOBALS['connection'];
	$currDbConnSettings = $connSettings[$dbn];
	
	$host = $currDbConnSettings['host'];
	$login = $currDbConnSettings['login'];
	$password = $currDbConnSettings['pass'];
	$database = $currDbConnSettings['dbname'];

	$mssql->selectDb($database);
	$err = (int)$mssql->executeQuery($query);
	
	if ( $err != -1 )
	{
		$fullBiblio = $mssql->getRow('assoc');

        // Правильные МПК на дату бюлетеня
        if (in_array($dbn, array('inv', 'invc', 'invd', 'invdu'))) {
            if ($dbn == 'invc') {
                if (!empty($fullBiblio['claimBullDate'])) {
                    $publication = $fullBiblio['claimBullDate'];
                } else {
                    $publication = $fullBiblio['claimBullDate'];
                }
            } else {
                $publication = $fullBiblio['i_46'];
            }
            //$fullBiblio['i_51'] = getIPC($dbn, $mssql, $fullBiblio['i_21'], $publication);
        }

		return $fullBiblio;		
	}
	else
		; 
	return -1;
} // end executeGetFullBiblioQuery


/**
 * Функция возвращает строку с реальными индексами МПК на дату выхода бюлетеня.
 *
 * @param $dbn
 * @param $mssql
 * @param $i_21
 * @param $claimBullDate
 * @return int|string
 */
function getIPC($dbn, $mssql, $i_21, $claimBullDate)
{
    $connSettings = $GLOBALS['connection'];
    $currDbConnSettings = $connSettings[$dbn];

    $host = $currDbConnSettings['host'];
    $login = $currDbConnSettings['login'];
    $password = $currDbConnSettings['pass'];
    $database = $currDbConnSettings['dbname'];

    // Запрос
    $fpath = 'incs/queries/get_ipc_by_bul_date.txt';
    $handle = fopen($fpath, "r");
    $query = fread($handle, filesize($fpath));
    fclose($handle);
    $query = str_replace('###zayav_num###', $i_21, $query);
    $query = str_replace('###bul_date###', date('Ymd', strtotime($claimBullDate)), $query);

    $mssql->selectDb($database);
    $mssql->executeQuery('SET ANSI_NULLS ON');
    $mssql->executeQuery('SET ANSI_WARNINGS ON');
    $err = (int)$mssql->executeQuery($query);

    if ( $err != -1 )
    {
        $res = '';
        $iscore = 0;
        // Распарсиваем данные и собираем строку для представления
        while ($data = $mssql->getRow('assoc')) {

            //var_dump($query);
            if ($data['level'] == 'C' || $data['gr'] == 0) {
                if ($data['i'] == 'I') {
                    $ipcrow = '<b>' . $data['ipc'] . '</b>';
                } else {
                    $ipcrow = $data['ipc'];
                }
            } else {
                if ($data['i'] == 'I') {
                    $ipcrow = '<i><b>' . $data['ipc'] . '</b></i>';
                } else {
                    $ipcrow = '<i>' . $data['ipc'] . '</i>' ;
                }
            }

            if ($data['level'] == 'A' && $data['gr'] != 0) {
                $ipcrow = $ipcrow . ' (' . $data['y'] . '.' . $data['m'] . ')';
            } else {
                $iscore = 1;
            }

            $res .= '###mpk###'.$ipcrow;
        }

        $pubdate = (int) date('Y', strtotime($claimBullDate));
        if ($pubdate == 2009 || $pubdate == 2010) {
            $pubdate = '2009';
        } elseif ($pubdate < 2009 ) {
            $pubdate = '2006';
        } else {
            $pubdate = $pubdate . '.01';
        }

        if ($iscore) {
            $ipctitle = 'МПК (' . $pubdate . ')';
        } else {
            $ipctitle = 'МПК';
        }

        $res = $ipctitle . $res;

        return $res;
    }
    else
        ;
    return -1;
}

function getPageNumbersStr($action, $dbn, $section, $page_count, $curr_page, $fname)
{
	$LANG_SETTINGS = $GLOBALS['LANG_SETTINGS'];
	
	$href = '';
	if ( !empty($action) )
		$href .= 'action='.$action;

	if ( !empty($dbn) )
		$href .= '&dbname='.$dbn;

	if ( !empty($section) )
		$href .= '&section='.$section;

	if ( !empty($fname) )
		$href .= '&fname='.$fname;
	
	$script = 'search.php';
	if ( $action == 'viewdict' )
		$script = 'dictionary.php';
		
	$s = '';
	$s .= '<font class="viennacat2">[&nbsp;&nbsp;</font>';
	
	if ( $page_count <= 14 )
	{
		for ($i = 1; $i <= $page_count; $i++)
			if ( $i == $curr_page )
				$s .= '<font class="viennacat">'.$i.'</font>&nbsp;&nbsp;';
			else
				$s .= '<a class="pgline" href="'.$script.'?'.$href.'&page='.$i.'">'.$i.'</a>&nbsp;&nbsp;';
	}
	else
	{
		if ( $curr_page < 10 )
		{
			for ($i = 1; $i <= 14; $i++)
				if ( $i == $curr_page )
					$s .= '<font class="viennacat">'.$i.'</font>&nbsp;&nbsp;';
				else
				$s .= '<a class="pgline" href="'.$script.'?'.$href.'&page='.$i.'">'.$i.'</a>&nbsp;&nbsp;';

			$s .= '<font class="viennacat2">...</font>&nbsp;&nbsp;';
			$s .= '<a class="pgline" href="'.$script.'?'.$href.'&page='.$page_count.'">'.$page_count.'</a>&nbsp;&nbsp;';
		}
		else
		if ( $curr_page < ( $page_count - 6 ) )
		{
			$s .= '<a class="pgline" href="'.$script.'?'.$href.'&page=1">1</a>&nbsp;&nbsp;';
			$s .= '<font class="viennacat2">...</font>&nbsp;&nbsp;';
			
			for ($i = $curr_page - 7; $i <= ($curr_page + 5); $i++ )
				if ( $i == $curr_page )
					$s .= '<font class="viennacat">'.$i.'</font>&nbsp;&nbsp;';
				else
					$s .= '<a class="pgline" href="'.$script.'?'.$href.'&page='.$i.'">'.$i.'</a>&nbsp;&nbsp;';

			$s .= '<font class="viennacat2">...</font>&nbsp;&nbsp;';
			$s .= '<a class="pgline" href="'.$script.'?'.$href.'&page='.$page_count.'">'.$page_count.'</a>&nbsp;&nbsp;';
		}
		else
		{
			$s .= '<a class="pgline" href="'.$script.'?'.$href.'&page=1">1</a>&nbsp;&nbsp;';
			$s .= '<font class="viennacat2">...</font>&nbsp;&nbsp;';
			
			for ($i = $page_count - 13; $i <= $page_count; $i++)
				if ( $i == $curr_page )
					$s .= '<font class="viennacat">'.$i.'</font>&nbsp;&nbsp;';
				else
					$s .= '<a class="pgline" href="'.$script.'?'.$href.'&page='.$i.'">'.$i.'</a>&nbsp;&nbsp;';
		}
	}
	
	$s .= '<font class="viennacat2">]&nbsp;</font>';
	
	$s .= ($curr_page < 2 ) ? '<font class="pglinedis">'.$LANG_SETTINGS['res']['back'].'</font>' : '<a class="pgline" href="'.$script.'?'.$href.'&page='.($curr_page-1).'">'.$LANG_SETTINGS['res']['back'].'</a>';
	$s .= ($curr_page >= $page_count ) ? '<font class="viennacat2">&nbsp;|&nbsp;</font><font class="pglinedis">'.$LANG_SETTINGS['res']['forw'].'</font>' : '<font class="viennacat2">&nbsp;|&nbsp;</font><a href="'.$script.'?'.$href.'&page='.($curr_page+1).'" class="pgline">'.$LANG_SETTINGS['res']['forw'].'</a>';
	
	return $s;
} // end getPageNumbersStr


function CopyTmImagesToTemp($ids, $copy_full_image)
{
	$pref = ( !$copy_full_image ) ? 's' : ''; 
	
	for($i = 0; $i < count( $ids ); $i++)
	{
		$source_path = TMImageTemplatePath.'tm_'.$ids[$i].$pref.'.jpg';

		$dest_path = 'tempdocs/'.'tm_'.$ids[$i].$pref.'.jpg';
		
		if ( file_exists( $source_path ) ) 
			copy( $source_path, $dest_path );
	} // end for
} // end CopyTmImagesToTemp

/*
function CopyPpImagesToTemp($variantInfo, $copy_all_images)
{
	while( list($idClaim, $vi) = each($variantInfo) )
	{
		if ( !$copy_all_images )
		{
			$fname = 'pp_'.$vi[0]['idVariant'].'-1.jpg';
			$source_path = PPImageTemplatePath.$fname;

			//print($source_path.'<br>');

			$dest_path = 'tempdocs/'.$fname;

			if ( file_exists( $source_path ) ) 
				copy( $source_path, $dest_path );
		} // end if $copy_all_images
		else
		{
			for($i = 0; $i < count($vi); $i++)
			{
				for($j = 1; $j <= $vi[$i]['countSubImage']; $j++)
				{
					$fname = 'pp_'.$vi[$i]['idVariant'].'-'.$j.'.jpg';
					$source_path = PPImageTemplatePath.$fname;
		
					//print($source_path.'<br>');
		
					$dest_path = 'tempdocs/'.$fname;
		
					if ( file_exists( $source_path ) ) 
						copy( $source_path, $dest_path );
				} // end for $j
			} // end for $i
		} // end else
	} // end while
} // end CopyPpImagesToTemp
*/

function getPpVariantInfo($searchShortBiblioSet)
{
	$fullVariantInfo = array();

	for($i = 0; $i < count( $searchShortBiblioSet ); $i++)
	{
		$row = $searchShortBiblioSet[$i];

		$i_55 = explode('###variants###', $row['fi_55']);		
		$variantInfo = array();
		for($j = 0; $j < count( $i_55 ); $j++)
		{	
			$vi = explode('|', $i_55[$j]);					
			$variantInfo = $variantInfo + array($j => array('idVariant' => $vi[0], 'colors' => $vi[1], 'countSubImage' => $vi[2]) ); 
		} // end for
		
		$fullVariantInfo = $fullVariantInfo + array( $row['idClaim'] => $variantInfo);
	} // end for
	
	//print_r($fullVariantInfo);

	return $fullVariantInfo;
} // end getPpVariantInfo

function saveMadridImagesToTemp($biblio, $act)
{
	//print('working save');
	if ( $act == 'viewdetails' )
	{
		$biblio[0] = $biblio;
	}
	
	for($i = 0; $i < count( $biblio ); $i++)
	{
		$row = $biblio[$i];

		if ( !empty($row['image']) )
		{
			$fh = fopen('tempdocs/madrid_'.$row['idClaim'].'.'.strtolower($row['imageType']), "w+" );
			fwrite($fh, $row['image']);
			fclose($fh);
		}

		if ( $act == 'viewdetails' && !empty($row['xml']) )
		{
			$fh = fopen('tempdocs/xml_'.$row['idClaim'].'.xml', "w+" );
			
			
			$row['xml'] = str_replace('E:\\ROM\\Romarin_base\\', '../../images/madridall/', $row['xml']);
			$row['xml'] = str_replace('D:\\Romarin\\', '../../images/madridall/', $row['xml']);
			
			//$row['xml'] = str_replace('E:\\ROM\\Romarin_base\\', '', $row['xml']);
			
			//$row['xml'] = str_replace('<!DOCTYPE MARKGR SYSTEM "MARKGR.dtd">', '', $row['xml']); 
			
			
			
			$row['xml'] = preg_replace('/NAME=\'([0-9]+)\'/', 'NAME=\'madrid_'.$row['idClaim'].'.'.strtolower($row['imageType']).'\'', $row['xml']);
			
			
			fwrite($fh, $row['xml']);
			fclose($fh);
		}

	} // end for
} // end saveMadridImagesToTemp

function saveWKMImagesToTemp($biblio)
{
	for($i = 0; $i < count( $biblio ); $i++)
	{
		$row = $biblio[$i];
		
		if ( !empty($row['image']) )
		{
			$fh = fopen('tempdocs/wkm_'.$row['idMark'].'.jpg', "w+" );
			fwrite($fh, $row['image']);
			fclose($fh);
		}
	} // end for
} // end saveWKMImagesToTemp

function saveAllNoticeToTemp($mssql)
{
	$connSettings = $GLOBALS['connection'];
	$currDbConnSettings = $connSettings['official'];
	
	$host = $currDbConnSettings['host'];
	$login = $currDbConnSettings['login'];
	$password = $currDbConnSettings['pass'];
	$database = $currDbConnSettings['dbname'];
	
	$fpath = 'incs/queries/view_save_all_notice.txt';
	$handle = fopen($fpath, "r");
	$query = fread($handle, filesize($fpath));
	fclose($handle);
	
	$mssql->selectDb($database);
	$mssql->executeQuery($query);

	$i = 0;
	while ( $data = $mssql->getRow('assoc') )
	{
		if ( !empty($data['file']) )
		{
			$i++;
			$fname = substr($data['filename'], 0, strpos($data['filename'], '.'));
			$fext = substr($data['filename'], strpos($data['filename'], '.')+1, strlen($data['filename']));
			
			//$fpath = 'tempdocs/notice/'.$fname.'_'.$data['idBul'].'_'.$i.'.'.$fext;
			$fpath = 'tempdocs/'.$data['filename'];

			$fh = fopen( $fpath, "w+" );
			fwrite($fh, $data['file']);
			fclose($fh);
			
			$filedata = file($fpath);
		}
	}
} // saveAllNoticeToTemp

function getBulNumberList($dbn, $mssql, $addDbName)
{
	$LANG_SETTINGS = $GLOBALS['LANG_SETTINGS'];
	$connSettings = $GLOBALS['connection'];
	$currDbConnSettings = $connSettings[$dbn];
	$database = $currDbConnSettings['dbname'];

	$fpath = 'incs/queries/view_bul_numbers_'.$dbn.'.txt';
	$handle = fopen($fpath, "r");
	$query = fread($handle, filesize($fpath));
	fclose($handle);
	
	if ( !empty($addDbName) ) 	
		$query = str_replace('01.04.2006', '01.01.1900', $query);
	
	$mssql->selectDb($database);
	$mssql->executeQuery($query);
	
	$bulNumbers = array();

	$i = 0;
	if ( $dbn == 'wkm' )
	{
		$bulNumbers += array($i => '* ['.$LANG_SETTINGS['interface']['CBALLBULL'].']');
		$i++;
	}
		
	while ( $data = $mssql->getRow('assoc') )
	{
		$bulNumbers += array($i => $data['bullNumb'].' '.$data['bullDate']);
		$i++;
	}
	
	return $bulNumbers;
} // getBulNumberList

function cmp($a, $b)
{
	$a_date = explode(' ', $a);
	$b_date = explode(' ', $b);
	$a_date_str = $a_date[1];
	$b_date_str = $b_date[1];
	
	$a_date = strtotime($a_date_str);
	$b_date = strtotime($b_date_str);
	
	//print("$a_date_str: $a_date, $b_date_str: $b_date<br>");
	//print("$a, $b <br>");
	
    if ($a == $b) {
        return 0;
    }
    return ($a_date > $b_date) ? -1 : 1;
}

function getNoticeBulNumberList($dbn, $mssql)
{
	$currDbName = $dbn;
	$bulNumbers = array();
	
	if ( $dbn == 'tm' || $dbn == 'pp' || $dbn == 'madrid' )
	{
		$dir = 'notices/'.$dbn;

		$i = 0;
		foreach(glob($dir.'/*') as $sf) {	
			//print($sf.'<BR>');
			$t = explode('_', $sf);
			//print_r($t);
			$numbb = str_replace('-', '/', ($t[2]));
			$dateb = substr($t[3], 0, 2).'.'.substr($t[3], 2, 2).'.'.substr($t[3], 4, 4);
			
			$now = getdate();
			$now_stamp = $now[0];
			$dateb_stamp = strtotime($dateb);

			if ($now_stamp > $dateb_stamp)			
			{
				$bulNumbers += array($i => $numbb.' '.$dateb);
				$i++;
			}
		} // end foreach
		
		usort($bulNumbers, 'cmp');
		
		return $bulNumbers;
	}
	
	

	$connSettings = $GLOBALS['connection'];
	$currDbConnSettings = $connSettings[$dbn];
	$database = $currDbConnSettings['dbname'];

	$fpath = 'incs/queries/view_bul_notice_numbers_'.$currDbName.'.txt';
	$handle = fopen($fpath, "r");
	$query = fread($handle, filesize($fpath));
	fclose($handle);
//print_r($currDbConnSettings); print('<br>');
//print('$database='.$database.'<br>');
//print('$query='.$query.'<br>');
	$mssql->selectDb($database);

	$mssql->executeQuery($query);
//print_r($mssql); print('<br>');	
	$i = 0;
   if (($dbn == 'tm2')||($dbn == 'pp2'))
      {  $bulNumbers += array($i => '-- --');
        $i++;
      }
	while ( $data = $mssql->getRow('assoc') )
	{
		$bulNumbers += array($i => $data['bullNumb'].' '.$data['bullDate']);
		$i++;
	}
	
	return $bulNumbers;
} // getNoticeBulNumberList

function buildGetIdsBulViewQuery($dbn, $currSecName, $bulId, $bulStr, $isIndexSec, $addDbName, $currBulDate)
{
	// bulNumber - строка вида 12/2006 (неоходим для изобретений, знаков и промзразков)
	// bulId - идентификатор бюллетня в AccBul_New для wellknowmarks и madrida

	//print('*******'.$bulStr.'*********');
	$year = (int)substr($bulStr, strpos($bulStr, '/')+1, 1000);
	$dateBegin = '01.01.'.$year;
	$dateEnd = '31.12.'.$year;

	$bulNumbStart = (int)substr($bulStr, 0, strpos($bulStr, '/'));
	$bulNumbEnd = $bulNumbStart;

	if ( $bulStr == '*' )
	{
		$dateBegin = '01.01.1900';
		$dateEnd = '31.12.2100';
		$bulNumbStart = 0;
		$bulNumbEnd = 100;
	}

	if ( !$isIndexSec )
	{
		$fpath = 'incs/queries/view_'.$dbn.'_ids.txt';
		$handle = fopen($fpath, "r");
		$query = fread($handle, filesize($fpath));
		fclose($handle);
	}
	else
	{
		$fpath = 'incs/queries/view_'.$dbn.'_'.$currSecName.'_biblio.txt';
		$handle = fopen($fpath, "r");
		$query = fread($handle, filesize($fpath));
		fclose($handle);
	}
	
	//print($query.'<BR><BR>');
	
	if ( !empty($addDbName) )
	{
		$query = str_replace('01.04.2006', '01.01.1900', $query);		
		$query = str_replace('c450.bulletinNumber>=$$$BULNUMBSTART$$$ and c450.bulletinNumber<=$$$BULNUMBEND$$$', 'c450.bullStr=\''.$bulStr.'\'', $query); 
	}

	
	if ( substr( $dbn, 0, 3 ) == 'inv' )
	{
		$letter = substr( $currSecName, 3, 1 );
		
		$query = str_replace('$$$LETTER$$$', $letter, $query);
	} 
	
	
	if ( ( substr( $dbn, 0, 3 ) == 'inv' || $dbn == 'pp' || $dbn == 'madrid' )  && ( $currSecName != 'notice' ) ) 
	{
		$query = str_replace('$$$PUBDATE$$$', $currBulDate, $query);
	}
	
	
	/*
	if ( ( $dbn == 'pp' ) && ( $currSecName != 'notice' ) ) 
	{
		$query = str_replace('$$$DATEBEGIN$$$', $dateBegin, $query);
		$query = str_replace('$$$DATEEND$$$', $dateEnd, $query);
		
		$query = str_replace('$$$BULNUMBSTART$$$', $bulNumbStart, $query);
		$query = str_replace('$$$BULNUMBEND$$$', $bulNumbEnd, $query);
	}
	*/
	

	if ( substr($dbn, 0, 2) == 'tm' ||  $currSecName == 'notice' ) 
		$query = str_replace('$$$BULNUMB$$$', $bulStr, $query);
	elseif ( $dbn == 'wkm' )
	{
		if ( $bulStr == '*')
			$bulStr = '%';
			
		$query = str_replace('=\'$$$BULNUMB$$$\'', ' like \''.$bulStr.'\'', $query);
	} 
	
	return $query;
	
} // end buildGetIdsBulViewQuery




function buildGetIdsKindViewQuery($dbn, $currSecName, $Kind, $isIndexSec, $StrKind)
{
	// PROP - строка - номер свидоцтва
	

	if ( !$isIndexSec )
	{
		$fpath = 'incs/queries/view_'.$dbn.'_'.$StrKind.'_ids.txt';
		$handle = fopen($fpath, "r");
		$query = fread($handle, filesize($fpath));
		fclose($handle);
	}
	else
	{
		$fpath = 'incs/queries/view_'.$dbn.'_'.$currSecName.'_'.$StrKind.'_biblio.txt';
		$handle = fopen($fpath, "r");
		$query = fread($handle, filesize($fpath));
		fclose($handle);
	}
	
	//print($query.'<BR><BR>');
	$query = str_replace('$$$'.$StrKind.'$$$', $Kind, $query);
	
	 
	
	return $query;
	
} // end buildGetIdsKindViewQuery


function executeGetIdsBulViewQuery($dbn, $query, $isIndexSec, $currSecName, $mssql)
{
	if ( $dbn!='tm2' && $dbn!='pp2' && $currSecName == 'notice' && substr($dbn, 0, 3) != 'inv' )
		$dbn = 'official';
		
	$connSettings = $GLOBALS['connection'];
	$currDbConnSettings = $connSettings[$dbn];
	$database = $currDbConnSettings['dbname'];
	
	//print($query.'<BR>');
//print($dbn.'<BR>');
//print($database.'<BR>');
//print($isIndexSec.'<BR>');
//print($currSecName.'<BR>');

	$mssql->selectDb($database);
	$err = (int)$mssql->executeQuery($query);
	
	if ( $err != -1 )
	{
		$resIds = array();
	
		$i = 0;
$type='num';
if (($dbn=='tm2')||($dbn=='pp2')) $type='assoc';

		while ( $data = $mssql->getRow($type) )
		{	
			if ( !$isIndexSec && $dbn != 'official' )
				array_push( $resIds, $data[0] );
			else
				array_push( $resIds, $data );

			$i++;
		}
	
		return $resIds;		
	}
	else
		;

	return -1;
	
} // end executeGetIdsBulViewQuery


function getActualizationDates()
{ 
	$db_names = array_keys($GLOBALS['db_names']);
	$connection = $GLOBALS['actualization_connection'];

	$mssql = new mssql();
	$mssql->connection($connection['host'], $connection['login'], $connection['pass'], $connection['dbname'], '');
	
	$actualDates = array();
	for($i = 0; $i < count($db_names); $i++)
	{
		$dbn = $db_names[$i];
		
		if (substr($db_names[$i], 0, 3) == 'inv') 
			$dbn = 'inv';
		if (substr($db_names[$i], 0, 3) == 'tmc') 
			$dbn = 'tmc';
		elseif (substr($db_names[$i], 0, 2) == 'tm') 
			$dbn = 'tm';	
		if (substr($db_names[$i], 0, 2) == 'pp') 
			$dbn = 'pp';
			
		$q = "select top 1 convert(varchar(20), e.enddate, 121) [date] from dbo.actualstat e inner join dbo.dbnames dn on e.iddb = dn.iddb where dn.code = '$dbn' order by enddate desc";
	    //print($db_names[$i].'<br>');
		//print($q.'<br>');
		
		$mssql->executeQuery($q);
		$data = $mssql->getRow('num');
		
		$actualDates = $actualDates + array($db_names[$i] => substr($data[0], 0, 19));
	} // end for

	$mssql->disconnection();
	return $actualDates;
	
} // end getActualizationDates

function extractIdClaimFromIndexData($currSearchIds)
{
	$newCurrSearchIds = array();
	
	for ($i = 0; $i < count($currSearchIds); $i++)
	{
		$id = $currSearchIds[$i][0];
		
		if ( !in_array($id, $newCurrSearchIds) )
			array_push($newCurrSearchIds, $id);
	} // end for
	
	return $newCurrSearchIds;
} // end extractIdClaimFromIndexData

function getInvMPKItemCount($dbn, $currSecName, $currBulId, $currBulStr, $isIndexSec, $mssql, $currBulDate)
{
	$connSettings = $GLOBALS['connection'];
	$currDbConnSettings = $connSettings[$dbn];
	
	$host = $currDbConnSettings['host'];
	$login = $currDbConnSettings['login'];
	$password = $currDbConnSettings['pass'];
	$database = $currDbConnSettings['dbname'];
	$view_sections_list = $GLOBALS['view_sections_list'];

	$mssql->selectDb($database);

	$invMPKItemCount = array();
	
	for($i = 0; $i < count($view_sections_list); $i++)
		if ( strlen($view_sections_list[$i]) === 1 )
		{
			$query = buildGetIdsBulViewQuery($dbn, 'ipc'.$view_sections_list[$i], $currBulId, $currBulStr, 0, null, $currBulDate);
			$query = str_replace('select mi.idClaim', 'select count(mi.idClaim)' , $query);
			$query = str_replace('order by mi.idClaim', '' , $query);

			$query = str_replace('$$$ORDERCLAUSE$$$', '', $query);
			
			//print($query);
			
			$mssql->executeQuery($query);
			$data = $mssql->getRow('num');
			
			$invMPKItemCount += array('ipc'.$view_sections_list[$i] => $data[0] );
		}
	

	return $invMPKItemCount;

} // end getInvMPKItemCount


function getNoticeItemCountInv($dbn, $currSecName, $currBulId, $currBulStr, $isIndexSec, $mssql, $currBulDate)
{
	$connSettings = $GLOBALS['connection'];
	$currDbConnSettings = $connSettings[$dbn];
	
	$host = $currDbConnSettings['host'];
	$login = $currDbConnSettings['login'];
	$password = $currDbConnSettings['pass'];
	$database = $currDbConnSettings['dbname'];
	
	$noticeCount = array();
	$query = buildGetIdsBulViewQuery($dbn, 'notice', $currBulId, $currBulStr, 1, null, $currBulDate);
	
	$p = strpos($query, 'from');
	$s = substr($query, $p);
	$query = 'select count(distinct n.typePub) '.$s;
	$p = strpos($query, 'order');
	$query = substr($query, 0, $p);
	
	$mssql->selectDb($database);
	$mssql->executeQuery($query);
	$data = $mssql->getRow('num');
			
	$noticeCount += array('notice' => $data[0] );
	
	return $noticeCount;
	
} // end getNoticeItemCount


function getNoticeItemCount($dbn, $currSecName, $currBulId, $currBulStr, $isIndexSec, $mssql, $currBulDate)
{
	$connSettings = $GLOBALS['connection'];
	$currDbConnSettings = $connSettings['official'];
	
	$host = $currDbConnSettings['host'];
	$login = $currDbConnSettings['login'];
	$password = $currDbConnSettings['pass'];
	$database = $currDbConnSettings['dbname'];
	
	$noticeCount = array();
	$query = buildGetIdsBulViewQuery($dbn, 'notice', $currBulId, $currBulStr, 1, null, $currBulDate);
	$query = str_replace('n.notifnum [code],', '', $query);	
	$query = str_replace('n.filename [fname],', '', $query);	
	$query = str_replace('n.val [file]', 'count(n.notifnum)', $query);			
	 	

	$mssql->selectDb($database);
	$mssql->executeQuery($query);
	$data = $mssql->getRow('num');
			
	$noticeCount += array('notice' => $data[0] );

	return $noticeCount;
	
} // end getNoticeItemCount



function getIndexItemCount($dbn, $currSecName, $currBulId, $currBulStr, $isIndexSec, $mssql, $currBulDate)
{
	$connSettings = $GLOBALS['connection'];
	$currDbConnSettings = $connSettings[$dbn];
	
	$host = $currDbConnSettings['host'];
	$login = $currDbConnSettings['login'];
	$password = $currDbConnSettings['pass'];
	$database = $currDbConnSettings['dbname'];
	
	$index_sections = $GLOBALS['index_sections'];
	$viewDbSections = $GLOBALS['view_db_sections'];

	$currViewDbSections = array_keys($viewDbSections[$dbn]);
	
	$mssql->selectDb($database);
	
	$indexCount = array();
	for($i = 0; $i < count($index_sections); $i++)
		if ( in_array( $index_sections[$i], $currViewDbSections ) && $index_sections[$i] != 'notice' )
		{
			$query = buildGetIdsBulViewQuery($dbn, $index_sections[$i], $currBulId, $currBulStr, 1, null, $currBulDate);
			
			$q1 = substr($query, strpos($query, 'from'), strlen($query));
			$q2 = substr($q1, 0, strpos($q1, 'order by'));
			
			$n = 'mi';
			if ( $dbn == 'tm' || $dbn == 'pp' )
				$n = 'rc';
			$query = 'select count('.$n.'.idclaim) '.$q2;
			
			//print($query.'<BR><BR>');
			$mssql->executeQuery($query);
			$data = $mssql->getRow('num');
			
			$indexCount += array($index_sections[$i] => $data[0] );

			//print($query.'<br><br><br>');
		}

	return $indexCount;
} // end getIndexItemCount

function copyInvMaterialFilesToTemp($claim_number)
{
	$claim_number = substr($claim_number.'/', 0, strpos($claim_number.'/', '/'));

	$part1 = substr( $claim_number, 0, 6 );
		
	$src_folder = INVDocsTemplatePath.$part1.'/';
	$dest_folder = 'tempdocs/'.$part1.'/';
	
	$t = array('fu', 'pu', 'ru', 'rr', 're', 'ou');
	for($i = 0; $i < count( $t ); $i++)
	{
		$type = $t[$i];
		
		if ( !is_dir( $dest_folder ) )
			@mkdir( $dest_folder );
			
		$src_file_mat = $src_folder.$claim_number.$type.'.htm';
	
		if ( ( $type == 'fu' ) && !file_exists( $src_file_mat ) ) 
		{
			 $type = 'pu';
		 	 $src_file_mat = $src_folder.$claim_number.$type.'.htm';
		}
	
		$dest_file_mat = $dest_folder.$claim_number.$type.'.htm';
	
		$src_folder_mat = $src_folder.$claim_number.$type.'.files/';
		$dest_folder_mat = $dest_folder.$claim_number.$type.'.files/';
				
		if ( is_dir( $dest_folder_mat ) )
			@rmdir( $dest_folder_mat );
			
		if ( file_exists( $src_file_mat ) )
			copy( $src_file_mat, $dest_file_mat );
		
		if ( is_dir( $src_folder_mat ) )
			dircopy($src_folder_mat, $dest_folder_mat, false);
		
	} // end for
} // end copyInvMaterialFilesToTemp


function getViewMaterialQuery($claimNumber)
{
	if ( empty( $_SESSION['reestrDbName'] ) )
		$fpath = 'incs/queries/search_inv_full_biblio_materials.txt';
	else
		$fpath = 'incs/queries/search_reestr_full_biblio_materials.txt';
		
	$handle = fopen($fpath, "r");
	$query = fread($handle, filesize($fpath));
	fclose($handle);
	
	$query = str_replace(':CLAIMNUMBER', $claimNumber, $query);
	
	return $query;
} // end getViewMaterialQuery

function getMaterialFiles($query, $mssql)
{
	$connSettings = $GLOBALS['connection'];
	$currDbConnSettings = $connSettings['materials'];
	$database = $currDbConnSettings['dbname'];
	
	$mssql->selectDb($database);
	$mssql->executeQuery($query);

	$matFiles = array();

	$i = 0;
	while ( $data = $mssql->getRow('assoc') )
	{
		$matFiles = $matFiles + array($i => $data);
		$i++;
	}

	@mssql_close( $db );
	
	return $matFiles;
	
} // end getMaterialFiles

function saveMaterialFileToDisc($materialFiles, $claimNumber)
{
	//unrar x -o+ -inul d:\!!!\test10*.rar d:\!!!\test

	$claimNumber = substr($claimNumber.'/', 0, strpos($claimNumber.'/', '/'));
	
	$part = substr( $claimNumber, 0, 6 );
	$folder = 'tempdocs/'.$part.'/';
	$folder2 = $folder.$claimNumber.'/';

	if ( !is_dir( $folder ) )
		@mkdir( $folder );
	
	if ( !is_dir( $folder2 ) )
		@mkdir( $folder2 );
	
	// сохраняет все файлы (*.rar, *.pdf) на диск
	for($i = 0; $i < count($materialFiles); $i++)
	{
		$idDoc = $materialFiles[$i]['iddoc'];
		$i_21 = $materialFiles[$i]['i_21'];
		$code = $materialFiles[$i]['matCode'];
		$rar = $materialFiles[$i]['rar'];
		$pdf = $materialFiles[$i]['pdf'];
		$path = '';
		if ( !empty($rar) && $code != 'ou' )
		{
			$path = $folder2.session_id().'_'.$idDoc.'_'.$code.'.rar';
			$f = $rar;
		} 
		elseif( !empty($pdf) && $code == 'ou' )
		{
			$path = $folder2.session_id().'_'.$code.'.pdf';
			$f = $pdf;
		}

		if ( !empty( $path ) )
		{
			$fh = fopen( $path, "w+" );
			fwrite($fh, $f);
			fclose($fh);
		}

		if( !empty($pdf) && $code == 'ou' )
		{
			$oldPath = $path;
			$newPath = $folder2.$code.'.pdf';
			
			if (file_exists($newPath))
				unlink($newPath);
				
			rename($oldPath, $newPath);
			
			if ( file_exists($oldPath) )	
				unlink($oldPath);
		}

	} // end for
	
	// раскрываем архивы
	$rar_str = RarProgPath.'unrar.exe x -o+ -inul '.realpath($folder2).'\\'.session_id().'_*.rar'.' '.realpath($folder2).'\\';
	//print($rar_str.'<BR><BR>');
	$err = shell_exec($rar_str);
	
	// удаляем *.rar, переименовываем папки и пути в файлах
	for($i = 0; $i < count($materialFiles); $i++)
	{
		$idDoc = $materialFiles[$i]['iddoc'];
		$i_21 = $materialFiles[$i]['i_21'];
		$code = $materialFiles[$i]['matCode'];
		
		$path = '';
		if ( $code != 'ou' )
		{
			$path = $folder2.session_id().'_'.$code.'.rar';

			if ( file_exists($path) )
				unlink($path);
			
			$oldName = $folder2.$idDoc.'/';
			$newName = $folder2.$claimNumber.$code.'/';
			
			//print('oldname='.$oldName.'; '.$newName.'<BR>');

			// переименование папки
			if ( is_dir($oldName) )
			{
				// удаляем папку
				if ( is_dir($newName) )
				{
					ClearTempFiles($newName, 0);
					rmdir($newName);
				}
				
				rename($oldName, $newName);
			}
			
			// перименование html-файла 
			$fileOldName = $newName.$idDoc.'.html';
			if (!file_exists($fileOldName))
				$fileOldName = $newName.$idDoc.'.htm';
			if (!file_exists($fileOldName))			
				exit('Erorrrrrrrrrrrrrrrrrrrrrrr!!!');
				
			$fileNewName = $newName.$claimNumber.$code.'.html';
			
			//print('oldfilename='.$fileOldName.'; '.$fileNewName.'<BR>');
			
			if ( file_exists($fileOldName) && !file_exists($fileNewName) )
				rename($fileOldName, $fileNewName);
				
			// переименование папки, содержащей изображения html-файла
			$dirOldName = $newName.$idDoc.'.files/';
			$dirNewName = $newName.$claimNumber.$code.'.files/';
			
			//print('dirOldName='.$dirOldName.'; '.$dirNewName.'<BR>');
			
			if ( file_exists($dirOldName) && !file_exists($dirNewName) )
				rename($dirOldName, $dirNewName);
			
			// заменяем пути к изображениям в html-файлах
			if ( is_dir($dirNewName) )
			{
				//print($fileNewName.'<BR>');
				$handle = fopen($fileNewName, "r");
				$htmlFile = fread($handle, filesize($fileNewName));
				fclose($handle);
				
				$htmlFile = str_replace($idDoc.'.files', $claimNumber.$code.'.files', $htmlFile);
				
				$fh = fopen( $fileNewName, "w+" );
				fwrite($fh, $htmlFile);
				fclose($fh);
			}
		}
		else
		{
			
		}
	} // end for
} // end saveMaterialFileToDisc

// вызов CounterIPDB($currDbName,'N='.$NReg .',P='.$PROP.',B='.$currBulStr);
function CounterIPDB($dbName, $txt)
{
 $serverName = "10.10.18.1";
 $connectionOptions = array("UID" => "ndcpe", "PWD" => "ipro", "Database"=>"STM");
 $conn = sqlsrv_connect( $serverName, $connectionOptions);
 if( $conn==false ) 
 { return '';
   die( print_r( sqlsrv_errors(), true)); //FormatErrors( sqlsrv_errors() );
 }
 $dt = date("Y-m-d H:i:s") ;
 $IP = $_SERVER['REMOTE_ADDR'];
 $txt= str_replace(array("'",':'),' ',$txt);

 $tsql = "select count(distinct ip) q, Count(*) qAll from counterIPDB where db='".$dbName."'" ; //кол юзеров, кол обращений всех юзеров
 $stmt = sqlsrv_query( $conn, $tsql);
 if( $stmt === false )
 {    return '';
      echo "Row selection failed.<br>";
      die( print_r( sqlsrv_errors(), true));
 }
 $row = sqlsrv_fetch_array( $stmt, SQLSRV_FETCH_ASSOC);
 $q = $row['q']; $qall = $row['qAll'];
 sqlsrv_free_stmt( $stmt);
 
 $tsqlInsert = "insert counterIPDB (ip,dt,db,w) Values ('".$IP."','".$dt."','".$dbName."','".$txt."') " ;
 //print($tsqlInsert.'<BR>');
 $stmt = sqlsrv_query( $conn, $tsqlInsert );
 sqlsrv_free_stmt( $stmt);

 sqlsrv_close( $conn );
 return '('.$q.','.$qall.')';
 
}

function toUpper($content) { //трансформирует все буквы в верхний регистр
  $content = strtr($content, "абвгдеёжзийклмнорпстуфхцчшщъьыэюяіїє", 
"АБВГДЕЁЖЗИЙКЛМНОРПСТУФХЦЧШЩЪЬЫЭЮЯІЇЄ"); 
  return strtoupper($content); 
} 
 
function toLower($content) { //трансформирует все буквы в нижний регистр
  $content = strtr($content, "АБВГДЕЁЖЗИЙКЛМНОРПСТУФХЦЧШЩЪЬЫЭЮЯІЇЄ", 
"абвгдеёжзийклмнорпстуфхцчшщъьыэюяіїє"); 
  return strtolower($content); 
}

?>
