<?
	$access = false;
	if ( !empty( $addDbName ) )
		$access = true;


	$access = false;
	if ( !empty( $addDbName ) )
	{
		$access = true;
		if ( $addDbName == 'cert' )
		{
			// для статистики
			// =============
			if ( $currFullBiblioChapter == 'biblio' )
				doStatistics('createnewaction', 'certmadridall', null, $_SESSION['statInfo']['idUser'], 4, $mssql, null); // 4 - пергляд бібліографічних даних
	
			// тому що перегляд бібліографії влючає такоє перегляд документу
			doStatistics('createnewaction', 'certmadridall', null, $_SESSION['statInfo']['idUser'], 5, $mssql, null); // 5 - пергляд документа		
		}
	}
	
	//print($currFullBiblioChapter);
		
	$idClaim = (int)$_GET['IdClaim'];
	if ( !empty($fullBiblio) )
	{
		while(list($fname, $fvalue) = each($fullBiblio))
			$fullBiblio[$fname] = ltrim(rtrim($fullBiblio[$fname]));
			


		/*		
		$xmlPath = 'tempdocs/xml_'.$_GET['IdClaim'].'.xml';
		if ( file_exists($xmlPath) )
		{
			$handle = fopen($xmlPath, "r+");
			$xml = fread($handle, filesize($xmlPath));
			fseek($handle, 0);

			
			fwrite($handle, $t);
			
			fclose($handle);
	
			//$fullBiblio['i_732'] = textBlink($currDbName, $fullBiblio['i_732'], 'PROP', false);

		}
		*/
		

	} // if ( !empty($fullBiblio) )

	// для php5
	//$data = mb_convert_encoding($data, "UTF-8", "Windows-1251"); 
	
	if ( version_compare(PHP_VERSION,'5','>=') && extension_loaded('xsl') ) 
	{
		/*
		print('php5');
		require_once('incs/xslt-php4-to-php5.php.inc'); 
		*/
		
		$xsl = new DomDocument();
		$xsl->load("images/madridall/rom_01.xsl");

		$inputDom = new DomDocument();
		$inputDom->load('tempdocs/xml_'.$idClaim.'.xml');

		$proc = new XsltProcessor();
		$xsl = $proc->importStylesheet($xsl);
		$res = $proc->transformToXML($inputDom);
	}
	else
	{
		$xsl_error = false;
		$xslt = xslt_create() or $xsl_error = true;
	
		$stylesheetfile = 'images/madridall/rom_01.xsl';
		$sourcefile = 'tempdocs/xml_'.$idClaim.'.xml';
	
		$sourcehandle = fopen($sourcefile, "r");
		$xml = fread($sourcehandle, filesize($sourcefile));
		
		
	    $stylesheethandle = fopen($stylesheetfile, "r");
	    $xsl = fread($stylesheethandle, filesize($stylesheetfile));
	    
	    //print($xml);
	    
		$arguments = array(
	    '/_xml' => $xml,
	    '/_xsl' => $xsl
	    );
	
		$res = @xslt_process($xslt, 'arg:/_xml', 'arg:/_xsl', NULL, $arguments) or $xsl_error = true;
		
		if ( $xsl_error ) 
			$res = '<font class="viennacat2">Помилка обробки xml документа ('.@xslt_error($xslt).')</font>';
	
		@xslt_free($xslt) or $xsl_error = true;
	}
	
	$img = 'tempdocs/madrid_'.$fullBiblio['idClaim'].'.'.$fullBiblio['imageType'];
	
	$res = str_replace('X_IMAGE_FILENAME', $img, $res);
	$res = str_replace('@NAME', $fullBiblio['fi_540'], $res);
	
	

	
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

					<tr><td colspan=2 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
					
					<tr>
						<td valign="top" colspan=2>
						<table class="absTable" border="0" cellspacing="2" cellpadding="0" width=100%>
						<tbody>

						<tr valign="top">
							<td colspan=4 width=10>
							<table border="0" cellspacing="0" cellpadding="0" width=700>
							<tr>
								<td>
								
								<?=$res;?>

								</td>
							</tr>

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
						<td width="40" valign="bottom"><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid210'];?>">(210)</font></td>
						<td width="" valign="top">
							<font style="font-size: 16px" class="viennacat"><?=$_SESSION['lastFullBiblioPatentNumber'];?></font>
						</td>
					</tr>

					<tr><td height="10" colspan=2><img src="images/spacer.gif" height="10"></td></tr>						
					
					<tr>
						<td width="40" valign="top"><font class="viennacatunder"><acronym title="<?=$LANG_SETTINGS['tm_details']['inid540'];?>">(540)</font></td>
						<td width="" valign="top">
							<?
							if ( file_exists( $img ) )
							{
							?>
							<img border=0 src="<?=$img;?>">
							<?
							}
							else
							{
							?>
							<font class="pageHeaderText"><?=$fullBiblio['fi_540'];?></font>
							<?
							}
							?>
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

