<?
include('incs/config.inc');
include('incs/mssql.class.inc');

// =================
// підключення до БД
// =================
$connection = $GLOBALS['connection'];
	
$currConn = $connection['pp'];
$mssql = new mssql();
$mssql->connection($currConn['host'], $currConn['login'], $currConn['pass'], $currConn['dbname'], connType);
$mssql->selectDb('spp');

// CHANGES
$query = <<<QUERY
	select top 1 c2.idvariant 
	from claim210 c
	inner join claim550 c2 on c.idclaim = c2.idclaim
	where c.i_210 = '{$_GET['app_number']}'
	order by c2.idvariant
QUERY;

if ( (int)$mssql->executeQuery($query) != -1 ) {
	$data = $mssql->getRow('num');
	$f = PPImageTemplatePath.'pp_'.$data[0].'-1.jpg';
		
	if ( file_exists($f) ) 
	{
		$info = getimagesize($f);
		
		header("Expires: Mon, 26 Jul 1997 05:00:00 GMT"); 
		header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT"); 
		header("Cache-Control: no-cache, must-revalidate"); 
		header("Cache-Control: post-check=0,pre-check=0"); 
		header("Cache-Control: max-age=0"); 
		header("Pragma: no-cache");
		
		header('Accept-Ranges: bytes');
		header('Content-Length: '.filesize( $f ));
		header('Connection: close');
		header('Content-Type: '.$info['mime']);
		header("Content-Disposition: inline; filename=im");
		
		readfile($f);
	}
	else
		print('file not exists');

}

// =================
// відключення від БД
// =================
$mssql->disconnection();
// =================



/*
select top 1 c2.idvariant 
from claim210 c
inner join claim550 c2 on c.idclaim = c2.idclaim
where c.i_210 = 's201200483'
order by c2.idvariant

$dbn = $_GET['dbn'];
$idVariant = (int)$_GET['idVariant'];
$idClaim = (int)$_GET['idClaim'];
$varIndex = (int)$_GET['varIndex'];
$imageType = $_GET['it'];

if ( $dbn == 'pp' )
	$f = PPImageTemplatePath.'pp_'.$idVariant.'-'.$varIndex.'.jpg';
elseif ( substr($dbn, 0, 2) == 'tm' )
	$f = TMImageTemplatePath.'tm_'.$idClaim.'.jpg';
elseif ( $dbn == 'madrid' || $dbn == 'madridall' )
	$f = 'tempdocs/madrid_'.$idClaim.'.'.$imageType;
elseif ( $dbn == 'wkm' )
	$f = 'tempdocs/wkm_'.$idClaim.'.jpg';

if ( file_exists($f) ) 
{
	$info = getimagesize($f);
	
	header("Expires: Mon, 26 Jul 1997 05:00:00 GMT"); 
	header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT"); 
	header("Cache-Control: no-cache, must-revalidate"); 
	header("Cache-Control: post-check=0,pre-check=0"); 
	header("Cache-Control: max-age=0"); 
	header("Pragma: no-cache");
	
	header('Accept-Ranges: bytes');
	header('Content-Length: '.filesize( $f ));
	header('Connection: close');
	header('Content-Type: '.$info['mime']);
	header("Content-Disposition: inline; filename=im");
	
	readfile($f);
}
else
	print('file not exists');
*/

?>
