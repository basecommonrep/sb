<?
	if ( !empty($fullBiblio) )
	{
		while(list($fname, $fvalue) = each($fullBiblio))
			$fullBiblio[$fname] = ltrim(rtrim($fullBiblio[$fname]));
    
	} // if ( !empty($fullBiblio) )
?>

		<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tbody>
		<tr>
            <td colspan="5">
			<table border="0" cellpadding="0" cellspacing="0" width="100%">
			<tbody>

			<!-- Third header row covers the bottoms of the tabs. -->
			<!-- ONE cell per UNSELECTED tab. The SELECTED tab covers THREE cells-->
			<tr>
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
			

			<tr>
				<td class="tab_left"><img alt="" src="images/esp/point.gif" height="2" width="2"></td>
				<td class="tab_sel" colspan="2" id="contentCell" valign="top">

					<table border="0" cellpadding="0" cellspacing="0" width="100%">
					<tbody>
					<tr><td colspan=2 height="5"><img src="images/spacer.gif" height="5"></td></tr>						


					<tr><td colspan=2 height="10"><img src="images/spacer.gif" height="10"></td></tr>						
					
					<tr>
						<td valign="top" colspan=2>

            <table border=0 height=100% width=100% cellpadding=0 cellspacing=0>
              <tr><td height=3 colspan=2><img height=3 width=1 src="images/spacer.gif"></td></tr>
            
              <tr valign=top>
                <td>
                  <table width=650 border=0 height=50 width=100% cellpadding=0 cellspacing=0>
<?
  if(!empty($fullBiblio['app_number']))
  {
?>
                  <tr>
                    <td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['geo_fields']['NC'];?></font></td>
                  </tr>

                  <tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

                  <tr>
                    <td width=20><img height=1 width=20 src="images/spacer.gif"></td>
                    <td width=580><font class="viennacat2"><?=$fullBiblio['app_number'];?></font></td>
                  </tr>

                  <tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
<?
  }

  if(!empty($fullBiblio['app_date']))
  {
?>
                  <tr>
                    <td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['geo_fields']['FD'];?></font></td>
                  </tr>

                  <tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

                  <tr>
                    <td><img height=1 width=20 src="images/spacer.gif"></td>
                    <td><font class="viennacat2"><?=$fullBiblio['app_date'];?></font></td>
                  </tr>
                  
                  <tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
<?
  }

  if(!empty($fullBiblio['Holder']))
  {
?>
                  <tr>
                    <td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['geo_fields']['artem2'];?></font></td>
                  </tr>

                  <tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

                  <tr>
                    <td><img height=1 width=20 src="images/spacer.gif"></td>
                    <td><font class="viennacat2"><?=$fullBiblio['Holder'];?></font></td>
                  </tr>
              
                  <tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
<?
  }

  if(!empty($fullBiblio['product_name']))
  {
?>
                  <tr>
                    <td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['geo_fields']['appGOODNAME'];?></font></td>
                  </tr>

                  <tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

                  <tr>
                    <td><img height=1 width=20 src="images/spacer.gif"></td>
                    <td><font class="viennacat2"><?=$fullBiblio['product_name'];?></font></td>
                  </tr>

                  <tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
<?
  }

  if(!empty($fullBiblio['area']))
  {
?>
                  <tr>
                    <td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['geo_fields']['artem4'];?></font></td>
                  </tr>

                  <tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

                  <tr>
                    <td><img height=1 width=20 src="images/spacer.gif"></td>
                    <td><font class="viennacat2"><?=$fullBiblio['area'];?></font></td>
                  </tr>

                  <tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
<?
  }

  if(!empty($fullBiblio['descr']))
  {
?>
                  <tr>
                    <td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['geo_fields']['artem5'];?></font></td>
                  </tr>

                  <tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

                  <tr>
                    <td><img height=1 width=20 src="images/spacer.gif"></td>
                    <td><font class="viennacat2"><?=$fullBiblio['descr'];?></font></td>
                  </tr>

                  <tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
<?
  }

  if(!empty($fullBiblio['termofuse']))
  {
?>
                  <tr>
                    <td colspan=2><font class="viennacat"><?=$LANG_SETTINGS['geo_fields']['artem6'];?></font></td>
                  </tr>

                  <tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>

                  <tr>
                    <td><img height=1 width=20 src="images/spacer.gif"></td>
                    <td><font class="viennacat2"><?=$fullBiblio['termofuse'];?></font></td>
                  </tr>

                  <tr><td height=5 colspan=2><img height=5 width=1 src="images/spacer.gif"></td></tr>
<?
  }
?>
                  </tr>
                  </table>
                </td>
                
              </tr>
            
              <tr><td height=3 colspan=2><img height=3 width=1 src="images/spacer.gif"></td></tr>
              
              </table>
              
						</td>
					</tr>

					</tbody>
					</table>
				</td>
				<td class="tab_right"><img alt="" src="images/esp/point.gif" height="2" width="2"></td>
			</tr>
				


			
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

