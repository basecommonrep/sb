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
		<td width=300><b><font class="help"><?=strtoupper($LANG_SETTINGS['help']['help']);?></font></b></td>
		<td>&nbsp;</td>
		<td width="25" height="20">&nbsp;</td>
	</tr>
	</table>
	</td>
</tr>

<tr>
	<td width="600">
	<table width="600" border=0 cellspacing=0 cellpadding=0>

	<tr>
		<td>
<?
	
	if ( empty( $currFieldName ) )
		include('help/commonhelp_'.$_SESSION['lastLang'].'.htm');
	else
	{
		$fid = (int)$fid;
		if ( $fid > 0 )
			$fid = 0;
			
		$title = $curr_db_params_table_content[$currFieldName][3];
		$inid = $curr_db_params_table_content[$currFieldName][4];
		$ftype = $curr_db_params_table_content[$currFieldName][0];

		switch( $ftype )
		{
			case 1:
				$ftype_str = $LANG_SETTINGS['help']['int'];
			break;
			case 2:
				$ftype_str = $LANG_SETTINGS['help']['char'];
			break;
			case 3:
				$ftype_str = $LANG_SETTINGS['help']['date'];
			break;
		}

		include('../searchBul/incs/helptable.php.inc');
	}
	
?>
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

