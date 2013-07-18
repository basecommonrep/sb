<table border=0 class="maintable" width="100%" height=820 cellspacing=0 cellpadding=0>
<tr>
<td valign=top>

<form name="main" id="viewbul" method="post" action="">

<table border=0 cellspacing=0 cellpadding=5 width=100%>
<tr>
<td>

<table border=0 cellspacing=0 cellpadding=3 width=100%>
<tr>
	<td>
	<table border=0	cellspacing=0 cellpadding=0 width=100%>
	<tr>
		<td width=400 height=20 valign=top><font class="viennacat"><?=strtoupper($currDbTitle);?></font></td>
		<td width=1 bgcolor="#00518f"><img src="images/spacer.gif" width="2"></td>
		<td valign=top align=left style="padding-left: 10px;"><font class="viennacat"><?=(!empty($currSecTitle)) ? strtoupper($currSecTitle) : '&nbsp;';?></font></td>
<!--		<td class="helpbox" height="20" align=center><a style="text-decoration:none; color: white;" target=_blank href="help.php#main">?</a></td>-->
		<td>&nbsp;</td>
	</tr>

	<tr><td width=1 height=10 colspan=4><img height=10 width=1 src="images/spacer.gif"></td></tr>

	<tr><td height=2 bgcolor="#00518f" colspan=4><img src="images/spacer.gif" height="2" width="100%"></td></tr>
	<tr><td height=5 width=1><img height=5 width=1 src="images/spacer.gif"></td></tr>
	
	<tr>
		<td height=20>
		<table width=100% border=0 cellpadding=0 cellspacing=0>
		<tr>
			<td>
				<font class="viennacat2"><?=$LANG_SETTINGS['common_viewparts']['bul2'];?></font>&nbsp;
				<select class="inputstyle" style="width:140px; height:20px" name="newviewbulid" onchange="javascript:doAction('viewbul','<?=$currDbName;?>','<?=$currSecName;?>','','');">
		<?
		
		//reset($bulNumbList);
		while( list($bulId, $bulStr) = each($bulNumbList) )
		{
			$s = ( $currBulId == $bulId ) ? 'selected': '';
			print('<option value="'.$bulId.'" '.$s.'>'.$bulStr.'</option>');
		}
		?>
				</select>&nbsp;

			</td>
			<td align=right>
				<font class="viennacat2"><?=(isDiskBul == 'no') ? $LANG_SETTINGS['interface']['actual2'].'&nbsp;'.$currActualDate : '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';?></font>&nbsp;
			</td>
			
		</tr>
		</table>

		</td>
		<td height=5 width=1 bgcolor="#00518f"><img height=5 width=1 src="images/spacer.gif"></td>
		
		<td colspan=2 style="padding-left: 10px;"><font style="text-decoration: underline" class="viennacat2"><?=$LANG_SETTINGS['interface']['info'];?></font></td>
	</tr>

	<tr><td height=5 width=1><img height=5 width=1 src="images/spacer.gif"></td></tr>
	<tr><td height=2 bgcolor="#00518f" colspan=4><img src="images/spacer.gif" height=2 width="100%"></td></tr>

	<tr><td height=10 width=1><img height=10 width=1 src="images/spacer.gif"></td></tr>

	<tr>
		<td width=400 valign=top>
		<table width=100% border=0 cellpadding=0 cellspacing=0>
		<?
			$i = 0;
			while( list( $secName, $secInfo ) = each( $currViewDbSections ) )
			{
				$i++;
				$isSubSec = $secInfo[0];
				$secHref = $secInfo[1];
				$secTitle = $secInfo[2];
				
				if ( !empty( $secHref ) )
					$secHref = 'search.php?action=viewbul&dbname='.$currDbName.'&section='.$secHref;
				
				if ( !$isSubSec )
					$secTitle = strtoupper( $secTitle );
				
				$subSecStyle = 'viennacat2';
				if ( ( $secName == $currSecName ) && $isSubSec )
					$subSecStyle = 'viennacat2under';
				elseif ( ( $secName == $currSecName ) && !$isSubSec && !empty( $secHref ))
					$subSecStyle = 'viennacatunder';
				elseif ( ( !$isSubSec  ))
					$subSecStyle = 'viennacat';
					
				$ic = '';
				if ( isset($itemCount[$secName]) && ( !in_array($secName, $index_sections) || $secName == 'notice') )
					$ic = '&nbsp;('.$itemCount[$secName].')';
				
				if ( $isSubSec && !empty( $secHref ) )
					$secLine = '<a class="'.$subSecStyle.'" href="'.$secHref.'">'.$secTitle.$ic.'</a>';
				elseif ( !$isSubSec && !empty( $secHref ) )
					$secLine = '<a class="'.$subSecStyle.'" href="'.$secHref.'">'.$secTitle.$ic.'</a>';
				else
					$secLine = '<font class="'.$subSecStyle.'">'.$secTitle.'</font>';

		?>

		<?
			if ( $isSubSec && !empty( $secHref ) )
			{
			if ( ( substr($currDbName, 0, 3) == 'inv' && ($itemCount[$secName] > 0 || strstr($secName, 'num') || strstr($secName, 'syst'))) || substr($currDbName, 0, 3) != 'inv'  )
			{
			//print(rtrim($currDbName));
		?>	
			
			<tr>
			<td colspan=4>
			<table width=100% border=0 cellpadding=0 cellspacing=0>
			<tr>
			<td width=15><img height=1 width=15 src="images/spacer.gif"></font></td>
			<td><?=$secLine;?></td>
			</tr>
			</table>
			</td>
			</tr>

			<tr><td width=1 height=15 colspan=4><img height=15 width=1 src="images/spacer.gif"></td></tr>
		<?
			}
			}
			elseif ( !$isSubSec && !empty( $secHref ) )			
			{
			if ( ( $secName == 'notice' && $itemCount[$secName] > 0 ) || $secName != 'notice' )
			{
		?>
			<tr>
			<td colspan=4>
			<table width=100% border=0 cellpadding=0 cellspacing=0>
			<tr>
			<td width=3><img width=3 height=3 src="images/kub.gif" border=0></td>
			<td width=5><img width=5 height=1 src="images/spacer.gif" border=0></td>
			<td><?=$secLine;?></td>
			</tr>
			</table>
			</td>
			</tr>
	
			<tr><td width=1 height=15 colspan=4><img height=15 width=1 src="images/spacer.gif"></td></tr>
		<?	
			}
			}
			else
			{
		?>
			<tr>
			<td colspan=4>
			<table width=100% border=0 cellpadding=0 cellspacing=0>
			<tr>
			<td width=3><img width=3 height=3 src="images/kub.gif" border=0></td>
			<td width=5><img width=5 height=1 src="images/spacer.gif" border=0></td>
			<td><?=$secLine;?></td>
			</tr>
			</table>
			</td>
			</tr>
	
			<tr><td width=1 height=15 colspan=4><img height=15 width=1 src="images/spacer.gif"></td></tr>
		<?
			}
		?>

		


		<?
			} // end for
		?>

		</table>

		</td>
		<td height=100% width=1 bgcolor="#00518f" rowspan=4><img src="images/spacer.gif" height=100% width="1"></td>
		
		<td valign=top align=left colspan=3 rowspan=4 style="padding-left: 10px;">
<?
	if ( empty( $errors ) )	
		include('incs/viewbulresult.php.inc');		
	else

?>		
		<font class="viennacat"><?=strtoupper($errors);?></font>

		</td>
	</tr>
	
	<tr><td width=1 height=10><img height=10 width=1 src="images/spacer.gif"></td></tr>

<!--
	<tr><td height=2 bgcolor="#00518f"><img src="images/spacer.gif" height=2 width="100%"></td></tr>
-->
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

