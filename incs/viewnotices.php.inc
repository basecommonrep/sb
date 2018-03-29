<table border=0 class="maintable" width="100%" height=820 cellspacing=0 cellpadding=0>
<tr>
<td valign=top>

<form name="main" id="viewbul" method="post" action="">

<table border=0 cellspacing=0 cellpadding=5 width=100%>
<tr>
<td>

<table border=0 cellspacing=0 cellpadding=3 width=100%>
<tr>
	<td>

	<table border=0	cellspacing=0 cellpadding=0 width=100%>
	<tr>
		<td valign=top><font class="viennacat"><?=strtoupper($LANG_SETTINGS['menu']['notice']).'.&nbsp;'.toUpper($LANG_SETTINGS['notice'][$currDbName]);?></font></td>
	</tr>

	<tr><td width=1 height=10><img height=10 width=1 src="images/spacer.gif"></td></tr>
	<tr><td height=2 bgcolor="#00518f"><img src="images/spacer.gif" height="2" width="100%"></td></tr>
	<tr><td height=5 width=1><img height=5 width=1 src="images/spacer.gif"></td></tr>
	
	<tr>
		<td height=20>
		<table width=100% border=0 cellpadding=0 cellspacing=0>
		<tr>
			<td>
				<font class="viennacat2"><?=$LANG_SETTINGS['common_viewparts']['bul'];?></font>&nbsp;
				<select class="inputstyle" style="width:150px; height:20px" name="newviewbulid" onchange="javascript:doAction('viewnotices','<?=$currDbName;?>','<?=$currSecName;?>','','');">
		<? 
		
		while( list($bulId, $bulStr) = each($bulNumbList) )
		{
			$s = ( $currBulId == $bulId ) ? 'selected': '';
			print('<option value="'.$bulId.'" '.$s.'>'.$bulStr.'</option>');
		} 
		?>
				</select>&nbsp;

			</td>



			<td align=right>
				<?
					if ( isDiskBul == 'no' && $currDbName != 'geo' )
					{
				?>
					<font class="viennacat2"><?=$LANG_SETTINGS['interface']['actual2']?>&nbsp;<?=$currActualDate;?></font>&nbsp;
				<?
					} // end isDiskBul
					else
					{
				?>
					&nbsp;
				<?
					}
				?>
				
			</td>
			
		</tr>
<?
if ($currDbName=='tm2' || $currDbName=='pp2') { $predstr=substr($currDbName,0,2);
?>
<tr>
 <td>
	<font class="viennacat2"><?=$LANG_SETTINGS[$predstr.'_fields']['NUMER'];?></font>&nbsp;
	<input type="text" name="NReg" style="width:113px; height:20px">
	
	
 </td>

 <td>
	<font class="viennacat2"><?=$LANG_SETTINGS[$predstr.'_fields']['NAMES'];?></font>&nbsp;
	<input type="text" name="PROP" style="width:270px; height:20px">
	<input type="submit" value="v" style="width:18px; height:20px">
	
 </td>
</tr>
<?
}
?>
		</table>

		</td>
	</tr>
	
	<tr><td width=1 height=5><img height=5 width=1 src="images/spacer.gif"></td></tr>
	<tr><td height=2 bgcolor="#00518f"><img src="images/spacer.gif" height="2" width="100%"></td></tr>
	<tr><td height=5 width=1><img height=5 width=1 src="images/spacer.gif"></td></tr>
		
	<tr>
		<td valign=top align=left>
		<?
			//print('viewnotices ' . $currDbName .'<BR>');
    if ( substr($currDbName, 0, 3) == 'inv' )
      include('../searchBul/incs/restables/reslisttab_inv_notice.php.inc');		
    elseif ($currDbName == 'tm2' || $currDbName == 'pp2')
      include('../searchBul/incs/restables/reslisttab_tm2_notice.php.inc');
    elseif ($currDbName == 'tm' || $currDbName == 'pp' || $currDbName == 'madrid' || $currDbName == 'geo' )
      include('../searchBul/incs/restables/reslisttab_pdf_notice.php.inc');		
		else
      include('../searchBul/incs/restables/reslisttab_allnotice.php.inc');
		?>		

		</td>
	</tr>



	</table>
	</td>
</tr>

</table>

</td>
</tr>
</table>
</form>

</td>
</tr>
</table>

