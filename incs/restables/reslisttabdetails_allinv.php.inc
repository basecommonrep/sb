<?
	if ( $currDbName != 'invc' )
	{
	 	$statusImg = 'images/emptystatus.gif';
	 	$statusStr = $LANG_SETTINGS['res']['nd'];
	 	
	 	if (  strstr( $fullBiblio['status'], 'не діє' ) )
	 	{
		 	$statusImg = 'images/red.gif';	
			$statusStr = $LANG_SETTINGS['res']['ndie'];
		}
	 	elseif (  strstr( $fullBiblio['status'], 'діє' ) )
	 	{
		 	$statusImg = 'images/green.gif';
			$statusStr = $LANG_SETTINGS['res']['die'];
		}
	 	elseif (  strstr( $fullBiblio['status'], 'дію патента припинено' ) )
	 	{
		 	$statusImg = 'images/yellow.gif';	
			$statusStr = $LANG_SETTINGS['res']['ndiea'];
		}
	 	elseif (  strstr( $fullBiblio['status'], 'перша сплата' ) )
	 	{
		 	$statusImg = 'images/yellow.gif';	
			$statusStr = $LANG_SETTINGS['res']['nd4'];
		}
	}
	
	$claim_number = $_SESSION['lastFullBiblioClaimNumber'];
	$claim_number = substr($claim_number.'/', 0, strpos($claim_number.'/', '/'));
	
	$n = $claim_number;
	$part1 = substr( $n, 0, 6 );
	$part2 = substr( $n, 6, 10000 );
	
	// ==============================================
	// формула
	// ==============================================

	if ( isInvDocFromDb == 'yes' )
	{
		$folder = 'tempdocs/'.$part1.'/'.$claim_number.'/';
		
		$path_formula_uk = $folder.$n.'fu/'.$n.'fu.html';
		if ( !file_exists( $path_formula_uk ) )
			$path_formula_uk = '';
	}
	else
	{
		$folder = 'tempdocs/'.$part1.'/';
		
		$path_formula_uk_1 = $folder.$n.'fu.htm';
		$path_formula_uk_2 = $folder.$n.'pu.htm';

		if ( file_exists( $path_formula_uk_2 ) )
			$path_formula_uk = $path_formula_uk_2;
	
		if ( file_exists( $path_formula_uk_1 ) )
			$path_formula_uk = $path_formula_uk_1;
	}


	$fileLink = array(
			'claim'			=> array( 'path' => $path_formula_uk, 'matTitle' => $LANG_SETTINGS['details']['formulaFull'].'&nbsp;', 'code' => 'fu' )
	);
	


	$access = false;

	if ( !empty( $addDbName ) )
	{
		//$access = true;
		if ( $addDbName == 'app' )
		{
			// для статистики
			// =============
			if ( $currFullBiblioChapter == 'biblio' )
				doStatistics('createnewaction', 'appinvc', null, $_SESSION['statInfo']['idUser'], 4, $mssql, null); // 4 - пергляд бібліографічних даних
			elseif ( file_exists($fileLink['claim']['path']) )
				doStatistics('createnewaction', 'appinvc', null, $_SESSION['statInfo']['idUser'], 5, $mssql, null); // 5 - пергляд документа
		}
	}
	
	//print_r($fileLink);

	if ( !empty($fullBiblio) )
	{
		while(list($fname, $fvalue) = each($fullBiblio))
			$fullBiblio[$fname] = ltrim(rtrim($fullBiblio[$fname]));
		
		$fullBiblio['i_71_ukr'] = str_replace('###app###', '; ', $fullBiblio['i_71_ukr']);
		$fullBiblio['i_71_rus'] = str_replace('###app###', '; ', $fullBiblio['i_71_rus']);
		$fullBiblio['i_71_eng'] = str_replace('###app###', '; ', $fullBiblio['i_71_eng']);
		
		$fullBiblio['i_72_ukr'] = str_replace('###inv###', '; ', $fullBiblio['i_72_ukr']);
		$fullBiblio['i_72_rus'] = str_replace('###inv###', '; ', $fullBiblio['i_72_rus']);
		$fullBiblio['i_72_eng'] = str_replace('###inv###', '; ', $fullBiblio['i_72_eng']);

		$fullBiblio['i_73_ukr'] = str_replace('###prop###', '; ', $fullBiblio['i_73_ukr']);
		$fullBiblio['i_73_rus'] = str_replace('###prop###', '; ', $fullBiblio['i_73_rus']);
		$fullBiblio['i_73_eng'] = str_replace('###prop###', '; ', $fullBiblio['i_73_eng']);

		$fullBiblio['i_46'] = str_replace('бюл', $LANG_SETTINGS['details']['b'], $fullBiblio['i_46']);
		
		$ipcarr = explode('###mpk###', $fullBiblio['i_51']);
		$ipcTitle = $ipcarr[0];
		unset($ipcarr[0]);
		$fullBiblio['i_51'] = implode('<br>', $ipcarr);
		
		$fullBiblio['i_56'] = str_replace('###analog###', '<br>', $fullBiblio['i_56']);
		$fullBiblio['i_62'] = str_replace('###convent###', '<br>', $fullBiblio['i_62']);
		
		$inid31arr = explode('###convent###', $fullBiblio['i_31']);
		$inid32arr = explode('###convent###', $fullBiblio['i_32']);
		$inid33arr = explode('###convent###', $fullBiblio['i_33']);

		if ( empty($inid31arr[0]) )
		{
			$inid31arr = array();
			$inid32arr = array();
			$inid33arr = array();			
		}
		
		$fullBiblio['i_51'] = textBlink($currDbName, $fullBiblio['i_51'], 'MPK', false);
		$fullBiblio['i_56'] = textBlink($currDbName, $fullBiblio['i_56'], 'ANALOG', false);
		$fullBiblio['i_54_ukr'] = textBlink($currDbName, $fullBiblio['i_54_ukr'], 'TITLE', false);
		$fullBiblio['i_71_ukr'] = textBlink($currDbName, $fullBiblio['i_71_ukr'], 'APP', false);
		$fullBiblio['i_72_ukr'] = textBlink($currDbName, $fullBiblio['i_72_ukr'], 'INV', false);
		$fullBiblio['i_73_ukr'] = textBlink($currDbName, $fullBiblio['i_73_ukr'], 'PROP', false);
		
		
		$fullBiblio['i_54_ukr'] = devidedLongNames($fullBiblio['i_54_ukr'], 30);
		

		$publication = $LANG_SETTINGS['res']['publ'];
		
		if ($currDbName == 'invc')
		{
			$publication = str_replace('%1', '<b>'.$fullBiblio['claimBullDate'].'</b>', $publication);		
			$publication = str_replace('%2', '<b>'.$fullBiblio['claimBullNumber'].'</b>', $publication);		
		}
		else
		{
			$publication = str_replace('%1', '<b>'.$fullBiblio['i_46'].'</b>', $publication);		
			$publication = str_replace('%2', '<b>'.$fullBiblio['patentBullNumber'].'</b>', $publication);		
		}

		/*
		if ( (int)$fullBiblio['i_13_code'] == 53 )
			$fullBiblio['i_11'] .= '&nbsp;A';
		*/

/*
		print_r($inid31arr);
		print('<br>');
		print_r($inid32arr);
		print('<br>');
		print_r($inid33arr);
		print('<br>');
*/		
	} // if ( !empty($fullBiblio) )
	
	//$fullBiblio['i_20']	= '22';
	//print_r($fileLink);
	
	//$fileLink['claim']['path'] = '';
	
?>

		<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tbody>
		<tr>
            <td colspan="5">
			<table border="0" cellpadding="0" cellspacing="0" width="100%">
			<tbody>
			
			<!-- First header row covers the tops of the tabs. Three cells per tab. -->
			<tr>
<?
	reset($currChapterTitles);
	while( list( $key, $val ) = each( $currChapterTitles ) )
	{
		$selStr = 'un';
		if ( $key == $currFullBiblioChapter )
			$selStr = '';
		
?>

				<td class="tab_<?=$selStr;?>sel_topLeft" valign="bottom"><img alt="" src="images/esp/point.gif" height="3" width="13"></td>
				<td class="tab_<?=$selStr;?>sel_top" valign="bottom"><img alt="" src="images/esp/point.gif" height="3" width="4"></td>
				<td class="tab_<?=$selStr;?>sel_topRight" valign="bottom"><img alt="" src="images/esp/point.gif" height="4" width="15"></td>

<?
	} // end for
?>
				<td rowspan="2" align="right" valign="bottom"><img alt="" src="images/esp/point_wit.gif" height="2" width="2"></td>
			</tr>






			<!-- Second header row covers the contents of the tabs. Three cells per tab. -->
			<tr>
<?
	
	reset($currChapterTitles);
	while( list( $key, $val ) = each( $currChapterTitles ) )
	{
		$cTitle = $val;

		$selStr = 'un';
		$cFontStr = '<a href="search.php?action=viewdetails&IdClaim='.$idClaim.'&chapter='.$key.'&dbname='.$currDbName.'" class="viennacat2">'.$cTitle.'</font>';
				
		if ( $key != 'biblio' && empty( $fileLink[$key]['path'] ) )
			$cFontStr = '<font style="color:#ffffff" class="viennacat2">'.$cTitle.'</font>';
			

		$w = 200;
		if ( $key == 'claim' )
			$w = 270;

		if ( $key == $currFullBiblioChapter )
		{
			$selStr = '';
			$cFontStr = '<font class="viennacat">'.$cTitle.'</font>';
		}
		
?>
				<td class="tab_<?=$selStr;?>sel_left" width="13">&nbsp;</td>
				<td width=<?=$w;?> height=20 class="tab_<?=$selStr;?>sel"><?=$cFontStr;?></td>
				<td class="tab_<?=$selStr;?>sel_right" width="15">&nbsp;</td>

<?
	} // end for
?>
			</tr>







			<!-- Third header row covers the bottoms of the tabs. -->
			<!-- ONE cell per UNSELECTED tab. The SELECTED tab covers THREE cells-->
			<tr>
<?
	reset($currChapterTitles);
	while( list( $key, $val ) = each( $currChapterTitles ) )
	{
		$selStr = 'un';
		if ( $key == $currFullBiblioChapter )
		{
?>

				<td class="tab_sel_botLeft" valign="bottom"><img alt="" src="images/esp/tab_sel_lb.gif" height="2" width="13"></td>
				<td class="tab_sel_bot" valign="bottom"><img alt="" src="images/esp/point.gif" height="1"></td>
				<td class="tab_sel_botRight" valign="bottom"><img alt="" src="images/esp/point.gif" height="2" width="15"></td>
<?

		} // end if
		else
		{
		
?>
				<td colspan="3" class="tab_unsel_bot" valign="bottom"><img alt="" src="images/esp/point.gif" height="2" width="2"></td>

<?
		} // end else
	} // end for
?>


				<td class="tab_unsel_bot" align="right" valign="bottom">
				<div align="right"><img alt="" src="images/esp/tab_top_right.gif" height="2" width="15"><img alt="" src="images/esp/point_wit.gif" height="2" width="0"></div>
				</td>
			</tr>

			</tbody>
			</table>
			
			
			<table border="0" cellpadding="0" cellspacing="0" width="100%">
			<tbody>
			<tr> 
				<td class="tab_left"><img alt="" src="images/esp/point.gif" height="2" width="2"></td>
				<td class="tab_sel" width="100%"><img alt="" src="images/esp/point.gif" height="2" width="2"></td>
				<td class="tab_sel" width="100%"><img alt="" src="images/esp/point.gif" height="2" width="2"></td>
				<td class="tab_right"><img alt="" src="images/esp/point.gif" height="2" width="2"></td>
			</tr> 
			
<?
			if ( $currFullBiblioChapter == 'biblio' )
			{
?>
			<tr>
				<td class="tab_left"><img alt="" src="images/esp/point.gif" height="2" width="2"></td>
				<td class="tab_sel" colspan="2" id="contentCell" valign="top">

					<table border="0" cellpadding="0" cellspacing="0" width="100%">
					<tbody>

					<tr>
						<td valign="top" colspan=2>
						<table class="absTable" border="0" cellspacing="2" cellpadding="0" width=100%>
						<tbody>

						<tr valign="top">
							<td colspan=4 width=10>
							<table border="0" cellspacing="0" cellpadding="0" width=700>
							<tr><td colspan=4 height="5"><img src="images/spacer.gif" height="5"></td></tr>						
							
							<tr>
								<td valign="top" colspan=4 height=10>
								<table border="0" cellspacing="0" cellpadding="0" width=100%>
								<tbody>
								<tr valign="top">
								
								<td align=left><font class="viennacat2"><?=$publication;?></font></td>
								
								<?
								if ( $currDbName != 'invc' && isDiskBul == 'no' )
								{
								?>
									<td align=right>
										<font class="viennacat2"><?=$statusStr;?></font>
									</td>
			
									<td width="5"><img src="images/spacer.gif" height="1" width="5"></td>
									<td width=14>
										<img alt="<?=$statusStr;?>" height=14 width=14 align=top src="<?=$statusImg;?>">
									</td>
		
								<?
								} // end if ( $currDbName != 'invc' )
								?>

								</tr>

									
								</tbody>
								</table>

								</td>
							</tr>

							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							
							<?
							if ( $currDbName != 'invc' )
							{
							?>
							
							<tr>
								<td colspan=4>
								<table border=0 cellspacing="0" cellpadding="0" width=100%>
								<tr valign="top">
									<td width=35><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid11'];?>">(11)</acronym></font></td>
									<td width=150><font style="font-size: 16px" class="viennacat"><?=$fullBiblio['i_11'];?></font></td>
									<td width=35 rowspan=3 valign="top"><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid51'];?>">(51)</acronym></font></td>
									<td rowspan=3 valign="top"><font class="viennacat2"><?=$ipcTitle;?><BR><?=$fullBiblio['i_51'];?></font></td>
								</tr>
	
								<tr><td height="8"><img src="images/spacer.gif" height="8"></td></tr>						
	
							<?
								if ( !empty( $fullBiblio['i_10'] ) )
								{
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid10'];?>">(10)</acronym></font></td>
								<td colspan=3 valign="top"><font class="viennacat2"><?=$fullBiblio['i_10'];?></font></td>
								
							</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_10'] ) )
							?>

								</table>
								</td>
							</tr>

							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						

								<tr>
									<td valign="bottom"><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid24'];?>">(24)</acronym></font></td>
									<td valign="bottom" colspan=3><font class="viennacat"><?=$fullBiblio['i_24'];?></font></td>
								</tr>

							
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
							<tr>
								<td colspan=4>
								<table border=0 cellspacing="0" cellpadding="0" width=100%>
								<tr valign="top">
									<td width=35 valign=top><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid21'];?>">(21)</acronym></font></td>
									<td width=150 valign="middle"><font class="viennacat"><?=$fullBiblio['i_21'];?></font></td>
									<td width=35><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid22'];?>">(22)</acronym></td>
									<td valign="middle"><font class="viennacat"><?=$fullBiblio['i_22'];?></font></td>
								</tr>
	
								</table>
								</td>
							</tr>




							<?
							} // end if ( $currDbName != 'invc' )
							else
							{
							?>

							<tr>
								<td colspan=4>
								<table border=0 cellspacing="0" cellpadding="0" width=100%>
								<tr valign="top">
									<td width=35 valign=top><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid21'];?>">(21)</acronym></font></td>
									<td width=150><font style="font-size: 16px" class="viennacat"><?=$fullBiblio['i_21'];?></font></td>
									<td width=35 rowspan=3 valign="top"><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid51'];?>">(51)</acronym></font></td>
									<td rowspan=3 valign="top"><font class="viennacat2"><?=$ipcTitle;?><BR><?=$fullBiblio['i_51'];?></font></td>
								</tr>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td width=35><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid22'];?>">(22)</acronym></font></td>
									<td valign="top"><font class="viennacat"><?=$fullBiblio['i_22'];?></font></td>
								</tr>
								</table>
								</td>
							</tr>
							<?
							} // end else ( $currDbName == 'invc' )
							?>


							<?
							if ( !empty( $fullBiblio['i_20'] ) )
							{
								if ( strstr( $fullBiblio['i_20'], ' ' ) ) // есть номер заявки и дата
									$fname_20 = 4;
								elseif ( strstr( $fullBiblio['i_20'], '.' ) && !empty( $fullBiblio['i_10'] ) ) // есть дата и есть номер свидетельства СССР
									$fname_20 = 2;
								else
									$fname_20 = 1;
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid20_'.$fname_20];?>">(20)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat"><?=$fullBiblio['i_20'];?></font></td>
								</tr>
	
							<?
							} // end if ( !empty( $fullBiblio['i_20'] ) )
							?>


							<?
							for($i = 0; $i < count($inid31arr); $i++)
							{
							?>
							
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid31'];?>">(31)</acronym></font></td>
								<td colspan=3 valign="middle"><font class="viennacat"><?=$inid31arr[$i];?></font></td>
							</tr>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid32'];?>">(32)</acronym></font></td>
								<td colspan=3 valign="middle"><font class="viennacat"><?=$inid32arr[$i];?></font></td>
							</tr>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid33'];?>">(33)</acronym></font></td>
								<td colspan=3 valign="middle"><font class="viennacat"><?=$inid33arr[$i];?></font></td>
							</tr>
	
							<?
							} // end for
							?>
	
							<?
								if ( !empty( $fullBiblio['i_62'] ) )
								{
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid62'];?>">(62)</acronym></font></td>
								<td colspan=3 valign="top"><font class="viennacat"><?=$fullBiblio['i_62'];?></font></td>
								
							</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_62'] ) )
							?>
							
							<?
								if ( !empty( $fullBiblio['i_56'] ) && $access )
								{
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid56'];?>">(56)</acronym></font></td>
								<td colspan=3 valign="middle"><font class="viennacat2"><?=$fullBiblio['i_56'];?></font></td>
							</tr>
	
							<?
								} // end if !empty( $fullBiblio['i_56'] )
							?>
	
							<?
								if ( !empty( $fullBiblio['i_85'] ) )
								{
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid85'];?>">(85)</acronym></font></td>
								<td colspan=3 valign="middle"><font class="viennacat"><?=$fullBiblio['i_85'];?></font></td>
							</tr>
	
							<?
								} // end if !empty( $fullBiblio['i_86'] )
							?>

							<?
								if ( !empty( $fullBiblio['i_86'] ) )
								{
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid86'];?>">(86)</acronym></font></td>
								<td colspan=3 valign="middle"><font class="viennacat"><?=$fullBiblio['i_86'];?></font></td>
							</tr>
	
							<?
								} // end if !empty( $fullBiblio['i_86'] )
							?>
							
	
							<?
								if ( !empty( $fullBiblio['i_71_ukr'] ) && $currDbName == 'invc' )
								{
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid71'];?>">(71)</acronym></font></td>
								<td colspan=3 valign="middle">
								<font class="viennacat"><?=$fullBiblio['i_71_ukr'];?></font>
								<?
									if ( !empty( $fullBiblio['i_71_rus'] ) )
									{
								?>
									<br><font class="viennacat2">...................................................................................................................................................................</font>
									<br><font class="viennacat"><?=$fullBiblio['i_71_rus'];?></font>
								<?
									}
								?>
	
									
								<?
									if ( !empty( $fullBiblio['i_71_eng'] ) )
									{
								?>
									<br><font class="viennacat2">...................................................................................................................................................................</font>
									<br><font class="viennacat"><?=$fullBiblio['i_71_eng'];?></font>
	
								<?
									}
								?>
	
								</td>
							</tr>
	
							<?
								} // end if !empty( $fullBiblio['i_71_ukr'] )
							?>
	
							<?
								if ( !empty( $fullBiblio['i_72_ukr'] ) )
								{
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid72'];?>">(72)</acronym></font></td>
								<td colspan=3 valign="middle">
								<font class="viennacat2"><?=$fullBiblio['i_72_ukr'];?></font>
								<?
									if ( !empty( $fullBiblio['i_72_rus'] ) )
									{
								?>
									<br><font class="viennacat2">...................................................................................................................................................................</font>
									<br><font class="viennacat2"><?=$fullBiblio['i_72_rus'];?></font>
								<?
									}
								?>
	
									
								<?
									if ( !empty( $fullBiblio['i_72_eng'] ) )
									{
								?>
									<br><font class="viennacat2">...................................................................................................................................................................</font>
									<br><font class="viennacat2"><?=$fullBiblio['i_72_eng'];?></font>
	
								<?
									}
								?>
	
								</td>
							</tr>
							<?
								} // end if !empty( $fullBiblio['i_72_ukr'] )
							?>
	
	
							<?
								if ( !empty( $fullBiblio['i_73_ukr'] ) && $currDbName != 'invc' )
								{
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid73'];?>">(73)</acronym></font></td>
								<td colspan=3 valign="middle">
								<font class="viennacat"><?=$fullBiblio['i_73_ukr'];?></font>
								<?
									if ( !empty( $fullBiblio['i_73_rus'] ) )
									{
								?>
									<br><font class="viennacat2">...................................................................................................................................................................</font>
									<br><font class="viennacat"><?=$fullBiblio['i_73_rus'];?></font>
								<?
									}
								?>
	
									
								<?
									if ( !empty( $fullBiblio['i_73_eng'] ) )
									{
								?>
									<br><font class="viennacat2">...................................................................................................................................................................</font>
									<br><font class="viennacat"><?=$fullBiblio['i_73_eng'];?></font>
	
								<?
									}
								?>
	
								</td>
							</tr>
							<?
								} // end if !empty( $fullBiblio['i_73_ukr'] )
							?>
	
	
							<?
								if ( !empty( $fullBiblio['i_54_ukr'] ) )
								{
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['inv_details']['inid54'];?>">(54)</acronym></font></td>
								<td colspan=3 valign="middle">
								<font class="viennacat"><?=$fullBiblio['i_54_ukr'];?></font>
								<?
									if ( !empty( $fullBiblio['i_54_rus'] ) )
									{
								?>
									<br><font class="viennacat2">...................................................................................................................................................................</font>
									<br><font class="viennacat"><?=$fullBiblio['i_54_rus'];?></font>
								<?
									}
								?>
	
									
								<?
									if ( !empty( $fullBiblio['i_54_eng'] ) )
									{
								?>
									<br><font class="viennacat2">...................................................................................................................................................................</font>
									<br><font class="viennacat"><?=$fullBiblio['i_54_eng'];?></font>
	
								<?
									}
								?>
	
								</td>
							</tr>
							<?
								} // end if !empty( $fullBiblio['i_54_ukr'] )
							?>
	
	
							
							<?
							if ( $currDbName != 'invc' )
							{
							?>
							
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							
							<tr valign="top">
								<td width=35><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['details']['formulaFull_'.$nn].'&nbsp;'.$_SESSION['lastFullBiblioPatentNumber'];?>">(57)</acronym></font></td>
								
								<td width=660 colspan=3 valign="middle" 
								<?
									if ( !file_exists($fileLink['claim']['path']) )
									{
								?>
									align="left">
									<font class="viennacat2">[<?=$LANG_SETTINGS['details']['nodata'];?>]</font>
								<?
									}
									else
									{
								?>
									align="right">
									<a class="viennacatchange" target=_blank href="getdocument.php?claimnumber=<?=$claim_number;?>&doctype=<?=$fileLink['claim']['code'];?>"><?=$LANG_SETTINGS['details']['opennew'];?></a>
	
								<?
									}
								?>
	
								</td>
							</tr>
		
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>	

							<tr>
								<td colspan=4>

<?
					if ( $currFullBiblioChapter == 'biblio' && !empty( $fileLink['claim']['path'] ) )
					{
?>				

								<table border="0" cellpadding="0" cellspacing="0" width="100%">
								<tbody>
								<tr>
									<td class="tab_inner_lt"><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
									<td class="tab_inner_mt"><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
									<td class="tab_inner_rt"><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
								</tr>
								
								<tr>
									<td class="tab_inner_lm"><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
									<td class="tab_inner" width="100%">
										<table>
										<tbody>
			
										<tr>
											<td id="abCell" valign="top">
											<iframe vspace="5" width=670 height=200 frameborder=0 scrolling="auto" 
											<?
											if ( isInvDocFromDb == 'yes' )
											{
											?>
											 src="getdocument.php?claimnumber=<?=$claim_number;?>&doctype=<?=$fileLink['claim']['code'];?>">
											<?
											}
											else
											{
											?>
 											 src="<?=$fileLink['claim']['path'];?>">
											<?
											}
											?>
											</iframe>
										</tr>
										</tbody>
										</table>
									</td>
									<td class="tab_inner_rm"><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
								</tr>
								
								<tr>
									<td class="tab_inner_lb"><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
									<td class="tab_inner_mb"><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
									<td class="tab_inner_rb"><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
								</tr>
								</tbody>
								</table>								

<?
					} // end if $currFullBiblioChapter == 'biblio'
?>				

								</td>
							</tr>
							
							<?
								} // end if ( $currDbName != 'invc' )
								else
								{
							?>

							<tr>
								<td width=35>&nbsp;</td>
								<td width=660 colspan=3 valign="middle">&nbsp;</td>
							</tr>

							<?
								} // end else ( $currDbName != 'invc' )
							?>

							</table>

							</td>
						</tr>

						</tbody>
						</table>
						</td>

					</tr>

					</tbody>
					</table>
					
				</td>
				<td class="tab_right"><img alt="" src="images/esp/point.gif" height="2" width="2"></td>
			</tr>
<?
			} // end if $currFullBiblioChapter == 'biblio'
?>				


<?
			if ( $currFullBiblioChapter != 'biblio' )
			{
?>
			<tr>
				<td class="tab_left"><img alt="" src="images/esp/point.gif" height="2" width="2"></td>
				<td class="tab_sel" colspan="2" id="contentCell" valign="top">
					<img alt="" src="images/esp/point.gif" height="4" width="1">

					<table border="0" cellpadding="0" cellspacing="0" width="100%">
					<tbody>
					<tr>
						<td width="100%" valign="top">
							<font class="viennacat2">
							<?=$LANG_SETTINGS['details']['formulaFull_'.$nn].'&nbsp;'.$_SESSION['lastFullBiblioPatentNumber'];?>
							</font>
						</td>
					</tr>
					
					<?
						if ( file_exists($fileLink[$currFullBiblioChapter]['path']) )
						{
					?>
					<tr>
						<td style="padding-right: 5px;" align=right><a class="viennacatchange" target=_blank href="getdocument.php?claimnumber=<?=$claim_number;?>&doctype=<?=$fileLink[$currFullBiblioChapter]['code'];?>"><?=$LANG_SETTINGS['details']['opennew'];?></a></td>
					</tr>
					<?
						}
					?>
					
					</tbody>
					</table>
				</td>
				<td class="tab_right"><img alt="" src="images/esp/point.gif" height="2" width="2"></td>
			</tr>

			<tr>
				<td class="tab_left"><img alt="" src="images/esp/point.gif" height="2" width="2"></td>
				<td class="tab_sel" align="left" valign="top">&nbsp;</td>
				<td class="tab_sel" align="left" valign="top">&nbsp;</td>
				<td class="tab_right"><img alt="" src="images/esp/point.gif" height="2" width="2"></td>
			</tr>
<?
			} // end if $currFullBiblioChapter != 'biblio'
?>				

			
			<tr>
				<td class="tab_left" width="13"><img alt="" src="images/esp/point.gif" height="2" width="2"></td>
				<td colspan="2" class="tab_sel" id="abstractOuter" align="left" valign="top">
<?
					if ($currFullBiblioChapter != 'biblio')
					{
?>				

					<?
					if( file_exists( $fileLink[$currFullBiblioChapter]['path'] ) )
					{
					?>

					<table border="0" cellpadding="0" cellspacing="0" width="100%">
					<tbody>
					<tr>
						<td class="tab_inner_lt"><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
						<td class="tab_inner_mt"><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
						<td class="tab_inner_rt"><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
					</tr>
					
					<tr>
						<td class="tab_inner_lm"><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
						<td class="tab_inner" width="100%">
							<table>
							<tbody>
							<tr>
								<td id="abCell" valign="top">
								<iframe vspace="5" width=680 frameborder=0 scrolling="auto" height=400
								<?
								if ( isInvDocFromDb == 'yes' )
								{
								?>
								 src="getdocument.php?claimnumber=<?=$claim_number;?>&doctype=<?=$fileLink[$currFullBiblioChapter]['code'];?>">
								<?
								}
								else
								{
								?>
								 src="<?=$fileLink[$currFullBiblioChapter]['path'];?>">
								<?
								}
								?>
								</iframe>
								
								</td>
							</tr>
							</tbody>
							</table>
						</td>
						<td class="tab_inner_rm"><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
					</tr>
					
					<tr>
						<td class="tab_inner_lb"><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
						<td class="tab_inner_mb"><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
						<td class="tab_inner_rb"><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
					</tr>
					</tbody>
					</table>

					<?
					} // end if file_exists( $fileLink['claim']['path'] )
					else
					{
					?>

					<table border="0" cellpadding="0" cellspacing="0" width="100%">
					<tbody>
					<tr>
						<td valign="top" align=center><font class="viennacat2">[<?=$LANG_SETTINGS['details']['nodata'];?>]</font></td>
					</tr>
					
					<tr><td height="15"><img src="images/spacer.gif" height="15"></td></tr>	
					</tbody>
					</table>

					<?
					} // end else f
					?>
				
<?
					} // end else
?>				

				</td>
				
				<td class="tab_right" width="15">&nbsp;</td>
			</tr>
			
			<tr>
				<td class="tab_botLeft" width="7"><img alt="" src="images/esp/point.gif" height="10" width="7"></td>
				<td class="tab_bot" colspan="2" width="100%"><img alt="" src="images/esp/point.gif" height="10" width="344"></td>
				<td class="tab_botRight" width="9"><img alt="" src="images/esp/point.gif" height="10" width="9"></td>
			</tr>

			</tbody>
			</table>

			</td>
		</tr>

		<tr>
			<td><img alt="" src="images/esp/point.gif" height="1" width="10"></td>
			<td><img alt="" src="images/esp/point.gif" height="1" width="444"></td>
			<td><img alt="" src="images/esp/point.gif" height="1" width="80"></td>
			<td><img alt="" src="images/esp/point.gif" height="1" width="160"></td>
			<td><img alt="" src="images/esp/point.gif" height="1" width="10"></td>
		</tr>
		</tbody>
		</table>

