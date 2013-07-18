<table width=100% border=0 cellspacing="0" cellpadding="0">
<?
$varCountInLine = 0;
$rowCount = 0;
for($i = 0; $i < count($vi); $i++)									
{
?>
	
	
<?
	if ( $varCountInLine === 0 && $i === 0)
	{
?>
	<tr>

<?
	} // end if $varCountInLine === 0
?>

<?

	for($j = 1; $j <= $vi[$i]['countSubImage']; $j++)									
	{
		++$varCountInLine;
		
?>

		<td valign=top>
			<table width=150 border=0 cellspacing="0" cellpadding="0">
			<tr>
				<td align=center><a target="_blank" style="text-decoration: underline" href="realimage.php?idVariant=<?=$vi[$i]['idVariant'];?>&varIndex=<?=$j;?>&chapter=<?=$currFullBiblioChapter;?>&dbn=<?=$currDbName;?>" class="viennacat2"><?=($i+1)?>.<?=$j;?></a></td>
			</tr>
			<tr><td colspan=4 height="5"><img src="images/spacer.gif" height="5"></td></tr>						
			<tr>
				<td><a target="_blank" href="realimage.php?idVariant=<?=$vi[$i]['idVariant'];?>&varIndex=<?=$j;?>&chapter=<?=$currFullBiblioChapter;?>&dbn=<?=$currDbName;?>" class="viennacat2"><img border=0 src="resize.php?idVariant=<?=$vi[$i]['idVariant'];?>&varIndex=<?=$j;?>&chapter=<?=$currFullBiblioChapter;?>&dbn=<?=$currDbName;?>"></a></td>
			</tr>
			</table>
		</td>
		
		<td height=1 width=10><img src="images/spacer.gif" width="10"></td>
	
<?
		//if ( ( $varCountInLine % 3 ) === 0 )
		if ( $varCountInLine == 3)
		{
			$varCountInLine	= 0;
			++$rowCount;
?>

		</tr>

		<tr><td colspan=6 height="10"><img src="images/spacer.gif" height="10"></td></tr>						

		<tr>

<?
		} // end if ( $varCountInLine % 4 ) === 0
?>

	
<?
	} // end for $j 
	
	if ( $rowCount >= 1 )
	{
		$varCountInLine = 0;
?>

	</tr>

	<tr><td colspan=6 height="10"><img src="images/spacer.gif" height="10"></td></tr>						

	<tr>

<?
	} // end if ($i - 1) >=0 && $vi[$i]['countSubImage'] === 1

	
} // end for $i

if ( $varCountInLine < 3 )
{
?>
	</tr>

<?
} // end if $varCountInLine < 4 

?>

</table>
	

