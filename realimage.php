<?
include('incs/config.inc');

$dbn = $_GET['dbn'];
$idVariant = (int)$_GET['idVariant'];
$idClaim = (int)$_GET['idClaim'];
$varIndex = (int)$_GET['varIndex'];
$imageType = $_GET['it'];
$geo_img_id = $_GET['id']; // geo image id

if ( $dbn == 'pp' )
	$f = PPImageTemplatePath.'pp_'.$idVariant.'-'.$varIndex.'.jpg';
elseif ( substr($dbn, 0, 2) == 'tm' )
	$f = TMImageTemplatePath.'tm_'.$idClaim.'.jpg';
elseif ( $dbn == 'madrid' || $dbn == 'madridall' )
	$f = 'tempdocs/madrid_'.$idClaim.'.'.$imageType;
elseif ( $dbn == 'wkm' )
	$f = 'tempdocs/wkm_'.$idClaim.'.jpg';
elseif (substr($dbn, 0, 3) == 'geo')
  $dbn = 'geo';

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
elseif ( $dbn == 'geo' && !empty($geo_img_id) )
{
  $connection = $GLOBALS['connection'][$dbn];
  $link = mssql_connect($connection['host'], $connection['login'], $connection['pass']);
  mssql_select_db($connection['dbname'], $link);
  $query = mssql_query("SELECT [image] FROM [dbo].[geo_image] WHERE id=$geo_img_id");  
  $row = mssql_fetch_assoc($query);
  mssql_close($link);
  
  if(!empty($row['image']))
    $img = imagecreatefromstring($row['image']);
  else
    die('file not exists');
  
  if ( @array_pop(unpack('H4', $row['image'])) == 'ffd8' ) 
  {
    header("Content-type: image/jpeg");
    header("Content-Disposition: inline; filename=$geo_img_id.jpg");
    imagejpeg($img);
    imagedestroy($img);
  } 
  elseif ( @array_pop(unpack('H16', $row['image'])) == '89504e470d0a1a0a' ) 
  {
    header("Content-type: image/png");
    header("Content-Disposition: inline; filename=$geo_img_id.png");
    imagepng($img);
    imagedestroy($img);
  } 
  else
  {
    header("Content-type: image/jpeg");
    header("Content-Disposition: inline; filename=$geo_img_id.jpg");
    imagejpeg($img);
    imagedestroy($img);
  }     
}
else
	print('file not exists');

?>
