<table border=0 width=100% height=100 cellpadding=3 cellspacing=0>

<?
	
	for($i = 0; $i < count( $searchShortBiblioSet ); $i++)
	{
		$row = $searchShortBiblioSet[$i];
		
		//print(strtotime($row['bulld']));
		//print('<br>');
		//print((int)strtotime('14.06.2011'));
		//print('<br>');
		//print(((int)strtotime($row['bulld']) > (int)strtotime('14.06.2011')));
	
		// changes associated with changing from name of department to service
		$desi = ((int)strtotime($row['bulld']) > (int)strtotime('14.06.2011')) ? $LANG_SETTINGS['wkm_fields']['DESI2'] : $LANG_SETTINGS['wkm_fields']['DESI'];
		//$desi = $LANG_SETTINGS['wkm_fields']['DESI'];
		$desi = str_replace('%1', '<b>'.$row['decisionDate'].'</b>', $desi);
		$desi = str_replace('%2', '<b>'.$row['orderDate'].'</b>', $desi);		
		$desi = str_replace('%3', '<b>'.$row['orderNumber'].'</b>', $desi);

		$row['fi_72'] = str_replace('###prop###', '; ', $row['fi_72']);

		$row['fi_72'] = textBlink($currDbName, $row['fi_72'], 'PROP', false);
		$row['keyWords'] = textBlink($currDbName, $row['keyWords'], 'MARK', false);
		$row['fi_511'] = textBlink($currDbName, $row['fi_511'], 'NICE', false);
		$row['fi_511'] = textBlink($currDbName, $row['fi_511'], 'LGS', false);
		
		$mktp = explode('###mktp###', $row['fi_511']);

		$bcs = $basket_check_str;
		$bcs = str_replace('###IDCLAIM###', $row['idMark'], $bcs);

		if ( in_array($row['idMark'], $currBasketIds) )
			$bcs = str_replace('###checked###', 'checked', $bcs);
?>

<tr>
	<td class="resnumbcell"><?=($i+$startId);?></td>
	<td class="restitlecell" height=20>
		<table border=0 width=100% cellpadding=0 cellspacing=0>
		<tr>
			<td><font class="pageHeaderText"><?=$row['keyWords'];?></font></td>
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
					<td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['wkm_fields']['D'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td width=20><img height=1 width=20 src="images/spacer.gif"></td>
					<td width=580><font class="viennacat2"><?= (!empty($row['courtcomments'])) ? $row['courtcomments'] : $desi;?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['wkm_fields']['DWKM'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td><img height=1 width=20 src="images/spacer.gif"></td>
					<td><font class="viennacat2"><?=$row['rightsDate'];?></font></td>
				</tr>
		
				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['wkm_fields']['PD'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td><img height=1 width=20 src="images/spacer.gif"></td>
					<td><font class="viennacat2"><?=$row['bulStr'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['wkm_fields']['PROP'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td><img height=1 width=20 src="images/spacer.gif"></td>
					<td><font class="viennacat2"><?=$row['fi_72'];?></font></td>
				</tr>
				
				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>		
				<tr>
					<td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['wkm_fields']['MARK'];?></font></td>
				</tr>

				<tr><td height=5><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td><img height=1 width=20 src="images/spacer.gif"></td>
					<td align=left valign=top>
					<?
						if ( !empty($row['image']) )
						{
					?>
						<img border=0 src="resize.php?dbn=<?=$currDbName;?>&idClaim=<?=$row['idMark'];?>">
					
					<?
						}
						else
						{
					?>

						<font class="pageHeaderText"><?=$row['keyWords'];?></font>
					<?
						}
					?>
					
					</td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['wkm_fields']['LGS'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td colspan=2>
					<table border=0 width=100% cellpadding=0 cellspacing=0>
					<?
					for($j = 0; $j < count($mktp); $j++)
					{
						$mktpRow = explode('$$$', $mktp[$j]);
						if (!empty($mktpRow[1]))
						{
							$mktpRow[1][0] = strtoupper($mktpRow[1][0]);
							$mktpRow[1] = $mktpRow[1].';';
						}
						
					?>

					<tr><td height="5"><img src="images/spacer.gif" height="5"></td></tr>						

					<tr>
						<td width=30 valign=top><font class="viennacat2"> Î.<?= $mktpRow[0]; ?>&nbsp;Ã “œ:&nbsp;</font></td>
						<td width=550 valign=top><font class="viennacat2"><?= $mktpRow[1]; ?></font></td>
					</tr>
						
					<?
					} // end for $mktp
					?>

					</table>
					</td>
				
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
