<table border=0 width=100% height=100 cellpadding=3 cellspacing=0>

<?
	for($i = 0; $i < count( $searchShortBiblioSet ); $i++)
	{
		$row = $searchShortBiblioSet[$i];
		//print_r($row);

		$row['fi_72'] = str_replace('###inv###', '; ', $row['fi_72']);
		$row['fi_73'] = str_replace('###prop###', '; ', $row['fi_73']);
		$row['fi_51'] = str_replace('###mkpz###', ', ', $row['fi_51']);

		$row['fi_21'] = textBlink($currDbName, $row['fi_21'], 'NC', false);
		$row['fi_54'] = textBlink($currDbName, $row['fi_54'], 'TITLE', false);
		$row['fi_72'] = textBlink($currDbName, $row['fi_72'], 'AUTH', false);
		$row['fi_73'] = textBlink($currDbName, $row['fi_73'], 'PROP', false);
		$row['fi_51'] = textBlink($currDbName, $row['fi_51'], 'MKPZ', false);
		
		$publication = $LANG_SETTINGS['res']['publ'];
		$publication = str_replace('%1', '<b>'.$row['bullDate'].'</b>', $publication);		
		$publication = str_replace('%2', '<b>'.$row['bulletinNumber'].'</b>', $publication);		
			
		$rowVariantInfo = $variantInfo[$row['idClaim']];
		
		$imagePath = 'tempdocs/'.'pp_'.$rowVariantInfo[0]['idVariant'].'-1s.jpg';
		if ( file_exists($imagePath) )
		$imageData = getimagesize($imagePath);

		$width = $imageData[0];
		$heigth = $imageData[1];

		//print_r($rowVariantInfo);
		//print('<br>');
		
		$statusImg = 'images/green.gif';
		$statusStr = $LANG_SETTINGS['pp_fields']['patenton'];
		if ( !empty( $row['fi_14'] ) )
		{
		 	$statusImg = 'images/red.gif';	
			$statusStr = $LANG_SETTINGS['pp_fields']['patentoff'];
		}
		
		$bcs = $basket_check_str;
		$bcs = str_replace('###IDCLAIM###', $row['idClaim'], $bcs);				

		if ( in_array($row['idClaim'], $currBasketIds) )
			$bcs = str_replace('###checked###', 'checked', $bcs);	

?>

<tr>
	<td class="resnumbcell"><a class="viennacatwhiteunder" href="search.php?action=viewdetails<?=$detailStr;?>&IdClaim=<?=$row['idClaim'];?>"><?=($i+$startId);?></a></td>
	<td class="restitlecell">
		<table border=0 width=100% cellpadding=0 cellspacing=0>
		<tr>
			<td><a href="search.php?action=viewdetails<?=$detailStr;?>&IdClaim=<?=$row['idClaim'];?>" class="pageHeaderText"><?=$row['fi_54'];?></a></td>
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
				<?=(!$isUEFA) ? $bcs : '';?>

				<?
				if ( isDiskBul == 'no' )
				{
				?>
				<font class="viennacat">|</font>
				<font class="viennacat2"><?=$statusStr;?></font>
				<?
				}
				?>
			</td>

			<?
			if ( isDiskBul == 'no' )
			{
			?>
			<td width=5><img height=1 width=5 align=top src="images/spacer.gif"></td>
			<td width=14><img height=14 width=14 align=top src="<?=$statusImg;?>"></td>
			<?
			}
			?>

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
			<td width=200>
				<table border=0 height=50 width=100% cellpadding=0 cellspacing=0>
				<tr>
					<td width=35><acronym title="<?=$LANG_SETTINGS['pp_details']['inid11'];?>"><font class="viennacatunder">(11)</font></acronym></td>
					<td valign=middle><font class="pageHeaderText"><?=$row['fi_11'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
		
				<tr>
					<td valign=top><acronym title="<?=$LANG_SETTINGS['pp_details']['inid21'];?>"><font class="viennacatunder">(21)</font></acronym></td>
					<td valign=middle><font class="viennacat2"><?=$row['fi_21'];?></font></td>
				</tr>
		
				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
				<tr>
					<td valign=top><acronym title="<?=$LANG_SETTINGS['pp_details']['inid22'];?>"><font class="viennacatunder">(22)</font></acronym></td>
					<td valign=middle><font class="viennacat2"><?=$row['fi_22'];?></font></td>
				</tr>
		
				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td valign=top><acronym title="<?=$LANG_SETTINGS['pp_details']['inid24'];?>"><font class="viennacatunder">(24)</font></acronym></td>
					<td valign=middle><font class="viennacat2"><?=$row['fi_24'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
				
				<tr>
					<td width=35 valign=top><acronym title="<?=$LANG_SETTINGS['pp_details']['inid51'];?>"><font class="viennacatunder">(51)</font></acronym></td>
					<td valign=middle><font class="pageHeaderText"><?=$row['fi_51'];?></font></td>
				</tr>

				</table>
			</td>
			
			<td width=300>
				<table border=0 width=100% cellpadding=0 cellspacing=0>
				
				<tr>
					<td width=35 valign=top><acronym title="<?=$LANG_SETTINGS['pp_details']['inid72'];?>"><font class="viennacatunder">(72)</font></acronym></td>
					<td valign=middle><font class="viennacat2"><?=$row['fi_72'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
		
				<tr>
					<td width=35 valign=top><acronym title="<?=$LANG_SETTINGS['pp_details']['inid73'];?>"><font class="viennacatunder">(73)</font></acronym></td>
					<td valign=middle><font class="viennacat2"><?=$row['fi_73'];?></font></td>
				</tr>
				</table>
			</td>
	
			<td >
				<table border=0 width=100% cellpadding=0 cellspacing=0>

				<tr>
					<td width=200 valign=top align=center><img src="resize.php?idVariant=<?=$rowVariantInfo[0]['idVariant'];?>&varIndex=1&dbn=<?=$currDbName;?>"></td>
				</tr>
				<tr>
					<td valign=top align=center><font class="viennacat2">1.1</font></td>
				</tr>

				</table>

			</td>
	
		</tr>
	
		<tr><td height=3 colspan=3><img height=3 width=1 src="images/spacer.gif"></td></tr>
		
		<tr>
			<td align=left colspan=2><font class="viennacat2"><?=$publication;?></font></td>
			<td align=right><a class="info" href="search.php?action=viewdetails<?=$detailStr;?>&IdClaim=<?=$row['idClaim'];?>"><?=$LANG_SETTINGS['details']['details'];?>...</a>&nbsp;</td>
		</tr>		

		<tr><td height=3 colspan=3><img height=3 width=1 src="images/spacer.gif"></td></tr>
		
		</table>
	</td>
</tr>

<?
	} // end for
?>
</table>
