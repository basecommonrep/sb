<table border=0 class="maintable" width="100%" height=730 cellspacing=0 cellpadding=0>
<tr>
<td valign=top>

<form name="main" id="searchbul" method="post" action="">

<table border=0 cellspacing=0 cellpadding=5 width=100%>
<tr>
<td>

<table border=0 cellspacing=0 cellpadding=3 width=100%>
<?

	$h = $LANG_SETTINGS['menu'][$currDbName];
	if ( $isUEFA )
		$h = $LANG_SETTINGS['euro_headers'][$currDbName];
	
	if ( empty($addDbName) )
	{
?>
<tr>
	<td>
	<table border=0 cellspacing=0 cellpadding=0 width=100%>
	<tr>
		<td width=650><font class="viennacat"><?=strtoupper($h);?></font></td>
		<td>&nbsp;</td>
		<td width="25">&nbsp;</td>
	</tr>

	</table>
	</td>
</tr>
<?
	} // end addDbName
?>







<?
	if ( !empty($isUEFA) && ($_GET['dbname'] == 'madridpartners' || $_GET['dbname'] == 'tmpartners') )
	{
?>
<tr>
	<td>
	<table border=0 cellspacing=0 cellpadding=0 width=100%>
	<tr>
		<td colspan=3>
		<img src="sign/image001.gif">&nbsp;
		<img src="sign/image002.gif">&nbsp;
		<img src="sign/image003.gif">&nbsp;
		<img src="sign/image004.gif">&nbsp;
		<img src="sign/image005.gif">&nbsp;
		<img src="sign/image006.gif">&nbsp;
		<img src="sign/image008.gif">&nbsp;						
		<img src="sign/image007.gif">&nbsp;						
		<img src="sign/image009.png">&nbsp;
		<img src="sign/image010.png" width="60">&nbsp;
		</td>
	</tr>

	</table>
	</td>
</tr>
<?
	} // end addDbName
?>

<?
	if ( !empty($isUEFA) && ($_GET['dbname'] == 'tmpartnersnat') )
	{
?>
<tr>
	<td>
	<table border=0 cellspacing=0 cellpadding=0 width=100%>
	<tr>
		<td colspan=3 height="30">
		Творимо історію разом
		</td>
	</tr>
	<tr>
		<td colspan=3>
		<img src="sign/image017.png">&nbsp;
		<img src="sign/image018.png">&nbsp;
		<img src="sign/image019.png">&nbsp;
		</td>
	</tr>

	</table>
	</td>
</tr>
<?
	} // end addDbName
?>




<?
	if ( count( $currSearchIds ) > 0 )
	{
?>
<tr>
	<td>
	<table width="700" border=0 cellspacing=0 cellpadding=0>

	<?
		if ( $currAction != 'viewall' && $_GET['section'] != 'viewall' )
		{
	?>
	<tr>
		<td>
		<table width=100% border=0 cellspacing=0 cellpadding=0>
		<tr>
			<td><font class="viennacat"><?=strtoupper($LANG_SETTINGS['res']['sres']);?></font></td>
		</tr>
		</table>
		</td>
	</tr>
	<?
		}
	?>

	<tr><td><img src="images/spacer.gif" height="5" width="100%"></td></tr>

<?
	if ( $currDbName != 'wkm' && !$isUEFA)
	{
?>
	<tr>
		<td>
		<?
			include('../searchBul/incs/sorttable.php.inc');
		?>
		</td>
	</tr>

	<tr><td><img src="images/spacer.gif" height="5" width="100%"></td></tr>
<?
	} // end if
?>

<?
//	if ( $resClaimsCount > $currSearchClaimsPerPage )
	{
?>

	<tr>
		<td>
		<table border=0 width=100% cellpadding=0 cellspacing=0>
		<tr>
			<td align=left width=350>
			<font class="viennacat2"><?=$LANG_SETTINGS['res']['count'];?></font>
			<font class="viennacat"><?=$startId;?></font>
			<font class="viennacat2">-</font>
			<font class="viennacat"><?=$endId;?></font>
			<font class="viennacat2"><?=$LANG_SETTINGS['res']['of'];?></font>
			<font class="viennacat"><?=$resClaimsCount;?></font>
			</td>
			<td align=right>&nbsp;
			<!--
				<font class="viennacat2">Сортувати за </font>
			-->
			</td>
		</tr>
		</table>
		</td>
	</tr>
	
<?
	}
?>


<?
	if ( $pageCount > 1 )
	{
?>
	<tr><td align=right><?=$pageNumbersStr;?></td></tr>
<?
	}
?>
	<tr><td><img src="images/spacer.gif" height="10" width="100%"></td></tr>

	<tr><td bgcolor="#00518f"><img src="images/spacer.gif" height="2"></td></tr>

	<tr>
		<td>
<?
	$basket_check_str = '<font class="viennacat2">'.$LANG_SETTINGS['basket']['tobasket'].'</font>&nbsp;'.
						'<input ###checked### type="checkbox" class="viennacat2" onclick="javascript: basketAction(this,\''.$currDbName.'\',###IDCLAIM###);">';
	
	$detailStr .= '&dbname='.$currDbName;
	
	//print($currDbName);
	
	if ( substr($currDbName, 0, 3) == 'inv' )
		include('../searchBul/incs/restables/reslisttab_allinv.php.inc');
	elseif ( substr($currDbName, 0, 2) == 'pp' )
		include('../searchBul/incs/restables/reslisttab_pp.php.inc');
	elseif ( substr($currDbName, 0, 2) == 'tm' )
		include('../searchBul/incs/restables/reslisttab_tm.php.inc');
	elseif ( $currDbName == 'madrid' || ( substr($currDbName, 0, 6) == 'madrid' && $currDbName != 'madridall') )
		include('../searchBul/incs/restables/reslisttab_madrid.php.inc');
	/*
	elseif ( $currDbName == 'madrid' )
		include('../searchBul/incs/restables/reslisttab_madrid.php.inc');
	elseif ( substr($currDbName, 0, 6) == 'madrid' )
		include('../searchBul/incs/restables/reslisttab_madrid.php.inc');
	*/
	else
		include('../searchBul/incs/restables/reslisttab_'.$currDbName.'.php.inc');


?>
		</td>
	</tr>	

	<tr><td bgcolor="#00518f"><img src="images/spacer.gif" height="2"></td></tr>

	<tr><td><img src="images/spacer.gif" height="5" width="100%"></td></tr>


<?
	if ( $pageCount > 1 )
	{
?>
	<tr><td align=right><?=$pageNumbersStr;?></td></tr>
<?
	}
?>

    </table>
	</td>
</tr>
<?
	} // isUEFA
	else
	{
		if ( strstr($currDbName, 'partners') )
			$ss = '. комерційних партнерів тимчасово не визначено';
?>
	
	
	<tr><td><font class="viennacat2"><?=$errors.$ss;?></font></td></tr>

<?
	} // else
?>
</table>

</td>
</tr>
</table>
</form>

</td>
</tr>
</table>


