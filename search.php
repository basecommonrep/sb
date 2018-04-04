<?
	session_start();
	
	/*
	print('(sess)NReg='.$_SESSION['NReg'].'<BR>');
	print('section='.$_GET['section'].'<BR>');
	print('action='.$_GET['action'].'<BR>');
	print('newviewbulid='.$_POST['newviewbulid'].'<BR>');
	print('(post)NReg='.$_POST['NReg'].'<BR>');
*/
    $startPage = 'http://www.uipv.org/ua/bases2.html';
    if ( ( $_GET['action'] == 'search' || $_GET['action'] == 'viewdetails' ) &&
    ( ( empty($_SESSION['bulStartedSession']) && empty($_SESSION['addDbName']) ) || ( count($_POST) === 0 && count($_SESSION['lastSearchIds']) === 0 && count($_SESSION['lastViewIds']) === 0 && $_GET['from'] != 'notice' && empty($_GET['chapter']) ) ) )
	{
		if ($_GET['from_efiling'] != 'yes') {
			header('Location: ' . $startPage);
			exit;	
		}
	}

    // TODO: исправить ошибки, возникающие при пр€мом переходе на http://base.ukrpatent.org/searchBul/search.php?action=viewbul&dbname=inv (когда сесси€ не инициализирована)
    error_reporting(0); // временное решение (убрать вывод warning и т.д. в браузер)
    /* if ( $_GET['action'] == 'viewbul' && empty($_SESSION['bulStartedSession']) ) {
        header('Location: ' . $startPage);
    }*/

	$isFirst = false;
	$access = array('certtm', 'certpp', 'appinvc', 'certwkm', 'certmadridall', 'apptmc', 'reestrtm', 'reestrpp');
	// ===========================================================
	// Ф?ЉО?Нї? Ч?ЧЧїЭННЭЕ їНСЯ "ЭЧУЉђ°?ЕЧ€" ЭУ ??Ч "УЮ" їОї MKTP9
	// ===========================================================
	if ( ( count($_GET) === 0 && count($_POST) === 0 ) || 
		 ( count($_GET) === 1 && count($_POST) === 0 && in_array($_GET['dbname'], $access) ) ||
		 ( ( count($_GET) === 1 || ( count($_GET) === 2 && !empty($_GET['special']) )) && !empty($_GET['dbname']) && count($_POST) === 0 && empty($_SESSION['addDbName']) ) 
	   ) 
	{
		session_unset();
		$isFirst = true;
	}
	
	if ($_GET['from_efiling'] == 'yes') { 
		session_unset();
		$isFirst = true;
	}
	// ===========================================================================
	
	// ===========================================================================
	// НЉДЉОєНЯ? ФЧУЉНЭђ†ї, ЂЉvЦФЂ†Љ €ЂЯ†Љ їНУ?ЦС?ЕЧЉ
	// ===========================================================================
	$langs = array( 'ukr', 'rus', 'eng' );
	
	if ( !empty( $_GET['lang'] ) )
		$_SESSION['lastLang'] = ( in_array( $_GET['lang'], $langs ) ) ? $_GET['lang'] : $langs[0];
	else
		$_SESSION['lastLang'] = ( !empty( $_SESSION['lastLang'] ) ) ? $_SESSION['lastLang'] : $langs[0];

	$LANG_SETTINGS = parse_ini_file( 'incs/langsettings/'.$_SESSION['lastLang'].'.ini', true );
	$NOTICE_LANG_SETTINGS = parse_ini_file( 'incs/langsettings/notices_'.$_SESSION['lastLang'].'.ini', true );
	$LANG_SETTINGS += $NOTICE_LANG_SETTINGS;
	// ===========================================================================

	include('incs/parser.inc');
	include('incs/config.inc');
	include('incs/interface.inc');
	include('incs/common_funcs.inc');
	include('incs/bul_funcs.inc');
	include('incs/mssql.class.inc');
	include('.././inetstatistics/incs/statistics_funcs.inc');
	include('.././inetstatistics/incs/config.inc');
	
	$T1 = microtime_float();	

	$params_table_content = $GLOBALS['params_table_content'];
	$actions = $GLOBALS['actions'];
	
	//if ( empty($_SESSION['addDbName']) )
	//	unset($GLOBALS['db_names']['madridall']);

	$db_names = $GLOBALS['db_names'];
	//print_r($db_names);
	$db_names_codes = array_keys($db_names);
	$view_sections_list = $GLOBALS['view_sections_list'];
	$in_var_names = $GLOBALS['in_var_names'];
	$chapterTitles = $GLOBALS['chapterTitles'];
	$claimsPerPageList = $GLOBALS['claimsPerPageList'];
	$viewDbSections = $GLOBALS['view_db_sections'];
	$index_sections = $GLOBALS['index_sections'];
	$sortOrderTable = $GLOBALS['sortordertable'];
	$sortOrders = $GLOBALS['sortOrderTypes'];	
	$connection = $GLOBALS['connection'];
	
		
	// ===========================================================
	// ЧЭЂ?ЉНї? Ч?ЧЧїЭННЯТ Њ?Ц?Ю?ННЯТ
	// ===========================================================
	
	//if ( ( count($_GET) === 0 && count( $_POST ) === 0 ) || ( ( count($_GET) === 1 || ( count($_GET) === 2 && !empty($_GET['special']) )) && !empty($_GET['dbname']) && count($_POST) === 0 ) ) 
	//if ( !empty($_GET['test']) )
	if ( $isFirst )
	{
		// дл§ статистики
		// =============
		session_register( 'statInfo' );
		$_SESSION['statInfo'] = array(
						idUser 	=> 	'',
						userip	=>	'',
		);

	
		//print('is started'.$_SESSION['bulStartedSession']);
		$langTemp = $_SESSION['lastLang'];
		session_unset();
		$_SESSION['lastLang'] = $langTemp;
		
		// очистка временных файлов
		//ClearTempFiles('tempdocs', 24);

		// дл§ словарика
		// =============
		session_register( 'searchDictValue' );
		$_SESSION['searchDictValue'] = '';
		
		session_register( 'lastSearchDictIds' );				
		$_SESSION['lastSearchDictIds'] = array();
		// =============
		
		// дл§ корзины
		// =============
		session_register( 'basketIds' );
		$_SESSION['basketIds'] = array();

		while( list( $dbn, $dbt ) = each( $db_names ) )
			$_SESSION['basketIds'] += array( $dbn => array() );
			
		session_register( 'basketItemsCount' );
		$_SESSION['basketItemsCount'] = 0;
		// =============


		// дл§ оптимизации детального просмотра библиографии
		// =============
		session_register( 'viewedIds' );
		$_SESSION['viewedIds'] = array();

		reset($db_names);
		while( list( $dbn, $dbt ) = each( $db_names ) )
			$_SESSION['viewedIds'] += array( $dbn => array() );
		// =============

	
		session_register( 'lastLang' );
		$_SESSION['lastLang'] = $langs[0];
		
		if ( isDiskBul == 'no' )
		{
			$actualDatesArr = array();
			$actualDatesArr = getActualizationDates();
		}
		
		session_register( 'actualDates' );
		$_SESSION['actualDates'] = $actualDatesArr;
		
		session_register( 'lastSearchDbName' );
		$_SESSION['lastSearchDbName'] = $db_names_codes[0];
		
		session_register( 'lastSuccessSearchDbName' );
		$_SESSION['lastSuccessSearchDbName'] = '';

		session_register( 'lastViewBulNumb' );		
		$_SESSION['lastViewBulNumb'] = 0; 
		
		session_register( 'lastViewBulDbName' );		
		$_SESSION['lastViewBulDbName'] = ''; 

		session_register( 'lastSearchBulNumb' );				
		
		session_register( 'lastViewIds' );				
		$_SESSION['lastViewIds'] = array();

		session_register( 'lastSearchIds' );				
		$_SESSION['lastSearchIds'] = array();
		
		session_register( 'lastSearchClaimsPerPage' );
		$_SESSION['lastSearchClaimsPerPage'] = $claimsPerPageList[0];
		
		session_register( 'searchDbsValues' );
		
		$tempSearchDbsValues = array();
		while( list($key, $val) = each( $params_table_content ) )
		{	
			$temp_db_name = $key;
			$temp_fields_arr = $val;
			
			$tempOneDbValues = array();
			while( list($fname, $fsettings) = each( $temp_fields_arr ) )
				$tempOneDbValues += array( $fname => '' );
				
			$tempSearchDbsValues += array( $temp_db_name => $tempOneDbValues );
		} // end while while( list($key, $val) = each( $params_table_content ) )

		$_SESSION['searchDbsValues'] = $tempSearchDbsValues;
		
		session_register( 'lastInFound' );
		$_SESSION['lastInFound'] = 0;
		
		// нужны дл§ оптимизации:
		// исключить необходимость при каждом переходе по закладкам деталей читать библиографию и копировать файлы

        //session_register( 'NReg' );
		//$_SESSION['NReg'] = '';
		
		session_register( 'lastFullBiblioIdClaim' );
		$_SESSION['lastFullBiblioIdClaim'] = 0;
		
		session_register( 'lastFullBiblioClaimNumber' );
		$_SESSION['lastFullBiblioClaimNumber'] = '';

		session_register( 'lastFullBiblioPatentNumber' );
		$_SESSION['lastFullBiblioPatentNumber'] = '';

		session_register( 'lastFullBiblioClaimTitle' );
		$_SESSION['lastFullBiblioClaimTitle'] = '';

		session_register( 'lastPageNumb' );
		$_SESSION['lastPageNumb'] = 0;

		session_register( 'lastViewBulPageNumb' );
		$_SESSION['lastViewBulPageNumb'] = 0;

		session_register( 'lastViewBulSecName' );
		$_SESSION['lastViewBulSecName'] = '';

		session_register( 'lastAction' );
		$_SESSION['lastAction'] = '';

		session_register( 'lastSearchQuery' );
		$_SESSION['lastSearchQuery'] = '';
		
		// дл§ сортуванн§
		// ==============
		session_register( 'lastSortField' );
		$_SESSION['lastSortField'] = '';
		session_register( 'lastSortOrder' );
		$_SESSION['lastSortOrder'] = '';
		
		// дл§ реѓстра та спец?ал?зованих љ?
		// =============

		if ( !empty($_GET['dbname']) ) 
		{
			
			
			
			session_register( 'addDbName' );
			
			//$access = array('reestrtm', 'reestrpp', 'certtm', 'certpp', 'appinvc');
			
			$_SESSION['basketIds'] += array( 'madridall' => array() );
			
			$_GET['dbname'] = (in_array($_GET['dbname'], $access)) ? $_GET['dbname'] : $access[0];
			
			// выдел§ем из certpp, certtm, reestrpp, reestrtm, appinvc -> tm, pp, invc
			$n = '';
			$c = '';
			if ( strstr($_GET['dbname'], 'cert') )
			{
				$n = substr($_GET['dbname'], 4);
				$c = 'cert';
			}
			
			if ( strstr($_GET['dbname'], 'reestr') )
			{
				$n = substr($_GET['dbname'], 6, 2);
				$c = 'reestr';
			}

			if ( strstr($_GET['dbname'], 'app') )
			{
				$n = substr($_GET['dbname'], 3, 4);
				$c = 'app';
			}

			
			
			
			if ( !empty($c) )
			{
				$_SESSION['addDbName'] = $c;
				$_SESSION['lastSearchDbName'] = $n;
			}
		} // !empty dbname
		else
		{
			session_register( 'bulStartedSession' );
			$_SESSION['bulStartedSession'] = 'on';
		}

	
		session_register( 'specialEnter' );
		$_SESSION['specialEnter'] = false;
		if ( $_GET['special'] == '54321' ) 
			$_SESSION['specialEnter'] = true;

	} // end if ( ( count( $_GET ) === 0 ) && ( count( $_POST ) === 0 ) )

	//print_r($_POST);
	
	$lastSearchIds = $_SESSION['lastSearchIds'];
	$currAction = ( !empty( $_GET['action'] ) && in_array( $_GET['action'], $actions ) ) ? $_GET['action'] : $actions[0];
	$addDbName = $_SESSION['addDbName'];
	if ( !empty($addDbName) && $_GET['dbname'] != $_SESSION['lastSearchDbName'] )
		$_GET['dbname'] = $_SESSION['lastSearchDbName'];
	
	$_SESSION['lastSearchDictIds'] = array();
	
	


	// =================
	// п?дключенн§ до љ?
	// =================
	$currConn = $connection[$db_names_codes[0]];
	//print_r($currConn);
	
	$mssql = new mssql();
	$mssql->connection($currConn['host'], $currConn['login'], $currConn['pass'], $currConn['dbname'], connType);

	//print($_SESSION['bulStartedSession'].'<BR>');
	//print(session_id().'<BR>');
	
	//print_r($currConn['host']);


	if ( $isFirst )
	{
		// =========================================================
		// С?ксуѓмо вх?д в систему ?снуючого та нового користувача
		// =========================================================
		//print('enter');
		$idUser = doStatistics('createnewuser', null, $_SERVER['REMOTE_ADDR'], null, null, $mssql, null);
		$_SESSION['statInfo']['userip'] = $_SERVER['REMOTE_ADDR'];
		$_SESSION['statInfo']['idUser'] = $idUser;
		
		if ( empty($addDbName) )
		{
			doStatistics('createnewaction', 'bul', null, $_SESSION['statInfo']['idUser'], 1, $mssql, null); // 1 - вх?д в систему
			//print('111');
		}
		else
			doStatistics('createnewaction', $addDbName.$_SESSION['lastSearchDbName'], null, $_SESSION['statInfo']['idUser'], 1, $mssql, null); // 1 - вх?д в систему
		// =========================================================
	} // end if $isFirst

	
	// ================================================================================================================
	// ФљїЦЉ?Ю їЂ ЊЭїЧ†ЭђЯТ ЊЭО?Е ?О€ УЮ Н?†ЭУЭЦЯ? ЊЭО€, ФљїЦЉ?Ю їЂ ЧЊїЧ†Љ їЧУЭДНї†Эђ ?О€ ЊЭїЧ†Љ љЄО?У?Н€ Н?НФ?НЯ? ЊЭО€
	// ================================================================================================================
//print($_SESSION['addDbName'].' - '.$_SESSION['lastSearchDbName'].' - '.$_POST['newsearchdbname']);	
	if ( empty($_SESSION['addDbName']) && (( $_SESSION['lastSearchDbName'] == 'tm') || ($_POST['newsearchdbname'] == 'tm')) ) {
		unset($params_table_content['tm']['NUSSR']);
		unset($params_table_content['tm']['DUSSR']);
		unset($params_table_content['tm']['TUSSR']);
		unset($params_table_content['tm']['APP']);
		unset($params_table_content['tm']['ADDR']);
	}	
	

	if ( empty($_SESSION['addDbName']) && (( $_SESSION['lastSearchDbName'] == 'pp') || ($_POST['newsearchdbname'] == 'pp')) ) {
		unset($params_table_content['pp']['APP']);
		unset($params_table_content['pp']['ADDR']);
	}	
	
	if ( empty($_SESSION['addDbName']) && (( $_SESSION['lastSearchDbName'] == 'invdu') || ($_POST['newsearchdbname'] == 'invdu')) ) {
		unset($params_table_content['invdu']['ANALOG']);
	}	
	
	if ( $_SESSION['addDbName'] == 'cert' && $_SESSION['lastSearchDbName'] == 'pp' && !$_SESSION['specialEnter'] )
	{
		unset($params_table_content['pp']['ADDR']);
	}
	elseif ( empty($_SESSION['addDbName']) )
	{
		unset($GLOBALS['db_names']['madridall']);
		unset($GLOBALS['db_names']['tmc']);
		$db_names = $GLOBALS['db_names'];
		$db_names_codes = array_keys($db_names);		
	}
	
	// ================================================
	// ================================================
	// ================================================
	
	//print_r($_SESSION['searchDbsValues']);

	switch( $currAction )
	{
		case 'setsearchcond':
			$currDbName = $_SESSION['lastSearchDbName'];
			$currClaimsPerPage = $_SESSION['lastSearchClaimsPerPage'];
			$currInFound = $_SESSION['lastInFound'];
			$currActualDate = $_SESSION['actualDates'][$currDbName];
			$curr_db_params_table_content = $params_table_content[$currDbName];
			
			getFieldValues( $currDbName, $_POST, $_SESSION['searchDbsValues'] );
		break;
		
		case 'changedb':
			saveFieldValues( $_SESSION['lastSearchDbName'], $_POST, $_SESSION['searchDbsValues'] );
		
			if ( empty( $_GET['lang'] ) )
			{
				$_SESSION['lastSearchDbName'] = ( !empty( $_POST['newsearchdbname'] ) && in_array( $_POST['newsearchdbname'], $db_names_codes ) ) ? $_POST['newsearchdbname'] : $db_names_codes[0];
				$_SESSION['lastSearchClaimsPerPage'] = ( !empty( $_POST['newclaimsperpage'] ) && in_array( $_POST['newclaimsperpage'], $claimsPerPageList ) ) ? $_POST['newclaimsperpage'] : $claimsPerPageList[0];
				$_SESSION['lastInFound'] = ( !empty( $_POST['newinfound'] ) ) ? 1 : 0;				
			}
			else
				$_SESSION['lastSearchDbName'] = ( !empty( $_GET['dbname'] ) && in_array( $_GET['dbname'], $db_names_codes )	) ? $_GET['dbname'] : $db_names_codes[0];

		//	print('<br>'.$_SESSION['addDbName'].' - '.$_SESSION['lastSearchDbName'].' - '.$_POST['newsearchdbname']);	
			$currDbName = $_SESSION['lastSearchDbName'];
			
			$currClaimsPerPage = $_SESSION['lastSearchClaimsPerPage'];
			
			$currActualDate = $_SESSION['actualDates'][$currDbName];
			$curr_db_params_table_content = $params_table_content[$currDbName];
			$_SESSION['lastInFound'] = 0;
			$currInFound = $_SESSION['lastInFound'];		
			getFieldValues( $currDbName, $_POST, $_SESSION['searchDbsValues'] );

			//$_SESSION['lastSearchQuery'] = '';
		break;

		case 'search':
			$currDbName = $_SESSION['lastSearchDbName'];
			saveFieldValues($currDbName, $_POST, $_SESSION['searchDbsValues']);
			$curr_db_params_table_content = $params_table_content[$currDbName];
			$currActualDate = $_SESSION['actualDates'][$currDbName];
			$_SESSION['lastInFound'] = ( !empty( $_POST['newinfound'] ) ) ? 1 : 0;
			$isInFound = $_SESSION['lastInFound'];
			
			// сортуванн§
			$currSortOrderTable = $sortOrderTable[$currDbName];
			$orderFields = array_keys($currSortOrderTable);
			
			$_SESSION['lastSortField'] = $orderFields[0];
			$_SESSION['lastSortOrder'] = $sortOrders[0];

			$currSortField = $orderFields[0];
			$currSortOrder = $sortOrders[0];
			$currSortExpr = $currSortOrderTable[$currSortField]['sortexpr'];
			// =========
							
			$lastSearchQuery = '';
			if ( $isInFound )
				$lastSearchQuery = $_SESSION['lastSearchQuery'];
			
			//print($lastSearchQuery.'<BR><BR>');
									
			$_SESSION['lastSearchClaimsPerPage'] = ( !empty( $_POST['newclaimsperpage'] ) && in_array( $_POST['newclaimsperpage'], $claimsPerPageList ) ) ? $_POST['newclaimsperpage'] : $claimsPerPageList[0];


			$currSearchDbsValues = getSearchFieldsValues($currDbName, $_POST);
			//print_r($currSearchDbsValues);
			//print('<br><br>');
			
			if ( ($_SESSION['lastLang'] == 'rus') || ($_SESSION['lastLang'] == 'eng'));
			{
				$currSearchDbsValues['TYPE'] = str_replace($LANG_SETTINGS['wkm_fields']['TYPE_NAME_COURT'],'за р≥шенн€м суду',$currSearchDbsValues['TYPE']);
				$currSearchDbsValues['TYPE'] = str_replace($LANG_SETTINGS['wkm_fields']['TYPE_NAME_AP'],'за р≥шенн€м јпел€ц≥йноњ палати',$currSearchDbsValues['TYPE']);
			}
			
			//print('<br><br>');
			//print_r($currSearchDbsValues);
			
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
				//exit;
				
				// подставл§ем имена переменных в таблицах mssql, 
				castSearchValuesToSqlFormat($currDbName, $currSearchDbsValuesParsed, false);
				//print('======================================================================<br>');
				//print('<br><br>');

				//print_r($currSearchDbsValuesParsed);
				//print('<br><br>');
				
				$query = buildGetIdsQuery($currDbName, $currSearchDbsValuesParsed, $lastSearchQuery, $addDbName);
				$query = str_replace('$$$ORDERCLAUSE$$$', 'order by '.$currSortExpr.' '.$currSortOrder, $query);

				print($query.'<br><br>');
				
				// убираем ограничение, которое есть дл§ отображени§ раздела бюлетн§ "з§вки, прин§тые к рассмотрению", 
				// но которого не должно быть дл§ љ? "ђедомости о з§вка на изобренеи§, которые прин§ты к расмотрению"
				// кроме того делает возможным поиск за§вок, которые не имеют (41) даты публикации (за§вки ЧЧЧЦ)
				if ( $_SESSION['addDbName'] == 'app' && $_SESSION['lastSearchDbName'] == 'invc' )
				{
					$query = str_replace('where mi.i_11 is null', '', $query);
					
					/*
					$query = str_replace(
						'inner join publication p on p.idClaim=res.idClaim and p.typePub=2', 
						'left join publication p on p.idClaim=res.idClaim and p.typePub=2', 
						$query
					);
					*/
				}
				
				//if ( $currDbName == 'wkm' && !empty($addDbName))
				//	$query = str_replace('order by', " where m.wheretopublish = 'both' order by", $query);
	
				//print($query.'<br>');
				//print($_SESSION['lastSearchQuery'].'<br>');
				//print($isInFound.'<br>');

				
				// пошуковий запит не задано
				if ( empty( $query ) )
					$errors = $LANG_SETTINGS['errors']['header'].': '.$LANG_SETTINGS['errors']['noset'];

				// запит занадто складний
				if ( empty( $errors ) && strlen( $query ) >= 8000 )
					$errors = $LANG_SETTINGS['errors']['header'].': '.$LANG_SETTINGS['errors']['hard'];
				
				if ( empty( $errors ) )
					$currSearchIds = executeGetIdsQuery($currDbName, $query, $mssql);
print($currDbName);
print_r($currSearchIds);
				// помилка при виконнанн? запиту
				if ( empty( $errors ) && $currSearchIds == -1 )
					$errors = $LANG_SETTINGS['errors']['header'].': '.$LANG_SETTINGS['errors']['req'];				
				
				// по запиту н?чого не знайдено
				if ( empty( $errors ) && count($currSearchIds) === 0 )
					$errors = $LANG_SETTINGS['errors']['nores'];					
				
				if ( empty( $errors ) )
				{
					// дл§ статистики
					// =============
					// 2 - усп?шний пошук
					if ( !empty( $addDbName ) )
						$idDbAction = doStatistics('createnewaction', $addDbName.$currDbName, null, $_SESSION['statInfo']['idUser'], 2, $mssql, null); 
					else
						$idDbAction = doStatistics('createnewaction', 'bul', null, $_SESSION['statInfo']['idUser'], 2, $mssql, null); 

					$_SESSION['lastSearchQuery'] = $query;
					$_SESSION['lastSearchIds'] = $currSearchIds;
					
					$_SESSION['lastSuccessSearchDbName'] = $currDbName;
					
					$_SESSION['lastSortField'] = $orderFields[0];
					$_SESSION['lastSortOrder'] = $sortOrders[0];
				}
				else
				{
					// дл§ статистики
					// =============
					// 3 - неусп?шний пошук
					if ( !empty( $addDbName ) )
						$idDbAction = doStatistics('createnewaction', $addDbName.$currDbName, null, $_SESSION['statInfo']['idUser'], 3, $mssql, null); 
					else
						$idDbAction = doStatistics('createnewaction', 'bul', null, $_SESSION['statInfo']['idUser'], 3, $mssql, null); 
				}
				
				// додаѓмо текст запиту до љ?
				doStatistics('createnewquery', $currDbName, null, null, $idDbAction, $mssql, $currSearchDbsValues);
				
			} // empty $errors
		
		case 'sort':
			if ( $currAction == 'sort' )
			{
				$currDbName = $_SESSION['lastSuccessSearchDbName'];
				$currSortOrderTable = $sortOrderTable[$currDbName];
				$orderFields = array_keys($currSortOrderTable);
				$sortby = $_GET['sortby'];

				$currSortField = substr($sortby, 0, strpos($sortby, '_')); 
				if ( !in_array($currSortField, $orderFields) )
					$currSortField = $orderFields[0];
				
				$currSortOrder = substr($sortby, strpos($sortby, '_')+1); 
				if ( !in_array($currSortOrder, $sortOrders) )
					$currSortOrder = $sortOrders[0];

				$currSortExpr = $currSortOrderTable[$currSortField]['sortexpr'];

				$_SESSION['lastSortField'] = $currSortField;
				$_SESSION['lastSortOrder'] = $currSortOrder;
				
				// модиф?куѓмо попередн?й запит в?дпов?дно до нових критер?Ьв			
				$query = $_SESSION['lastSearchQuery'];
				$query = substr($query, 0, strrpos($query, 'order by'));
				$query .= 'order by '.$currSortExpr.' '.$currSortOrder;
				
				// сортуѓмо за новими кр?тер?§ми
				$currSearchIds = executeGetIdsQuery($currDbName, $query, $mssql);

				$_SESSION['lastSearchQuery'] = $query;
				$_SESSION['lastSearchIds'] = $currSearchIds;
				$_SESSION['lastSuccessSearchDbName'] = $currDbName;
			} // end if $action == 'sort' 
		
		case 'viewsearchres':
			if ( empty( $errors ) )
			{
				$currDbName = $_SESSION['lastSuccessSearchDbName'];
				$lastSearchIds = $_SESSION['lastSearchIds'];
				$currSearchIds = $_SESSION['lastSearchIds'];
				$currSearchClaimsPerPage = $_SESSION['lastSearchClaimsPerPage'];
				$currBasketIds = $_SESSION['basketIds'][$currDbName];
				
				// сортуванн§
				$currSortOrderTable = $sortOrderTable[$currDbName];
				$orderFields = array_keys($currSortOrderTable);
	
				$currSortField = $_SESSION['lastSortField'];
				$currSortOrder = $_SESSION['lastSortOrder'];
				$currSortExpr = $currSortOrderTable[$currSortField]['sortexpr'];
				// =========

				//print_r($currSearchIds);
				$resClaimsCount = count($currSearchIds);
				$pageCount = ceil( $resClaimsCount / $currSearchClaimsPerPage );
				
				if ( empty( $_GET['page'] ) && $currAction == 'viewsearchres' )
					$_GET['page'] = ( (int)$_SESSION['lastPageNumb'] > 0 ) ? (int)$_SESSION['lastPageNumb'] : 1;
				
				$currPage = ( !empty( $_GET['page'] ) ) ? (int)$_GET['page'] : 1;
				$_SESSION['lastPageNumb'] = $currPage;

				if ( $currPage > $pageCount )
					$currPage = $pageCount;
				elseif ( $currPage < 1 )
					$currPage = 1;
				
				$startId = 1 + ( $currSearchClaimsPerPage * ($currPage - 1) );
				$endId = $startId + $currSearchClaimsPerPage - 1;
				if ( $endId > $resClaimsCount )
					$endId = $resClaimsCount;
					
				$currSubSetSearchIds = array_slice($currSearchIds, $startId-1, $endId-$startId+1);
		
				$query = buildGetShortBiblioQuery($currDbName, $currSubSetSearchIds, '');
				$query = str_replace('$$$ORDERCLAUSE$$$', 'order by '.$currSortExpr.' '.$currSortOrder, $query);
				$query = str_replace('###pubtype###', $currDbName, $query); // тип публикации дл§ ЮЊ†
				//print('<br><br>'.$query.'<br><br>');
				//die;

				$searchShortBiblioSet = executeGetShortBiblioQuery($currDbName, $query, $mssql);
				//print_r($searchShortBiblioSet);

				$pageNumbersStr = getPageNumbersStr('viewsearchres', '', '', $pageCount, $currPage, '');
				
				//if ( $currDbName == 'tm' )
				//	CopyTmImagesToTemp($currSubSetSearchIds, 0);
					
				if ( $currDbName == 'pp' )
					$variantInfo = getPpVariantInfo($searchShortBiblioSet);

				if ( $currDbName == 'madrid' || $currDbName == 'madridall' )
					saveMadridImagesToTemp($searchShortBiblioSet, '');				

				if ( $currDbName == 'wkm' )
					saveWKMImagesToTemp($searchShortBiblioSet);
			} // end if epty errors

		break;
		
		case 'viewbul':
			$currDbName = ( !empty( $_GET['dbname'] ) && in_array( $_GET['dbname'], $db_names_codes ) ) ? $_GET['dbname'] : $db_names_codes[0];
			$currDbTitle = $db_names[$currDbName];

      if ( substr($currDbName, 0, 3) == 'geo')
      {
        $bulNumbList = getGeoBulNumberList($currDbName);
        
        $currBulNumbIds = array_keys($bulNumbList);

        $_SESSION['lastViewBulNumb'] = ( isset($_POST['newviewbulid']) && $_POST['newviewbulid'] >= 0 && in_array( $_POST['newviewbulid'], $currBulNumbIds ) ) ? (int)$_POST['newviewbulid'] : $_SESSION['lastViewBulNumb'];
        $_SESSION['lastViewBulNumb'] = ( in_array( $_SESSION['lastViewBulNumb'], $currBulNumbIds ) ) ? (int)$_SESSION['lastViewBulNumb'] : 0;
        $currBulId = $_SESSION['lastViewBulNumb'];
        
        $currBulStr = substr($bulNumbList[$currBulId], 0, strpos($bulNumbList[$currBulId], ' '));
        $currBulDate = substr($bulNumbList[$currBulId], strpos($bulNumbList[$currBulId], ' ')+1);
        $currViewDbSections = $viewDbSections[$currDbName];
        $currViewDbSectionsCodes = array_keys($currViewDbSections);
        $currSecName = ( !empty( $_GET['section'] ) && in_array( $_GET['section'], $currViewDbSectionsCodes ) ) ? $_GET['section'] : $currViewDbSectionsCodes[0];
        $currSecTitle = $currViewDbSections[$currSecName][2];

        $t = explode(' ', $currBulStr);

				$numbb = str_replace('/', '-', ($currBulStr));
				$d = explode('.', $currBulDate);
				$bstr = $d[0].$d[1].$d[2];

        if($currSecName == 'pointer')
          $bul_pdf_fpath = 'geo/'.$currDbName.'/pointer/pointer_'.$currDbName.'_'.$numbb.'.pdf';
        else
          $bul_pdf_fpath = 'geo/'.$currDbName.'/bul_'.$currDbName.'_'.$numbb.'_'.$bstr.'.pdf';
        
        break;
      }
      
			if ( $currDbName != 'official' )
			{
				// сортуванн§
				$currSortOrderTable = $sortOrderTable[$currDbName];
				$orderFields = array_keys($currSortOrderTable);
	
				$currSortField = $orderFields[0];
				$currSortOrder = $sortOrders[0];
				$currSortExpr = $currSortOrderTable[$currSortField]['sortexpr'];
				// =========
			}

			$currBasketIds = $_SESSION['basketIds'][$currDbName];
						
			if ( $currDbName != 'official' )
			{
				$bulNumbList = getBulNumberList($currDbName, $mssql, $addDbName);
				$currBulNumbIds = array_keys($bulNumbList);

				$_SESSION['lastViewBulNumb'] = ( isset($_POST['newviewbulid']) && $_POST['newviewbulid'] >= 0 && in_array( $_POST['newviewbulid'], $currBulNumbIds ) ) ? (int)$_POST['newviewbulid'] : $_SESSION['lastViewBulNumb'];
				
				if ( $currDbName == 'wkm' && !isset($_POST['newviewbulid']) && empty($_GET['page']))
					$_SESSION['lastViewBulNumb'] = 1;
					
				$_SESSION['lastViewBulNumb'] = ( in_array( $_SESSION['lastViewBulNumb'], $currBulNumbIds ) ) ? (int)$_SESSION['lastViewBulNumb'] : 0;
			}
						
			$_SESSION['lastViewBulDbName'] = $currDbName;
			
			$currBulId = $_SESSION['lastViewBulNumb'];

			$currBulStr = substr($bulNumbList[$currBulId], 0, strpos($bulNumbList[$currBulId], ' '));
			$currBulDate = substr($bulNumbList[$currBulId], strpos($bulNumbList[$currBulId], ' ')+1);
			$currViewDbSections = $viewDbSections[$currDbName];
			$currViewDbSectionsCodes = array_keys($currViewDbSections);
			$currSecName = ( !empty( $_GET['section'] ) && in_array( $_GET['section'], $currViewDbSectionsCodes ) ) ? $_GET['section'] : $currViewDbSectionsCodes[0];
			$currSecTitle = $currViewDbSections[$currSecName][2];

			$currSearchClaimsPerPage = $_SESSION['lastSearchClaimsPerPage'];
			
			$itemCount = array();
			//15.02.2007
			//print $currBulDate.'<BR>';
			
			//$date = new DateTime();
			//echo $date;			
			//print strtotime('15.02.2007').'<BR>';
			//print strtotime('14.02.2007').'<BR>';
			//print strtotime('16.02.2007').'<BR>';
			
			if ($currDbName == 'invdu' && ( strtotime($currBulDate) < strtotime('16.02.2007')) )
				$currDbTitle = $LANG_SETTINGS['menu']['invdu2'];
			

			if ( $currDbName != 'official' && empty($addDbName))
			{
				// получаем кол-во патентов/за§вок в разделе ЮЊ†
				if ( substr($currDbName, 0, 3) == 'inv' )
				{
					$invMPKItemCount = getInvMPKItemCount($currDbName, $currSecName, $currBulId, $currBulStr, $isIndexSec, $mssql, $currBulDate);
					$itemCount += $invMPKItemCount;
				}
				
				// получаем кол-во в разделе покажчики
				if ( $currDbName != 'wkm' && substr($currDbName, 0, 2) == 'tm' && $currDbName != 'pp' && $currDbName != 'madrid' )
				{
					$indexCount = getIndexItemCount($currDbName, $currSecName, $currBulId, $currBulStr, $isIndexSec, $mssql, $currBulDate);
					$itemCount += $indexCount;
				}
			} // end if $currDbName != 'official'
			
			//print_r($itemCount);
			
			$isIndexSec = in_array($currSecName, $index_sections);
			
			if ( $isIndexSec )
				$currSearchClaimsPerPage = 30;

			if ( $currSecName == 'notice' )
				$currSearchClaimsPerPage = 3000;

			$currActualDate = $_SESSION['actualDates'][$currDbName];
			
			if ( ( $currSecName == 'notice' || !isset( $_GET['page'] ) || $_GET['from'] == 'details' ) )
			{

				// в том числе формируем запрос на получение спов?щень
				$query = buildGetIdsBulViewQuery($currDbName, $currSecName, $currBulId, $currBulStr, $isIndexSec, $addDbName, $currBulDate);
				//print($query);
		
				// убираем ограничение, которое есть дл§ отображени§ раздела бюлетн§ "з§вки, прин§тые к рассмотрению", 
				// но которого не должно быть дл§ љ? "ђедомости о з§вка на изобренеи§, которые прин§ты к расмотрению"
				if ( $_SESSION['addDbName'] == 'app' && $_SESSION['lastSearchDbName'] == 'invc' ) 
					$query = str_replace('where mi.i_11 is null', '', $query);

				
				if ( $currDbName != 'wkm' )
					$query = str_replace('$$$ORDERCLAUSE$$$', 'order by '.$currSortExpr.' '.$currSortOrder, $query);
				else {
					$query = str_replace('$$$ORDERCLAUSE$$$', '', $query);
					if (!empty($addDbName))
						$query = str_replace('where', "where mi.wheretopublish = 'both' and ", $query);
				}

				//print($query.'<BR><BR>');
				$currSearchIds = executeGetIdsBulViewQuery($currDbName, $query, $isIndexSec, $currSecName, $mssql);
				
				//print_r($currSearchIds);

				if ( $currSecName != 'notice' )
					$_SESSION['lastViewIds'] = $currSearchIds;
			}
			
			if ( $currSecName != 'notice' )
				$currSearchIds = $_SESSION['lastViewIds'];
			
			
			
			$errors = '';
			if ( count($currSearchIds) === 0 )
				$errors = $LANG_SETTINGS['errors']['novres'];
			

			//print_r($_SESSION['lastViewIds']);
			
			if ( empty( $errors ) )			
			{
				$resClaimsCount = count($currSearchIds);
				$pageCount = ceil( $resClaimsCount / $currSearchClaimsPerPage );
	
				//if ( empty( $_GET['page'] ) )
				//	$_GET['page'] = ( (int)$_SESSION['lastViewBulPageNumb'] > 0 ) ? (int)$_SESSION['lastViewBulPageNumb'] : 1;

				$currPage = ( !empty( $_GET['page'] ) ) ? (int)$_GET['page'] : 1;
	
				if ( $currPage > $pageCount )
					$currPage = $pageCount;
				elseif ( $currPage < 1 )
					$currPage = 1;
					
				$startId = 1 + ( $currSearchClaimsPerPage * ($currPage - 1) );
				$endId = $startId + $currSearchClaimsPerPage - 1;
				if ( $endId > $resClaimsCount )
					$endId = $resClaimsCount;
						
				
				$currSubSetSearchIds = array_slice($currSearchIds, $startId-1, $endId-$startId+1);
				
				if ( !$isIndexSec && $currDbName != 'official' )
				{
					$query = buildGetShortBiblioQuery($currDbName, $currSubSetSearchIds, $currSecName);
					$query = str_replace('$$$ORDERCLAUSE$$$', 'order by '.$currSortExpr.' '.$currSortOrder, $query);
					$query = str_replace('###pubtype###', $currDbName, $query); // тип публикации дл§ ЮЊ†
					$searchShortBiblioSet = executeGetShortBiblioQuery($currDbName, $query, $mssql);
				}
				else
					$searchShortBiblioSet = $currSubSetSearchIds;
					
				//print($query);
				
				$pageNumbersStr = getPageNumbersStr($currAction, $currDbName, $currSecName, $pageCount, $currPage, '');			

				if ( $currSecName == 'all' )
				{
					if ( $currDbName == 'pp' )
						$variantInfo = getPpVariantInfo($searchShortBiblioSet);

					//if ( $currDbName == 'tm' )
						//CopyTmImagesToTemp($currSubSetSearchIds);
						
					if ( $currDbName == 'madrid' )
						saveMadridImagesToTemp($searchShortBiblioSet, '');				
						
					if ( $currDbName == 'wkm' )
						saveWKMImagesToTemp($searchShortBiblioSet);
						
				} // end if $currSecName == 'all'
				
				if ( $currDbName == 'official' ) 
					saveAllNoticeToTemp($mssql);
					
				//print_r($searchShortBiblioSet);
				$_SESSION['lastViewBulPageNumb'] = $currPage;
				$_SESSION['lastViewBulSecName'] = $currSecName;
				
			} // empty errors

			//saveAllNoticeToTemp();
			
			//exit;
		break;
		
		case 'viewdetails':
			$idClaim = ( !empty( $_GET['IdClaim'] ) && (int)$_GET['IdClaim'] > 0 ) ? $_GET['IdClaim'] : $_SESSION['lastFullBiblioIdClaim'];
			$currDbName = ( !empty( $_GET['dbname'] ) ) ? $_GET['dbname'] : $_SESSION['lastSearchDbName'];

			if ( !in_array( $currDbName, $db_names_codes ) )
				$currDbName = $db_names_codes[0];
				
			$currBasketIds = $_SESSION['basketIds'][$currDbName];
			
			$currChapterTitles = $chapterTitles[$currDbName];
			
			$fullBiblioChapters = array_keys($currChapterTitles);
		 	$currFullBiblioChapter = ( !empty( $_GET['chapter'] ) && in_array( $_GET['chapter'], $fullBiblioChapters ) ) ? $_GET['chapter'] : $fullBiblioChapters[0];
			
			//if ( $currFullBiblioChapter == 'biblio' || $currDbName == 'pp' )
			{
				$fullBiblioQuery = buildGetFullBiblioQuery($currDbName, $idClaim);
				$fullBiblioQuery = str_replace('###pubtype###', $currDbName, $fullBiblioQuery); // тип публикации дл§ ЮЊ†
				print($fullBiblioQuery);
				$fullBiblio = executeGetFullBiblioQuery($currDbName, $fullBiblioQuery, $mssql);
				//print_r($fullBiblio);

				$_SESSION['lastFullBiblioClaimNumber'] = $fullBiblio['i_21'];
				$_SESSION['lastFullBiblioPatentNumber'] = $fullBiblio['i_11'];
				$_SESSION['lastFullBiblioClaimTitle'] = devidedLongNames($fullBiblio['i_54_ukr'], 30);;

				if ( $currDbName == 'pp' )
					$_SESSION['lastFullBiblioClaimTitle'] = $fullBiblio['i_54'];	

				if ( $currDbName == 'tm' )
				{
					$_SESSION['lastFullBiblioClaimTitle'] = str_replace('###keywords###', '; ', $fullBiblio['i_539']) ;	
					$_SESSION['lastFullBiblioPatentNumber'] = $fullBiblio['i_111'];
				}
				if ( $currDbName == 'madridall' )
				{
					$_SESSION['lastFullBiblioClaimTitle'] = $fullBiblio['fi_540'];	
					$_SESSION['lastFullBiblioPatentNumber'] = $fullBiblio['fi_111'];
				}
				

			} // end if 
			
			if ( $currDbName == 'pp' )
			{
				$variantInfo = getPpVariantInfo(array(0 => $fullBiblio));
				$vi = $variantInfo[$idClaim];
			}
			
			if ( $currDbName == 'madridall' )
			{
				saveMadridImagesToTemp($fullBiblio, $currAction);				
			}



			//print_r($_SESSION['viewedIds']);	
			//print('<BR><BR>');
			
			//print_r($db_names);
			//print_r($_SESSION['viewedIds']);
			//print($currDbName);
			if ( !in_array($idClaim, $_SESSION['viewedIds'][$currDbName]) && substr($currDbName, 0, 3) == 'inv' && $currDbName != 'invc' )	
			{
				//print('saved<BR><BR>');
				if ( isInvDocFromDb == 'yes' ) 
				{
					$materialQuery = getViewMaterialQuery($fullBiblio['i_21_original']);
					$materialFiles = getMaterialFiles($materialQuery, $mssql);
					
					//print($materialQuery.'<BR><BR>');
					
					//print_r($materialFiles);
					saveMaterialFileToDisc($materialFiles, $_SESSION['lastFullBiblioClaimNumber']);
					
					//print($materialQuery);
				}
				else
					copyInvMaterialFilesToTemp($fullBiblio['i_21_original'], '');

				array_push($_SESSION['viewedIds'][$currDbName], $idClaim);
			}



			$_SESSION['lastFullBiblioIdClaim'] = $idClaim;
			
			
			$currSearchIds = $_SESSION['lastSearchIds'];
			if ( $_SESSION['lastAction'] == 'viewbul' || $_SESSION['lastAction'] == 'viewbasket')
				$currSearchIds = $_SESSION['lastViewIds'];
			
			
			if ( $_GET['from'] == 'index' )
			{
				$currSearchIds = extractIdClaimFromIndexData($currSearchIds);
				$_SESSION['lastViewIds'] = $currSearchIds;
			}
			elseif ( $_GET['from'] == 'viewbasket' )
			{
				$currSearchIds = $_SESSION['basketIds'][$currDbName];
				$_SESSION['lastViewIds'] = $currSearchIds;
			}
			
			if ( $_GET['from'] == 'notice' )
			{
				$currSearchIds = array();
				$_SESSION['lastViewIds'] = array();
			}
				
			if ( count( $currSearchIds ) > 1 )
			{
				$ids = array_flip($currSearchIds);
				$currIdClaimIndex = $ids[$idClaim];
				
				$nextId = ( ($currIdClaimIndex+1) < count($currSearchIds)) ? $currSearchIds[$currIdClaimIndex+1] : '';
				$prevId = ( ($currIdClaimIndex-1) >= 0) ? $currSearchIds[$currIdClaimIndex-1] : '';
			}
			
			
			/*
			$T2 = microtime_float();
			$T3 = $T2 - $T1;

			print('<tr><td>'.$T3.' сек</td></tr>');
			exit;
			*/
	
				
		break;

		case 'viewhelp':
			$currDbName = $_SESSION['lastSearchDbName'];

			$curr_db_params_table_content = $params_table_content[$currDbName];
			$fnames = array_keys($curr_db_params_table_content);

			$currFieldName = ( !empty( $_GET['fname'] ) && in_array( $_GET['fname'], $fnames ) ) ? $_GET['fname'] : '';
		break;
		
		case 'viewnotices':
		 
			$currDbName = ( !empty( $_GET['dbname'] ) && in_array( $_GET['dbname'], $db_names_codes ) ) ? $_GET['dbname'] : 'inv';
//print('<br><br>search.php(viewnotices) -- $currDbName='. $currDbName.'<br><br>');

			$bulNumbList = getNoticeBulNumberList($currDbName, $mssql);
//print('<br><br>search.php(viewnotices) $bulNumbList= <br>');
//print_r($bulNumbList);	print('<br>');		
			$currBulNumbIds = array_keys($bulNumbList);

			$_SESSION['lastViewBulNumb'] = ( isset($_POST['newviewbulid']) && $_POST['newviewbulid'] >= 0 && in_array( $_POST['newviewbulid'], $currBulNumbIds ) ) ? (int)$_POST['newviewbulid'] : $_SESSION['lastViewBulNumb'];
			$_SESSION['lastViewBulNumb'] = ( in_array( $_SESSION['lastViewBulNumb'], $currBulNumbIds ) ) ? (int)$_SESSION['lastViewBulNumb'] : 0;
			$currBulId = $_SESSION['lastViewBulNumb'];
//print('<br><br>search.php(viewnotices) currBulId= '.$currBulId.'<br>');	

if (empty($_POST['NReg']) && empty($_POST['PROP']))  //прищли от javaScipt (смена §зыка)
{ $NReg=$_GET['fname'];	
  $PROP=$_GET['chapter'];
}
else //прищли от ввода данных на поиск
{ $NReg=$_POST['NReg'];
  $PROP=$_POST['PROP'];
}

//print('search.php(viewnotices) $NReg='.$NReg.' fname(GET)='.$_GET['fname'].'(POST)'.$_POST['NReg'].'<br>');
//print('search.php(viewnotices) $PROP='.$PROP.' chapter(GET)='.$_GET['chapter'].'(POST)'.$_POST['PROP'].'<br>');

	//print('$currBulIdDo='.$currBulId.'<BR>');
	if ( ($currDbName == 'tm2' ) || ($currDbName == 'pp2' ))
	{
			if (($NReg!='') ||  ($PROP!='')) 
			{$currBulId = 0; //'--';
			 //print('$currBulIdIN='.$currBulId.'<BR>');
			}
			//elseif ($currBulId =='--') $currBulId =1;
			elseif ($currBulId ==0) $currBulId =1;
			//else $currBulId =0;
			//print('$currBulIdAfter='.$currBulId.'<BR>');		
	}		
    		
			$currBulStr = substr($bulNumbList[$currBulId], 0, strpos($bulNumbList[$currBulId], ' '));
			$currBulDate = substr($bulNumbList[$currBulId], strpos($bulNumbList[$currBulId], ' ')+1);
			$currActualDate = $_SESSION['actualDates'][$currDbName];
//print($currActualDate.'<BR>');
			//print($currBulStr.'<BR>');	
			if ( ($currDbName == 'tm2' ) || ($currDbName == 'pp2' ))
			{
				// в том числе формируем запрос на получение спов?щень
				if (($NReg=='') &&  ($PROP==''))
				 $query = buildGetIdsBulViewQuery($currDbName, 'notice', $currBulId, $currBulStr, true, $addDbName, $currBulDate);
				elseif ($NReg!='')
				 $query = buildGetIdsKindViewQuery($currDbName, 'notice', $NReg, true,'NREG');
				elseif ($PROP!='')
				 { if ($PROP=='examples') 
				    $query = buildGetIdsKindViewQuery($currDbName, 'notice', $PROP, true,'examples'); 
				   elseif (substr($PROP,0,5)=='type=')
				    $query = buildGetIdsKindViewQuery($currDbName, 'notice', substr($PROP,5), true,'NOTICECOD'); 
				   else 
				    $query = buildGetIdsKindViewQuery($currDbName, 'notice', $PROP, true,'PROP'); 		
				 }
				//print($currBulId); print('<br>');
				//print($currBulStr); print('<br>');
				//print($currBulDate); print('<br>');
				//print($query); print('<br>');
				
				$currSearchIds = executeGetIdsBulViewQuery($currDbName, $query, true, 'notice', $mssql);

				$searchShortBiblioSet = $currSearchIds;
			    $RecordCount= count($searchShortBiblioSet);
				//print_r($searchShortBiblioSet);	print('<br>');
			}
			else if ( !( $currDbName == 'tm' || $currDbName == 'pp' || $currDbName == 'madrid' || $currDbName == 'geo' ) )
			{
				// в том числе формируем запрос на получение спов?щень
				$query = buildGetIdsBulViewQuery($currDbName, 'notice', $currBulId, $currBulStr, true, $addDbName, $currBulDate);
				$currSearchIds = executeGetIdsBulViewQuery($currDbName, $query, true, 'notice', $mssql);
				
				$searchShortBiblioSet = $currSearchIds;
				$RecordCount= count($searchShortBiblioSet);
			}
			else
			{
				$t = explode(' ', $currBulStr);

				$numbb = str_replace('/', '-', ($currBulStr));
				$d = explode('.', $currBulDate);
				$bstr = $d[0].$d[1].$d[2];

				$notice_fpath = 'notices/'.$currDbName.'/notices_'.$currDbName.'_'.$numbb.'_'.$bstr.'.pdf';
				$RecordCount= '';
			}
		break;

	} // end switch

	if ( !($_SESSION['lastAction'] == 'viewbul' && $currAction == 'viewdetails' 	) 
	  && !($_SESSION['lastAction'] == 'viewnotices' && $currAction == 'viewdetails' )
	  && !($_SESSION['lastAction'] == 'viewbasket' && $currAction == 'viewdetails' 	) 
	  )
			$_SESSION['lastAction'] = $currAction;
	
	/*
	print($currAction);
	print('<BR><BR>');
	print($_SESSION['lastAction']);
	*/
	
?>

<?

	/*
	if ( $_SESSION['addDbName'] == 'cert' )
		include('incs/sitetemplate_noaccess.php.inc');
	else
	*/
		include('incs/sitetemplate.php.inc');
exit;		

	// =================
	// в?дключенн§ в?д љ?
	// =================
	$mssql->disconnection();
	// =================
		
?>


