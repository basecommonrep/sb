<table border=0 class="maintable" width="100%" height=820 cellspacing=0 cellpadding=0>
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
		<td width=300><font class="viennacat"><?=strtoupper($LANG_SETTINGS['menu'][0]);?></font></td>
		<td>&nbsp;</td>
		<td width="25">&nbsp;</td>
	</tr>
	</table>
	</td>
</tr>

<tr>
	<td width="600">
	<table width="600" border=0 cellspacing=0 cellpadding=0>

<?
	//$errors = 'Помилка при тестовый обробцы';
	if ( !empty( $errors ) )
	{

?>

	<tr>
		<td colspan=9>
		<table border=0 cellspacing=0 cellpadding=0 width="100%">
		<tr><td><font class="SoftErrorText"><?=$errors;?></font></td></tr>
		<tr><td width=5><img height=5 width=1 src="images/spacer.gif"></td></tr>
		<tr><td bgcolor="#00518f"><img src="images/spacer.gif" height="2" width="100%"></td></tr>
		<tr><td width=5><img height=5 width=1 src="images/spacer.gif"></td></tr>
		</table>
		</td>
	</tr>

	<tr><td colspan=9><img src="images/spacer.gif" height="15" width="100%"></td></tr>

<?
	}
?>

<?
	if ( empty($addDbName))
	{
?>

	<tr>
		<td colspan=9>
		<table width=100% border=0 cellspacing=0 cellpadding=0>
		<tr>
			<td width=20><font class="viennacat"><?=$LANG_SETTINGS['setfieldspage']['bds'];?></font>&nbsp;&nbsp;</td>
			<td>
				<select class="inputstyle" style="width:<?=($isUEFA) ? 570 : 480;?>px; height:20px" name="newsearchdbname" onchange="javascript:doAction('changedb','','','','');">
		<?

		reset($db_names);
		while( list( $dbn, $dbt ) = each( $db_names ) )
		{

			if ( ($dbn != 'official' ) && ($dbn != 'tm2' ) && ($dbn != 'pp2' ))
			{
				$s = ( $dbn == $currDbName ) ? 'selected': '';
				print('<option value="'.$dbn.'" '.$s.'>'.$dbt.'</option>');
			}
		}
		?>
				</select>&nbsp;
			</td>
		</tr>
		</table>
		</td>
	</tr>

	<tr><td colspan=9><img src="images/spacer.gif" height="15" width="100%"></td></tr>

<?
	} // end if addDbName
?>

	<tr>
		<td colspan=9>
		<table width=100% border=0 cellspacing=0 cellpadding=0>

		<tr>
			<td width=100%><font class="viennacat2"><?=$LANG_SETTINGS['setfieldspage']['resperpage'];?></font>&nbsp;&nbsp;
			
				<select class="inputstyle" style="width:50px;height:18px" name="newclaimsperpage">
		<?
		
		for($i = 0; $i < count($claimsPerPageList); $i++)
		{
			$s = ( $claimsPerPageList[$i] == $currClaimsPerPage ) ? 'selected': '';
			print('<option value="'.$claimsPerPageList[$i].'" '.$s.'>'.$claimsPerPageList[$i].'</option>');
		}
		?>
				</select>
				
			</td>
		</tr>
		</table>
		</td>
	</tr>

	
	<tr><td colspan=9><img src="images/spacer.gif" height="10" width="100%"></td></tr>
	<tr>
		<td align=left colspan=9>
		<table width=100% border=0 cellspacing=0 cellpadding=0>
		<tr>
<?
 	if ( substr($currDbName, 0, 3)=='tmc')
	{
?>
			<td align=left width=250><font class="viennacat2"><?=(isDiskBul == 'no') ? $LANG_SETTINGS['interface']['actual2'].'&nbsp;'.$currActualDate : '&nbsp;';?></font></td>
<?  
    } 
    else
	{
?>
			<td align=left width=250><font class="viennacat2"><?=(isDiskBul == 'no') ? $LANG_SETTINGS['interface']['actual2'].'&nbsp;'.$currActualDate : '&nbsp;';?></font></td>
<?
    }
	if ( empty($addDbName) && !$isUEFA && isDiskBul == 'no' )
	{
?>
			<td align=right colspan=9><font style="text-decoration: underline" class="viennacat2"><?=$LANG_SETTINGS['interface']['info'];?></font></td>
<?
	} // end if addDbName
?>

		</tr>
		</table>
		</td>
	</tr>

	<tr>
		<td colspan=9>
		<table width=100% border=0 cellspacing=0 cellpadding=0>
	
		<tr><td colspan=2><img src="images/spacer.gif" height="10"></td></tr>
		<tr>
			<td width=80 align=left><button class="viennacat" onclick="javascript:doAction('search','','','','');"><b><?=$LANG_SETTINGS['buttons']['search'];?></b></button></td>
			<td align=right valign=bottom>
			<input <?if ( $currInFound ) print("checked");?> type=checkbox name=newinfound value="yes">
			<font class="viennacat2"><?=$LANG_SETTINGS['buttons']['infound'];?></font>			
			</td>
		</tr>
		</table>
		</td>
	</tr>	

	<tr><td colspan=9><img src="images/spacer.gif" height="10" width="100%"></td></tr>
	<tr><td colspan=9 bgcolor="#00518f"><img src="images/spacer.gif" height="2" width="100%"></td></tr>
	<tr><td colspan=9 bgcolor="#c5d9eb"><img src="images/spacer.gif" height="5"></td></tr>
	
<?
	$n = '';
	if ( substr($currDbName, 0, 3) == 'inv' || substr($currDbName, 0, 3) == 'wkm' )
		$n = substr($currDbName, 0, 3);
	elseif ( substr($currDbName, 0, 2) == 'pp' || substr($currDbName, 0, 2) == 'tm' )
		$n = substr($currDbName, 0, 2);
	elseif ( substr($currDbName, 0, 6) == 'madrid' )
		$n = substr($currDbName, 0, 6);
	else
		$n = $currDbName;

	$exclude_pp = array('NUSSR', 'TUSSR', 'NAUSSR', 'DAUSSR');
	$exclude_reestrtm = array('KEYW', 'PROP');
	
	$i = 0;
	while( list($key, $val) = each( $curr_db_params_table_content ) )
	{

		if ( ($currDbName == 'pp' && empty($addDbName) && in_array($key, $exclude_pp))  )  // условие для скрытия поисковых полей "Ключевые слова" и "Владелец" || ($addDbName == 'reestr' && substr($currDbName, 0, 2) == 'tm' && in_array($key, $exclude_reestrtm))
			continue;
		$i++;
	
		$ftitle = $curr_db_params_table_content[$key][3];
		$inid = ( $curr_db_params_table_content[$key][4] !== 0 ) ? '('.$curr_db_params_table_content[$key][4].')&nbsp;' : '';
		$example = $curr_db_params_table_content[$key][5];
		
		$ftitle_short = $ftitle;
		if ( strlen( $ftitle ) > 40 )
			$ftitle_short = substr($ftitle, 0, 40).'...';
		
		
?>

		<tr bgcolor="#c5d9eb">
			<td style="PADDING-LEFT: 4px;" width=250 height=35><acronym title="<?=$ftitle;?>"><a href="search.php?action=viewhelp&dbname=<?=$n;?>&fname=<?=$key;?>" class="viennacat"><?=$inid;?><?=$ftitle_short;?></a></acronym></td>
			<td width=3><img src="images/spacer.gif" height="1" width="3"></td>
			<td width=16 align=center>
		<?
			if($addDbName != 'reestr')
			{
		?>
				<a target=_blank  
				<?
				if (!$isUEFA && $currDbName != 'madridall' )
				{
				?>
				href="dictionary.php?action=viewdict&dbname=<?=$currDbName;?>&fname=<?=$key;?>"
				<?
				}
				?>
				
				<?
				if ( $currDbName != 'madridall' )
				{
				?>
				class="viennacat"><img alt="<?=$LANG_SETTINGS['setfieldspage']['dict'];?>" vspace=2 width=16 height=15 src="images/dict3.gif" border=0></a>
				<?
				}
				else
				{
				?>
				<img vspace=2 width=16 height=1 src="images/spacer.gif" border=0>
			<?
				}
			}
			?>
			</td>
			<td width=3><img src="images/spacer.gif" height="1" width="3"></td>
			<td width=200><input class="inputstyle" type="text" name="<?=$key;?>" maxLen=40 value="<?=htmlspecialchars($_POST[$key], ENT_QUOTES);?>" onFocus="javascript:ma(this,<?=$i;?>)">
			<td width=3><img src="images/spacer.gif" height="1" width="3"></td>
			<td width=12 align=center><a onclick="javascript:clf('<?=$key;?>')" href="javascript:void(0);"><img border=0 alt="<?=$LANG_SETTINGS['setfieldspage']['clear'];?>" id="dc<?=$i;?>" src="images/erase2.gif" width="12" height="14"></a></td>
			<td width=3><img src="images/spacer.gif" height="1" width="10"></td>
			<td width=150 align=left><font class="viennacat2"><?=$example;?></font></td>
		</tr>
		
<?
	if ( $i < count($curr_db_params_table_content) )
	{
?>
		<tr bgcolor="#ffffff"><td colspan=9><img src="images/spacer.gif" height="2" width="100%"></td></tr>

<?
	}
	} // end while
?>


	<tr><td colspan=9 bgcolor="#c5d9eb"><img src="images/spacer.gif" height="5"></td></tr>
	<tr><td colspan=9 bgcolor="#00518f"><img src="images/spacer.gif" height="2"></td></tr>

	<tr>
		<td colspan=9>
		<table width=100% border=0 cellspacing=0 cellpadding=0>
	
		<tr><td colspan=2><img src="images/spacer.gif" height="10"></td></tr>
		<tr>
			<td width=80 align=left><button class="viennacat" onclick="javascript:doAction('search','','','','');"><b><?=$LANG_SETTINGS['buttons']['search'];?></b></button></td>
			<td align=right><button class="viennacat" onclick="javascript: clrall();"><b><?=$LANG_SETTINGS['buttons']['clear'];?></b></button></td>
		</tr>
		<tr><td colspan=2><img src="images/spacer.gif" height="20"></td></tr>
		</table>
		</td>
	</tr>	

    </table>
	</td>

	<td valign=top>
	<table width=100% border=0 cellspacing=0 cellpadding=0>
<?
	//$errors = 'Помилка при тестовый обробцы';
	if ( !empty( $errors ) )
	{

?>

	<tr>
		<td colspan=9>
		<table border=0 cellspacing=0 cellpadding=0 width="100%">
		<tr><td><font class="SoftErrorText">&nbsp;</font></td></tr>
		<tr><td width=5><img height=5 width=1 src="images/spacer.gif"></td></tr>
		<tr><td><img src="images/spacer.gif" height="2" width="100%"></td></tr>
		<tr><td width=5><img height=5 width=1 src="images/spacer.gif"></td></tr>
		</table>
		</td>
	</tr>

	<tr><td colspan=9><img src="images/spacer.gif" height="15" width="100%"></td></tr>

<?
	}

?>

	<tr>
		<td colspan=9 height="25">
		<table width=100% border=0 cellspacing=0 cellpadding=0>
		<tr>
			<td width=20><font class="viennacat">&nbsp;</td>
			<td>&nbsp;</td>
		</tr>
		</table>
		</td>
	</tr>

	<tr><td colspan=9 height="15"><img src="images/spacer.gif" height="15"></td></tr>

<?
	if ( empty($addDbName) )
	{
?>
	<tr>
		<td colspan=9 height="25">
		<table width=100% border=0 cellspacing=0 cellpadding=0>
		<tr>
			<td width=100%>&nbsp;</td>
		</tr>
		</table>
		</td>
	</tr>

	<tr><td colspan=9><img src="images/spacer.gif" height="10" width="100%"></td></tr>
<?
	} // end addDbName
?>

	<tr>
		<td align=left colspan=9>
		<table width=100% border=0 cellspacing=0 cellpadding=0>
		<tr>
			<td align=left width=250>&nbsp;</td>
			<td align=right colspan=9>&nbsp;</td>
		</tr>
		</table>
		</td>
	</tr>

	<tr>
		<td colspan=9>
		<table width=100% border=0 cellspacing=0 cellpadding=0>
	
		<tr><td colspan=2><img src="images/spacer.gif" height="10"></td></tr>
		<tr>
			<td width=80 align=left>&nbsp;</td>
			<td align=right valign=bottom>&nbsp;</td>
		</tr>
		</table>
		</td>
	</tr>	

	<tr><td colspan=9><img src="images/spacer.gif" height="7" width="100%"></td></tr>

	<tr>
		<td>
		<table class="mt" width=50 border=1 cellspacing=0 cellpadding=3>

		<tr align="center">
			<td colspan=2 bgcolor="#c5d9eb"><a class="ftc" href="javascript:void(0);" onclick='javascript:ata(" <?=$LANG_SETTINGS['logical']['and'];?> ")'><?=$LANG_SETTINGS['logical']['and'];?></a></td>
		</tr>
		<tr align="center">
			<td colspan=2 bgcolor="#eef0f4"><a class="ftc" href="javascript:void(0);" onclick='javascript:ata(" <?=$LANG_SETTINGS['logical']['or'];?> ")'><?=$LANG_SETTINGS['logical']['or'];?></a></td>
		</tr>
		<tr align="center">
			<td colspan=2 bgcolor="#c5d9eb"><a class="ftc" href="javascript:void(0);" onclick='javascript:ata(" <?=$LANG_SETTINGS['logical']['not'];?> ")'><?=$LANG_SETTINGS['logical']['not'];?></a></td>
		</tr>
		
		<tr align="center">
			<td width="25" bgcolor="#eef0f4"><a class="ftc" href="javascript:void(0);" onclick='javascript:ata("(")'>(</a></td>
			<td width="25" bgcolor="#eef0f4"><a class="ftc" href="javascript:void(0);" onclick='javascript:ata(")")'>)</a></td>	
		</tr>
		
		<tr align="center">
			<td width="25" bgcolor="#c5d9eb"><a class="ftc" href="javascript:void(0);" onclick='javascript:ata("*")'>*</a></td>
			<td width="25" bgcolor="#c5d9eb"><a class="ftc" href="javascript:void(0);" onclick='javascript:ata("?")'>?</a></td>	
		</tr>

		<tr align="center">
			<td width="25" bgcolor="#eef0f4"><a class="ftc" href="javascript:void(0);" onclick='javascript:ata("<")'>&lt;</a></td>
			<td width="25" bgcolor="#eef0f4"><a class="ftc" href="javascript:void(0);" onclick='javascript:ata(">")'>&gt;</a></td>	
		</tr>

		<tr align="center">
			<td colspan=2 bgcolor="#c5d9eb"><a class="ftc" href="javascript:void(0);" onclick='javascript:ata("=")'>=</a></td>
		</tr>

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

