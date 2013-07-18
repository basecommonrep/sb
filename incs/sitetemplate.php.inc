<?
	$printed = ($_GET['print'] == 'yes') ? true : false;
	
	$ids_name = $LANG_SETTINGS['interface']['IDS'];
	if ( !empty($addDbName) )
		$ids_name = $LANG_SETTINGS['interface'][$currDbName.'_'.$addDbName];
?>

<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=windows-1251">
	<title><?=$ids_name;?></title>
	<link rel="stylesheet" type="text/css" href="images/st_all.css">
	<link rel="stylesheet" type="text/css" href="images/css_ie.css">
	<SCRIPT language=JavaScript src="images/search.js"></SCRIPT>
	<SCRIPT language=JavaScript src="images/myajax/yahoo.js"></SCRIPT>
	<SCRIPT language=JavaScript src="images/myajax/event.js"></SCRIPT>
	<SCRIPT language=JavaScript src="images/myajax/connection.js"></SCRIPT>
</head>

<body topmargin=0 leftmargin=0>

<table border=0 cellspacing=0 cellpadding=0 id=tblWorkingMsg style="display:none; position:absolute;">
<tr>
	<td><img src="images/indicator.gif"></td>
</tr>
</table>

<table width="100%" border=0 cellspacing=0 cellpadding=0>
<tr>
<td colspan=2>

	<table width="100%" border="0" cellspacing="0" cellpadding="0">

<?
	if ( !$printed )
	{
?>

	<tr>
		<td width="167"><img src="images/top_01.jpg" width="167" height="63"></td>
		<td width="171"><img src="images/top_02.jpg" width="171" height="63"></td>
		<td>
	
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td width="207"><img src="images/top1_03.jpg" width="207" height="63"></td>
	    	<td background="images/top_bg_large_05.jpg"><img src="images/top1_04.jpg" width="1" height="63"></td>
	    </tr>
		</table>
	
		</td>
	</tr>
	
	<tr>
		<td><img src="images/top_05.jpg" width="167" height="48"></td>
		<td><img src="images/top_ua_07.jpg" width="171" height="48"></td>
		<td valign="top">
		<table width="100%" border="0" cellspacing="0" cellpadding="0" height="48">
		<tr>
			<td background="images/bg_search_08.gif" align="right" style="background-repeat: no-repeat" bgcolor="#DBE6F0">
			<table border="0" cellspacing="0" cellpadding="0">
			<tr>
<?
	$ca = $currAction;
	if ($currAction == 'search' )
		$ca = 'viewsearchres';

if (($currDbName=='tm2') || ($currDbName=='pp2'))
{ $currFieldName=$NReg; //fname
  $currFullBiblioChapter=$PROP; //chapter
}

	$langStr = "'$ca','$currPage','$currSecName','$currDbName','$currFullBiblioChapter','$currFieldName','{$_GET['from']}','".$currSortField."_".$currSortOrder."'";

	if ( $_SESSION['lastLang'] == 'ukr' )
	{ //print('<BR><BR>'.$langStr.'<BR><BR>');
?>

		<td valign="bottom" width="44"><img src="images/b_uk_ov_12.gif" width="44" height="14" border="0"></td>

<?
	}
	else
	{
?>	
		<td valign="bottom" width="44"><a href="javascript:void(0);" onclick="javascript:setlang('ukr',<?=$langStr;?>); return false;"><img src="images/b_uk_12.gif" width="44" height="14" border="0"></a></td>

<?
	}
	
	if ( $_SESSION['lastLang'] == 'rus' )
	{
?>
		<td valign="bottom" width="44"><img src="images/b_ru_ov_12.gif" width="44" height="14" border="0"></td>

<?
	}
	else
	{
?>
		<td valign="bottom" width="44"><a href="javascript:void(0);" onclick="javascript:setlang('rus',<?=$langStr;?>); return false;"><img src="images/b_ru_12.gif" width="44" height="14" border="0"></a></td>
<?
	}
	
	if ( $_SESSION['lastLang'] == 'eng' )
	{
?>
		<td valign="bottom" width="44"><img src="images/b_en_ov_12.gif" width="44" height="14" border="0"></td>
<?
	}
	else
	{
?>	
		<td valign="bottom" width="44"><a href="javascript:void(0);" onclick="javascript:setlang('eng',<?=$langStr;?>); return false;"><img src="images/b_en_12.gif" width="44" height="14" border="0"></a></td>
<?
	}
?>
			</tr>
			</table>
			</td>
		</tr>
		<tr>
			<td bgcolor="#DBE6F0" align="right">
			<table>
			<tr>
				<td><font class="maintitle"><?=$ids_name;?></font></td>
			</tr>
			</table>
			</td>
		</tr>

		</table>
		</td>

	</tr>
	</table>
</td>
</tr>
<?
	} // printed
?>

<tr>

<?
	if ( !$printed )
	{
?>
	<td background="images/bg_left_33.gif" width="1px" height=100% align=left valign=top>
<?
include('incs/menu.php.inc');
?>	
	</td>
<?
	} // printed
?>


	<td width=100% height=100% bgcolor="<?=(!$printed) ? '#dbe6f0' : '';?>" align=left valign=top>
	<table width=100% border=0 cellspacing=0 cellpadding=0 id="MainTable">
	<tr>
		<td>
<?
	if ( !$printed && !empty($_SESSION['addDbName']) && $currDbName == 'tm' )
	{
?>

<!--
			<div style="position: absolute; top: 0; right: 0px;">
			<table border=0 cellspacing=0 cellpadding=2 width=70%>
			<tr>
				<td>
					<font style="color: yellow; font-size: 9;" class="info">
					Згідно з розпорядженням Державної служби інтелектуальної власності № 111 від 31 грудня 2008 року, у базі даних 
					&quot;Зареєстровані в Україні знаки для товарів і послуг&quot; виключені із множини раніше установлених критеріїв пошуку наступні поля:
					&quot;віденська класифікація&quot;, &quot;ключові слова&quot;, &quot;власник&quot;, &quot;адресат&quot;.<BR>
					За вилученими критеріями пошук відповідних відомостей можна здійснювати в &quot;БД Електронна версія акумулятивного офіційного бюлетеня &quot;Промислова власність&quot;
					</font>
				</td>
			</tr>
			</table>
			</div>
-->
<?
	} // printed
?>


			<div style="position: absolute; top: 115; left: 176; visibility: hidden" id="Message">
				<font class="viennacat"><?=$LANG_SETTINGS['interface']['wait'];?>...</font>
			</div>

			
<?
$printStr = '?';

if (!empty($currAction))
$printStr .= 'action='.$currAction;

if (!empty($currDbName))
$printStr .= '&dbname='.$currDbName;

if (!empty($currSecName))
$printStr .= '&section='.$currSecName;

if (!empty($currPage))
$printStr .= '&page='.$currPage;

if (!empty($currFullBiblioChapter))
$printStr .= '&chapter='.$currFullBiblioChapter;

if (!empty($idClaim))
$printStr .= '&IdClaim='.$idClaim;

$printStr .= '&print=yes';

switch( $currAction )
{
	case 'setsearchcond':
	case 'changedb':
		include("incs/searchconditiontable.php.inc");
	break;

	case 'viewbul':
		if ( $currDbName != 'official' )
		{
			if ( empty($addDbName) )
				include("incs/viewbulsections.php.inc");
			else	
				include("incs/viewbulsections_reestr.php.inc");
		}
		else
			include("incs/viewofficial.php.inc");
	break;
	
	case 'search':
	case 'viewsearchres':
	case 'sort':
		if ( count( $lastSearchIds ) > 0 && empty( $errors ) )
			include("incs/searchresult.php.inc");
		else
			include("incs/searchconditiontable.php.inc");
	break;
	case 'viewdetails':
			include("incs/viewdetails.php.inc");
	break;	
	
	case 'viewdict':
	case 'searchdict':
			include("incs/dictionarytable.php.inc");
	break;	

	case 'viewbasket':
			include("incs/baskettable.php.inc");
	break;	

	case 'viewhelp':
		include("incs/viewhelp.php.inc");
	break;

	case 'viewnotices':
		include("incs/viewnotices.php.inc");
	break;

}

?>

		</td>
	</tr>
	</table>
	</td>
</tr>

<?
	if ( !$printed )
	{
?>

<tr>
	<td colspan=2> 
	<table width="100%" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td width="167"><img src="images/bot_bg_29.jpg" width="167" height="55"></td>
		<td width="171"><img src="images/bot_30.gif" width="171" height="55"></td>
		<td bgcolor="#DBE6F0">
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td valign="bottom" align="right">
			<table border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td></td>
			</tr>
			</table>
			</td>
			<td width="30"><img src="images/spacer.gif" width="30" height="55"></td>
		</tr>
		</table>
		</td>
	</tr>
	
	<tr>
		<td><img src="images/bot_bg_31.jpg" width="167" height="28"></td>
		<td background="images/bot_32.gif" align="left" valign="top" class="desig"></td>
		<td background="images/bot_34.gif"><img src="images/bot_33.gif" width="160" height="28"></td>
	</tr>
	</table>
	</td>
</tr>
<?
	$T2 = microtime_float();
	$T3 = $T2 - $T1;
	$T4 =' ';
	if (!empty($RecordCount)) $T4 = $RecordCount.' записів ';
	$T6 = ''; if($currAction=='viewnotices') $T6 = 'Notices'; 
	
        //$T5 = CounterIPDB($currDbName.$T6,'N='.$NReg .',P='.$PROP.',B='.$currBulStr);
	print('<tr><td><font size=1>'.substr($T3,0,5).' сек '.$T4.$T5.'</font></td></tr>');

	} // printed
?>


</table>
</html>
