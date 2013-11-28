<?php 

// test comment my new
include('incs/config.inc');

$dbn = $_GET['dbn'];
$idVariant = (int)$_GET['idVariant'];
$idClaim = (int)$_GET['idClaim'];
$varIndex = (int)$_GET['varIndex'];
$imageType = $_GET['it'];

if ( $dbn == 'pp' )
{
	$width = ( $_GET['chapter'] != 'variants' ) ? 150 : 200;
	$f = PPImageTemplatePath.'pp_'.$idVariant.'-'.$varIndex.'.jpg';
}
elseif ( substr($dbn, 0, 2) == 'tm' )
{
	$width = ( $_GET['chapter'] != 'signimage' ) ? 150 : 400;
	$f = TMImageTemplatePath.'tm_'.$idClaim.'.jpg';
}
elseif ( $dbn == 'madrid' || $dbn == 'madridall' )
{
	$width = ( $_GET['chapter'] != 'signimage' ) ? 200 : 400;
	$f = 'tempdocs/madrid_'.$idClaim.'.'.$imageType;
}
elseif ( $dbn == 'wkm' )
{
	$width = ( $_GET['chapter'] != 'signimage' ) ? 350 : 400;
	$f = 'tempdocs/wkm_'.$idClaim.'.jpg';
}

//copy($f, 'd:/server/project/www/searchbul/tempdocs/pp_'.$idVariant.'-'.$varIndex.'.jpg');


/*
if (file_exists($f))
	print($f);
	
exit;
*/
$type = 2;

// f - ��� ����� 
// type - ������ ��������������� 
// q - �������� ������ 
// src - �������� ����������� 
// dest - �������������� ����������� 
// w - ������ ����������� 
// ratio - ����������� ������������������ 
// str - ��������� ������ 

// ��� ��������������, ���� �� ������� ������� 
if ($type == 0) $w = 70;  // ���������� 70x70 
if ($type == 1) $w = 90;  // ���������� 90x90 
if ($type == 2) $w = $width; // ���������������� ������� $width 


// �������� jpeg �� ��������� 
if (!isset($q)) $q = 100;

// ������ �������� ����������� �� ������ 
// ��������� ����� � ����������� ��� ������� 

$info = getimagesize($f);

if ( $info['mime'] == 'image/bmp' )
	$src = ImageCreateFromBMP($f);	
else
{
	if ( $imageType != 'gif' )
		$src = imagecreatefromjpeg($f); 
	else
	{
		$src = imagecreatefromgif($f); 
	}
}

$w_src = imagesx($src); 
$h_src = imagesy($src);

header("Content-type: image/jpeg"); 

// ���� ������ ��������� ����������� 
// ���������� �� ���������� ������� 
if ($w_src > $w) 
{
   // �������� ��� ��������� �������������� ����� 
   if ($type==2) 
   { 
       // ���������� ��������� 
       $ratio = $w_src/$w; 
       $w_dest = round($w_src/$ratio); 
       $h_dest = round($h_src/$ratio); 

       // ������ ������ �������� 
       // ����� ������ truecolor!, ����� ����� ����� 8-������ ��������� 
       $dest = imagecreatetruecolor($w_dest,$h_dest); 
       $str = '';
       imagecopyresized($dest, $src, 0, 0, 0, 0, $w_dest, $h_dest, $w_src, $h_src); 

      // ���������� ���������� ������ ������ 
        $size = 2; // ������ ������ 
        $x_text = $w_dest-imagefontwidth($size)*strlen($str)-3; 
        $y_text = $h_dest-imagefontheight($size)-3; 

        // ���������� ����� ������ �� ����� ���� �������� ����� 
        $white = imagecolorallocate($dest, 255, 255, 255); 
        $black = imagecolorallocate($dest, 0, 0, 0); 
        $gray = imagecolorallocate($dest, 127, 127, 127); 
        if (imagecolorat($dest,$x_text,$y_text)>$gray) $color = $black; 
        if (imagecolorat($dest,$x_text,$y_text)<$gray) $color = $white; 

        // ������� ����� 
        imagestring($dest, $size, $x_text-1, $y_text-1, $str,$white-$color); 
        imagestring($dest, $size, $x_text+1, $y_text+1, $str,$white-$color); 
        imagestring($dest, $size, $x_text+1, $y_text-1, $str,$white-$color); 
        imagestring($dest, $size, $x_text-1, $y_text+1, $str,$white-$color); 

        imagestring($dest, $size, $x_text-1, $y_text,   $str,$white-$color); 
        imagestring($dest, $size, $x_text+1, $y_text,   $str,$white-$color); 
        imagestring($dest, $size, $x_text,   $y_text-1, $str,$white-$color); 
        imagestring($dest, $size, $x_text,   $y_text+1, $str,$white-$color); 

        imagestring($dest, $size, $x_text,   $y_text,   $str,$color); 
    } 
  // �������� ��� ��������� ����������� ����� 
    if (($type==0)||($type==1)) 
    { 
         // ������ ������ ���������� �������� 
         // ����� ������ truecolor!, ����� ����� ����� 8-������ ��������� 
         $dest = imagecreatetruecolor($w,$w); 

         // �������� ���������� ��������� �� x, ���� ���� �������������� 
         if ($w_src>$h_src) 
         imagecopyresized($dest, $src, 0, 0,
                          round((max($w_src,$h_src)-min($w_src,$h_src))/2),
                          0, $w, $w, min($w_src,$h_src), min($w_src,$h_src)); 

         // �������� ���������� �������� �� y, 
         // ���� ���� ������������ (���� ����� ���� ���������) 
         if ($w_src<$h_src) 
         imagecopyresized($dest, $src, 0, 0, 0, 0, $w, $w,
                          min($w_src,$h_src), min($w_src,$h_src)); 

         // ���������� �������� �������������� ��� ������� 
         if ($w_src==$h_src) 
         imagecopyresized($dest, $src, 0, 0, 0, 0, $w, $w, $w_src, $w_src); 
     } 

	// ����� �������� � ������� ������ 
	imagejpeg($dest,'',$q); 
	imagedestroy($dest); 
	imagedestroy($src); 
} 
else
{
	imagejpeg($src,'',$q); 
	imagedestroy($dest); 
	imagedestroy($src); 
}

?>
