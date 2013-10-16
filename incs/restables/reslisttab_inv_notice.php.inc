<?

	include('.././searchBul/incs/xml.php.inc');
	
	$dictPrefix = 'inv_';
	if ($currDbName == 'invdu')
		$dictPrefix = 'invu_';
		
	$w = 550;
	if ( !empty( $_SESSION['reestrDbName'] ) )
	{
		$w = 600; 
		if ( $_SESSION['reestrDbName'] == 'reestrinv' )
		{
			$dictPrefix = 'inv_';
			$tagPrefix = 'i_';
		}
		else
		{
			$dictPrefix = 'invu_';
			$tagPrefix = 'u_';
		}
	}
	

	$tagPrefix = 'i_';
	if ( $currDbName == 'invu' || $currDbName == 'invdu' )
		$tagPrefix = 'u_';	
?>

<table width="<?=$w;?>" border=0 cellspacing=0 cellpadding=0>

<?
	$objXML = new xml2Array();

	$prevNoticeCode = 0;
	$count = 0;
	
	for($i = 0; $i < count($searchShortBiblioSet); $i++)
	{
		$noticeCode = $searchShortBiblioSet[$i][0];
		$i_11 = $searchShortBiblioSet[$i][1];		
		$i_21 = $searchShortBiblioSet[$i][2];
		$notice = $searchShortBiblioSet[$i][3];
		$idclaim = $searchShortBiblioSet[$i][4];
		
		$bullDate = $searchShortBiblioSet[$i][4];
		$bullNumber = $searchShortBiblioSet[$i][5];
		
		$notice = str_replace('patentNumber', 'patentnumber', $notice);
		$notice = str_replace('inputNumber', 'inputnumber', $notice);
		$notice = str_replace('&', '@@@and@@@', $notice);
		$notice = str_replace('<BR>', '@@@br@@@', $notice);


		// 37 - Припинення дії деклараційного патенту на винахід у зв'язку з видачею патенту на винахід після проведення кваліфікаційної експертизи
		if ( $currDbName == 'inv' && $noticeCode == 37 ) 
		{
			$notice = str_replace('patentnumber', 'patentnumber_2', $notice);
			$notice = str_replace('dateFactStop', 'datefactstop_2', $notice);
		}

		// 64 - Визнання деклараційного патенту на винахід таким, що не набрав чинності, у зв'язку з прийняттям рішення про відмову у видачі патенту на винахід
		if ( $currDbName == 'inv' && $noticeCode == 64 ) 
		{
			$notice = str_replace('patentnumber', 'patentnumber_2', $notice);
			$notice = str_replace('dateFactStop', 'datefactstop_3', $notice);
		}


		
		
		$parserNotice = $objXML->parse($notice);
		$objXML->clearXML();
		
		$n = $parserNotice[0]['children'];
		
		++$count;
		
		/*
		{
		print('<tr><td colspan=10>');
		print_r($searchShortBiblioSet[$i]);
		print('<BR><BR><BR>');
		print('</td></tr>');
		}
		*/
		
		/*
		print('<tr><td colspan=10>');
		print($noticeCode.'-'.htmlspecialchars($notice));
		print('<BR><BR>');
		print_r($n);
		print('<BR><BR><BR>');
		print('</td></tr>');
		*/


		


/*
		if ($noticeCode == 48)
		{
		print('<tr><td colspan=10>');
		print(htmlspecialchars($notice));
		print('<BR><BR><BR>');
		print('</td></tr>');
		}
*/
		
?>

<?
	if ( $noticeCode != $prevNoticeCode)
	{
		if ( $i > 0 )
		{
			$count = 0;
?>
			<tr><td height="1"><img src="images/spacer.gif" height="1"></td></tr>
			</table>	
			</td>				
		</tr>
<?
		} // end if ( $i > 0 )
?>
		<tr><td align=left><font class="viennacat"><?=$LANG_SETTINGS['inv_notices'][$dictPrefix.$noticeCode];?></font></td></tr>	

		<tr><td height="5"><img src="images/spacer.gif" height="5"></td></tr>
		
		<?
		if ( $noticeCode == 69 || $noticeCode == 72 )
		{
		?>
		<tr>
			<td><font class="viennacat2"><?=$LANG_SETTINGS['inv_notices']['license'];?></font></td>
		</tr>
		<tr><td height="5"><img src="images/spacer.gif" height="5"></td></tr>
		<?
		}
		?>
	
		<tr>
			<td>
			<table width=100% border=0 cellspacing=0 cellpadding=5>
			
			<?
				if ( $noticeCode == 48 )
				{
			?>
				<tr valign=top>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_INID_11'];?></td>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_INPUTNUMBER'];?></td>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_BULLETIN'];?></td>
					<td class="notifyHeaderNot2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_read'];?></td>
				</tr>
			<?
				} // noticeCode = 48 - виправлення очевидних помилок
				elseif ( $noticeCode == 45 )
				{

			?>
				<tr valign=top>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_INID_11'];?></td>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_INPUTNUMBER'];?></td>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'my_tag_court'];?></td>
					<td class="notifyHeaderNot2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'my_tag_notavail'];?></td>
				</tr>
			
			<?
				} // end elseif noticeCode = 45 - Визнання патенту (деклараційного патенту) на винахід недійсним за рішенням суду
				elseif ( $noticeCode == 50 )
				{
			?>
				<tr valign=top>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_INID_11'];?></td>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_INPUTNUMBER'];?></td>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_BULLETIN'];?></td>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'my_tag_court'];?></td>
					<td class="notifyHeaderNot2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'my_tag_change'];?></td>
				</tr>
			
			<?
				} // end elseif noticeCode = 50 - Зміни, внесені за рішенням суду
				elseif ( $noticeCode == 63 )
				{

			?>
				<tr valign=top>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_INID_11'];?></td>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_INPUTNUMBER'];?></td>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'my_tag_court'];?></td>
					<td class="notifyHeaderNot2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_INID_73_2'];?></td>
				</tr>

			<?
				} // end elseif noticeCode = 63 - Встановлення власника патенту (деклараційного патенту) на винахід за рішенням суду
				elseif ( $noticeCode == 69 )
				{
			?>
				<tr valign=top>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_PATENTNUMBERS'];?></td>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_LICENSIARS'];?></td>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_LICENSIATS'];?></td>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_LICENSETYPE'];?></td>
					<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_CONTRACTNUMBER'];?></td>
					<td class="notifyHeaderNot2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_CONTRACTDATE'];?></td>												
				</tr>
						
			<?
				} // end elseif noticeCode = 69 - Видача ліцензії на використання винаходу
				elseif ( $noticeCode == 70 )
				{
			?>
					<tr valign=top>
						<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_PATENTNUMBERS'];?></td>
						<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_OLDOWNERS'];?></td>
						<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_NEWOWNERS'];?></td>
						<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_CONTRACTNUMBER'];?></td>
						<td class="notifyHeaderNot2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_CONTRACTDATE'];?></td>												
					</tr>
			<?
				} // end elseif noticeCode = 70 - Передача права власності на винахід(корисну модель)
				elseif ( $noticeCode == 72 )
				{
			?>
					<tr valign=top>
						<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_PATENTNUMBERS'];?></td>
						<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_CONTRACTNUMBER'];?></td>
						<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_CONTRBULL'];?></td>
						<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_LICENSIARS'];?></td>
						<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_LICENSIATS'];?></td>
						<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_LICENSETYPE'];?></td>
						<td class="notifyHeaderNot2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'my_tag_change'];?></td>												
					</tr>
			<?
				} // end elseif noticeCode = 72 - Зміни, що внесені у відомості про видачу ліцензії на використання
				elseif ( $noticeCode == 75 )
				{
			?>
					<tr valign=top>
						<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_PATENTNUMBERS'];?></td>
						<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_BULLETIN'];?></td>
						<td class="notifyHeader2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_INID_54'];?></td>
						<td class="notifyHeaderNot2"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_OLDOWNERS_2'];?></td>
					</tr>
						
			<?
				} // end elseif noticeCode = 75 - Заява власника патенту (деклараційного патенту) про готовність надання будь-якій особі дозволу на використання винаходу
				else
				{
			?>
					<tr>
			<?
					for ($j = 0; $j < count($n); $j++)
					{
						$tagName = $n[$j]['name'];
						$tagAttrs = $n[$j]['attrs'];
						
						$cl = 'notifyHeader';
						if ( $j == count($n)-1 )
							$cl = 'notifyHeaderNot';
							
						if ( $tagAttrs['ISSPOV'] == 'Y' )
						{
			?>
							<td class="<?=$cl;?>" valign=top><font class="viennacat2white"><?=$LANG_SETTINGS['inv_notices'][$tagPrefix.'tag_'.$tagName];?></font></td>			
			<?
						} // end if  $tagAttrs['SSPOV'] == 'Y'
					} // end for $j
			?>
					</tr>
			<?
				} // end else
			?>

<?
	} // notice != prevnotice
?>

		
		



			<?
				$notices_with_inid = array(48, 49, 77);
				

				// приводит содержимое тегов в "нормальный вид"
				for ($j = 0; $j < count($n); $j++)
				{
					$tagName = $n[$j]['name'];
					$tagAttrs = $n[$j]['attrs'];
					$n[$j]['tagData'] = ltrim(rtrim($n[$j]['tagData']));
					$n[$j]['tagData'] = str_replace('@@@and@@@', '&', $n[$j]['tagData']);
					$n[$j]['tagData'] = str_replace('@@@br@@@', '<br>', $n[$j]['tagData']);
					//$n[$j]['tagData'] = str_replace('((BR))', '<br>', $n[$j]['tagData']);
					$n[$j]['tagData'] = (!empty($n[$j]['tagData'])) ? $n[$j]['tagData'] : '&nbsp;';
					$n[$j]['tagData'] = utf8_decode($n[$j]['tagData']);
					//$n[$j]['tagData'] = str_replace('((/i))', '</i>', $n[$j]['tagData']);					
					//$n[$j]['tagData'] = str_replace('((i))', '<i>', $n[$j]['tagData']);					
					$n[$j]['tagData'] = str_replace('((', '<', $n[$j]['tagData']);					
					$n[$j]['tagData'] = str_replace('))', '>', $n[$j]['tagData']);					
										
					if ( $tagAttrs['ISSPOV'] != 'Y' )
						$n[$j]['tagData'] = '';
						
					if ($tagName == 'INID_57' && empty( $_SESSION['reestrDbName'] ) && isDiskBul == 'no' )
						$n[$j]['tagData'] = '<font class="viennacatchange">(57)&nbsp;</font><a href="search.php?action=viewdetails&dbname='.$currDbName.'&IdClaim='.$idclaim.'&from=notice&chapter=claim" class="viennacatchange">'.$LANG_SETTINGS['details']['viewformula'].'</a>';
					elseif ($tagName == 'INID_57' && empty( $_SESSION['reestrDbName'] ) && isDiskBul == 'yes' )
						$n[$j]['tagData'] = '<font class="viennacatchange">(57)&nbsp;</font><font class="viennacatchange">'.$LANG_SETTINGS['details']['viewformula2'].'</font>';
					elseif ($tagName == 'INID_57' && !empty( $_SESSION['reestrDbName'] ))
						$n[$j]['tagData'] = '<font class="viennacatchange">(57)&nbsp;'.$LANG_SETTINGS['details']['viewformula'].'</font>';			
					elseif (($tagName == 'PATENTNUMBER' || $tagName == 'PATENTNUMBER_2') && empty( $_SESSION['reestrDbName'] ) && isDiskBul == 'no' )				
						$n[$j]['tagData'] = '<a class="viennacat2under" href="search.php?action=viewdetails&dbname='.$currDbName.'&IdClaim='.$idclaim.'&from=notice">'.$n[$j]['tagData'].'</a>';
					elseif (($tagName == 'PATENTNUMBER' || $tagName == 'PATENTNUMBER_2' ) && !empty( $_SESSION['reestrDbName'] ) )				
						$n[$j]['tagData'] = $n[$j]['tagData'];
					elseif ( strstr($tagName, 'INID_') )
					{
						if ( in_array( $noticeCode, $notices_with_inid ) )
							$n[$j]['tagData'] = '('.substr($tagName, strpos($tagName, '_')+1).')&nbsp;'.$n[$j]['tagData'];
						else
							$n[$j]['tagData'] = $n[$j]['tagData'];
					}
					elseif ( $tagName == 'INPUTNUMBER' && empty($tagDat))
						$n[$j]['tagData'] = $i_21;
				
				} // end for
				?>

				<?
				if ( !empty( $_SESSION['reestrDbName'] ) )
				{
				$notice_publication = $LANG_SETTINGS['res']['notice_publ'];
				
				$notice_publication = str_replace('%1', '<b>'.$bullDate.'</b>', $notice_publication);		
				$notice_publication = str_replace('%2', '<b>'.$bullNumber.'</b>', $notice_publication);		
				
				?>
				<tr><td colspan=8 align=left class="noticeNotifyLineLeft2"><font class="viennacat2"><?=$notice_publication;?></font></td></tr>				
				<?
				} // end if
				?>

				<?
/*				
					print('<tr><td colspan=4>');
					//print_r($n);
					print($n[$k]['name']);
					print('</td></tr>');
					print('<tr><td colspan=4>');
					print('<BR><BR>');
					print('</td></tr>');
*/

				if ( $noticeCode == 48 )
				{
					$s = '';
					for($k = 0; $k < count($n); $k++)
					{
						$tagAttrs = $n[$k]['attrs'];
						$tagName = $n[$k]['name'];

						if ( $tagAttrs['ISSPOV'] == 'Y' && strstr($tagName, 'INID_') )
						{
							$s .= $n[$k]['tagData'];
							if ( $k < count($n)-2 )
								 $s .= '<BR><BR>';
						}
					} // end for
					
					if ( empty($s) )
						$s = '&nbsp;';
					
			?>
				<tr valign=top>
					<td class="notifyLineLeft2"><?=getDataByTagName($n, 'PATENTNUMBER');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'INPUTNUMBER');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'BULLETIN');?></td>
					<td class="notifyLine2"><?=$s;?></td>
				</tr>
			<?
				} // noticeCode = 48 - виправлення очевидних помилок
				elseif ( $noticeCode == 45 )
				{
					$s = '';
					if ( getDataByTagName($n, 'COURTNAME') != '&nbsp;' )
						$s .= getDataByTagName($n, 'COURTNAME').',&nbsp;';

					if ( getDataByTagName($n, 'COURTDOCNUMBER') != '&nbsp;' )
						$s .= getDataByTagName($n, 'COURTDOCNUMBER').',&nbsp;';
						
					if ( getDataByTagName($n, 'COURTDOCDATE') != '&nbsp;' )
						$s .= getDataByTagName($n, 'COURTDOCDATE');
					
			?>
				<tr valign=top>
					<td class="notifyLineLeft2"><?=getDataByTagName($n, 'PATENTNUMBER');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'INPUTNUMBER');?></td>
					<td class="notifyLine2"><?=$s;?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'DATEFACTSTOP');?></td>
				</tr>
			<?
				} // end elseif noticeCode = 45 - Визнання патенту (деклараційного патенту) на винахід недійсним за рішенням суду
				elseif ( $noticeCode == 50 )
				{
					$court = '';
					if ( getDataByTagName($n, 'COURTNAME') != '&nbsp;' )
						$court .= getDataByTagName($n, 'COURTNAME').',&nbsp;';

					if ( getDataByTagName($n, 'COURTDOCNUMBER') != '&nbsp;' )
						$court .= getDataByTagName($n, 'COURTDOCNUMBER').',&nbsp;';
						
					if ( getDataByTagName($n, 'COURTDOCDATE') != '&nbsp;' )
						$court .= getDataByTagName($n, 'COURTDOCDATE');

					if ( empty($court) )
						$court = '&nbsp;';

					$s = '';
					for($k = 0; $k < count($n); $k++)
					{
						$tagAttrs = $n[$k]['attrs'];
						$tagName = $n[$k]['name'];

						if ( $tagAttrs['ISSPOV'] == 'Y' && ( strstr($tagName, 'INID_') || strstr($tagName, 'OTHER') ) )
						{
							$s .= $n[$k]['tagData'];
							if ( $k < count($n)-2 )
								 $s .= '<BR><BR>';
						}
					} // end for

					if ( empty($s) )
						$s = '&nbsp;';

			?>
				<tr valign=top>
					<td class="notifyLineLeft2"><?=getDataByTagName($n, 'PATENTNUMBER');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'INPUTNUMBER');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'BULLETIN');?></td>
					<td class="notifyLine2"><?=$court;?></td>
					<td class="notifyLine2"><?=$s;?></td>
				</tr>
			<?
				} // noticeCode = 48 - виправлення очевидних помилок
				elseif ( $noticeCode == 63 )
				{
					$s = '';
					if ( getDataByTagName($n, 'COURTNAME') != '&nbsp;' )
						$s .= getDataByTagName($n, 'COURTNAME').',&nbsp;';

					if ( getDataByTagName($n, 'COURTDOCNUMBER') != '&nbsp;' )
						$s .= getDataByTagName($n, 'COURTDOCNUMBER').',&nbsp;';
						
					if ( getDataByTagName($n, 'COURTDOCDATE') != '&nbsp;' )
						$s .= getDataByTagName($n, 'COURTDOCDATE');
					
			?>
				<tr valign=top>
					<td class="notifyLineLeft2"><?=getDataByTagName($n, 'PATENTNUMBER');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'INPUTNUMBER');?></td>
					<td class="notifyLine2"><?=$s;?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'INID_73');?></td>
				</tr>
			<?
				} // noticeCode = 63 - Встановлення власника патенту (деклараційного патенту) на винахід за рішенням суду
				elseif ( $noticeCode == 69 )
				{
			?>
				<tr valign=top>
					<td class="notifyLineLeft2"><?=getDataByTagName($n, 'PATENTNUMBERS');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'LICENSIARS');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'LICENSIATS');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'LICENSETYPE');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'CONTRACTNUMBER');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'CONTRACTDATE');?></td>
				</tr>
			<?
				} // noticeCode = 69 - Видача ліцензії на використання винаходу
				elseif ( $noticeCode == 70 )
				{
			?>
				<tr valign=top>
					<td class="notifyLineLeft2"><?=getDataByTagName($n, 'PATENTNUMBERS');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'OLDOWNERS');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'NEWOWNERS');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'CONTRACTNUMBER');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'CONTRACTDATE');?></td>
				</tr>
			<?
				} // noticeCode = 70 
				elseif ( $noticeCode == 72 )
				{
			?>
				<tr valign=top>
					<td class="notifyLineLeft2"><?=getDataByTagName($n, 'PATENTNUMBERS');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'CONTRACTNUMBER');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'BULLETIN');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'LICENSIARS');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'LICENSIATS');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'LICENSETYPE');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'C_LICENSIATS');?></td>
				</tr>
			<?
				} // noticeCode = 72
				elseif ( $noticeCode == 75 )
				{
			?>
				<tr valign=top>
					<td class="notifyLineLeft2"><?=getDataByTagName($n, 'PATENTNUMBERS');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'BULLETIN');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'PATENTTITLES');?></td>
					<td class="notifyLine2"><?=getDataByTagName($n, 'OLDOWNERS');?></td>
				</tr>
			<?
				} // noticeCode = 75
				else
				{
			?>
				<tr valign=top>
			<?
				for ($j = 0; $j < count($n); $j++)
				{
					$tagData = $n[$j]['tagData'];
					$tagName = $n[$j]['name'];
					$tagAttrs = $n[$j]['attrs'];
					
					$cl = 'notifyLine2';
					if ( $j == 0 )
						$cl = 'notifyLineLeft2';
					
					if ( $tagAttrs['ISSPOV'] == 'Y' )
					{
			?>
						<td class="<?=$cl;?>"><?=$tagData;?></td>
			<?				
					} // end if  $tagAttrs['SSPOV'] == 'Y'
				} // end for $j
			?>
				</tr>
			<?
				} // end else
			?>


<?
		/*
		print('<tr><td colspan=10>');
		print_r($n);
		print('<BR><BR><BR>');
		print('</td></tr>');
		*/

		$prevNoticeCode = $noticeCode;
	} // end for
?>
			</table>	
			</td>				
		</tr>

</table>
