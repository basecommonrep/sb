<table border=0 width=100% height=100 cellpadding=3 cellspacing=0>

<?
	for($i = 0; $i < count( $searchShortBiblioSet ); $i++)
	{
		$row = $searchShortBiblioSet[$i];
		//print_r($row);

		$row['fi_731'] = str_replace('###app###', '; ', $row['fi_731']);
		$row['fi_732'] = str_replace('###prop###', '; ', $row['fi_732']);
		$row['fi_732'] = str_replace('УЕФА', 'УЄФА', $row['fi_732']);
		$row['fi_511'] = str_replace('###mktp###', ', ', $row['fi_511']);
		$row['fi_539'] = str_replace('###keywords###', '; ', $row['fi_539']);
		
		if ( $addDbName == 'cert' && $currDbName == 'tm' )
			$row['fi_539'] = '';
			
		$row['fi_591'] = str_replace('###colors###', ', ', $row['fi_591']);

		$row['fi_210'] = textBlink($currDbName, $row['fi_210'], 'NC', false);
		$row['fi_731'] = textBlink($currDbName, $row['fi_731'], 'APP', false);
		$row['fi_732'] = textBlink($currDbName, $row['fi_732'], 'PROP', false);
		$row['fi_539'] = textBlink($currDbName, $row['fi_539'], 'KEYW', false);
		$row['fi_591'] = textBlink($currDbName, $row['fi_591'], 'COLORS', false);
		
		$publication = $LANG_SETTINGS['res']['publ'];
		$publication = str_replace('%1', '<b>'.$row['bullDate'].'</b>', $publication);		
		$publication = str_replace('%2', '<b>'.$row['bulletinNumber'].'</b>', $publication);		

		if ( $currDbName != 'tmc' )
		{
			if ( !empty( $row['fi_141'] ) )
			{
			 	$statusImg = 'images/red.gif';	
				$statusStr = $LANG_SETTINGS['tm_fields']['patentoff'];
			} else { // Если статус действительный, то нужно ещё проверить не просрочена ли оплата (до полугода)
                $now = time();
				// 181 - очікувана дата закінчення дії свідоцтва
				// 186 - очікувана дата строку продовження дії свідоцтва
                $i_181UnixTime = strtotime($row['fi_181']);
                $i_186UnixTime = strtotime($row['fi_186']);
                if ($now >= $i_181UnixTime && (is_null($row['fi_186']) || $now >= $i_186UnixTime)) {
                    //$dateFinalIndex = ($i_186UnixTime > $i_181UnixTime) ? 'fi_186' : 'fi_181';
                    //$dateFinalUnixTime = strtotime("{$row[$dateFinalIndex]} +6 months");

                    // Проверка, ставить ли желтый статус
                    //if ($now <= $dateFinalUnixTime) {

                        // "Жёлтый статус" остаётся при отсутсвии 141-го кода
                        $statusImg = 'images/yellow.gif';
                        $statusStr = $LANG_SETTINGS['tm_fields']['patentoff_6m'];

                    //} else {
                    //    $statusImg = 'images/red.gif';
                    //    $statusStr = $LANG_SETTINGS['tm_fields']['patentoff'];
                    //}
                } else {
                    $statusImg = 'images/green.gif';
                    $statusStr = $LANG_SETTINGS['tm_fields']['patenton'];
                }
            }
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
			<td><a href="search.php?action=viewdetails<?=$detailStr;?>&IdClaim=<?=$row['idClaim'];?>" class="pageHeaderText"><?=$row['fi_539'];?></a></td>
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
				if ( $currDbName != 'tmc' && isDiskBul == 'no' )
				{
				?>
				<font class="viennacat">|</font>
				<font class="viennacat2"><?=$statusStr;?></font>
				<?
				}
				?>
			</td>

			<?
			if ( $currDbName != 'tmc' && isDiskBul == 'no' )
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
		<tr><td height=3 colspan=7><img height=3 width=1 src="images/spacer.gif"></td></tr>
	
		<tr valign=top>
			<td width=180>
				<table border=0 height=50 width=100% cellpadding=0 cellspacing=0>
				<?
				if ( $currDbName != 'tmc' )
				{	
				?>
				<tr>
					<td width=40><acronym title="<?=$LANG_SETTINGS['tm_details']['inid111'];?>"><font class="viennacatunder">(111)</font></acronym></td>
					<td valign=middle><font class="pageHeaderText"><?=$row['fi_111'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
		
				<tr>
					<td valign=top><acronym title="<?=$LANG_SETTINGS['tm_details']['inid151'];?>"><font class="viennacatunder">(151)</font></acronym></td>
					<td valign=middle><font class="viennacat2"><?=$row['fi_151'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
				<?
				}
				?>

		
				<tr>
					<td width=40 valign=top><acronym title="<?=$LANG_SETTINGS['tm_details']['inid210'];?>"><font class="viennacatunder">(210)</font></acronym></td>
					<?
					if( $currDbName != 'tmc' )
					{
					?>
					<td valign=top><font class="viennacat"><?=$row['fi_210'];?></font></td>
					<?
					}
					else
					{
					?>
					<td valign=top><font><a class="viennacat" target="_blank" href="http://base.uipv.org/SearchTMStat/showclaimdetails.php?IdClaim=<?=$row['idClaim'];?>&resId=1"><?=$row['fi_210'];?></a></font></td>
					<? } ?>
				</tr>
		
				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td valign=top><acronym title="<?=$LANG_SETTINGS['tm_details']['inid220'];?>"><font class="viennacatunder">(220)</font></acronym></td>
					<td valign=top><font class="viennacat2"><?=$row['fi_220'];?></font></td>
				</tr>

				</table>
			</td>

			<td width=5><img height=1 width=5 src="images/spacer.gif"><td>
			
			<td width=300>
				<table border=0 width=100% cellpadding=0 cellspacing=0>

				<?
				if ( $currDbName != 'tmc' )
				{	
				?>
				<tr>
					<td width=40 valign=top><acronym title="<?=$LANG_SETTINGS['tm_details']['inid732'];?>"><font class="viennacatunder">(732)</font></acronym></td>
					<td valign=middle><font class="viennacat2"><?=$row['fi_732'];?></font></td>
				</tr>

				<?
				}
				else
				{
				?>
				<tr>
					<td width=40 valign=top><acronym title="<?=$LANG_SETTINGS['tm_details']['inid731'];?>"><font class="viennacatunder">(731)</font></acronym></td>
					<td valign=middle><font class="viennacat2"><?=$row['fi_731'];?></font></td>
				</tr>

				<?
				}
				?>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
		
				<tr>
					<td valign=top><acronym title="<?=$LANG_SETTINGS['tm_details']['inid511'];?>"><font class="viennacatunder">(511)</font></acronym></td>
					<td valign=middle><font class="viennacat"><?=$row['fi_511'];?></font></td>
				</tr>

				<?
				if ( !empty( $row['fi_591'] ) )
				{
				?>
				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
		
				<tr>
					<td valign=top><acronym title="<?=$LANG_SETTINGS['tm_details']['inid591'];?>"><font class="viennacatunder">(591)</font></acronym></td>
					<td valign=middle><font class="viennacat"><?=$row['fi_591'];?></font></td>
				</tr>
				<?
				} // end if !empty( $row['fi_591']
				?>

				</table>
			</td>
	
			<td width=5><img height=1 width=5 src="images/spacer.gif"><td>
			
			<td>
				<table border=0 width=100% cellpadding=0 cellspacing=0>
				<tr>
					<td width=40 valign=top><acronym title="<?=$LANG_SETTINGS['tm_details']['inid540'];?>"><font class="viennacatunder">(540)</font></acronym></td>
					<td width=5><img height=1 width=5 src="images/spacer.gif"></td>
					<td width=200 valign=top align=center>
					<?if (empty($row['fi_539note'])) 
					{ ?>
					 <a href="search.php?action=viewdetails<?=$detailStr;?>&IdClaim=<?=$row['idClaim'];?>"><img border=0 src="resize.php?dbn=<?=$currDbName;?>&idClaim=<?=$row['idClaim'];?>"></a>
					<?}  
					else 
					{?> 
					 <font class="viennacat"><?=$LANG_SETTINGS['tm_details']['inid539note'];?> <?=$row['fi_539note'];?></font> 
					<?} ?> 
					</td>
				</tr>
				</table>
			</td>
		</tr>
	
		<tr><td height=5 colspan=7><img height=5 width=1 src="images/spacer.gif"></td></tr>
		
		<tr>
			<?
			if ( $currDbName != 'tmc' )
			{	
			?>
			<td align=left colspan=6><font class="viennacat2"><?=$publication;?></font></td>
			<?
			}
			?>
			<td align=right <?=($currDbName == 'tmc') ? 'colspan=7': '';?>><a class="info" href="search.php?action=viewdetails<?=$detailStr;?>&IdClaim=<?=$row['idClaim'];?>"><?=$LANG_SETTINGS['details']['details'];?>...</a>&nbsp;</td>
		</tr>		

		<tr><td height=3 colspan=7><img height=3 width=1 src="images/spacer.gif"></td></tr>

		</table>
	</td>
</tr>

<?
	} // end for
?>
</table>
