<table border=0 width=100% height=100 cellpadding=3 cellspacing=0>

<?
	$sname = session_name();
	$sid = session_id();

	for($i = 0; $i < count( $searchShortBiblioSet ); $i++)
	{
		$row = $searchShortBiblioSet[$i];
		//print_r($row);

		$row['applicants'] = str_replace('###app###', '; ', $row['applicants']);
		$row['inventors'] = str_replace('###inv###', '; ', $row['inventors']);
		$row['owners'] = str_replace('###prop###', '; ', $row['owners']);

		//$row['mpk'] = str_replace('###mpk###', ', ', $row['mpk']);
		$ipcarr = explode('###mpk###', $row['mpk']);
		$ipcTitle = $ipcarr[0];
		unset($ipcarr[0]);
		$row['mpk'] = implode(', ', $ipcarr);

		$row['fi_21'] = textBlink($currDbName, $row['fi_21'], 'NC', false);
		$row['fi_54'] = textBlink($currDbName, $row['fi_54'], 'TITLE', false);
		$row['applicants'] = textBlink($currDbName, $row['applicants'], 'APP', false);
		$row['inventors'] = textBlink($currDbName, $row['inventors'], 'INV', false);
		$row['owners'] = textBlink($currDbName, $row['owners'], 'PROP', false);
		$row['mpk'] = textBlink($currDbName, $row['mpk'], 'MPK', false);
		
		$row['fi_54'] = devidedLongNames($row['fi_54'], 30);
		
		$publication = $LANG_SETTINGS['res']['publ'];
		
		if ($currDbName == 'invc')
		{
			$row['patentType'][0] = strtolower($row['patentType'][0]);
			
			if ( !empty($row['claimBullDate']) ) 
			{
				$publication = '<font class="viennacatinid"><acronym title="'.$LANG_SETTINGS['inv_details']['inid41'].'">(41)</acronym></font>&nbsp;'.$publication;
				$publication = str_replace('%1', '<b>'.$row['claimBullDate'].'</b>', $publication);		
				$publication = str_replace('%2', '<b>'.$row['claimBullNumber'].'</b>', $publication);		
			}
			else
				$publication = $LANG_SETTINGS['res']['nopubl'];		
		}
		else
		{
			$publication = str_replace('%1', '<b>'.$row['fi_46'].'</b>', $publication);		
			$publication = str_replace('%2', '<b>'.$row['patentBullNumber'].'</b>', $publication);		
		}
		

		if ( $currDbName != 'invc')
		{
		 	$statusImg = 'images/emptystatus.gif';
		 	$statusStr = $LANG_SETTINGS['res']['nd'];
		 	
		 	if (  strstr( $row['status'], 'не діє' ) )
		 	{
			 	$statusImg = 'images/red.gif';	
				$statusStr = $LANG_SETTINGS['res']['ndie'];
			}
		 	elseif (  strstr( $row['status'], 'діє' ) )
		 	{
			 	$statusImg = 'images/green.gif';
				$statusStr = $LANG_SETTINGS['res']['die'];
			}
		 	elseif (  strstr( $row['status'], 'дію патента припинено' ) )
		 	{
			 	$statusImg = 'images/yellow.gif';	
				$statusStr = $LANG_SETTINGS['res']['ndiea'];
			}
			elseif (  strstr( $row['status'], 'перша сплата' ) )
			{
				$statusImg = 'images/yellow.gif';	
				$statusStr = $LANG_SETTINGS['res']['nd4'];
			}
		} // end if
		
		$bcs = $basket_check_str;
		$bcs = str_replace('###IDCLAIM###', $row['idClaim'], $bcs);	

		if ( in_array($row['idClaim'], $currBasketIds) )
			$bcs = str_replace('###checked###', 'checked', $bcs);	
			
		/*
		if ( (int)$row['fi_13_code'] == 53 )
			$row['fi_11'] .= '&nbsp;A';
		*/
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
			<td align=left>&nbsp;</td>

<?
	if ( $currDbName != 'invc' && isDiskBul == 'no' )
	{
?>
			<td align=right>
				<?=(!$isUEFA) ? $bcs : '';?>
				<font class="viennacat">|</font>
				<font class="viennacat2"><?=$statusStr;?></font>
			</td>

			<td width=5><img height=1 width=5 src="images/spacer.gif"></td>

			<td width=14>
			<img alt="<?=$statusStr;?>" height=14 width=14 align=top src="<?=$statusImg;?>">
			</td>
<?
	} // end if
	else
	{
?>
			<td align=right>
				<?=(!$isUEFA) ? $bcs : '';?>
			</td>
<?
	} // end else
?>
			
		</tr>
		</table>
	</td>
</tr>

<tr>
	<td>&nbsp;</td>
	<td class="resbibliocell">
		<table border=0 height=100% width=100% cellpadding=0 cellspacing=0>

		<tr><td height=3 colspan=3><img height=3 width=1 src="images/spacer.gif"></td></tr>
	
		<tr valign=top>
			<td width=290>
				<table border=0 height=20 width=100% cellpadding=0 cellspacing=0>
<?
	if ( $currDbName != 'invc')
	{
?>
				<tr>
					<td><font class="viennacat">(11)&nbsp;<?=$LANG_SETTINGS['inv_fields']['NP'];?>:</font></td>
					<td valign=top><font class="viennacat"><?=$row['fi_11'];?></font></td>
				</tr>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
<?
	}
?>
		
				<tr>
					<td valign=top><font class="viennacat">(21)&nbsp;<?=$LANG_SETTINGS['inv_fields']['NC'];?>:&nbsp;</font></td>
					<td valign=top><font class="viennacat2"><?=$row['fi_21'];?></font></td>
				</tr>
		
				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td valign=top><font class="viennacat">(22)&nbsp;<?=$LANG_SETTINGS['inv_fields']['FD'];?>:&nbsp;</font></td>
					<td valign=top><font class="viennacat2"><?=$row['fi_22'];?></font></td>
				</tr>
<?
	if ( $currDbName != 'invc' )
	{
?>
		
				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

				<tr>
					<td valign=top><font class="viennacat">(24)&nbsp;<?=$LANG_SETTINGS['inv_fields']['DATECOM'];?>:&nbsp;</font></td>
					<td valign=top><font class="viennacat2"><?=$row['fi_24'];?></font></td>
				</tr>

<?
	} // end if $currDbName != 'invc'
?>
				</table>
			</td>
	
			<td width=5><img width=5 src="images/spacer.gif"></td>
			
			<td>
				<table border=0 height=20 width=100% cellpadding=0 cellspacing=0>
				<tr>
					<td valign=top><font class="viennacat">(51)&nbsp;<?=$ipcTitle;?>:</font></td>
					<td valign=top><font class="viennacat2"><?=$row['mpk'];?></font></td>
				</tr>
		

<?
	if ( $currDbName == 'invc')
	{
?>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
		
				<tr>
					<td align=top><font class="viennacat">(71)&nbsp;<?=$LANG_SETTINGS['inv_fields']['APP'];?>:&nbsp;</font></td>
					<td valign=top><font class="viennacat2"><?=$row['applicants'];?></font></td>
				</tr>
<?
	}
?>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
		
				<tr>
					<td width=120 valign=top><font class="viennacat">(72)&nbsp;<?=$LANG_SETTINGS['inv_fields']['INV'];?>:&nbsp;</font></td>
					<td valign=top><font class="viennacat2"><?=$row['inventors'];?></font></td>
				</tr>
		
<?
	if ( $currDbName != 'invc')
	{
?>

				<tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
		
				<tr>
					<td valign=top><font class="viennacat">(73)&nbsp;<?=$LANG_SETTINGS['inv_fields']['PROP'];?>:&nbsp;</font></td>
					<td valign=top><font class="viennacat2"><?=$row['owners'];?></font></td>
				</tr>
<?
	}
?>


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
