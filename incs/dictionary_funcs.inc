<?
function buildGetDictIdsQuery($dbn, $fname, $currSearchDbsValuesParsed, $addDbName)	
{
	$params_table_content = $GLOBALS['params_table_content'];
	$ptc = $params_table_content[$dbn];
	$ftype = $ptc[$fname][0];
	
	if ( empty( $currSearchDbsValuesParsed[$fname][0] ) && $currSearchDbsValuesParsed != 'all' )
		return '';

	$fpath = 'incs/queries/dict_ids.txt';
		
	$handle = fopen($fpath, "r");
	$query = fread($handle, filesize($fpath));
	fclose($handle);
	
	//print($addDbName);
	if ( empty($addDbName) || $addDbName == 'app' || $dbn == 'wkm' )
		$query = str_replace('$$$DICTNAME$$$', 'bul_'.$dbn, $query);
	else//if ( $addDbName != 'app' )
		$query = str_replace('$$$DICTNAME$$$', $addDbName.$dbn, $query);
	
	$query = str_replace('$$$FIELDNAME$$$', $fname, $query);

	if ( $currSearchDbsValuesParsed == 'all' )
		$query = str_replace('$$$WHEREDICT$$$', '', $query);
	else
		$query = str_replace('$$$WHEREDICT$$$', ' and '.$currSearchDbsValuesParsed[$fname][0], $query);
	
	if ( $ftype == 3 )
		$query = str_replace('$$$ORDERDICT$$$', 'order by d.valueDate desc', $query);
	else
		$query = str_replace('$$$ORDERDICT$$$', '', $query);
				
	//print($query);
	return $query;
} // buildGetDictIdsQuery 
	
function buildGetDictValuesQuery($dbn, $fname, $ids, $addDbName)
{
	$fpath = 'incs/queries/dict_values.txt';
		
	$handle = fopen($fpath, "r");
	$query = fread($handle, filesize($fpath));
	fclose($handle);

	$idsStr = '';
	for($i = 0; $i < count( $ids ); $i++)
		$idsStr .= $ids[$i].',';
		
	if ( $idsStr[strlen($idsStr)-1] == ',' )
		$idsStr[strlen($idsStr)-1] = '';
		
	$idsStr = trim(ltrim($idsStr));
	
	if ( empty($addDbName) || $addDbName == 'app' || $dbn == 'wkm' )
		$query = str_replace('$$$DICTNAME$$$', 'bul_'.$dbn, $query);
	else
		$query = str_replace('$$$DICTNAME$$$', $addDbName.$dbn, $query);

	$query = str_replace('$$$FIELDNAME$$$', $fname, $query);
	$query = str_replace('$$$DICTIDS$$$', $idsStr, $query);
		
	return $query;
} // buildGetDictIdsQuery 

function executeGetDictIdsQuery($dbn, $query, $mssql)
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

function executeGetDictValues($dbn, $query, $mssql)
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
		$dictValues = array();
	
		$i = 0;
		while ( $data = $mssql->getRow('assoc') )
		{
			$dictValues += array($i => $data);
			$i++;
		}
	
		return $dictValues;		
	}
	else
		;

	return -1;
} // executeGetDictIdsQuery
	
?>
