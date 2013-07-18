<table width="300" border=0 cellspacing=0 cellpadding=5 class="mt">
<?
	switch($currSecName)
	{
		case 'nump':
			$f1 = $LANG_SETTINGS['tm_fields']['NCERT'];
			$f2 = $LANG_SETTINGS['tm_fields']['NC'];
			$f3 = $LANG_SETTINGS['tm_fields']['MKTP'];
		break;

		case 'numc':
			$f1 = $LANG_SETTINGS['tm_fields']['NC'];
			$f2 = $LANG_SETTINGS['tm_fields']['NCERT'];
			$f3 = $LANG_SETTINGS['tm_fields']['MKTP'];
		break;

		case 'syst':
			$f1 = $LANG_SETTINGS['tm_fields']['MKTP'];
			$f2 = $LANG_SETTINGS['tm_fields']['NC'];
			$f3 = $LANG_SETTINGS['tm_fields']['NCERT'];
		break;
	}
?>


<tr class="hdr" align=center>
	<td width=100 height=35 align=center><b><font class="viennacat" style="color:#FFFFFF"><?=$f1;?></font></b></td>
	<td width=100 align=center class=""><b><font class="viennacat" style="color:#FFFFFF"> <?=$f2;?></font></b></td>
	<td width=100 align=center class=""><b><font class="viennacat" style="color:#FFFFFF"> <?=$f3;?></font></b></td>
</tr>

<?
	for($i = 0; $i < count( $searchShortBiblioSet ); $i++)
	{
		$row = $searchShortBiblioSet[$i];
	
		$idClaim = $row[0]; // idclaim
		$field1 = $row[1]; // i_111
		$field2 = $row[2]; // i_210
		$field3 = $row[3]; // class mkpz
		
		if ( !((int)$field2[0] >= 1 && (int)$field2[0] <= 9) )
			$field2 = $field2[0].'&nbsp;'.substr($field2, 1, 4).'&nbsp;'.substr($field2, 5, strlen($field2));

		$line_bgcolor = "";
		if ( ($i % 2) == 0 )
	 		$line_bgcolor = "#C5D9EB";
?>

<?	
	if ( $currSecName == 'nump' )
	{
?>
	<tr bgcolor="<?=$line_bgcolor;?>">
		<td align=center class=""><font class="viennacat2"><?=$field1;?></font></td>
		<td align=center class=""><a style="text-decoration:underline" href="search.php?action=viewdetails&IdClaim=<?=$idClaim;?>&dbname=<?=$currDbName;?>&from=index" class="viennacat2"><?=$field2;?></a></td>
		<td align=center class=""><font class="viennacat2"><?=$field3;?></font></td>
	</tr>
<?	
	} // inv - numc
	elseif ( $currSecName == 'numc' )
	{
?>
	<tr bgcolor="<?=$line_bgcolor;?>">
		<td align=center class=""><a style="text-decoration:underline" href="search.php?action=viewdetails&IdClaim=<?=$idClaim;?>&dbname=<?=$currDbName;?>&from=index" class="viennacat2"><?=$field2;?></a></td>
		<td align=center class=""><font class="viennacat2"><?=$field1;?></font></td>
		<td align=center class=""><font class="viennacat2"><?=$field3;?></font></td>
	</tr>
<?	
	} // inv - syst
	elseif ( $currSecName == 'syst' )
	{
?>
	<tr bgcolor="<?=$line_bgcolor;?>">
		<td align=center class=""><font class="viennacat2"><?=$field3;?></font></td>
		<td align=center class=""><a style="text-decoration:underline" href="search.php?action=viewdetails&IdClaim=<?=$idClaim;?>&dbname=<?=$currDbName;?>&from=index" class="viennacat2"><?=$field2;?></a></td>
		<td align=center class=""><font class="viennacat2"><?=$field1;?></font></td>
	</tr>
<?
	} // end else
	} // end for
?>
</table>
