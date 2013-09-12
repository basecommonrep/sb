<?
	session_start();

	//a	
	// ===========================================================
	// ÓÄÀËÅÍÈÅ ÑÅÑÑÈÎÍÍÎÉ ÈÍÔÛ "ÎÑÒÀÂØÅÉÑß" ÎÒ ²ÄÑ "ÒÌ" ÈËÈ MKTP9
	// ===========================================================
	/*
	if ( ( count($_GET) === 0 && count($_POST) === 0 && empty($_SESSION['bulStartedSession'])) || 
		 ( ( count($_GET) === 1 || ( count($_GET) === 2 && !empty($_GET['special']) )) && !empty($_GET['dbname']) && count($_POST) === 0 && empty($_SESSION['addDbName']) ) 
	   ) 
		session_unset();
	// ===========================================================================
	*/

	// ===========================================================================
	// ÍÀ×ÀËÜÍÛÅ ÓÑÒÀÍÎÂÊÈ, ÇÀÃÐÓÇÊÀ ßÇÛÊÀ ÈÍÒÅÐÔÅÉÑÀ
	// ===========================================================================
	$langs = array( 'ukr', 'rus', 'eng' );
	
	if ( !empty( $_GET['lang'] ) )
		$_SESSION['lastLang'] = ( in_array( $_GET['lang'], $langs ) ) ? $_GET['lang'] : $langs[0];
	else
		$_SESSION['lastLang'] = ( !empty( $_SESSION['lastLang'] ) ) ? $_SESSION['lastLang'] : $langs[0];

	$LANG_SETTINGS = parse_ini_file( 'incs/langsettings/'.$_SESSION['lastLang'].'.ini', true );
	// ===========================================================================

	include('incs/config.inc');
	include('incs/interface.inc');
	include('incs/common_funcs.inc');
	include('incs/bul_funcs.inc');
	include('incs/mssql.class.inc');	
	
	$T1 = microtime_float();	

	$params_table_content = $GLOBALS['params_table_content'];
	$actions = $GLOBALS['basket_actions'];
	$db_names = $GLOBALS['db_names'];
	$db_names_codes = array_keys($db_names);
	$sortOrderTable = $GLOBALS['sortordertable'];
	$sortOrders = $GLOBALS['sortOrderTypes'];
	
	// ===========================================================
	// ÑÎÇÄÀÍÈÅ ÑÅÑÑÈÎÍÍÛÕ ÏÅÐÅÌÅÍÍÛÕ
	// ===========================================================

	$currAction = ( !empty( $_GET['action'] ) && in_array( $_GET['action'], $actions ) ) ? $_GET['action'] : $actions[0];
	$currDbName = ( !empty( $_GET['dbname'] ) && in_array( $_GET['dbname'], $db_names_codes ) ) ? $_GET['dbname'] : $db_names_codes[0];
	$currIdClaim = (int)$_GET['idClaim'];

	$addDbName = $_SESSION['addDbName'];
	if (!empty($addDbName))
		$currDbName = $_SESSION['lastSearchDbName'];
	
	$curr_params_table_content = $params_table_content[$currDbName];
	
	// =================
	// ï³äêëþ÷åííÿ äî ÁÄ
	// =================
	$currConn = $connection[$db_names_codes[0]];
	
	$mssql = new mssql();
	$mssql->connection($currConn['host'], $currConn['login'], $currConn['pass'], $currConn['dbname'], connType);
	// =================

	switch( $currAction )
	{
		case 'addtobasket':
			if ( !in_array($currIdClaim, $_SESSION['basketIds'][$currDbName]) )
			{
				array_push($_SESSION['basketIds'][$currDbName], $currIdClaim);
				++$_SESSION['basketItemsCount'];
			}
		break;
		
		case 'deletefrombasket':
			$valuePos = array_search($currIdClaim, $_SESSION['basketIds'][$currDbName]);
			$from = $_GET['from'];
			
			if ( $valuePos !== false )
			{
				//unset($_SESSION['basketIds'][$currDbName][$valuePos]);
				
				$tempIds = array();
				for($i = 0; $i < count($_SESSION['basketIds'][$currDbName]); $i++)
					if ( $_SESSION['basketIds'][$currDbName][$i] != $currIdClaim  )
						array_push($tempIds, $_SESSION['basketIds'][$currDbName][$i]);
				
				$_SESSION['basketIds'][$currDbName] = $tempIds;
				
				--$_SESSION['basketItemsCount'];
			}
			
			 if ( $from == 'viewbasket' ) 
			 	$currAction = 'viewbasket';
			 	
		case 'viewbasket':
			if ( $from == 'viewbasket' || $currAction == 'viewbasket' ) 
			{
				$basketIds = $_SESSION['basketIds'];
				$lastSearchIds = $_SESSION['lastSearchIds'];
				$db_names = $GLOBALS['db_names'];
				
				$_SESSION['lastAction'] = $currAction;
			}
		break;
		
		case 'clearbasket':	
			while( list($dbn, $ids) = each($_SESSION['basketIds']))
				$_SESSION['basketIds'][$dbn] = array();
			
			$_SESSION['basketItemsCount'] = 0;
			$currAction = 'viewbasket';
			$basketIds = $_SESSION['basketIds'];
			$lastSearchIds = $_SESSION['lastSearchIds'];			
			
			$_SESSION['lastAction'] = $currAction;
		break;
	} // end switch
	
	//print_r($_SESSION['basketIds']);
	
?>
<?
	if ( $currAction == 'viewbasket' )
		include('incs/sitetemplate.php.inc');
	else 
		echo($_SESSION['basketItemsCount']);
	
	// =================
	// â³äêëþ÷åííÿ â³ä ÁÄ
	// =================
	$mssql->disconnection();
	// =================
	
?>
