<table width="320" border=0 cellspacing=0 cellpadding=5 class="mt">
<?
	switch($currSecName)
	{
		case 'nump':
			$f1 = '(111)&nbsp;'.$LANG_SETTINGS['tm_fields']['NCERT'];
			$f2 = '(511)&nbsp;'.$LANG_SETTINGS['tm_fields']['MKTP'];
		break;

		case 'syst':
			$f1 = '(511)&nbsp;'.$LANG_SETTINGS['tm_fields']['MKTP'];
			$f2 = '(111)&nbsp;'.$LANG_SETTINGS['tm_fields']['NC'];
		break;
	}
?>


<tr class="hdr" align=center>
	<td width=160 height=35 align=center><b><font class="viennacat" style="color:#FFFFFF"><?=$f1;?></font></b></td>
	<td width=160 align=center class=""><b><font class="viennacat" style="color:#FFFFFF"> <?=$f2;?></font></b></td>
</tr>

<?
	for($i = 0; $i < count( $searchShortBiblioSet ); $i++)
	{
		$row = $searchShortBiblioSet[$i];
	
		$idClaim = $row[0]; // idclaim
		$field1 = $row[1]; // i_111
		$field2 = $row[2]; // mktp

		$line_bgcolor = "";
		if ( ($i % 2) == 0 )
	 		$line_bgcolor = "#C5D9EB";
?>

<?	
	if ( $currSecName == 'nump' )
	{
?>
	<tr bgcolor="<?=$line_bgcolor;?>">
		<td align=center><font class="viennacat2"><?=$field1;?></font></td>
		<td align=center><font class="viennacat2"><?=$field2;?></font></td>
	</tr>
<?	
	} // inv - numc
	elseif ( $currSecName == 'syst' )
	{
?>
	<tr bgcolor="<?=$line_bgcolor;?>">
		<td align=center><font class="viennacat2"><?=$field2;?></font></td>
		<td align=center><font class="viennacat2"><?=$field1;?></font></td>
	</tr>
<?	
	} // inv - syst
?>

<?
	} // end for
?>
</table>
