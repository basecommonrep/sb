<table border=0 class="maintable" width="100%" height=680 cellspacing=0 cellpadding=0>
<tr>
<td valign=top>

<form name="main" id="searchbul" method="post" action="">

<table border=0 cellspacing=0 cellpadding=5 width=100%>
<tr>
<td>

<table border=0 cellspacing=0 cellpadding=3 width=100%>
<tr>
	<td>
	<table border=0 cellspacing=0 cellpadding=0 width=100%>
	<tr>
		<td><font class="viennacat"><?=strtoupper($LANG_SETTINGS['setfieldspage'][3]);?>.&nbsp;<?=($finid>0) ? '('.$finid.')&nbsp;' : '';?><?=strtoupper($ftitle);?></font></td>
	</tr>
	</table>
	</td>
</tr>


<tr>
	<td>
	<table border=0 cellspacing=0 cellpadding=0 width=100%>
	<tr>
		<td><font class="viennacat"><?=$db_names[$currDbName];?></font></td>
	</tr>
	</table>
	</td>
</tr>

<tr>
	<td>
	<table width="500" border=0 cellspacing=0 cellpadding=0>

<?
	//$errors = 'Помилка при тестовый обробцы';
	if ( !empty( $errors ) )
	{

?>

	<tr><td><img src="images/spacer.gif" height="10" width="100%"></td></tr>
	
	<tr>
		<td>
		<table border=0 cellspacing=0 cellpadding=0 width="100%">
		<tr><td><font class="SoftErrorText"><?=$errors;?></font></td></tr>
		<tr><td width=5><img height=5 width=1 src="images/spacer.gif"></td></tr>
		</table>
		</td>
	</tr>

<?
	}
?>

<?
	if ( empty( $errors ) )
	{
?>

	<tr>
		<td>
			<table border=0 cellspacing=0 cellpadding=0 width="100%">

			<tr>
				<td>
				<table border=0 width=100% cellpadding=0 cellspacing=0>
				<tr>
					<td align=left width=300>
					<font class="viennacat2"><?=$LANG_SETTINGS['res']['count'];?></font>
					<font class="viennacat"><?=$startId;?></font>
					<font class="viennacat2">-</font>
					<font class="viennacat"><?=$endId;?></font>
					<font class="viennacat2"><?=$LANG_SETTINGS['res']['of'];?></font>
					<font class="viennacat"><?=$resClaimsCount;?></font>
					</td>
					<td align=right>&nbsp;
					<!--
						<font class="viennacat2">Сортувати за </font>
					-->
					</td>
				</tr>
				</table>
				</td>
			</tr>
<?
	} //  errors
?>


			<tr><td colspan=5><img src="images/spacer.gif" height="5" width="100%"></td></tr>
			<tr><td align=right colspan=5><a href="dictionary.php?action=viewdict&dbname=<?=$currDbName;?>&fname=<?=$currFieldName;?>" class="viennacat2under"><?=$LANG_SETTINGS['dict']['viewall'];?></a></td></tr>

				<?
					if ( !empty($errors) )
					{
				?>
					<tr><td colspan=5><img src="images/spacer.gif" height="15" width="100%"></td></tr>
				<?
					}
				?>

<?
	if ( empty( $errors ) )
	{
?>

			<tr><td><img src="images/spacer.gif" height="5" width="100%"></td></tr>

<?
	if ( $pageCount > 1 )
	{
?>
			<tr><td align=right><?=$pageNumbersStr;?></td></tr>
			<tr><td><img src="images/spacer.gif" height="5" width="100%"></td></tr>
<?
	}
?>

			<tr>
				<td>
					<table border=0 cellspacing=0 cellpadding=5 width="100%">
					<tr class="hdr" height=30>
						<td width=100 class="indexcell" align=center><font class="viennacatwhite"><?=$LANG_SETTINGS['res']['vx'];?></font></td>
						<td width=400 class="" align=center><font class="viennacatwhite"><?=$LANG_SETTINGS['res']['value'];?></font></td>
					</tr>
					
					<?
						$part_number = 30;
						for ($i = 0; $i < count($searchShortBiblioSet); $i++)
						{
							$bgcolor = '';
							if (($i % 2) === 0)
								$bgcolor = '#c5d9eb';
							
							 
							$val = $searchShortBiblioSet[$i]['value'];
							$val_original = $val;
							
							//print($val.'<br><br>');
							

							$quoted = 'no';
							
							if ($ftype == 2) // str
							{
								$val_parted = '';	
								$parts = explode(' ', $val);
								for ($j = 0; $j < count($parts); $j++)
								{
									if ( strlen($parts[$j]) > $part_number )
									{
										for ($k = 0; $k <= (int)(strlen($parts[$j])/$part_number); $k++)
											$val_parted = $val_parted.' '.substr($parts[$j], $k*$part_number, ($k+1)*$part_number).' ';
									}
									else
										$val_parted = $val_parted.' '.$parts[$j];
								}
								
								$val = $val_parted;
								$val = textBlink($currDbName, $val, $currFieldName, true);
								
								if ( (substr_count($val_original, '"') > 0) || (substr_count($val_original, '\'') > 0) )
								{
									$val_original = str_replace('\'', '######', $val_original);
									$val_original = str_replace("\"", "\&&&&&&", $val_original); 
								}

								// поля, значения которых не заключаются в кавчки
								$notQuoted = array('NBUL', 'NC', 'MKPZ');
								
								if ( !in_array($currFieldName, $notQuoted) )
									$quoted = 'yes';
							}
					?>

					<tr bgcolor="<?=$bgcolor;?>">
						<td valign=top align=center class=""><font class="viennacat2"><?=$searchShortBiblioSet[$i]['entries'];?></font></td>
						<td valign=top align=<?=$falign;?>><a class="viennacat2under" href="javascript:void(0);" onclick="javascript:addtext('<?=$currFieldName;?>','<?=$val_original;?>','<?=$quoted;?>'); return false;"><?=$val;?></a></td>
					</tr>
					<?
						} // end for
					?>

					</table>
				</td>
			</tr>
			<tr><td bgcolor="#00518f"><img src="images/spacer.gif" height="2" width="100%"></td></tr>
<?
	if ( $pageCount > 1 )
	{
?>
			<tr><td><img src="images/spacer.gif" height="5" width="100%"></td></tr>
			<tr><td align=right><?=$pageNumbersStr;?></td></tr>
<?
	}
?>

<?
	} // end if empty errors
?>
			
<?
	if ( $pageCount > 1 || !empty($errors))
	{
?>

			<tr><td><img src="images/spacer.gif" height="5" width="100%"></td></tr>
			<tr><td bgcolor="#00518f"><img src="images/spacer.gif" height="3" width="100%"></td></tr>
<?
	}
?>

			<tr><td><img src="images/spacer.gif" height="10" width="100%"></td></tr>
			<tr>
				<td>
				<table width=100% border=0 cellspacing=0 cellpadding=0>
				
				<tr>
					<td width=100 align=left><font class="viennacat"><?=$LANG_SETTINGS['res']['value'];?></font></td>
					<td width=310 align=left><font class="viennacat"><input style="WIDTH: 310px;" class="inputstyle" type="text" name="<?=$currFieldName;?>" maxLen=40 value="<?=htmlspecialchars($currDictFieldValue, ENT_QUOTES);?>"></td>

					<td width=12 align=center><a onclick="javascript:clf('<?=$currFieldName;?>')" href="javascript:void(0);"><img border=0 alt="<?=$LANG_SETTINGS['setfieldspage']['clear'];?>" id="dc<?=$i;?>" src="images/erase2.gif" width="12" height="14"></a></td>
					<td width=8><img src="images/spacer.gif" height="1" width="8"></td>
					<td width=60 align=right><button class="viennacat" onclick="javascript:doAction('searchdict','<?=$currDbName;?>','','','<?=$currFieldName;?>');"><b><?=$LANG_SETTINGS['buttons']['search'];?></b></button></td>
				</tr>
				</table>
				</td>
			</tr>	
			<tr><td><img src="images/spacer.gif" height="20" width="100%"></td></tr>

			</table>
		</td>
	</tr>

    </table>
	</td>

</tr>

</table>

</td>
</tr>
</table>
</form>

</td>
</tr>
</table>

