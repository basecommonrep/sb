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
				doStatistics('createnewaction', 'certtm', null, $_SESSION['statInfo']['idUser'], 4, $mssql, null); // 4 - пергляд бібліографічних даних

			// тому що перегляд бібліографії влючає такоє перегляд документу
			doStatistics('createnewaction', 'certtm', null, $_SESSION['statInfo']['idUser'], 5, $mssql, null); // 5 - пергляд документа		
		}
		
		if ($currDbName == 'tmc')
		{
			doStatistics('createnewaction', 'apptmc', null, $_SESSION['statInfo']['idUser'], 4, $mssql, null); // 4 - пергляд бібліографічних даних

			// тому що перегляд бібліографії влючає такоє перегляд документу
			doStatistics('createnewaction', 'apptmc', null, $_SESSION['statInfo']['idUser'], 5, $mssql, null); // 5 - пергляд документа	
		}
	}

    // Если есть 141-й код, то статус "красный" и проверок больше не надо
	if ( !empty( $fullBiblio['i_141'] ) )
	{
	 	$statusImg = 'images/red.gif';	
		$statusStr = $LANG_SETTINGS['tm_fields']['patentoff'];
	} else { // Если статус действительный, то нужно ещё проверить не просрочена ли оплата (до полугода)
        $now = time();
        $i_181UnixTime = strtotime($fullBiblio['i_181']);
        $i_186UnixTime = strtotime($fullBiblio['i_186']);
        if ($now >= $i_181UnixTime && (is_null($fullBiblio['i_186']) || $now >= $i_186UnixTime)) {
            //$dateFinalIndex = ($i_186UnixTime > $i_181UnixTime) ? 'i_186' : 'i_181';
            //$dateFinalUnixTime = strtotime("{$fullBiblio[$dateFinalIndex]} +6 months");

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

	if ( !empty($fullBiblio) )
	{
		while(list($fname, $fvalue) = each($fullBiblio))
			$fullBiblio[$fname] = ltrim(rtrim($fullBiblio[$fname]));
		
		$fullBiblio['i_731'] = str_replace('###app###', '<br>', $fullBiblio['i_731']);
		$fullBiblio['i_732'] = str_replace('###prop###', '<br>', $fullBiblio['i_732']);
		$fullBiblio['i_732'] = str_replace('УЕФА', 'УЄФА', $fullBiblio['i_732']);
		$fullBiblio['i_531'] = str_replace('###vienna###', '<br>', $fullBiblio['i_531']);
		$fullBiblio['i_539'] = str_replace('###keywords###', '; ', $fullBiblio['i_539']);
		$fullBiblio['i_591'] = str_replace('###colors###', ', ', $fullBiblio['i_591']);

		$inid310arr = explode('###priorclaim###', $fullBiblio['i_310']);
		$inid320arr = explode('###priorclaim###', $fullBiblio['i_320']);
		$inid330arr = explode('###priorclaim###', $fullBiblio['i_330']);
		
		//print_r($inid310arr);

		if ( empty($inid310arr[0]) )
		{
			$inid310arr = array();
			$inid320arr = array();
			$inid330arr = array();			
		}

		$fullBiblio['i_641'] = str_replace('###pravo641###', '<br>', $fullBiblio['i_641']);
		$fullBiblio['i_646'] = str_replace('###pravo646###', '<br>', $fullBiblio['i_646']);
				
		$mktp = explode('###mktp###', $fullBiblio['i_511']);

		$fullBiblio['i_732'] = textBlink($currDbName, $fullBiblio['i_732'], 'PROP', false);
		$fullBiblio['i_539'] = textBlink($currDbName, $fullBiblio['i_539'], 'KEYW', false);
		$fullBiblio['i_591'] = textBlink($currDbName, $fullBiblio['i_591'], 'COLORS', false);

		$publication = $LANG_SETTINGS['res']['publ'];
		$publication = str_replace('%1', '<b>'.$fullBiblio['bulletinDate'].'</b>', $publication);		
		$publication = str_replace('%2', '<b>'.$fullBiblio['bulletinNumber'].'</b>', $publication);		
		
		if ( !empty( $fullBiblio['i_556'] ) && $access )
		{
			SaveSoundToTemp($fullBiblio['idClaim']);
		}

	} // if ( !empty($fullBiblio) )
	
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
				

		$wi = 160;
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
							<?
							if ( $currDbName != 'tmc' )
							{
							?>

							<td width=450 align=left><font class="viennacat2"><?=$publication;?></font></td>
							<?
							} // != tmc
							?>

							<?
							if ( $currDbName != 'tmc' && isDiskBul == 'no' )
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
							} // != tmc
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

							<?
							if ( $currDbName == 'tm' )
							{
							?>
							<tr valign="top">
								<td width=35 valign=top><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid111'];?>">(111)</acronym></font></td>
								<td width=255><font style="font-size: 16px" class="viennacat"><?=$fullBiblio['i_111'];?></font></td>
								<td width=40 valign="top" ><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid210'];?>">(210)</acronym></font></td>
								<td width=370 valign="top"><font class="viennacat"><?=$fullBiblio['i_210'];?></font></td>
							</tr>
							<?
							}
							else
							{
							?>
							<tr valign="top">
								<td width=35 valign="top" ><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid210'];?>">(210)</acronym></font></td>
								<td width=370 valign="top"><font><a class="viennacat" target="_blank" href="http://base.uipv.org/SearchTMStat/showclaimdetails.php?IdClaim=<?=$fullBiblio['idClaim'];?>&resId=1"><?=$fullBiblio['i_210'];?></a></font></td>
							</tr>

							<?
							} // != tmc
							?>

							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						

							<?
							if ( $currDbName == 'tm' )
							{
							?>
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid151'];?>">(151)</acronym></font></td>
								<td valign="top"><font class="viennacat"><?=$fullBiblio['i_151'];?></font></td>
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid220'];?>">(220)</acronym></td>
								<td valign="middle"><font class="viennacat"><?=$fullBiblio['i_220'];?></font></td>
							</tr>
							<?
							}
							else
							{
							?>							
							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid220'];?>">(220)</acronym></td>
								<td valign="middle"><font class="viennacat"><?=$fullBiblio['i_220'];?></font></td>
							</tr>
							<?
							} // != tmc
							?>

							<?
							if ( $currDbName != 'tmc' )
							{
							?>
							
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						

							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid181'];?>">(181)</acronym></font></td>
								<td colspan=3 valign="top"><font class="viennacat"><?=$fullBiblio['i_181'];?></font></td>
							</tr>
							<?
							} // != tmc
							?>	
							
							<?
								if ( !empty( $fullBiblio['i_100'] ) && $access && $currDbName != 'tmc' )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid100'];?>">(100)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat"><?=$fullBiblio['i_100'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_100'] ) )
							?>

							<?
								if ( !empty( $fullBiblio['i_141'] ) && $access && $currDbName != 'tmc' )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid141'];?>">(141)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$fullBiblio['i_141'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_141'] ) )
							?>

							<?
								if ( !empty( $fullBiblio['i_186'] ) && $access && $currDbName != 'tmc' )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid186'];?>">(186)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$fullBiblio['i_186'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_186'] ) )
							?>


							<?
								if ( !empty( $fullBiblio['i_200'] ) && $access )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid200'];?>">(200)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$fullBiblio['i_200'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_200'] ) )
							?>

							<?
								if ( !empty( $fullBiblio['i_230'] ))
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid230'];?>">(230)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$fullBiblio['i_230'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_230'] ) )
							?>


							<?
							//if ( $access )
							for($i = 0; $i < count($inid310arr); $i++)
							{
							?>
							
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
							<tr valign="top">
								<td><font class="viennacatinid"><acronym title="<?=$LANG_SETTINGS[$currDbName.'_details']['inid310'];?>">(310)</acronym></font></td>
								<td colspan=3 valign="middle"><font class="viennacat"><?=$inid310arr[$i];?></font></td>
							</tr>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
							<tr valign="top">
								<td><font class="viennacatinid"><acronym title="<?=$LANG_SETTINGS[$currDbName.'_details']['inid320'];?>">(320)</acronym></font></td>
								<td colspan=3 valign="middle"><font class="viennacat"><?=$inid320arr[$i];?></font></td>
							</tr>
	
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
							<tr valign="top">
								<td><font class="viennacatinid"><acronym title="<?=$LANG_SETTINGS[$currDbName.'_details']['inid330'];?>">(330)</acronym></font></td>
								<td colspan=3 valign="middle"><font class="viennacat"><?=$inid330arr[$i];?></font></td>
							</tr>
	
							<?
							} // end for
							?>


							<?
								if ( !empty( $fullBiblio['i_526'] ) && $access && $currDbName != 'tmc' )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid526'];?>">(526)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$fullBiblio['i_526'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_526'] ) )
							?>

							<?
								if ( !empty( $fullBiblio['i_531'] ) && $access && $currDbName == 'tmc' )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid531'];?>">(531)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$fullBiblio['i_531'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_531'] ) )
					
							?>

							<?
								if ( !empty( $fullBiblio['i_551'] ) && $access )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid551'];?>">(551)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$LANG_SETTINGS['tm_details']['inid551'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_551'] ) )
							?>

							<?
								if ( !empty( $fullBiblio['i_554'] ) && $access )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid554'];?>">(554)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$LANG_SETTINGS['tm_details']['inid554'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_554'] ) )
							?>

							<?
								if ( !empty( $fullBiblio['i_555'] ) && $access && $currDbName != 'tmc' )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid555'];?>">(555)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$LANG_SETTINGS['tm_details']['inid555'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_555'] ) )
							?>

							<?
								if ( !empty( $fullBiblio['i_556'] ) && $access && $currDbName != 'tmc' )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid556'];?>">(556)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$LANG_SETTINGS['tm_details']['inid556'];?></font></td>
								</tr>
								<tr valign="top">
									<td><font class="viennacatunder"><acronym></acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><audio src="<?= 'tempdocs/'.$fullBiblio['idClaim'].'.wav'?>" controls></audio></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_556'] ) )
							?>

							<?
								if ( !empty( $fullBiblio['i_561'] ) && $access && $currDbName != 'tmc' )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid561'];?>">(561)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$fullBiblio['i_561'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_561'] ) )
							?>


							<?
								if ( !empty( $fullBiblio['i_591'] ) )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid591'];?>">(591)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$fullBiblio['i_591'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_591'] ) )
							?>

							<?
								if ( !empty( $fullBiblio['i_641'] ) && $access  && $currDbName != 'tmc' )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid641'];?>">(641)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$fullBiblio['i_641'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_641'] ) )
							?>

							<?
								if ( !empty( $fullBiblio['i_646'] ) && $access && $currDbName != 'tmc' )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid646'];?>">(646)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$fullBiblio['i_646'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_646'] ) )
							?>

							<?
								if ( !empty( $fullBiblio['i_731'] ) && $access )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid731'];?>">(731)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$fullBiblio['i_731'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_731'] ) )
							?>

							<?
							if ( $currDbName != 'tmc' )
							{
							?>

							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						

							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid732'];?>">(732)</acronym></font></td>
								<td colspan=3 valign="top"><font class="viennacat"><?=$fullBiblio['i_732'];?></font></td>
							</tr>
							<?
							} // != tmc
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
								if ( !empty( $fullBiblio['i_740'] ) && $access )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid740'];?>">(740)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$fullBiblio['i_740'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_740'] ) )
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
								if ( !empty( $fullBiblio['i_750'] ) && $access )
								{
							?>
	
								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
	
								<tr valign="top">
									<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid750'];?>">(750)</acronym></font></td>
									<td colspan=3 valign="top"><font class="viennacat2"><?=$fullBiblio['i_750'];?></font></td>
								</tr>
	
							<?
								} // end if ( !empty( $fullBiblio['i_750'] ) )
							?>

							<?
							if ( $addDbName == 'reestr' )
							{
							/*
							?>

							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
							<tr valign="top">
								<td width=45>&nbsp;</td>
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

							<tr><td colspan=4 height="5"><img src="images/spacer.gif" height="10"></td></tr>						

							<tr valign="top">
							<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid540'];?>">(540)</font></td>
							 <td colspan=3 valign="top" align=left>
								<?if (empty($fullBiblio['i_539note'])) 
								{ ?>
									<img border=0 src="resize.php?dbn=<?=$currDbName;?>&idClaim=<?=$fullBiblio['idClaim'];?>">
								<?}  
								else 
								{?> 
									<font class="viennacat"><?=$LANG_SETTINGS['tm_details']['inid539note'];?> <?=$fullBiblio['i_539note'];?></font> 
								<?} ?> 
							 </td>
							</tr>
							
							<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>						

							<tr valign="top">
								<td><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid511'];?>">(511)</acronym></font></td>
								<td colspan=3>&nbsp;</td>
							</tr>

							<tr><td colspan=4 height="5"><img src="images/spacer.gif" height="5"></td></tr>						


							<?
							for($i = 0; $i < count($mktp); $i++)
							{
								$mktpRow = explode('$$$', $mktp[$i]);
								$mktpRow[1][0] = strtoupper($mktpRow[1][0]);
								$mktpRow[1] = $mktpRow[1].';';
								
							?>

							<tr valign="top">
								<td width=40><font class="viennacat2">Кл.<?=$mktpRow[0];?>:</font></td>
								<td width=660 colspan=3 valign="top" align=left><p style="TEXT-ALIGN: justify"><font class="viennacat2"><?=$mktpRow[1];?></font></p></td>
							</tr>

							<tr><td colspan=4 height="5"><img src="images/spacer.gif" height="5"></td></tr>						

							<?
							} // end for $mktp
							?>
	
							<?
							if ( $addDbName == 'reestr' )
							{
							/*
							?>

							<tr><td colspan=4 height="20"><img src="images/spacer.gif" height="20"></td></tr>						
							
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
										<font class="viennacat">Припинення дії свідоцтва на знак для товарів та послуг разі несплати річного збору</font>
									</td>
								</tr>

								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>	

								<tr>
									<td>
									<table border="0" cellpadding="5" cellspacing="0" width="480">
									<tr valign="top">
										<td class="notifyHeader"><font class="viennacatwhite">(111) Номер свідоцтва</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">(210) Номер заявки</font></td>
										<td class="notifyHeaderNot"><font class="viennacatwhite">Дата припинення дії свідоцтва</font></td>
									</tr>
									<tr vlaign="top">
										<td class="notifyLine" align="left"><font class="viennacat2"><?=$fullBiblio['i_111'];?></font></td>
										<td class="notifyLine" align="left"><font class="viennacat2"><?=$fullBiblio['i_210'];?></font></td>
										<td class="notifyLineNot" align="left"><font class="viennacat2">03.03.2006</font></td>
									</tr>
									</table>
									</td>
								</tr>

								<tr><td colspan=4 height="15"><img src="images/spacer.gif" height="15"></td></tr>	

								<tr>
									<td>
										<font class="viennacat">Заява власника свідоцтва про надання будь-якій особі дозволу на використання знаку для товарів та послуг</font>
									</td>
								</tr>

								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>	

								<tr>
									<td>
									<table border="0" cellpadding="5" cellspacing="0" width="600">
									<tr valign=top>
										<td class="notifyHeader"  width=120><font class="viennacatwhite">(111) Номер свідоцтва</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">(450) Дата публікації та номер бюлетеня</font></td>
										<td class="notifyHeaderNot"><font class="viennacatwhite">(732) Повне ім'я або найменування власника свідоцтва та адреса для листування</font></td>
									</tr>
									<tr valign="top">
										<td class="notifyLine"><font class="viennacat2"><?=$fullBiblio['i_111'];?></font></td>
										<td class="notifyLine"><font class="viennacat2">16.09.2002 Бюл. № 9</font></td>
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
										<font class="viennacat">Видача ліцензії на використання знаку для товарів та послуг</font>
									</td>
								</tr>

								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>	

								<tr>
									<td>
									<table border="0" cellpadding="5" cellspacing="0" width="600">
									<tr valign=top>
										<td class="notifyHeader"  width=120><font class="viennacatwhite">(111) Номер свідоцтва</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">Ім'я або повне найменування ліцензіара</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">Ім'я або повне найменування ліцензіата</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">Вид ліцензії</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">Реєстрацій-ний номер рішення</font></td>
										<td class="notifyHeaderNot"><font class="viennacatwhite">(580) Дата внесення відомостей до Реєстру</font></td>
									</tr>
									<tr valign="top">
										<td class="notifyLine"><font class="viennacat2"><?=$fullBiblio['i_111'];?></font></td>
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
										<font class="viennacat">Передача права власності на знак для товарів та послуг</font>
									</td>
								</tr>

								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>	

								<tr>
									<td>
									<table border="0" cellpadding="5" cellspacing="0" width="600">
									<tr valign=top>
										<td class="notifyHeader"  width=120><font class="viennacatwhite">(111) Номер свідоцтва</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">(732) Ім'я або повне найменування власника свідоцтва</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">Ім'я або повне найменування правонаступника власника свідоцтва</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">Реєстрацій-ний номер рішення</font></td>
										<td class="notifyHeaderNot"><font class="viennacatwhite">(580) Дата внесення відомостей до Реєстру</font></td>
									</tr>
									<tr valign="top">
										<td class="notifyLine"><font class="viennacat2"><?=$fullBiblio['i_111'];?></font></td>
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
										<font class="viennacat">Виправлення очевидних помилок у публікаціях відомостей про видачу свідоцтв на знаки для товарів та послуг</font>
									</td>
								</tr>

								<tr><td colspan=4 height="10"><img src="images/spacer.gif" height="10"></td></tr>	

								<tr>
									<td>
									<table border="0" cellpadding="5" cellspacing="0" width="600">
									<tr valign=top>
										<td class="notifyHeader"  width=120><font class="viennacatwhite">(111) Номер свідоцтва</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">(210) Номер заявки</font></td>
										<td class="notifyHeader"><font class="viennacatwhite">(450) Дата публікації та номер бюлетеня</font></td>
										<td class="notifyHeaderNot"><font class="viennacatwhite">Слід читати</font></td>
									</tr>
									<tr valign="top">
										<td class="notifyLine"><font class="viennacat2"><?=$fullBiblio['i_111'];?></font></td>
										<td class="notifyLine"><font class="viennacat2"><?=$fullBiblio['i_210'];?></font></td>
										<td class="notifyLine"><font class="viennacat2">16.09.2002. Бюл. № 9</font></td>
										<td class="notifyLineNot"><font class="viennacat2">(732) Товариство з обмеженою відповідальністю з іноземними інвестиціями "Сан Інтербрю Україна";вул. Боженка, 87, м. Київ, 03150; UA</font></td>
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
					
					<?
					if( $currDbName != 'tmc')
					{
					?>
					<tr>
						<td width="40" valign="bottom"><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid111'];?>">(111)</font></td>
						<td width="" valign="top">
							<font style="font-size: 16px" class="viennacat"><?=$_SESSION['lastFullBiblioPatentNumber'];?></font>
						</td>
					</tr>
					<?
					}
					else
					{
					?> 
						<td width=40 valign="top" ><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid210'];?>">(210)</acronym></font></td>
						<td width=370 valign="top"><font"><font><a class="viennacat" target="_blank" href="http://base.uipv.org/SearchTMStat/showclaimdetails.php?IdClaim=<?=$fullBiblio['idClaim'];?>&resId=1"><?=$fullBiblio['i_210'];?></a></font></td>
					<?
					}
					?>
					<tr><td height="10" colspan=2><img src="images/spacer.gif" height="10"></td></tr>						
					
					<tr>
						<td width="40" valign="top"><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid540'];?>">(540)</font></td>
						<td width="" valign="top">

						<?if (empty($fullBiblio['i_539note'])) 
						{?>
							<img border=0 src="resize.php?dbn=<?=$currDbName;?>&idClaim=<?=$fullBiblio['idClaim'];?>&chapter=signimage">
						<?}  
						else 
						{?> 
							<font class="viennacat"><?=$LANG_SETTINGS['tm_details']['inid539note'];?> <?=$fullBiblio['i_539note'];?></font> 
						<?} ?> 	
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
				<td colspan="2" class="tab_sel" id="abstractOuter" align="left" valign="top"></td>
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

