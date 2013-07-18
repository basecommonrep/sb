<table border=0 width=100% height=100 cellpadding=3 cellspacing=0>

<?
	for($i = 0; $i < count( $searchShortBiblioSet ); $i++)
	{
		$row = $searchShortBiblioSet[$i];
		//print_r($row);

		/*
		$row['fi_732'] = str_replace('###prop###', '; ', $row['fi_732']);
		$row['fi_511'] = str_replace('###mktp###', ', ', $row['fi_511']);
		$row['fi_539'] = str_replace('###keywords###', '; ', $row['fi_539']);
		$row['fi_591'] = str_replace('###colors###', ', ', $row['fi_591']);

		$row['fi_732'] = textBlink($currDbName, $row['fi_732'], 'PROP', false);
		$row['fi_539'] = textBlink($currDbName, $row['fi_539'], 'KEYW', false);
		$row['fi_591'] = textBlink($currDbName, $row['fi_591'], 'COLORS', false);
		*/

		$publication = $LANG_SETTINGS['res']['publ'];
		$publication = str_replace('%1', '<b>'.$row['bulletinDate'].'</b>', $publication);		
		$publication = str_replace('%2', '<b>'.$row['bulletinNumber'].'</b>', $publication);		

		$row['fi_511'] = str_replace(',', ', ', $row['fi_511']);
		$row['fi_511'] = textBlink($currDbName, $row['fi_511'], 'NICE', false);
		$row['fi_540'] = textBlink($currDbName, $row['fi_540'], 'KEYW', false);
		$row['fi_73'] = str_replace('###prop###', '; ', $row['fi_73']);
		
		$bcs = $basket_check_str;
		$bcs = str_replace('###IDCLAIM###', $row['idClaim'], $bcs);				

		if ( in_array($row['idClaim'], $currBasketIds) )
			$bcs = str_replace('###checked###', 'checked', $bcs);	

?>

<tr>
	<td class="resnumbcell"><?=($i+$startId);?></td>
	<td class="restitlecell">
		<table border=0 width=100% cellpadding=0 cellspacing=0>
		<tr>
			<td><font class="pageHeaderText"><?=$row['fi_540'];?></font></td>
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
			</td>


		</tr>
		</table>
	</td>
</tr>

<tr>
	<td>&nbsp;</td>
	<td class="resbibliocell">
		<table border=0 height=100% width=100% cellpadding=0 cellspacing=0>
		<tr><td height=3 colspan=7><img height=3 width=1 src="images/spacer.gif"></td></tr>
	
		<tr valign=top>
			<td width=220>
				<table border=0 width=100% cellpadding=0 cellspacing=0>
				<tr>
					<td width=40 valign=top><acronym title="<?=$LANG_SETTINGS['madrid_fields']['NREG'];?>"><font class="viennacatunder">(111)</font></acronym>&nbsp;</td>
					<td valign=middle><font class="pageHeaderText"><?=$row['fi_111'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
		
				<tr>
					<td valign=top><acronym title="<?=$LANG_SETTINGS['madrid_fields']['DPUBL'];?>"><font class="viennacatunder">(450)</font></acronym>&nbsp;</td>
					<td valign=middle><font class="viennacat2"><?=$row['fi_450'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
		
				<tr>
					<td valign=top><acronym title="<?=$LANG_SETTINGS['madrid_fields']['NICE'];?>"><font class="viennacatunder">(511)</font></acronym>&nbsp;</td>
					<td valign=middle><font class="viennacat"><?=$row['fi_511'];?></font></td>
				</tr>

				</table>
			</td>

			<td width=5><img height=1 width=5 src="images/spacer.gif"><td>
			
			<td width=170>
				<table border=0 width=100% cellpadding=0 cellspacing=0>
				<tr>
					<td width=40 valign=top><acronym title="<?=$LANG_SETTINGS['madrid_fields']['DREG'];?>"><font class="viennacatunder">(151)</font></acronym>&nbsp;</td>
					<td valign=middle><font class="viennacat2"><?=$row['fi_151'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td width=40 valign=top><acronym title="<?=$LANG_SETTINGS['madrid_fields']['DM'];?>"><font class="viennacatunder">(580)</font></acronym>&nbsp;</td>
					<td valign=middle><font class="viennacat2"><?=$row['fi_580'];?></font></td>
				</tr>

				<?
				if ( $isUEFA && !empty($row['fi_73']))
				{
				?>
				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td width=40 valign=top><acronym title="<?=$LANG_SETTINGS['madrid_fields']['PROP'];?>"><font class="viennacatunder">(731)</font></acronym>&nbsp;</td>
					<td valign=middle><font class="viennacat2"><?=$row['fi_73'];?></font></td>
				</tr>
				<?
				} // uefa
				?>

				</table>
			</td>
	
			<td width=5><img height=1 width=5 src="images/spacer.gif"><td>
			
			<td>
				<table border=0 width=100% cellpadding=0 cellspacing=0>

				<tr>
					<td width=35 valign=top><acronym title="<?=$LANG_SETTINGS['madrid_fields']['MARK'];?>"><font class="viennacatunder">(540)</font></acronym></td>
					<td width=5><img height=1 width=5 src="images/spacer.gif"><td>
					<td width=250 valign=middle align=left>
<?
	if ( !empty($row['image']) )
	{
		if ( !empty($row['fi_540']) )
		{
?>
				<font class="viennacat"><?=$row['fi_540'];?></font><br>
				<img height=5 width=1 src="images/spacer.gif"><br>
<?
		} // end if !empty($row['fi_540'])
?>
					<img border=0 src="resize.php?dbn=<?=$currDbName;?>&idClaim=<?=$row['idClaim'];?>&it=<?=strtolower($row['imageType']);?>">
<?

	}
	else
	{
?>
					<font class="viennacat"><?=$row['fi_540'];?></font>
<?
	}
?>


					</td>
				</tr>

				</table>

			</td>
	
		</tr>
	
		<tr><td height=10 colspan=7><img height=10 width=1 src="images/spacer.gif"></td></tr>
		
		<?
		if ( !empty($row['bulletinDate']) )
		{
		?>
		<tr><td align=left colspan=7><font class="viennacat2"><?=$publication;?></font></td></tr>
		
		<tr><td height=3 colspan=7><img height=3 width=1 src="images/spacer.gif"></td></tr>
		<?
		}
		?>
		
		</table>
	</td>
</tr>

<?
	} // end for
?>
</table>
