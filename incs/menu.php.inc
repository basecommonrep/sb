<table width="100%" height="100%" border="0" cellspacing="0" cellpadding="0">
<tr>
	<td valign="top">
	<table border="0" cellspacing="0" cellpadding="0" style="padding-bottom: 2px">
	<tr>
		<td>
<?
	if ( empty($addDbName) )
	{
?>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td><img src="images/but_25.gif" width="132" height="11"></td>
			<td height="11" width="40"><img src="images/but_26.gif" width="40" height="11"></td>
		</tr>
		<tr>
			<td background="images/buttons_29.gif" align="right">
			<table height=40 width="95%" border="0" cellspacing="0" cellpadding="0">

<?
$s = $LANG_SETTINGS['menu']['official'];;
$str = '<a class="viennacat2" href="search.php?action=viewbul&dbname=official">'.$s.'</font>';
//$str = '<a class="viennacat2">'.$s.'</font>';
if ( $currAction == 'viewbul' && $currDbName == 'official' )
	$str = '<font style="text-decoration:underline" class="viennacat2">'.$s.'</font>';
?>

			<tr><td align="right" class="alttext"><p align="left"><?=$str;?></p></td></tr>
			</table>
			</td>
			<td valign="top" background="images/but_30.gif"><img src="images/but_29.gif" width="40" height="17"></td>
		</tr>
		</table>
<?
	} // end if reestrDbName
?>



<?
	if ( empty($addDbName) || ( !empty($addDbName) && $currDbName == 'invc' ) )
	{
?>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td><img src="images/but_25.gif" width="132" height="11"></td>
			<td height="11" width="40"><img src="images/but_26.gif" width="40" height="11"></td>
		</tr>
		<tr>
			<td background="images/buttons_29.gif" align="right">
			<table height=60 width="95%" border="0" cellspacing="0" cellpadding="0">

<?
$s = $LANG_SETTINGS['menu']['invc'];
$str = '<a class="viennacat2" href="search.php?action=viewbul&dbname=invc">'.$s.'</font>';
if ( $currAction == 'viewbul' && $currDbName == 'invc' )
	$str = '<font style="text-decoration:underline" class="viennacat2">'.$s.'</font>';
?>

			<tr><td align="right" class="alttext"><p align="left"><?=$str;?></p></td></tr>
			</table>
			</td>
			<td valign="top" background="images/but_30.gif"><img src="images/but_29.gif" width="40" height="17"></td>
		</tr>
		</table>
<?
	} // end if reestrDbName
?>


<?
	if ( empty($addDbName) )
	{
?>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td><img src="images/but_25.gif" width="132" height="11"></td>
			<td height="11" width="40"><img src="images/but_26.gif" width="40" height="11"></td>
		</tr>
		<tr>
			<td background="images/buttons_29.gif" align="right">
			<table height=50 width="95%" border="0" cellspacing="0" cellpadding="0">

<?
$s = $LANG_SETTINGS['menu']['inv'];
$str = '<a class="viennacat2" href="search.php?action=viewbul&dbname=inv">'.$s.'</font>';
if ( $currAction == 'viewbul' && $currDbName == 'inv' )
	$str = '<font style="text-decoration:underline" class="viennacat2">'.$s.'</font>';
?>

			<tr><td align="right" class="alttext"><p align="left"><?=$str;?></p></td></tr>
			</table>
			</td>
			<td valign="top" background="images/but_30.gif"><img src="images/but_29.gif" width="40" height="17"></td>
		</tr>
		</table>
<?
	} // end if reestrDbName
?>
		
<?
	if ( empty($addDbName) && isDiskBul == 'no' )
	{
?>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td><img src="images/but_25.gif" width="132" height="11"></td>
			<td height="11" width="40"><img src="images/but_26.gif" width="40" height="11"></td>
		</tr>
		<tr>
			<td background="images/buttons_29.gif" align="right">
			<table height=50 width="95%" border="0" cellspacing="0" cellpadding="0">

<?
$s = $LANG_SETTINGS['menu']['invd'];
$str = '<a class="viennacat2" href="search.php?action=viewbul&dbname=invd">'.$s.'</font>';
if ( $currAction == 'viewbul' && $currDbName == 'invd' )
	$str = '<font style="text-decoration:underline" class="viennacat2">'.$s.'</font>';
?>

			<tr><td align="right" class="alttext"><p align="left"><?=$str;?></p></td></tr>
			</table>
			</td>
			<td valign="top" background="images/but_30.gif"><img src="images/but_29.gif" width="40" height="17"></td>
		</tr>
		</table>
<?
	} // end if reestrDbName
?>

<?
	if ( empty($addDbName) )
	{
?>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td><img src="images/but_25.gif" width="132" height="11"></td>
			<td height="11" width="40"><img src="images/but_26.gif" width="40" height="11"></td>
		</tr>
		<tr>
			<td background="images/buttons_29.gif" align="right">
			<table height=50 width="95%" border="0" cellspacing="0" cellpadding="0">

<?
$s = $LANG_SETTINGS['menu']['invdu'];
$str = '<a class="viennacat2" href="search.php?action=viewbul&dbname=invdu">'.$s.'</font>';
if ( $currAction == 'viewbul' && $currDbName == 'invdu' )
	$str = '<font style="text-decoration:underline" class="viennacat2">'.$s.'</font>';
?>

			<tr><td align="right" class="alttext"><p align="left"><?=$str;?></p></td></tr>
			</table>
			</td>
			<td valign="top" background="images/but_30.gif"><img src="images/but_29.gif" width="40" height="17"></td>
		</tr>
		</table>
<?
	} // end if reestrDbName
?>

<?
	if ( empty($addDbName) || ( !empty($addDbName) && $currDbName == 'pp' ))
	{
?>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td><img src="images/but_25.gif" width="132" height="11"></td>
			<td height="11" width="40"><img src="images/but_26.gif" width="40" height="11"></td>
		</tr>
		<tr>
			<td background="images/buttons_29.gif" align="right">
			<table height=50 width="95%" border="0" cellspacing="0" cellpadding="0">

<?
$s = $LANG_SETTINGS['menu']['pp'];
$str = '<a class="viennacat2" href="search.php?action=viewbul&dbname=pp">'.$s.'</font>';
if ( $currAction == 'viewbul' && $currDbName == 'pp' )
	$str = '<font style="text-decoration:underline" class="viennacat2">'.$s.'</font>';
?>

			<tr><td align="right" class="alttext"><p align="left"><?=$str;?></p></td></tr>
			</table>
			</td>
			<td valign="top" background="images/but_30.gif"><img src="images/but_29.gif" width="40" height="17"></td>
		</tr>
		</table>
<?
	} // end if reestrDbName
?>
		
<?
	if ( empty($addDbName) || ( !empty($addDbName) && $currDbName == 'tm' ))
	{
?>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td><img src="images/but_25.gif" width="132" height="11"></td>
			<td height="11" width="40"><img src="images/but_26.gif" width="40" height="11"></td>
		</tr>
		<tr>
			<td background="images/buttons_29.gif" align="right">
			<table height=60 width="95%" border="0" cellspacing="0" cellpadding="0">

<?
$s = $LANG_SETTINGS['menu']['tm'];;
$str = '<a class="viennacat2" href="search.php?action=viewbul&dbname=tm">'.$s.'</font>';
if ( $currAction == 'viewbul' && $currDbName == 'tm' )
	$str = '<font style="text-decoration:underline" class="viennacat2">'.$s.'</font>';
?>

			<tr><td align="right" class="alttext"><p align="left"><?=$str;?></p></td></tr>
			</table>
			</td>
			<td valign="top" background="images/but_30.gif"><img src="images/but_29.gif" width="40" height="17"></td>
		</tr>
		</table>
<?
	} // end if reestrDbName
?>


<?
	if ( $currDbName == 'tmc' )
	{
?>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td><img src="images/but_25.gif" width="132" height="11"></td>
			<td height="11" width="40"><img src="images/but_26.gif" width="40" height="11"></td>
		</tr>
		<tr>
			<td background="images/buttons_29.gif" align="right">
			<table height=60 width="95%" border="0" cellspacing="0" cellpadding="0">

<?
$s = $LANG_SETTINGS['menu']['tmc'];;
$str = '<a class="viennacat2" href="search.php?action=viewbul&dbname=tmc">'.$s.'</font>';
if ( $currAction == 'viewbul' && $currDbName == 'tmc' )
	$str = '<font style="text-decoration:underline" class="viennacat2">'.$s.'</font>';
?>

			<tr><td align="right" class="alttext"><p align="left"><?=$str;?></p></td></tr>
			</table>
			</td>
			<td valign="top" background="images/but_30.gif"><img src="images/but_29.gif" width="40" height="17"></td>
		</tr>
		</table>
<?
	} // end if reestrDbName
?>

<!--
<?
	if ( empty($addDbName) )
	{
?>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td><img src="images/but_25.gif" width="132" height="11"></td>
			<td height="11" width="40"><img src="images/but_26.gif" width="40" height="11"></td>
		</tr>
		<tr>
			<td background="images/buttons_29.gif" align="right">
			<table height=65 width="95%" border="0" cellspacing="0" cellpadding="0">

<?
$s = $LANG_SETTINGS['menu']['madrid'];
$str = '<a class="viennacat2" href="search.php?action=viewbul&dbname=madrid">'.$s.'</font>';
if ( $currAction == 'viewbul' && $currDbName == 'madrid' )
	$str = '<font style="text-decoration:underline" class="viennacat2">'.$s.'</font>';
?>

			<tr><td align="right" class="alttext"><p align="left"><?=$str;?></p></td></tr>
			</table>
			</td>
			<td valign="top" background="images/but_30.gif"><img src="images/but_29.gif" width="40" height="17"></td>
		</tr>
		</table>
<?
	} // end if reestrDbName
?>
--> 

<?
	if ( empty($addDbName) || ( !empty($addDbName) && $currDbName == 'wkm' ))
	{
?>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td><img src="images/but_25.gif" width="132" height="11"></td>
			<td height="11" width="40"><img src="images/but_26.gif" width="40" height="11"></td>
		</tr>
		<tr>
			<td background="images/buttons_29.gif" align="right">
			<table height=45 width="95%" border="0" cellspacing="0" cellpadding="0">

<?
$s = $LANG_SETTINGS['menu']['wkm'];;
$str = '<a class="viennacat2" href="search.php?action=viewbul&dbname=wkm">'.$s.'</font>';
if ( $currAction == 'viewbul' && $currDbName == 'wkm' )
	$str = '<font style="text-decoration:underline" class="viennacat2">'.$s.'</font>';
?>

			<tr><td align="right" class="alttext"><p align="left"><?=$str;?></p></td></tr>
			</table>
			</td>
			<td valign="top" background="images/but_30.gif"><img src="images/but_29.gif" width="40" height="17"></td>
		</tr>
		</table>

<?
	} // end if reestrDbName
?>


<?
	if ( empty($addDbName) and false)
	{
?>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td><img src="images/but_25.gif" width="132" height="11"></td>
			<td height="11" width="40"><img src="images/but_26.gif" width="40" height="11"></td>
		</tr>
		<tr>
			<td background="images/buttons_29.gif" align="right">
			<table height=45 width="95%" border="0" cellspacing="0" cellpadding="0">

<?
$s = $LANG_SETTINGS['menu']['geo'];;
$str = '<a class="viennacat2" href="search.php?action=viewbul&dbname=geo">'.$s.'</font>';
if ( $currAction == 'viewbul' && $currDbName == 'geo' )
	$str = '<font style="text-decoration:underline" class="viennacat2">'.$s.'</font>';
?>

			<tr><td align="right" class="alttext"><p align="left"><?=$str;?></p></td></tr>
			</table>
			</td>
			<td valign="top" background="images/but_30.gif"><img src="images/but_29.gif" width="40" height="17"></td>
		</tr>
		</table>

<?
	} // end if reestrDbName
?>

<?
	if ( empty($addDbName) )
	{
?>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td><img src="images/but_25.gif" width="132" height="11"></td>
			<td height="11" width="40"><img src="images/but_26.gif" width="40" height="11"></td>
		</tr>
		<tr>
			<td background="images/buttons_29.gif" align="right">
			<table height=50 width="95%" border="0" cellspacing="0" cellpadding="0">

<?
$s = $LANG_SETTINGS['menu']['invc'];
$str = '<a class="viennacat2" href="search.php?action=viewbul&dbname=invc">'.$s.'</font>';
if ( $currAction == 'viewbul' && $currDbName == 'invc' )
	$str = '<font style="text-decoration:underline" class="viennacat2">'.$s.'</font>';
	
	
$s = '<font class="viennacat2">'.$LANG_SETTINGS['menu']['notice'].':'.'</font><BR>';

$str = '<font class="info2">-&nbsp;</font><a class="info2" href="search.php?action=viewnotices&dbname=inv">'.$LANG_SETTINGS['notice']['inv'].'</a>';
if ( $currDbName == 'inv' && $currAction == 'viewnotices' )
	$str = '<font class="info2">-&nbsp;</font><font style="text-decoration:underline" class="info2">'.$LANG_SETTINGS['notice']['inv'].'</font>';

$s .= $str.'<BR>';

$str = '<font class="info2">-&nbsp;</font><a class="info2" href="search.php?action=viewnotices&dbname=invdu">'.$LANG_SETTINGS['notice']['invdu'].'</a>';
if ( $currDbName == 'invdu' && $currAction == 'viewnotices' )
	$str = '<font class="info2">-&nbsp;</font><font style="text-decoration:underline" class="info2">'.$LANG_SETTINGS['notice']['invdu'].'</font>';


$s .= $str.'<BR>';

$str = '<font class="info2">-&nbsp;</font><a class="info2" href="search.php?action=viewnotices&dbname=pp">'.$LANG_SETTINGS['notice']['pp'].'</a>';
if ( $currDbName == 'pp' && $currAction == 'viewnotices' )
	$str = '<font class="info2">-&nbsp;</font><font style="text-decoration:underline" class="info2">'.$LANG_SETTINGS['notice']['pp'].'</font>';

$s .= $str.'<BR>';
//----------------notices pp2 -test

$str = '<font class="info2">-&nbsp;</font><a class="info2" href="search.php?action=viewnotices&dbname=pp2">'.$LANG_SETTINGS['notice']['pp2'].'</a>';
if ( $currDbName == 'pp2' && $currAction == 'viewnotices' )
	$str = '<font class="info2">-&nbsp;</font><font style="text-decoration:underline" class="info2">'.$LANG_SETTINGS['notice']['pp2'].'</font>';

//$s .= $str.'<BR>'; 
//----------------

$str = '<font class="info2">-&nbsp;</font><a class="info2" href="search.php?action=viewnotices&dbname=tm">'.$LANG_SETTINGS['notice']['tm'].'</a>';
if ( $currDbName == 'tm' && $currAction == 'viewnotices' )
	$str = '<font class="info2">-&nbsp;</font><font style="text-decoration:underline" class="info2">'.$LANG_SETTINGS['notice']['tm'].'</font>';

$s .= $str.'<BR>';

//----------------notices tm2 -test

$str = '<font class="info2">-&nbsp;</font><a class="info2" href="search.php?action=viewnotices&dbname=tm2">'.$LANG_SETTINGS['notice']['tm2'].'</a>';
if ( $currDbName == 'tm2' && $currAction == 'viewnotices' )
	$str = '<font class="info2">-&nbsp;</font><font style="text-decoration:underline" class="info2">'.$LANG_SETTINGS['notice']['tm2'].'</font>';

//$s .= $str.'<BR>'; //закоменчено ввиду изм пор€дка актуализации, смены е–еестра, доработки по рез тестир за год
//----------------


$str = '<font class="info2">-&nbsp;</font><a class="info2" href="search.php?action=viewnotices&dbname=madrid">'.$LANG_SETTINGS['notice']['madrid'].'</a>';
if ( $currDbName == 'madrid' && $currAction == 'viewnotices' )
	$str = '<font class="info2">-&nbsp;</font><font style="text-decoration:underline" class="info2">'.$LANG_SETTINGS['notice']['madrid'].'</font>';


$s .= $str;	
$str = $s;

?>

			<tr><td align="right" class="alttext"><p align="left"><?=$str;?></p></td></tr>
			</table>
			</td>
			<td valign="top" background="images/but_30.gif"><img src="images/but_29.gif" width="40" height="17"></td>
		</tr>
		</table>
<?
	} // end if reestrDbName
?>

		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td><img src="images/but_25.gif" width="132" height="11"></td>
			<td height="11" width="40"><img src="images/but_26.gif" width="40" height="11"></td>
		</tr>
		<tr>
			<td background="images/buttons_29.gif" align="right">
			<table width="95%" border="0" cellspacing="0" cellpadding="0">
<?

$s = $LANG_SETTINGS['menu'][0];

$str = '<a class="viennacat2" href="search.php?action=setsearchconditions">'.$s.'</a>';
if ( $currAction == 'setsearchcond' || $currAction == 'changedb' || ( $currAction == 'search' && !empty($errors)) )
	$str = '<font style="text-decoration:underline" class="viennacat2">'.$s.'</font>';

?>

			<tr><td align="right" class="alttext"><p align="left"><?=$str;?></p></td></tr>
			</table>
			</td>
			<td valign="top" background="images/but_30.gif"><img src="images/but_29.gif" width="40" height="17"></td>
		</tr>
		</table>

		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td><img src="images/but_25.gif" width="132" height="11"></td>
			<td height="11" width="40"><img src="images/but_26.gif" width="40" height="11"></td>
		</tr>
		<tr>
			<td background="images/buttons_29.gif" align="right">
			<table height=40 width="95%" border="0" cellspacing="0" cellpadding="0">

<?
$s = $LANG_SETTINGS['menu'][1].'&nbsp;('.(int)count($lastSearchIds).')';

if ( $currAction == 'viewsearchres' || ( $currAction == 'search' && count($lastSearchIds) > 0 && empty($errors) ) )
	$str = '<font style="text-decoration:underline" class="viennacat2">'.$s.'</a>';
elseif ( count($lastSearchIds) === 0 )
	$str = '<font style="color:#5b7288" class="viennacat2">'.$s.'</font>';
else
	$str = '<a class="viennacat2" href="search.php?action=viewsearchres">'.$s.'</a>';

?>

			<tr><td align="right" class="alttext"><p align="left"><?=$str;?></p></td></tr>
			</table>
			</td>
			<td valign="top" background="images/but_30.gif"><img src="images/but_29.gif" width="40" height="17"></td>
		</tr>
		</table>



		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td><img src="images/but_25.gif" width="132" height="11"></td>
			<td height="11" width="40"><img src="images/but_26.gif" width="40" height="11"></td>
		</tr>
		<tr>
			<td background="images/buttons_29.gif" align="right">
			<table height=30 width="95%" border="0" cellspacing="0" cellpadding="0">

<?
if ( $currAction == 'viewbasket' && $_SESSION['basketItemsCount'] > 0 )
	$str = '<a style="text-decoration:underline" id="basketHref" class="viennacat2">'.$LANG_SETTINGS['basket']['basket'].'&nbsp;(<font id="basketCount">'.(int)$_SESSION['basketItemsCount'].'</font>)</a>';
elseif ( $_SESSION['basketItemsCount'] === 0 )
	$str = '<a id="basketHref" class="viennacat2not">'.$LANG_SETTINGS['basket']['basket'].'&nbsp;(<font class="viennacat2not" id="basketCount">'.(int)$_SESSION['basketItemsCount'].'</font>)</a>';
else
	$str = '<a class="viennacat2" id="basketHref" href="basket.php?action=viewbasket">'.$LANG_SETTINGS['basket']['basket'].'&nbsp;(<font id="basketCount">'.(int)$_SESSION['basketItemsCount'].'</font>)</a>';

?>

			<tr><td align="right" class="alttext"><p align="left"><?=$str;?></p></td></tr>
			</table>
			</td>
			<td valign="top" background="images/but_30.gif"><img src="images/but_29.gif" width="40" height="17"></td>
		</tr>
		</table>


		<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td><img src="images/but_25.gif" width="132" height="11"></td>
			<td height="11" width="40"><img src="images/but_26.gif" width="40" height="11"></td>
		</tr>
		<tr>
			<td background="images/buttons_29.gif" align="right">
			<table height=30 width="95%" border="0" cellspacing="0" cellpadding="0">

<?
$s = $LANG_SETTINGS['help']['help'];

if ( $currAction == 'viewhelp' )
	$str = '<a href="search.php?action=viewhelp"><font style="text-decoration:underline" class="viennacat2">'.$s.'</a>';
else
	$str = '<a class="viennacat2" href="search.php?action=viewhelp">'.$s.'</a>';

?>

			<tr><td align="right" class="alttext"><p align="left"><?=$str;?></p></td></tr>
			</table>
			</td>
			<td valign="top" background="images/but_30.gif"><img src="images/but_29.gif" width="40" height="17"></td>
		</tr>
		</table>

		</td>
	</tr>



	</table>
	</td>
</tr>
</table>

