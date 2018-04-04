<table border=0 width=100% height=100 cellpadding=3 cellspacing=0>

<?
	
	for($i = 0; $i < count( $searchShortBiblioSet ); $i++)
	{
		$row = $searchShortBiblioSet[$i];
		
		$bcs = $basket_check_str;
		$bcs = str_replace('###IDCLAIM###', $row['id'], $bcs);
		
?>

<tr>
	<td class="resnumbcell"><?=($i+$startId);?></td>
	<td class="restitlecell" height=20>
		<table border=0 width=100% cellpadding=0 cellspacing=0>
		<tr>
			<td>
      <a href="search.php?action=viewdetails<?=$detailStr;?>&IdIdClaim=<?=$row['id'];?>" class="pageHeaderText"><?=$row['indication'];?></a>
      </td>
		</tr>
		</table>
	</td>
</tr>

<tr>
	<td height=10>&nbsp;</td>
	<td class="resbibliostatuscell">
		<table border=0 height=100% width=100% cellpadding=0 cellspacing=0>
		<tr>
			<td align=right>
				<?=$bcs;?>
			</td>
		</tr>
		</table>
	</td>
</tr>


<tr>
	<td>&nbsp;</td>
	<td class="resbibliocell">
		<table border=0 height=100% width=100% cellpadding=0 cellspacing=0>
		<tr><td height=3 colspan=2><img height=3 width=1 src="images/spacer.gif"></td></tr>
	
		<tr valign=top>
			<td>
				<table width=650 border=0 height=50 width=100% cellpadding=0 cellspacing=0>
				<tr>
					<td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['geo_fields']['NP'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td width=20><img height=1 width=20 src="images/spacer.gif"></td>
					<td width=580><font class="viennacat2"><?=$row['reg_number'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['geo_fields']['REGD'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td><img height=1 width=20 src="images/spacer.gif"></td>
					<td><font class="viennacat2"><?=$row['reg_date'];?></font></td>
				</tr>
		
				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['geo_fields']['GOODNAME'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td><img height=1 width=20 src="images/spacer.gif"></td>
					<td><font class="viennacat2"><?=$row['indication'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['geo_fields']['KZPNAME'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td><img height=1 width=20 src="images/spacer.gif"></td>
					<td><font class="viennacat2"><?=$row['product_name'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
        
        <tr>
					<td colspan=2 align=right>
          <a href="search.php?action=viewdetails<?=$detailStr;?>&IdClaim=<?=$row['id'];?>" class="info"><?=$LANG_SETTINGS['details']['details'];?></a>
          </td>
				</tr>
				
				</tr>
				</table>
			</td>
			
		</tr>
	
		<tr><td height=3 colspan=2><img height=3 width=1 src="images/spacer.gif"></td></tr>
		
		</table>
	</td>
</tr>

<?
	} // end for
?>
</table>
