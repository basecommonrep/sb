<table width="500" border=0 cellspacing=0 cellpadding=0>
<?
	for($i = 0; $i < count($searchShortBiblioSet); $i++)
	{
		$noticeCode = $searchShortBiblioSet[$i][0];
		$fname = $searchShortBiblioSet[$i][1];		
		$bulinfo = $searchShortBiblioSet[$i][2];
		$bulNumber = $searchShortBiblioSet[$i][3];
		$bulDate = $searchShortBiblioSet[$i][4];

		$publication = $LANG_SETTINGS['res']['publ'];
		
		$publication = str_replace('%1', $bulDate, $publication);		
		$publication = str_replace('%2', $bulNumber, $publication);		
		
?>

	<tr>
		<td height=25 bgcolor="#00518f"><font class="restitle">&nbsp;<?=$publication;?></font></td>
	</tr>

	<tr><td height="10"><img src="images/spacer.gif" height="10"></td></tr>

	<tr>
		<td><iframe style="BORDER-TOP: #00518F 1px solid; BORDER-LEFT: #00518F 1px solid; BORDER-RIGHT: #00518F 1px solid; BORDER-BOTTOM: #00518F 1px solid; background-color: #FFFFEE;" vspace="5" width=700 height=800 frameborder=0 scrolling="auto" src="tempdocs/<?=$fname;?>"></iframe></td>
	</tr>


	<tr><td height="40"><img src="images/spacer.gif" height="40"></td></tr>


<?
	} // end for
?>
</table>
