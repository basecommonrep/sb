<?
	$printed = ($_GET['print'] == 'yes') ? true : false;
	
	$ids_name = $LANG_SETTINGS['interface']['IDS'];
	if ( !empty($addDbName) )
		$ids_name = $LANG_SETTINGS['interface'][$currDbName.'_'.$addDbName]
?>

<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=windows-1251">
	<title><?=$ids_name;?></title>
	<link rel="stylesheet" type="text/css" href="images/st_all.css">
	<link rel="stylesheet" type="text/css" href="images/css_ie.css">
</head>

<body topmargin=0 leftmargin=0>
<table border=0 width=100% cellpadding=5 cellspacing=0>
<tr>
	<td>
		<font class="viennacat2">База даних тимчасово не доступна. <BR>Просимо вибачення за незручності.</font>
	</td>
</tr>

</table>
</html>
