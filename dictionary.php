<?
	session_start();

		
	// ===========================================================
	// Ф?ЉО?Нї? Ч?ЧЧїЭННЭЕ їНСЯ "ЭЧУЉђ°?ЕЧ¤" ЭУ ??Ч "УЮ" їОї MKTP9
	// ===========================================================
	/*
	if ( ( count($_GET) === 0 && count($_POST) === 0 && empty($_SESSION['bulStartedSession'])) || 
		 ( ( count($_GET) === 1 || ( count($_GET) === 2 && !empty($_GET['special']) )) && !empty($_GET['dbname']) && count($_POST) === 0 && empty($_SESSION['addDbName']) ) 
	   )
	{ 
		session_unset();
		print('flex');
	}
	*/
	// ===========================================================================


	// ===========================================================================
	// НЉДЉОєНЯ? ФЧУЉНЭђ†ї, ЂЉvЦФЂ†Љ ¤ЂЯ†Љ їНУ?ЦС?ЕЧЉ
	// ===========================================================================
	$langs = array( 'ukr', 'rus', 'eng' );
	
	if ( !empty( $_GET['lang'] ) )
		$_SESSION['lastLang'] = ( in_array( $_GET['lang'], $langs ) ) ? $_GET['lang'] : $langs[0];
	else
		$_SESSION['lastLang'] = ( !empty( $_SESSION['lastLang'] ) ) ? $_SESSION['lastLang'] : $langs[0];

	$LANG_SETTINGS = parse_ini_file( 'incs/langsettings/'.$_SESSION['lastLang'].'.ini', true );
	// ===========================================================================

	include('incs/parser.inc');
	include('incs/config.inc');
	include('incs/interface.inc');
	include('incs/common_funcs.inc');
	include('incs/bul_funcs.inc');
	include('incs/dictionary_funcs.inc');
	include('incs/mssql.class.inc');
	
	$T1 = microtime_float();	

	$params_table_content = $GLOBALS['params_table_content'];
	$actions = $GLOBALS['dict_actions'];
	$db_names = $GLOBALS['db_names'];
	$db_names_codes = array_keys($db_names);
	
	// ===========================================================
	// ЧЭЂ?ЉНї? Ч?ЧЧїЭННЯТ Њ?Ц?Ю?ННЯТ
	// ===========================================================
	//print_r($_SESSION);
	
	
	$currAction = ( !empty( $_GET['action'] ) && in_array( $_GET['action'], $actions ) ) ? $_GET['action'] : $actions[0];
	$currDbName = ( !empty( $_GET['dbname'] ) && in_array( $_GET['dbname'], $db_names_codes ) ) ? $_GET['dbname'] : $db_names_codes[0];
	$currPage = ( !empty( $_GET['page'] ) ) ? (int)$_GET['page'] : '';

	$fieldList = array_keys($params_table_content[$currDbName]);
	$currFieldName = ( !empty( $_GET['fname'] ) && in_array( $_GET['fname'], $fieldList ) ) ? $_GET['fname'] : $fieldList[0];
	
	$curr_params_table_content = $params_table_content[$currDbName];

	$ftitle = $curr_params_table_content[$currFieldName][3];
	$finid = $curr_params_table_content[$currFieldName][4];
	$ftype = $curr_params_table_content[$currFieldName][0];
	$falign = $curr_params_table_content[$currFieldName][7];

	$addDbName = $_SESSION['addDbName'];
	if (!empty($addDbName))
		$currDbName = $_SESSION['lastSearchDbName'];
	
	$lastSearchIds = $_SESSION['lastSearchIds'];			

	// =================
	// п?дключенн§ до љ?
	// =================
	$currConn = $connection[$db_names_codes[0]];
	
	$mssql = new mssql();
	$mssql->connection($currConn['host'], $currConn['login'], $currConn['pass'], $currConn['dbname'], connType);
	// =================
	
	//print_r($_SESSION['searchDbsValues']);
	
	switch( $currAction )
	{
		case 'searchdict':
			if ( empty($_GET['lang']) )
				$_SESSION['searchDictValue'] = $_POST[$currFieldName];
			else
				$_POST[$currFieldName] = $_SESSION['searchDictValue'];
			
			$_SESSION['lastSearchDictIds'] = array();
			
			$currSearchDbsValues = getSearchFieldsValues($currDbName, $_POST);
			
			//print_r($currSearchDbsValues);
			//print('<br><br>');
			
			$currSearchDbsValuesParsed = parseFieldsExpr($currDbName, $currSearchDbsValues);
			//print_r($currSearchDbsValuesParsed);
			//print('<br><br>');
			
			
			$errors = verifyFieldValues( $currDbName, $currSearchDbsValuesParsed );
			//print($errors);
			//print('<br><br>');
			
			
			if ( empty( $errors ) )
			{
				// подставл§ем где нужно AND, перед операндами ставим равно, 
				// укр-рус-анг логические операторы замен§ем на англи§ские AND, OR, NOT
				castSearchValuesToFormat($currDbName, $currSearchDbsValuesParsed);
				
				//print('<br><br>');
				//print_r($currSearchDbsValuesParsed);
				//print('<br><br>');
				
				
				// подставл§ем имена переменных в таблицах mssql, 
				castSearchValuesToSqlFormat($currDbName, $currSearchDbsValuesParsed, true);
				//print('======================================================================<br>');
				//print('<br><br>');

				//print_r($currSearchDbsValuesParsed);
				//print('<br><br>');
				//exit;
				
				$query = buildGetDictIdsQuery($currDbName, $currFieldName, $currSearchDbsValuesParsed, $addDbName);
				
				//print($query.'<br>');
				//print($lastSearchQuery.'<br>');
				//print($isInFound.'<br>');
				//exit;
				
				// пошуковий запит не задано
				if ( empty( $query ) )
					$errors = $LANG_SETTINGS['errors']['header'].': '.$LANG_SETTINGS['errors']['noset'];

				// запит занадто складний
				if ( empty( $errors ) && strlen( $query ) >= 8000 )
					$errors = $LANG_SETTINGS['errors']['header'].': '.$LANG_SETTINGS['errors']['hard'];
				
				if ( empty( $errors ) )
					$currSearchIds =  executeGetDictIdsQuery($currDbName, $query, $mssql);
					
				// помилка при виконнанн? запиту
				if ( empty( $errors ) && $currSearchIds == -1 )
					$errors = $LANG_SETTINGS['errors']['header'].': '.$LANG_SETTINGS['errors']['req'];				
				
				// по запиту н?чого не знайдено
				if ( empty( $errors ) && count($currSearchIds) === 0 )
					$errors = $LANG_SETTINGS['errors']['nores'];					
				
				if ( empty( $errors ) )
					$_SESSION['lastSearchDictIds'] = $currSearchIds;
			} // empty $errors
			
		case 'viewdict':
			
			// когда пришли на страничку со странички поиска бюллтн§
			if ( $currAction != 'searchdict' && empty($currPage) )
			{
				$query = buildGetDictIdsQuery($currDbName, $currFieldName, 'all', $addDbName);
				//print($query);

				$currPage = 1;
				$currSearchIds = executeGetDictIdsQuery($currDbName, $query, $mssql);
				//print_r($currSearchIds);
				
				if ( $currSearchIds == -1 )
					$errors = $LANG_SETTINGS['errors']['header'].': '.$LANG_SETTINGS['errors']['req'];				

				// по запиту н?чого не знайдено
				if ( empty( $errors ) && count($currSearchIds) === 0 )
					$errors = $LANG_SETTINGS['errors']['nores'];					

				if ( empty( $errors ) )
					$_SESSION['lastSearchDictIds'] = $currSearchIds;
					
				$_SESSION['searchDictValue'] = '';
			}

			$currDictFieldValue = $_SESSION['searchDictValue'];
			
			if ( empty( $errors ) )
			{
				$currSearchIds = $_SESSION['lastSearchDictIds'];
				$currSearchClaimsPerPage = 20;
	
				$resClaimsCount = count($currSearchIds);
				$pageCount = ceil( $resClaimsCount / $currSearchClaimsPerPage );

				if ( $currPage > $pageCount )
					$currPage = $pageCount;
				elseif ( $currPage < 1 )
					$currPage = 1;
				
				$startId = 1 + ( $currSearchClaimsPerPage * ($currPage - 1) );
				$endId = $startId + $currSearchClaimsPerPage - 1;
				if ( $endId > $resClaimsCount )
					$endId = $resClaimsCount;
					
				$currSubSetSearchIds = array_slice($currSearchIds, $startId-1, $endId-$startId+1);
				
				$query = buildGetDictValuesQuery($currDbName, $currFieldName, $currSubSetSearchIds, $addDbName);
				//print('<br><br>'.$query.'<br><br>');			
				//exit;
				//print ($currFieldName);
				
				$searchShortBiblioSet = executeGetDictValues($currDbName, $query, $mssql);
				//print_r($searchShortBiblioSet);

				//exit;



				if ($currFieldName = 'TYPE')
				{
					for ($t=0; $t<count($searchShortBiblioSet); $t++)
					{
					
					if ($searchShortBiblioSet[$t]['value'] == 'за рішенням суду')
						$searchShortBiblioSet[$t]['value'] = $LANG_SETTINGS['wkm_fields']['TYPE_NAME_COURT'];
					if ($searchShortBiblioSet[$t]['value'] == 'за рішенням апеляційної палати')
						$searchShortBiblioSet[$t]['value'] = $LANG_SETTINGS['wkm_fields']['TYPE_NAME_AP'];
					
					}
				}
				
				
				$pageNumbersStr = getPageNumbersStr('viewdict', $currDbName, '', $pageCount, $currPage, $currFieldName);
				
			} // end if epty errors

		break;
		
	} // end switch

?>

<?
	include('incs/sitetemplate.php.inc');
	
	// =================
	// в?дключенн§ в?д љ?
	// =================
	$mssql->disconnection();
	// =================
?>


