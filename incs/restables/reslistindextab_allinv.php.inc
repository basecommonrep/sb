<table width="<?=($currSecName == 'numpussr' ) ? '500' : '350';?>" border=0 cellspacing=0 cellpadding=5 class="mt">
<?
	if ( $currDbName == 'invc' )
	{
		switch($currSecName)
		{
			case 'syst':
				$f1 = $LANG_SETTINGS['inv_fields']['MPK'];
				$f2 = $LANG_SETTINGS['inv_fields']['NC'];
			break;
			case 'numc':
				$f2 = $LANG_SETTINGS['inv_fields']['MPK'];
				$f1 = $LANG_SETTINGS['inv_fields']['NC'];
			break;
		}
	} // invc
	elseif ( $currDbName == 'inv' || $currDbName == 'invd' || $currDbName == 'invdu' )
	{
		switch($currSecName)
		{
			case 'numc':
				$f1 = $LANG_SETTINGS['inv_fields']['NC'];
				$f2 = $LANG_SETTINGS['inv_fields']['NP'];
			break;

			case 'syst':
				$f1 = $LANG_SETTINGS['inv_fields']['MPK'];
				$f2 = $LANG_SETTINGS['inv_fields']['NP'];
			break;

			case 'nump':
				$f1 = $LANG_SETTINGS['inv_fields']['NP'];
				$f2 = $LANG_SETTINGS['inv_fields']['MPK'];
			break;

			case 'numpussr':
				$f1 = $LANG_SETTINGS['inv_fields']['NP2'];
				$f2 = $LANG_SETTINGS['inv_fields']['UPN2'];
				$f3 = $LANG_SETTINGS['inv_fields']['MPK'];
			break;

			case 'numcert':
				$f1 = $LANG_SETTINGS['inv_fields']['UPN2'];
				$f2 = $LANG_SETTINGS['inv_fields']['NP2'];
			break;
		}
	} // inv
?>

<?
	if ( $currSecName == 'numpussr' )
	{

?>

<tr class="hdr" align=center>
	<td width=160 height=35 align=center class=""><b><font class="viennacat" style="color:#FFFFFF"><?=$f1;?></font></b></td>
	<td width=160 align=center><b><font class="viennacat" style="color:#FFFFFF"><?=$f2;?></font></b></td>
	<td width=180 align=left class="indexcell"><b><font class="viennacat" style="color:#FFFFFF"> <?=$f3;?></font></b></td>
</tr>


<?
	} // end if $currSecName == 'numpussr'
	elseif ( $currSecName == 'numcert' )
	{
?>
<tr class="hdr" align=center>
	<td width=300 height=35 align=center><b><font class="viennacat" style="color:#FFFFFF"><?=$f1;?></font></b></td>
	<td width=200><b><font class="viennacat" style="color:#FFFFFF"> <?=$f2;?></font></b></td>
</tr>

<?
	} // end elseif ( $currSecName == 'numcert' )
	elseif ( ($currDbName == 'inv' || $currDbName == 'invd' || $currDbName == 'invdu') && $currSecName == 'nump' )
	{
?>
<tr class="hdr" align=center>
	<td width=150 height=35 align=center><b><font class="viennacat" style="color:#FFFFFF"><?=$f1;?></font></b></td>
	<td width=200 align=left class="indexcell"><b><font class="viennacat" style="color:#FFFFFF"> <?=$f2;?></font></b></td>
</tr>

<?
	} // end elseif ( $currSecName == 'numcert' )
	elseif ( $currDbName == 'invc' && $currSecName == 'numc' )
	{
?>
<tr class="hdr" align=center>
	<td width=150 height=35 align=center><b><font class="viennacat" style="color:#FFFFFF"><?=$f1;?></font></b></td>
	<td width=200 align=left class="indexcell"><b><font class="viennacat" style="color:#FFFFFF"> <?=$f2;?></font></b></td>
</tr>

<?
	} // end elseif ( $currSecName == 'numcert' )
	elseif ( ($currDbName == 'inv' || $currDbName == 'invd' || $currDbName == 'invdu') && $currSecName == 'numc' )
	{
?>
<tr class="hdr" align=center>
	<td width=180 height=35 align=center><b><font class="viennacat" style="color:#FFFFFF"><?=$f1;?></font></b></td>
	<td width=170 align=center><b><font class="viennacat" style="color:#FFFFFF"> <?=$f2;?></font></b></td>
</tr>

<?
	} // end elseif ( $currSecName == 'numc' )
	else
	{
?>
<tr class="hdr" align=center>
	<td width=200 height=35 align=left class="indexcell"><b><font class="viennacat" style="color:#FFFFFF"><?=$f1;?></font></b></td>
	<td width=150 align=center><b><font class="viennacat" style="color:#FFFFFF"> <?=$f2;?></font></b></td>
</tr>

<?
	}
?>



<?
	for($i = 0; $i < count( $searchShortBiblioSet ); $i++)
	{
		$row = $searchShortBiblioSet[$i];
		
		if ( $currDbName == 'invc' )
		{
			if ( $currSecName == 'syst' )
			{
				$idClaim = $row[0]; // idclaim
				$field1 = $row[1]; // mpk
				$field2 = $row[2]; // i_21
				
				if ( !((int)$field2[0] >= 1 && (int)$field2[0] <= 9) )
					$field2 = $field2[0].'&nbsp;'.substr($field2, 1, 4).'&nbsp;'.substr($field2, 5, strlen($field2));
					
			} // end if ( $currSecName == 'syst' )
	
			if ( $currSecName == 'numc' )
			{
				$idClaim = $row[0]; // idclaim
				$field1 = $row[1]; // mpk
				$field2 = $row[2]; // i_21
				
				if ( !((int)$field2[0] >= 1 && (int)$field2[0] <= 9) )
					$field2 = $field2[0].'&nbsp;'.substr($field2, 1, 4).'&nbsp;'.substr($field2, 5, strlen($field2));
			} // end if ( $currSecName == 'syst' )
		} // invc
		
		if ( $currDbName == 'inv' ||  $currDbName == 'invd' ||  $currDbName == 'invdu' )
		{
			if ( $currSecName == 'numc' )
			{
				$idClaim = $row[0]; // idclaim
				$field1 = $row[1]; // i_21
				$field2 = $row[2]; // i_11
				
				if ( !((int)$field1[0] >= 1 && (int)$field1[0] <= 9) )
					$field1 = $field1[0].'&nbsp;'.substr($field1, 1, 4).'&nbsp;'.substr($field1, 5, strlen($field1));
			} // end if ( $currSecName == 'numc' )

			if ( $currSecName == 'syst' )
			{
				$idClaim = $row[0]; // idclaim
				$field1 = $row[1]; // mpk
				$field2 = $row[2]; // i_11
				
			} // end if ( $currSecName == 'syst' )


			if ( $currSecName == 'nump' )
			{
				$idClaim = $row[0]; // idclaim
				$field2 = $row[1]; // mpk
				$field1 = $row[2]; // i_11
				
			} // end if ( $currSecName == 'nump' )

			if ( $currSecName == 'numpussr' )
			{
				$idClaim = $row[0]; // idclaim
				$field1 = $row[2]; // i_11
				$field2 = $row[3]; // ussrAC
				$field3 = $row[1]; // mpk
				
			} // end if ( $currSecName == 'nump' )

			if ( $currSecName == 'numcert' )
			{
				$idClaim = $row[0]; // idclaim
				$field1 = $row[1]; // ussrAC
				$field2 = $row[2]; // i_11
			} // end if ( $currSecName == 'nump' )

		} // inv		

		$line_bgcolor = "";
		if ( ($i % 2) == 0 )
	 		$line_bgcolor = "#C5D9EB";
?>

<?
	if ( $currDbName == 'invc' && $currSecName == 'syst' )
	{
?>
	<tr bgcolor="<?=$line_bgcolor;?>">
		<td align=left class="indexcell"><font class="viennacat2"><?=$field1;?></font></td>
		<td align=center><a style="text-decoration:underline" href="search.php?action=viewdetails&IdClaim=<?=$idClaim;?>&dbname=<?=$currDbName;?>&from=index" class="viennacat2"><?=$field2;?></a></td>
	</tr>
<?	
	} // invc - syst
	elseif ( $currDbName == 'invc' && $currSecName == 'numc' )
	{
?>
	<tr bgcolor="<?=$line_bgcolor;?>">
		<td align=center class=""><a style="text-decoration:underline" href="search.php?action=viewdetails&IdClaim=<?=$idClaim;?>&dbname=<?=$currDbName;?>&from=index" class="viennacat2"><?=$field2;?></a></td>
		<td align=left class="indexcell"><font class="viennacat2"><?=$field1;?></font></td>
	</tr>
<?	
	} // invc - numc
	elseif ( ($currDbName == 'inv' || $currDbName == 'invd' || $currDbName == 'invdu') && $currSecName == 'numc' )
	{
?>
	<tr bgcolor="<?=$line_bgcolor;?>">
		<td align=center class=""><a style="text-decoration:underline" href="search.php?action=viewdetails&IdClaim=<?=$idClaim;?>&dbname=<?=$currDbName;?>&from=index" class="viennacat2"><?=$field1;?></a></td>
		<td align=center class=""><font class="viennacat2"><?=$field2;?></font></td>
	</tr>
<?	
	} // inv - numc
	elseif ( ($currDbName == 'inv' || $currDbName == 'invd' || $currDbName == 'invdu') && $currSecName == 'syst' )
	{
?>
	<tr bgcolor="<?=$line_bgcolor;?>">
		<td align=left class="indexcell"><font class="viennacat2"><?=$field1;?></font></td>
		<td align=center class=""><a style="text-decoration:underline" href="search.php?action=viewdetails&IdClaim=<?=$idClaim;?>&dbname=<?=$currDbName;?>&from=index" class="viennacat2"><?=$field2;?></a></td>
	</tr>
<?	
	} // inv - syst
	elseif ( ($currDbName == 'inv' || $currDbName == 'invd' || $currDbName == 'invdu') && $currSecName == 'nump' )
	{
?>
	<tr bgcolor="<?=$line_bgcolor;?>">
		<td align=center ><a style="text-decoration:underline" href="search.php?action=viewdetails&IdClaim=<?=$idClaim;?>&dbname=<?=$currDbName;?>&from=index" class="viennacat2"><?=$field1;?></a></td>
		<td align=left class="indexcell"><font class="viennacat2"><?=$field2;?></font></td>
	</tr>
<?	
	} // inv - nump
	elseif ( $currDbName == 'inv' && $currSecName == 'numpussr' )
	{
?>
	<tr bgcolor="<?=$line_bgcolor;?>">
		<td align=center class=""><a style="text-decoration:underline" href="search.php?action=viewdetails&IdClaim=<?=$idClaim;?>&dbname=<?=$currDbName;?>&from=index" class="viennacat2"><?=$field1;?></a></td>
		<td align=center class=""><font class="viennacat2"><?=$field2;?></font></td>
		<td align=left class="indexcell"><font class="viennacat2"><?=$field3;?></font></td>
	</tr>
<?	
	} // inv - numpussr
	elseif ( $currDbName == 'inv' && $currSecName == 'numcert' )
	{
?>
	<tr bgcolor="<?=$line_bgcolor;?>">
		<td align=center class=""><font class="viennacat2"><?=$field1;?></font></td>
		<td align=center class=""><a style="text-decoration:underline" href="search.php?action=viewdetails&IdClaim=<?=$idClaim;?>&dbname=<?=$currDbName;?>&from=index" class="viennacat2"><?=$field2;?></a></td>
	</tr>
<?
	} // inv - numpussr
?>

<?
	} // end for
?>
</table>
