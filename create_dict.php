<?
	include('incs/config.inc');
	include('incs/interface.inc');
	include('incs/bul_funcs.inc');
	
	//$db_names = array_keys($GLOBALS['db_names']);	
	$special_queries = $GLOBALS['special_queries'];
	$params_table_content = $GLOBALS['params_table_content'];
	$connection = $GLOBALS['connection'];
	$search_idfield_names = $GLOBALS['search_idfield_names'];
	

	$db_names = array(
		'invc' 		=> '',
		'inv' 		=> '',
		'invd' 		=> '',
		'invdu' 	=> '',
		'pp' 		=> '',
		'tm' 		=> '',
		'madrid' 	=> '',
		'wkm' 		=> '',
		'certpp' 	=> 'pp',	
		'certtm' 	=> 'tm',
		'appinvc' 	=> 'invc',	
	);

	$prev_dbn = '';
	$curr_dbn = '';
	
	while(list($dbn, $base_dbn) = each($db_names))
	{
		$with_cut_query = true;

		$fieldName = 'bul_'.$dbn;					
		
		if ( !empty($base_dbn) )
		{
			$fieldName = $dbn;					
			$dbn = $base_dbn;
			$with_cut_query = false;
		}
			
		$sp_queries = $special_queries[$dbn]; // special_queries
		$sp_queries_fnames = array_keys($sp_queries);
		$ptc = $params_table_content[$dbn]; // params_table_content
		$idVarName = $search_idfield_names[$dbn];
		
		//print_r($ptc);
		
		$dbn_connection = $connection[$dbn];
		$sourceDbName = $dbn_connection['sourcedbname'];
		
		$sourceHost = $dbn_connection['sourcehost'];
		$sourceLogin = $dbn_connection['sourcelogin'];
		$sourcePass = $dbn_connection['sourcepass'];
		
		$db = @mssql_connect($sourceHost, $sourceLogin, $sourcePass);
		@mssql_select_db($sourceDbName);
	
		if ( substr($dbn, 0, 3) == 'inv' )
			$curr_dbn = 'inv';
		else
			$curr_dbn = $dbn;
		
		if ( $prev_dbn != $curr_dbn && $with_cut_query)
		{
			$query = 'truncate table '.$sourceDbName.'..dictionary';
			//mssql_query($query) or $err = -1;
		}
			
		if ( $prev_dbn != $curr_dbn ) 
		{
			$fpath = 'dict_'.$curr_dbn;
			
			if ( $i > 0 )
				fclose($qhandle);				
				
			
			if ( $with_cut_query )
				$qhandle = fopen($fpath, "w+");
			else
				$qhandle = fopen($fpath, "a"); // дозаписываем в файл
		}



		$j = 0;
		while( list($fname, $fproperties) = each($ptc) )
		{
			$ftype = $fproperties[0];
			$sql_tname = $fproperties[1];
			$sql_fname = $fproperties[2];
			$j++; 
			
			// ******************************************************************************
			// считываем запрос, который поможет ограничить множествоо сущностей в словарике
			// ******************************************************************************
			
			$cutQuery = '';
			//if ( $with_cut_query )
			{
				$fpath = 'incs/queries/search_'.$dbn.'_ids.txt';
				$handle = fopen($fpath, "r");
				$cutQuery = fread($handle, filesize($fpath));
				fclose($handle);
			} // $with_cut_query 
			
			$p1 = strpos($cutQuery, 'inner join');
			$p2 = strpos($cutQuery, 'inner join', $p1+1);

			if ( !$p2 )
				$p2 = strpos($cutQuery, 'left join', $p1+1);

			if ( !$p2 )
				$p2 = strpos($cutQuery, 'where', $p1+1);
				
			if ( !$p2 )
				$p2 = strpos($cutQuery, 'order by', $p1+1);

			$sub1 = substr($cutQuery, 0, $p1-1);
			$sub2 = substr($cutQuery, $p2, strlen($cutQuery)-$p2);
			$cutQuery = $sub1.' '.$sub2;
			
			$p1 = strpos($cutQuery, 'order by');
			if ( $p1 > 0 )
				$cutQuery = substr($cutQuery, 0, $p1-1);
			
			$cutQuery = str_replace('$$$VIEWBULWHERE$$$', ' ', $cutQuery);

			$cutQuery = str_replace('from ', 'from '.$sourceDbName.'..', $cutQuery);
			$cutQuery = str_replace('inner join ', 'inner join '.$sourceDbName.'..', $cutQuery);
			$cutQuery = str_replace('left join ', 'left join '.$sourceDbName.'..', $cutQuery);
			$cutQuery = str_replace('res.idClaim', 'mi.idClaim', $cutQuery);
			
			$s = 'res1.'.$sql_fname;
			if ( $ftype == 2 ) // str
			{
				$s = 'ltrim(rtrim(res1.'.$sql_fname.'))';
			}
			
			$order = 'ASC';
			switch($ftype)
			{
				case 1: //int
					$isnull = 'isnull(res1.'.$sql_fname.', 0)';
				break;
				case 2: //str
					$isnull = 'isnull(res1.'.$sql_fname.', \'\')';
				break;
				case 3: //date
					$order = 'DESC';
					$isnull = 'isnull(res1.'.$sql_fname.', \'01.01.1900\')';
				break;
			}
			
			$order_expr = 'res1.'.$sql_fname.' '.$order;
			if ( $fname == 'NBUL' )
				$order_expr = "convert(int,substring(res1.".$sql_fname.", charindex('/',res1.".$sql_fname.")+1, len(res1.".$sql_fname.")-charindex('/',res1.".$sql_fname."))) desc, ".
				"case ".
				"when charindex('-',res1.".$sql_fname.")>0 then convert(int,substring(res1.".$sql_fname.", 1, charindex('-',res1.".$sql_fname.")-1)) ".
				"else convert(int,substring(res1.".$sql_fname.", 1, charindex('/',res1.".$sql_fname.")-1)) ".
				"end desc";
			

				/*
				$order_expr = "convert(int,substring(res1.".$sql_fname.", charindex('/',res1.".$sql_fname.")+1, len(res1.".$sql_fname.")-charindex('/',res1.".$sql_fname."))) desc, ".
							"convert(int,substring(res1.".$sql_fname.", 1, charindex('/',res1.".$sql_fname.")-1)) desc";
				*/
			

			if ( in_array($fname, $sp_queries_fnames) ) // если поле имеет спец.запрос
			{
				// опередел€ем кол-во select-ов, если их больше одного в запросе, 
				// значит этот запрос нуждаетс€ в дополнитьльном анализе
				$baseQuery = $sp_queries[$fname];
				
				preg_match_all('/select/', $baseQuery, $matches);
				
				
				$baseQuery = str_replace('where (###WHEREEXPR###)', '', $baseQuery);
				$baseQuery = str_replace('###JOINQUERY###', '', $baseQuery);
				
				
				if ( count($matches[0]) > 1 )
				{	
					
					$baseQuery = str_replace('AND ###WHEREEXPR###', '', $baseQuery);
					
					// rc - стандартный алиас, значит что данные, по которым строитс€ словарик берутс€ из подзапроса
					$fname_alias = 'rc';
					$fname_subalias = 't_'.strtolower($fname);
					$fn = $fname_alias.'.'.$sql_fname;
					$fnsub = $fname_subalias.'.'.$sql_fname;

					// замен€ем "шапку подзапроса, чтобы он выдавал не только св€зующее поле айди или что-то, а еще значение пол€ дл€ словарика"
					$baseQuery = str_replace('inner join ( select distinct ', 
					'inner join ( select '.$fnsub.', ', 
					$baseQuery);
					
		 			// мен€ем "шапку" запроса
					$p = strpos($baseQuery, 'from');
					$subQuery = substr($baseQuery, $p, strlen($baseQuery)-$p);
					$subQuery = 'SELECT '.$fname_subalias.'.'.$idVarName.', '.$fn.' '.$subQuery;
					$baseQuery = $subQuery;
					
					// делаем все ссылки на таблицы абсолютными
					$baseQuery = str_replace('from ', 'from '.$sourceDbName.'..', $baseQuery);
					$baseQuery = str_replace('inner join claim', 'inner join '.$sourceDbName.'..claim', $baseQuery);
					$baseQuery = str_replace('inner join ref', 'inner join '.$sourceDbName.'..ref', $baseQuery);
					$baseQuery = str_replace('inner join ImageVienClasses', 'inner join '.$sourceDbName.'..ImageVienClasses', $baseQuery);					
					
					// создаем результирующий запрос с ограничением по разделам бюллетн€
					$baseQuery = 'SELECT \''.$fieldName.'\', \''.$fname.'\', COUNT('.$isnull.'), '.$s.' '.
					'FROM ('.$baseQuery.') as res1 ';
					// ===================================
					if ( $with_cut_query ) 
						$baseQuery .= 'INNER JOIN ('.$cutQuery.') AS cut ON cut.'.$idVarName.'=res1.'.$idVarName.' ';
					// ===================================
					$baseQuery .= 'GROUP BY res1.'.$sql_fname.' '.
								'HAVING '.$s.' is not null '.
								'ORDER BY '.$order_expr;

					$source_sub_query = $baseQuery;
		 			
					//print($source_sub_query.'<BR><BR>');					
				} // end if count($matches[0]) > 1
				else
				{
					
					$accept_fileds = array('NBUL', 'PPUBL');
					if ( in_array($fname, $accept_fileds) && substr($dbn, 0, 3) == 'inv' && empty( $base_dbn ) )
						$baseQuery = str_replace('AND ###WHEREEXPR###', 'AND t_'.$fname.'.bulletindate > convert(datetime, \'01.04.2006\', 104)', $baseQuery);
					else
						$baseQuery = str_replace('AND ###WHEREEXPR###', '', $baseQuery);						
					
					
					$baseQuery = str_replace('AND ###WHEREEXPR###', '', $baseQuery);
					
					$fname_alias = 't_'.strtolower($fname);
					$fn = $fname_alias.'.'.$sql_fname;
					
					if ( $fname == 'MPK' )
						$fn = 'ltrim(rtrim(substring('.$fn.', 1, 4)))+\' \'+ltrim(rtrim(substring('.$fn.', 5, 10))) ['.$sql_fname.']';

						

		 			// мен€ем "шапку" запроса
					$p = strpos($baseQuery, 'from');
					$subQuery = substr($baseQuery, $p, strlen($baseQuery)-$p);
					$subQuery = 'SELECT '.$fname_alias.'.'.$idVarName.', '.$fn.' '.$subQuery;
					$baseQuery = $subQuery;
					
					// делаем все ссылки на таблицы абсолютными
					$baseQuery = str_replace('from ', 'from '.$sourceDbName.'..', $baseQuery);
					$baseQuery = str_replace('inner join claim', 'inner join '.$sourceDbName.'..claim', $baseQuery);
	
					// создаем результирующий запрос с ограничением по разделам бюллетн€
					$baseQuery = 'SELECT \''.$fieldName.'\', \''.$fname.'\', COUNT('.$isnull.'), '.$s.' '.
					'FROM ('.$baseQuery.') as res1 ';
					// ===================================
					if ( $with_cut_query ) 
						$baseQuery .= 'INNER JOIN ('.$cutQuery.') AS cut ON cut.'.$idVarName.'=res1.'.$idVarName.' ';
					// ===================================
					$baseQuery .= 'GROUP BY res1.'.$sql_fname.' '.
								'HAVING '.$s.' is not null '.
								'ORDER BY '.$order_expr;

					$source_sub_query = $baseQuery;
					
					//print($source_sub_query.'<BR><BR>');					
				} // end else
				
			}
			else
			{
				$fname_alias = 't_'.$fname;
				$fn = $fname_alias.'.'.$sql_fname;
				
					$baseQuery .= 'GROUP BY res1.'.$sql_fname.' '.
								'ORDER BY '.$order_expr;


				$source_sub_query = 'SELECT '.$fname_alias.'.'.$idVarName.', '.$fn.' FROM '.$sourceDbName.'..'.$sql_tname.' '.$fname_alias;
				// ===================================
				if ( $with_cut_query ) 
					$source_sub_query .= ' INNER JOIN ('.$cutQuery.') AS cut ON cut.'.$idVarName.'='.$fname_alias.'.'.$idVarName;
				// ===================================
				$source_sub_query .= ' WHERE '.$fn.' is not null';


				$source_sub_query = 'SELECT \''.$fieldName.'\', \''.$fname.'\', COUNT('.$isnull.'), '.$s.' FROM '.
									'('.$source_sub_query.') res1 GROUP BY res1.'.$sql_fname.' ';
	
				$source_sub_query .= 'ORDER BY '.$order_expr;
				
				//print($source_sub_query.'<BR><BR>');
			}
			
			//print($source_sub_query.'<BR><BR>');
			
			switch($ftype)
			{
				case 2: // str
					$varname = 'valueStr';
				break;
				case 3: // date
					$varname = 'valueDate';
				break;
				case 1: // int
					$varname = 'valueInt';
				break;
			}
			
			
			$dest_query = 'insert into '.$sourceDbName.'..dictionary (dictName, fieldName, entries, '.$varname.') '.
			$source_sub_query;				
			
			fwrite($qhandle, $dest_query."\r\n\r\n");
			
			
			print($dest_query.'<BR><BR>');
			
			
			//$result = mssql_query($dest_query) or exit;
		} // end while ptc
		
		@mssql_close( $db );	
		
		
		$prev_dbn = $curr_dbn;

		
	} // end for db_names
	
	fclose($qhandle);				



?>

