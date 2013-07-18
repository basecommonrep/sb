<?
	include('incs/interface.inc');
	
	$db_names = array_keys($GLOBALS['db_names']);	
	$params_table_content = $GLOBALS['params_table_content'];

	$prev_dbn = '';
	$curr_dbn = '';
	for($i = 0; $i < count($db_names)-1; $i++)
	{
		$dbn = $db_names[$i]; // db_names
		$ptc = $params_table_content[$dbn]; // params_table_content

		if ( substr($dbn, 0, 3) == 'inv' )
			$curr_dbn = 'inv';
		else
			$curr_dbn = $dbn;

		while( list($fname, $fproperties) = each($ptc) )
		{
			$fpath = 'help/'.$curr_dbn.'_help_'.strtolower($fname).'.txt';
			//if ( $prev_dbn != $curr_dbn ) 
			if ( !file_exists($fpath) )
			{
				$fpath = 'help/'.$curr_dbn.'_help_'.strtolower($fname).'.txt';
					
				$qhandle = fopen($fpath, "w+");
				fclose($qhandle);				
			}
		} // end while
		
		$prev_dbn = $curr_dbn;
	} // end for
	
?>

