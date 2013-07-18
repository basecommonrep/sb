<table border=0 class="<?=(!$printed) ? 'maintable' : '';?>" width="100%" height=730 cellspacing=0 cellpadding=0>
<tr>
<td valign=top>

<form name="main" id="basket" method="post" action="">

<table border=0 cellspacing=0 cellpadding=5 width=100%>
<tr>
<td>

<table border=0 cellspacing=0 cellpadding=3 width=100%>
<tr>
	<td>
	<table border=0 cellspacing=0 cellpadding=0 width=100%>
	<tr>
		<td width=650><font class="viennacat"><?=strtoupper($LANG_SETTINGS['basket']['basket']);?></font></td>
	</tr>

	</table>
	</td>
</tr>

<tr>
	<td>
	<table width="700" border=0 cellspacing=0 cellpadding=0>

	<tr><td><img src="images/spacer.gif" height="10" width="100%"></td></tr>
	
	<?
		if ( $_SESSION['basketItemsCount'] === 0 )
		{
	?>
			<tr><td><font class="viennacat2"><?=ucfirst($LANG_SETTINGS['res']['nd']);?></font></td></tr>
	<?
	
		}
	?>
	
	<?
		if ( $_SESSION['basketItemsCount'] > 0 )
		{
	?>
			<tr>
				<td>
					<table width="100%" border=0 cellspacing=0 cellpadding=0>
					<tr>
						<td align=right>
						<a class="viennacat2under" href="<?=$printStr;?>" target=_blank><?=strtolower($LANG_SETTINGS['details']['print']);?></a>
						<font class="viennacat2">|</font>
						<a class="viennacat2under" href="?action=clearbasket"><?=$LANG_SETTINGS['basket']['delAll'];?></a></td>
					</tr>
					</table>
				</td>
			</tr>

			<tr><td><img src="images/spacer.gif" height="5" width="100%"></td></tr>
	
	<?
	
		}
	?>

	<?



		while( list($currDbName, $currDbNameBasketIds) = each($basketIds))
		{
			if ( count( $currDbNameBasketIds ) > 0 )
			{
				// сортування
				$currSortOrderTable = $sortOrderTable[$currDbName];
				$orderFields = array_keys($currSortOrderTable);
	
				$currSortField = $orderFields[0];
				$currSortOrder = $sortOrders[0];
				$currSortExpr = $currSortOrderTable[$currSortField]['sortexpr'];
				// =========


				$currSubSetSearchIds = $currDbNameBasketIds;
				$currBasketIds = $currSubSetSearchIds;
				$query = buildGetShortBiblioQuery($currDbName, $currSubSetSearchIds, '');
				$query = str_replace('$$$ORDERCLAUSE$$$', 'order by '.$currSortExpr.' '.$currSortOrder, $query);
				
				$detailStr = '&dbname='.$currDbName.'&from=viewbasket';
				//print($query.'<BR><BR>');


				$basket_check_str = '<a title="'.$LANG_SETTINGS['basket']['delFull'].'" href="?action=deletefrombasket&dbname='.$currDbName.'&idClaim=###IDCLAIM###&from=viewbasket" class="viennacatunder">'.$LANG_SETTINGS['basket']['del'].'</a>';
				$searchShortBiblioSet = executeGetShortBiblioQuery($currDbName, $query, $mssql);
				$query = str_replace('$$$ORDERCLAUSE$$$', 'order by '.$currSortExpr.' '.$currSortOrder, $query);	
				
				$startId = 1;
				$endId = count($currSubSetSearchIds);
				
				if ( $currDbName == 'pp' )
					$variantInfo = getPpVariantInfo($searchShortBiblioSet);

				if ( $currDbName == 'madrid' )
					saveMadridImagesToTemp($searchShortBiblioSet, '');				

				if ( $currDbName == 'wkm' )
					saveWKMImagesToTemp($searchShortBiblioSet);
					
				/*
				if ( $currDbName == 'wkm' )
					print_r($searchShortBiblioSet);
				*/

	?>
		
	<?
		if ( empty($addDbName) )
		{		
	?>

	<tr>
		<td bgcolor="#00518f" height="25">
			<font class="viennacatwhite">&nbsp;<?=strtoupper($db_names[$currDbName]);?></font>
		</td>
	</tr>

	<?
		} // end
	?>

	<tr><td bgcolor="#00518f"><img src="images/spacer.gif" height="2"></td></tr>		
	<tr>
		<td>

		<?
			if ( substr($currDbName, 0, 3) == 'inv' )
				include('incs/restables/reslisttab_allinv.php.inc');
			elseif ( substr($currDbName, 0, 2) == 'tm' )
				include('incs/restables/reslisttab_tm.php.inc');
			else
				include('incs/restables/reslisttab_'.$currDbName.'.php.inc');
		?>

		</td>
	</tr>
	<tr><td bgcolor="#00518f"><img src="images/spacer.gif" height="2"></td></tr>
	<tr><td><img src="images/spacer.gif" height="40" width="100%"></td></tr>
	

	<?
			} // end if
		}
	?>

	<tr><td><img src="images/spacer.gif" height="5" width="100%"></td></tr>

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


