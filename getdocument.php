<?
	session_start();
	
	// ===========================================================================
	// ÍÀ×ÀËÜÍÛÅ ÓÑÒÀÍÎÂÊÈ, ÇÀÃÐÓÇÊÀ ßÇÛÊÀ ÈÍÒÅÐÔÅÉÑÀ
	// ===========================================================================
	$langs = array( 'ukr', 'rus', 'eng' );
	
	if ( !empty( $_GET['lang'] ) )
		$_SESSION['lastLang'] = ( in_array( $_GET['lang'], $langs ) ) ? $_GET['lang'] : $langs[0];
	else
		$_SESSION['lastLang'] = ( !empty( $_SESSION['lastLang'] ) ) ? $_SESSION['lastLang'] : $langs[0];

	$LANG_SETTINGS = parse_ini_file( 'incs/langsettings/'.$_SESSION['lastLang'].'.ini', true );
	$NOTICE_LANG_SETTINGS = parse_ini_file( '.././searchBul/incs/langsettings/notices_'.$_SESSION['lastLang'].'.ini', true );
	$LANG_SETTINGS += $NOTICE_LANG_SETTINGS;
	// ===========================================================================

	include('incs/interface.inc');
	include('incs/bul_funcs.inc');
	
	/*
	$params_table_content = $GLOBALS['params_table_content'];
	$fulltextsearch_fields = $GLOBALS['fulltextsearch_fields'];
	$short_help = $GLOBALS['short_help'];
	$view_table_parts = $GLOBALS['view_table_parts'];
	$actions = $GLOBALS['actions'];
	$db_names = $GLOBALS['db_names'];
	$db_names_codes = array_keys($db_names);
	$view_sections_list = $GLOBALS['view_sections_list'];
	$in_var_names = $GLOBALS['in_var_names'];
	$chapterTitles = $GLOBALS['chapterTitles'];
	*/
	
	$claimNumber = $_GET['claimnumber'];
	$matCode = $_GET['doctype'];
	
	$claimNumber = substr($claimNumber.'/', 0, strpos($claimNumber.'/', '/'));
	
	$part = substr( $claimNumber, 0, 6 );
	$folder = 'tempdocs/'.$part.'/';
	$folder2 = $folder.$claimNumber.'/';
	
	if ( $matCode != 'ou')
		$path = $folder2.$claimNumber.$matCode.'/'.$claimNumber.$matCode.'.html';
	else
		$path = $folder2.$matCode.'.pdf';

	if ( file_exists($path) )
	{
		$handle = fopen($path, "r");
		$document = fread($handle, filesize($path));
		fclose($handle);
		
		$document = str_replace($claimNumber.$matCode.'.files', $folder2.$claimNumber.$matCode.'/'.$claimNumber.$matCode.'.files', $document);
		
		$fn = '';
		switch($matCode)
		{
			case 'fu':
				$fn = 'FORMULA';
				break;
			case 'ru';
			case 'rr';
			case 're';
				$fn = 'REFERAT';
				break;
		}
		
		//header("Connection: close"); 
	
		if ($matCode == 'ou')
		{
			header('Last-Modified: '.gmdate('D, d M Y H:i:s') . ' GMT'); 
			header("Pragma: public");
			header("Expires: 0");
			header("Cache-Control: private");
			header("Accept-Ranges: bytes");
			header("Content-Length: ".filesize($path));
			header('Content-Transfer-Encoding: none'); 
			header("Content-Type: application/octet-stream");
			header("Content-type: application/pdf"); 
			//header("Content-Disposition: attachment; filename=".$matCode);
			
			print($document);
		
			exit;
		}
		else
		{
			//$document = textBlink('inv', $document, $fn, false);
			
			//$_SESSION['searchDbsValues']['inv']['REFERAT'] = 'ïðîáêà';
			//print_r($_SESSION['searchDbsValues']);
			//print('11111111');
			
			print($document);	
		}
	}
	else
		print('file does not exists');
?>
