<table border=0 class="maintable" width="100%" height=680 cellspacing=0 cellpadding=0>
<tr>
<td valign=top>

<form name="main" id="viewbul" method="post" action="">

<table border=0 cellspacing=0 cellpadding=5 width=100%>
<tr>
<td>

<table border=0 cellspacing=0 cellpadding=3 width=100%>
<tr>
	<td>

	<table border=0	cellspacing=0 cellpadding=0 width=700>
	<tr>
		<td valign=top><font class="viennacat"><?=strtoupper($currDbTitle);?></font></td>
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
				<select class="inputstyle" style="width:140px; height:20px" name="newviewbulid" onchange="javascript:doAction('viewbul','<?=$currDbName;?>','<?=$currSecName;?>','','');">
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
					if ( isDiskBul == 'no' )
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
		</table>

		</td>
	</tr>
	
	<tr><td width=1 height=5><img height=5 width=1 src="images/spacer.gif"></td></tr>
	<tr><td height=2 bgcolor="#00518f"><img src="images/spacer.gif" height="2" width="100%"></td></tr>
	<tr><td height=5 width=1><img height=5 width=1 src="images/spacer.gif"></td></tr>
		
	<tr>
		<td valign=top align=left>
<?
	if ( empty( $errors ) )	
		include('../searchBul/incs/viewbulresult.php.inc');		
	else
?>		
		<font class="viennacat"><?=strtoupper($errors);?></font>

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

