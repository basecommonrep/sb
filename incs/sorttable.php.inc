<?
	$width = 170;
	if ( $currDbName == 'invc' )
		$width = 120;
	if ( $currDbName == 'tm' )
		$width = 200;
	if ( $currDbName == 'madrid' )
		$width = 150;
	if ( $currDbName == 'madridall' )
		$width = 100;
	if ( $currDbName == 'tmc' )
		$width = 100;
	
?>
<table width=100% border=0 cellspacing=0 cellpadding=0>
<tr>
	<td align=right><font class="viennacat2"><?=$LANG_SETTINGS['sort']['sortby'];?>:&nbsp;&nbsp;&nbsp;</font></td>
	<td width=<?=$width;?>>
		<table width=100% border=0 cellspacing=0 cellpadding=0>
		<tr>
		<?
			$i = 0;
			while(list($sortFName, $sortSet) = each($currSortOrderTable))
			{	
				$i++;
				$class = 'viennacat2under';
				$order = $sortOrders[0]; //asc
				$iname = 'wdown.gif';
				if ( $currSortField == $sortFName )
				{
					$class = 'viennacatunder';
					if ( $currSortOrder == 'asc' )
						$order = 'desc';
					else
					{
						$order = 'asc';
						$iname = 'wup.gif';
					}
				}
				
				$sec = '';
				if ( $isUEFA && ($currAction == 'viewall' || $_GET['section'] == 'viewall' ) )
					$sec = '&section=viewall'
				
		?>
			<td width=30>
			<a title="<?=$sortSet['title'];?>" href="search.php?action=sort&sortby=<?=$sortFName;?>_<?=$order;?><?=$sec;?>" class="<?=$class;?>">(<?=$sortSet['fcode'];?>)</a>
			</td>
			<td width=7><a title="<?=$sortSet['title'];?>" href="search.php?action=sort&sortby=<?=$sortFName;?>_<?=$order;?>" class="<?=$class;?>"><img border=0 src="images/<?=$iname;?>" width=7 height=16></td></a>
		<?
			if ( $i < count($currSortOrderTable) )
			{
		?>
		
		
			<td width=10><img border=0 src="images/spacer.gif" width=5 height=1></td></a>
		<?
			} // end if
		?>
		
		<?
			} // end while
		?>
		</tr>
		</table>
	</td>
</tr>
</table>

