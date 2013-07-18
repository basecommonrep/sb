<?
	include('incs/mssql.class.inc');
	
	$mssql = new mssql();
	$mssql->connection('10.10.16.4', 'ndcpe', 'ipro', 'romarin_2', '');

		
	$query = 'select top 10 * from xml x where x.idtrademark=9561';
	$err = (int)$mssql->executeQuery($query);
	
	while ( $data = $mssql->getRow('assoc') )
	{
		print('11');
		$fpath = 'd:\\!_test_!\\'.$data['idTradeMark'].'.xml';
		$fh = fopen( $fpath, "w+" );
		fwrite($fh, $data['val']);
		fclose($fh);
	}

	$mssql->disconnection();
	
?>
