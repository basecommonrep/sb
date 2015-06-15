<?
	$access = false;
	if ( !empty( $addDbName ) )
	{
		$access = true;
		if ( $addDbName == 'cert' )
		{
			// для статистики
			// =============
			if ( $currFullBiblioChapter == 'biblio' )
				doStatistics('createnewaction', 'certpp', null, $_SESSION['statInfo']['idUser'], 4, $mssql, null); // 4 - пергляд бібліографічних даних

			// тому що перегляд бібліографії влючає такоє перегляд документу
			doStatistics('createnewaction', 'certpp', null, $_SESSION['statInfo']['idUser'], 5, $mssql, null); // 5 - пергляд документа		
		}
	}
		
	//$access = false;

	
	$statusImg = 'images/green.gif';
	$statusStr = $LANG_SETTINGS['pp_fields']['patenton'];
	if ( !empty( $fullBiblio['i_14'] ) )
	{
	 	$statusImg = 'images/red.gif';	
		$statusStr = $LANG_SETTINGS['pp_fields']['patentoff'];
		
		$date_fi_14 = new DateTime($fullBiblio['i_14']);
		$date_end = new DateTime($fullBiblio['i_14']);
		$date_end->modify('+6 month');
		$date_now = new DateTime;

			if ( ( $fullBiblio['status'] == 'Нагадування про необхідність підтримання чинності патенту') && (($date_now >= $date_fi_14) && ($date_now < $date_end)) )
			{
				$statusImg = 'images/yellow.gif';
				$statusStr = $LANG_SETTINGS['pp_fields']['patentoff_6m'];
			}
	}
	
	if ( $fullBiblio['status'] == 'Нагадування про необхідність підтримання чинності патенту')
		{
			$statusImg = 'images/yellow.gif';
			$statusStr = $LANG_SETTINGS['pp_fields']['patentoff_6m'];
		}
	
	if ( ( $fullBiblio['status'] == 'Повідомлення про припинення дії патента у разі несплати збору') && (empty( $fullBiblio['i_14'])) )
		{
			$statusImg = 'images/yellow.gif';
			$statusStr = $LANG_SETTINGS['pp_fields']['patentoff_6m'];
		}

	if ( !empty($fullBiblio) )
	{
		while(list($fname, $fvalue) = each($fullBiblio))
			$fullBiblio[$fname] = ltrim(rtrim($fullBiblio[$fname]));
		
		$fullBiblio['i_71'] = str_replace('###app###', '<br>', $fullBiblio['i_71']);
		$fullBiblio['i_72'] = str_replace('###inv###', '<br>', $fullBiblio['i_72']);
		$fullBiblio['i_73'] = str_replace('###prop###', '<br><br>', $fullBiblio['i_73']);
		$fullBiblio['i_62'] = str_replace('###poper###', '<br>', $fullBiblio['i_62']);
		$fullBiblio['i_66'] = str_replace('###poper###', '<br>', $fullBiblio['i_66']);
		
		$fullBiblio['i_51'] = str_replace('###mkpz###', ', ', $fullBiblio['i_51']); 
		
		$inid31arr = explode('###convent###', $fullBiblio['i_31']);
		$inid32arr = explode('###convent###', $fullBiblio['i_32']);
		$inid33arr = explode('###convent###', $fullBiblio['i_33']);

		if ( empty($inid31arr[0]) )
		{
			$inid31arr = array();
			$inid32arr = array();
			$inid33arr = array();			
		}
		
		$fullBiblio['i_51'] = textBlink($currDbName, $fullBiblio['i_51'], 'MKPZ', false);
		$fullBiblio['i_54'] = textBlink($currDbName, $fullBiblio['i_54'], 'TITLE', false);
		$fullBiblio['i_72'] = textBlink($currDbName, $fullBiblio['i_72'], 'AUTH', false);
		$fullBiblio['i_73'] = textBlink($currDbName, $fullBiblio['i_73'], 'PROP', false);

		$publication = $LANG_SETTINGS['res']['publ'];
		$publication = str_replace('%1', '<b>'.$fullBiblio['bulletinDate'].'</b>', $publication);		
		$publication = str_replace('%2', '<b>'.$fullBiblio['bulletinNumber'].'</b>', $publication);		
	} // if ( !empty($fullBiblio) )
	
	//print_r($fullBiblio);
	
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
	} // end while
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
				

		$wi = 230;
		if ( $key == 'biblio' )
			$wi = 190;
		
		if ( $key == $currFullBiblioChapter )
		{
			$selStr = '';
			$cFontStr = '<font class="viennacat">'.$cTitle.'</font>';
		}
		
?>
				<td class="tab_<?=$selStr;?>sel_left" width="13">&nbsp;</td>
				<td width=<?=$wi;?> height=20 class="tab_<?=$selStr;?>sel"><?=$cFontStr;?></td>
				<td class="tab_<?=$selStr;?>sel_right" width="15">&nbsp;</td>

<?
	} // end while
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
	} // end while
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
				<td class="tab_sel" width="10%"><img alt="" src="images/esp/point.gif" height="2" width="2"></td>
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
					<tr><td colspan=2 height="5"><img src="images/spacer.gif" height="5"></td></tr>						
					<tr>
						<td valign="top">&nbsp;</td>
												
						<td height=10>
						<table width=100% border="0" cellspacing="0" cellpadding="0">
						<tbody>
						<tr valign="top">
							<td width=450 align=left><font class="viennacat2"><?=$publication;?></font></td>

							<?
							if ( isDiskBul == 'no' )
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
							}
							?>

						</tr>
						</tbody>
						</table>
						</td>
					</tr>

					<tr><td colspan=2 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
					
					<tr>
						<td valign="top" colspan=2>
						<table class="absTable" border="0" cellspacing="2" cellpadding="0" width=100%>
						<tbody>

						<tr valign="top">
							<td colspan=4 width=10>
							<table border="0" cellspacing="0" cellpadding="0" width=700>
							
							<tr valign="top">
								<td width=35><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid51'];?>">(51)</acronym></font></td>
								<td width=665 colspan=3><font class="viennacat">МКПЗ&nbsp;<?=$fullBiblio['i_51'];?></font></td>
							</tr>

							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							
							<tr valign="top">
								<td width=35><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid11'];?>">(11)</acronym></font></td>
								<td width=255><font style="font-size: 16px" class="viennacat"><?=$fullBiblio['i_11'];?></font></td>
								<td width=35 valign="top" ><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid21'];?>">(21)</acronym></font></td>
								<td width=375 valign="top"><font class="viennacat"><?=$fullBiblio['i_21'];?></font></td>
							</tr>

							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						

							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid24'];?>">(24)</acronym></font></td>
								<td valign="top"><font class="viennacat"><?=$fullBiblio['i_24'];?></font></td>
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid22'];?>">(22)</acronym></td>
								<td valign="middle"><font class="viennacat"><?=$fullBiblio['i_22'];?></font></td>
							</tr>

							<?
								if ( !empty( $fullBiblio['i_10'] ) && $access )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid10'];?>">(10)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat"><?=$fullBiblio['i_10'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_10'] ) )
							?>
	
							<?
								if ( !empty( $fullBiblio['i_20'] ) && $access )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid20'];?>">(20)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat"><?=$fullBiblio['i_20'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_20'] ) )
							?>
	
							<?
								if ( !empty( $fullBiblio['i_23'] ) )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid23'];?>">(23)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat"><?=$fullBiblio['i_23'];?>; <?= $fullBiblio['i_23_country']; ?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_23'] ) )
							?>
	
							<?
							for($i = 0; $i < count($inid31arr); $i++)
							{
							?>
							
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid31'];?>">(31)</acronym></font></td>
								<td colspan=3 valign="middle"><font class="viennacat"><?=$inid31arr[$i];?></font></td>
							</tr>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid32'];?>">(32)</acronym></font></td>
								<td colspan=3 valign="middle"><font class="viennacat"><?=$inid32arr[$i];?></font></td>
							</tr>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid33'];?>">(33)</acronym></font></td>
								<td colspan=3 valign="middle"><font class="viennacat"><?=$inid33arr[$i];?></font></td>
							</tr>
	
							<?
							} // end for
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
							<tr valign="top">
								<td width=35><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid54'];?>">(54)</acronym></font></td>
								<td colspan=3 valign="middle">
									<font class="viennacat"><?=$fullBiblio['i_54'];?></font>
								</td>
							</tr>
							
							<?
							if ( $addDbName == 'reestr' )
							{
							/*
							?>

							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							<tr valign="top">
								<td>&nbsp;</td>
								<td colspan=3 valign="top">
								<table border="0" cellpadding="0" cellspacing="0" width="650">
								<tr>
									<td width=140 valign=top><font class="viennacatchange">10.02.2006, 3/2006</font></td>
									<td width=610><font class="viennacatchange">АВТОМАТИЗОВАНА ГАЗОРОЗПОДІЛЬНА СТАНЦІЯ</font></td>
								</tr>
								<tr><td colspan=2 height="5"><img src="images/spacer.gif" height="5"></td></tr>						
								<tr>
									<td valign=top><font class="viennacatchange">10.06.2007, 11/2007</font></td>
									<td><font class="viennacatchange">РИСУНОК ПРОТЕКТОРА</font></td>
								</tr>
								<tr><td colspan=2 height="5"><img src="images/spacer.gif" height="5"></td></tr>						
								<tr>
									<td valign=top><font class="viennacatchange">10.02.2006, 3/2006</font></td>
									<td><font class="viennacatchange">РЕШІТКА ПОВІТРОЗАБІРНИКА ВЕНТИЛЯЦІЇ ТРАНСПОРТНОГО ЗАСОБУ</font></td>
								</tr>

								</table>
								</td>
							</tr>

							<?
							*/
							} // end if addDbName
							?>
							
	

							<?
								if ( !empty( $fullBiblio['i_62'] ) )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid62'];?>">(62)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat"><?=$fullBiblio['i_62'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_62'] ) )
							?>

							<?
								if ( !empty( $fullBiblio['i_66'] ) && $access )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid66'];?>">(66)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat"><?=$fullBiblio['i_66'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_66'] ) )
							?>

	
							<?
								if ( !empty( $vi[0]['colors'] ) )
								{
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid55'];?>">(55)</acronym></font></td>
								<td colspan=3 valign="top">
							<?
								for ($k = 1; $k <= count($vi); $k++)
								{
								if (!empty($vi[$k-1]['colors']))
								{
							?>
								<font class="viennacat2"><?=$k;?>&nbsp;<?=$LANG_SETTINGS['details']['ppVar'];?>&nbsp;-&nbsp;<?=$vi[$k-1]['colors'];?></font><br>
	
							<?
								}
								} // end for
							?>
	
								</td>
								
							</tr>
	
							<?
								} // end if ( !empty( $vi[0]['colors'] ) )
							?>
	
	
							<?
								if ( !empty( $fullBiblio['i_71'] ) && $access )
								{
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid71'];?>">(71)</acronym></font></td>
								<td colspan=3 valign="middle">
									<font class="viennacat2"><?=$fullBiblio['i_71'];?></font>
								</td>
							</tr>
							<?
								} // end if !empty( $fullBiblio['i_71'] )
							?>

							<?
								if ( !empty( $fullBiblio['i_72'] ) )
								{
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid72'];?>">(72)</acronym></font></td>
								<td colspan=3 valign="middle">
									<font class="viennacat2"><?=$fullBiblio['i_72'];?></font>
								</td>
							</tr>
							<?
								} // end if !empty( $fullBiblio['i_72'] )
							?>

							<?
							if ( $addDbName == 'reestr' )
							{
							/*
							?>


							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							<tr valign="top">
								<td>&nbsp;</td>
								<td colspan=3 valign="top">
								<table border="0" cellpadding="0" cellspacing="0" width="650">
								<tr>
									<td width=140 valign=top><font class="viennacatchange">10.02.2007, 3/2007</font></td>
									<td width=610><font class="viennacatchange">Тряхов Валерій Миколайович, Гальчинський Ігор Борисович, Чуйко Генадій Володимирович</font></td>
								</tr>

								</table>
								</td>
							</tr>
							<?
							*/
							} // end if addDbName
							?>
	
	
							<?
								if ( !empty( $fullBiblio['i_73'] ) )
								{
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid73'];?>">(73)</acronym></font></td>
								<td colspan=3 valign="middle">
									<font class="viennacat"><?=$fullBiblio['i_73'];?></font>
								</td>
							</tr>

							<?
								} // end if !empty( $fullBiblio['i_73'] )
							?>

							
							<?
							if ( $addDbName == 'reestr' )
							{
							/*
							?>

							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							<tr valign="top">
								<td>&nbsp;</td>
								<td colspan=3 valign="top">
								<table border="0" cellpadding="0" cellspacing="0" width="650">
								<tr>
									<td width=140 valign=top><font class="viennacatchange">10.02.2006, 3/2006</font></td>
									<td width=610><font class="viennacatchange">Національний науковий центр "Інститут механізації та електрифікації сільського господарства" Української академії аграрних наук</font></td>
								</tr>
								<tr><td colspan=2 height="5"><img src="images/spacer.gif" height="5"></td></tr>						
								<tr>
									<td valign=top><font class="viennacatchange">10.06.2007, 11/2007</font></td>
									<td><font class="viennacatchange">ТОВАРИСТВО З ОБМЕЖЕНОЮ ВІДПОВІДАЛЬНІСТЮ "МИКОЛАЇВСЬКИЙ ГЛИНОЗЕМНИЙ ЗАВОД", <br>пр. Жовтневий, 471, м. Миколаїв, 54051</font></td>
								</tr>
								<tr><td colspan=2 height="5"><img src="images/spacer.gif" height="5"></td></tr>						
								<tr>
									<td valign=top><font class="viennacatchange">10.02.2006, 3/2006</font></td>
									<td><font class="viennacatchange">АстраЗенека АБ (пабл), SE-151 85 Sodertalje, Sweden, SE</font></td>
								</tr>

								</table>
								</td>
							</tr>

							<?
							*/
							} // end if addDbName
							?>

							
	
							<?
								if ( !empty( $fullBiblio['i_74'] ) && $access )
								{
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid74'];?>">(74)</acronym></font></td>
								<td colspan=3 valign="middle">
									<font class="viennacat2"><?=$fullBiblio['i_74'];?></font>
								</td>
							</tr>
							<?
								} // end if !empty( $fullBiblio['i_74'] )
							?>
	

							<?
							if ( $addDbName == 'reestr' )
							{
							/*
							?>

							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							<tr valign="top">
								<td>&nbsp;</td>
								<td colspan=3 valign="top">
								<table border="0" cellpadding="0" cellspacing="0" width="650">
								<tr>
									<td width=140 valign=top><font class="viennacatchange">11.12.2008, 3/2008</font></td>
									<td width=610><font class="viennacatchange">«Слободянюк та Партнери» (UA)</font></td>
								</tr>

								</table>
								</td>
							</tr>

							<?
							*/
							} // end if addDbName
							?>

							<?
								if ( !empty( $fullBiblio['i_98'] ) && $access )
								{
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid98'];?>">(98)</acronym></font></td>
								<td colspan=3 valign="middle">
									<font class="viennacat2"><?=$fullBiblio['i_98'];?></font>
								</td>
							</tr>
							<?
								} // end if !empty( $fullBiblio['i_98'] )
							?>
	
							<?
							if ( $addDbName == 'reestr' )
							{
							/*
							?>

							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							<tr valign="top">
								<td>&nbsp;</td>
								<td colspan=3 valign="top">
								<table border="0" cellpadding="0" cellspacing="0" width="650">
								<tr>
									<td width=140 valign=top><font class="viennacatchange">16.12.2006, 7/2004</font></td>
									<td width=610><font class="viennacatchange">Авраменко Наталія Василівна</font></td>
								</tr>

								</table>
								</td>
							</tr>

							<?
							*/
							} // end if addDbName
							?>

							<?
								if ( (int)$fullBiblio['i_28'] > 1 )
								{
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid28'];?>">(28)</acronym></font></td>
								<td colspan=3 valign="middle">
									<font class="viennacat"><?=$fullBiblio['i_28'];?>&nbsp;<?=$LANG_SETTINGS['details']['ppVars'];?></font>
								</td>
							</tr>
							<?
								} // end if !empty( $fullBiblio['i_28'] )
							?>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							
							<tr valign="top">
								<td><font class="viennacat">&nbsp;</td>
								<td colspan=3 valign="middle">
								<?
									include('../searchBul/incs/restables/view_pp_variants.php.inc');
								?>

								</td>
							</tr>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							
							<?
							if ( $addDbName == 'reestr' )
							{
							/*
							?>

							<tr valign="top">
								<td colspan=4><font class="viennawhitebgr">Сповіщення:</font></td>
							</tr>

							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="5"></td></tr>	

							<tr valign="top">
								<td>&nbsp;</td>
								<td colspan=3>
								<table border="0" cellpadding="0" cellspacing="0" width="100%">
								<tr>
									<td>
										<font class="viennacat">Припинення дії патенту на промисловий зразок у разі несплати річного збору</font>
									</td>
								</tr>

								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>	

								<tr>
									<td>
									<table border="0" cellpadding="5" cellspacing="0" width="480">
									<tr valign="top">
										<td class="notifyHeader"><font class="viennacatwhite">(11) Номер патенту</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">(21) Номер заявки</font></td>
										<td class="notifyHeaderNot"><font class="viennacatwhite">Дата припинення дії патенту</font></td>
									</tr>
									<tr vlaign="top">
										<td class="notifyLine" align="left"><font class="viennacat2"><?=$fullBiblio['i_11'];?></font></td>
										<td class="notifyLine" align="left"><font class="viennacat2"><?=$fullBiblio['i_21'];?></font></td>
										<td class="notifyLineNot" align="left"><font class="viennacat2">03.03.2006</font></td>
									</tr>
									</table>
									</td>
								</tr>

								<tr><td colspan=4 height="15"><img src="images/spacer.gif" height="15"></td></tr>	

								<tr>
									<td>
										<font class="viennacat">Заява власника патенту про надання будь-якій особі дозволу на використання промислового зразка</font>
									</td>
								</tr>

								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>	

								<tr>
									<td>
									<table border="0" cellpadding="5" cellspacing="0" width="650">
									<tr valign=top>
										<td class="notifyHeader"  width=120><font class="viennacatwhite">(11) Номер патенту</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">(46) Дата публікації та номер бюлетеня</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">(54) Назва корисної моделі</font></td>
										<td class="notifyHeaderNot"><font class="viennacatwhite">(73) Повне ім'я або найменування власника патенту та адреса для листування</font></td>
									</tr>
									<tr valign="top">
										<td class="notifyLine"><font class="viennacat2"><?=$fullBiblio['i_11'];?></font></td>
										<td class="notifyLine"><font class="viennacat2">16.09.2002 Бюл. № 9</font></td>
										<td class="notifyLine"><font class="viennacat2"><?=$fullBiblio['i_54'];?></font></td>
										<td class="notifyLineNot"><font class="viennacat2">
										Товариство з обмеженою відповідальністю "МЕКАП";вул. Лелюківська, 7, м. Харків, 61030; UA
										</font></td>
									</tr>
									</table>
									</td>
								</tr>

								<tr><td colspan=4 height="15"><img src="images/spacer.gif" height="15"></td></tr>	

								<tr>
									<td>
										<font class="viennacat">Видача ліцензії на використання промислового зразка</font>
									</td>
								</tr>

								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>	

								<tr>
									<td>
									<table border="0" cellpadding="5" cellspacing="0" width="650">
									<tr valign=top>
										<td class="notifyHeader"  width=120><font class="viennacatwhite">(11) Номер патенту</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">Ім'я або повне найменування ліцензіара</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">Ім'я або повне найменування ліцензіата</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">Вид ліцензії</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">Реєстрацій-ний номер рішення</font></td>
										<td class="notifyHeaderNot"><font class="viennacatwhite">(58) Дата внесення відомостей до Реєстру</font></td>
									</tr>
									<tr valign="top">
										<td class="notifyLine"><font class="viennacat2"><?=$fullBiblio['i_11'];?></font></td>
										<td class="notifyLine"><font class="viennacat2">ТІКОН БІЗНЕС ЛТД(CY)</font></td>
										<td class="notifyLine"><font class="viennacat2">ВІДКРИТЕ АКЦІОНЕРНЕ ТОВАРИСТВО "КИЇВСЬКИЙ ЗАВОД ГУМОВИХ ТА ЛАТЕКСНИХ ВИРОБІВ"</font></td>
										<td class="notifyLine"><font class="viennacat2">ЛН</font></td>
										<td class="notifyLine"><font class="viennacat2">557</font></td>
										<td class="notifyLineNot"><font class="viennacat2">25.01.2008</font></td>
									</tr>
									<tr valign="top">
										<td colspan=6><font class="viennacat2">ЛВ - ліцензія виключна, ЛН - ліцензія невиключна</font></td>
									</tr>

									</table>
									</td>
								</tr>

								<tr><td colspan=4 height="15"><img src="images/spacer.gif" height="15"></td></tr>	

								<tr>
									<td>
										<font class="viennacat">Передача права власності на промисловий зразок</font>
									</td>
								</tr>

								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>	

								<tr>
									<td>
									<table border="0" cellpadding="5" cellspacing="0" width="650">
									<tr valign=top>
										<td class="notifyHeader"  width=120><font class="viennacatwhite">(11) Номер патенту</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">(73) Ім'я або повне найменування власника патенту</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">Ім'я або повне найменування правонаступника власника патенту</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">Реєстрацій-ний номер рішення</font></td>
										<td class="notifyHeaderNot"><font class="viennacatwhite">(58) Дата внесення відомостей до Реєстру</font></td>
									</tr>
									<tr valign="top">
										<td class="notifyLine"><font class="viennacat2"><?=$fullBiblio['i_11'];?></font></td>
										<td class="notifyLine"><font class="viennacat2">АГРОТЕХНІЧНА КОРПОРАЦІЯ "УКРАГРОКОМ";вул. Мечникова, 16-а, м. Київ, 01133 (UA)</font></td>
										<td class="notifyLine"><font class="viennacat2">Товариство з обмеженою відповідальністю "УКРАЇНСЬКА АГРОТЕХНІЧНА КОМПАНІЯ СІЛЬСЬКОГОСПОДАРСЬКОГО МАШИНОБУДУВАННЯ"</font></td>
										<td class="notifyLine"><font class="viennacat2">2371</font></td>
										<td class="notifyLineNot"><font class="viennacat2">25.07.2007</font></td>
									</tr>
									</table>
									</td>
								</tr>

								<tr><td colspan=4 height="15"><img src="images/spacer.gif" height="15"></td></tr>	

								<tr>
									<td>
										<font class="viennacat">Виправлення очевидних помилок у публікаціях відомостей про видачу патентів на промислові зразки</font>
									</td>
								</tr>

								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>	

								<tr>
									<td>
									<table border="0" cellpadding="5" cellspacing="0" width="650">
									<tr valign=top>
										<td class="notifyHeader"  width=120><font class="viennacatwhite">(11) Номер патенту</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">(21) Номер заявки</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">(46) Дата публікації та номер бюлетеня</font></td>
										<td class="notifyHeaderNot"><font class="viennacatwhite">Слід читати</font></td>
									</tr>
									<tr valign="top">
										<td class="notifyLine"><font class="viennacat2"><?=$fullBiblio['i_11'];?></font></td>
										<td class="notifyLine"><font class="viennacat2"><?=$fullBiblio['i_21'];?></font></td>
										<td class="notifyLine"><font class="viennacat2">16.09.2002. Бюл. № 9</font></td>
										<td class="notifyLineNot"><font class="viennacat2">(73) Товариство з обмеженою відповідальністю з іноземними інвестиціями "Сан Інтербрю Україна";вул. Боженка, 87, м. Київ, 03150; UA</font></td>
									</tr>
									</table>
									</td>
								</tr>

								</table>
								</td>
							</tr>
							
							<?
							*/
							} // end if !empty addDbName
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
							<font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['pp_details']['inid11'];?>">(11)</acronym></font>&nbsp;
							<font style="font-size: 16px" class="viennacat">
							<?=$_SESSION['lastFullBiblioPatentNumber'];?>
							</font>
						</td>
					</tr>
					</tbody>
					</table>
				</td>
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
					<table border="0" cellpadding="0" cellspacing="0" width="100%">
					<tbody>
					
					<tr>
						<td><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
						<td width="100%">
							<table>
							<tbody>
							<tr>
								<td valign="top">
								<?
									include('../searchBul/incs/restables/view_pp_variants.php.inc');
								?>

								</td>
							</tr>
							</tbody>
							</table>
						</td>
						<td><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
					</tr>
					
					<tr>
						<td><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
						<td><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
						<td><img alt="" src="images/esp/point.gif" height="6" width="6"></td>
					</tr>
					</tbody>
					</table>
				
<?
					} // end if $currFullBiblioChapter != 'biblio'
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

