<table border=0 cellspacing=0 cellpadding=0 width=100%>
<tr>
	<td>
	<table width="<?=( !$isIndexSec ) ? 700 : 500;?>" border=0 cellspacing=0 cellpadding=0>

<?
//	if ( $resClaimsCount > $currSearchClaimsPerPage )
	if ( $currSecName != 'notice' )
	{
?>

	<tr>
		<td>
		<table border=0 width=100% cellpadding=0 cellspacing=0>
		<tr>
			<td align=left width=200>
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
	
	<tr><td><img src="images/spacer.gif" height="5" width="100%"></td></tr>

<?
	}
?>


<?
	if ( $pageCount > 1 )
	{
?>
	<tr><td align=<?=($isIndexSec) ? 'center': 'right';?>><?=$pageNumbersStr;?></td></tr>
<?
	}
?>

<?
	if ( $currSecName != 'notice' )
	{
?>

	<tr><td><img src="images/spacer.gif" height="10" width="100%"></td></tr>

	<tr><td bgcolor="#00518f"><img src="images/spacer.gif" height="2"></td></tr>

<?
	}
?>

	<tr>
		<td <?=($isIndexSec) ? 'align=center': '';?>>

<?
	//print('111');
	
	if ( ( substr( $currSecName, 0, 3 ) == 'ipc' || $currSecName == 'all' ) && !$isIndexSec )
	{

		if ( $currAction == 'viewbul' )
			$detailStr = '&dbname='.$currDbName;

		$basket_check_str = '<font class="viennacat2">'.$LANG_SETTINGS['basket']['tobasket'].'</font>&nbsp;'.
							'<input ###checked### type="checkbox" class="viennacat2" onclick="javascript: basketAction(this,\''.$currDbName.'\',###IDCLAIM###);">';

		if ( substr( $currDbName, 0, 3 ) == 'inv' )
			include('incs/restables/reslisttab_allinv.php.inc');
		elseif ( $currDbName == 'tmc' )
			include('incs/restables/reslisttab_tm.php.inc');
		else
			include('incs/restables/reslisttab_'.$currDbName.'.php.inc');
	}
	elseif ( $isIndexSec )
	{
		if ( substr( $currDbName, 0, 3 ) == 'inv' )
			$dbn = 'inv';
		else
			$dbn = $currDbName;
			
		if ( $currSecName != 'notice' )
			include('incs/restables/reslistindextab_all'.$dbn.'.php.inc');
		else
		{
			if ( substr( $currDbName, 0, 3 ) == 'inv' )
				include('incs/restables/reslisttab_inv_notice.php.inc');
			else
				include('incs/restables/reslisttab_allnotice.php.inc');
		}
	}
	
?>
	
		</td>
	</tr>	

<?
	if ( $currSecName != 'notice' )
	{
?>

	<tr><td bgcolor="#00518f"><img src="images/spacer.gif" height="2"></td></tr>
		
	<tr><td><img src="images/spacer.gif" height="10" width="100%"></td></tr>
<?
	}
?>


<?
	if ( $pageCount > 1 )
	{
?>
	<tr><td align=<?=($isIndexSec) ? 'center': 'right';?>><?=$pageNumbersStr;?></td></tr>
<?
	}
?>

    </table>
	</td>
</tr>
</table>
