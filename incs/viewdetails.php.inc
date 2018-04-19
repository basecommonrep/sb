<?
	if ( empty( $addDbName ) && !$isUEFA)
	{
		// для статистики
		// =============
		
		if ( $currFullBiblioChapter == 'biblio' )
			doStatistics('createnewaction', 'bul', null, $_SESSION['statInfo']['idUser'], 4, $mssql, null); // 4 - пергляд бібліографічних даних

		// тому що перегляд бібліографії влючає такоє перегляд документу
		if ( $currDbName != 'invc' )
			doStatistics('createnewaction', 'bul', null, $_SESSION['statInfo']['idUser'], 5, $mssql, null); // 5 - пергляд документа		
	}

?>

<table border=0 class="<?=(!$printed) ? 'maintable' : '';?>" width="100%" height=970 cellspacing=0 cellpadding=3>
<tr>
<td valign=top>
<form name="main" id="searchbul" method="post" action="">

<table border=0 cellspacing=0 cellpadding=5 width=100%>
<tr>
	<td>
	<table width="728" border=0 cellspacing=0 cellpadding=0>

<?
	if (!$printed)
	{
?>
	<tr>
		<td>
		<table class="box" border=0 cellspacing=0 cellpadding=0 width=100%>
		<tr>
			<td height=20 align="left" width=120>
				&nbsp;<font class="viennacat">
				<?=$currIdClaimIndex+1;?>
				/
				<?=((int)count($currSearchIds) > 0) ? (int)count($currSearchIds) : 1;?>
				</font>
			</td>

			<td align="right">
<?
	$basket_check_str = '<font class="viennacat2">'.$LANG_SETTINGS['basket']['tobasket'].'</font>&nbsp;'.
						'<input ###checked### type="checkbox" class="viennacat2" onclick="javascript: basketAction(this,\''.$currDbName.'\',###IDCLAIM###);">';

	$bcs = $basket_check_str;
	$bcs = str_replace('###IDCLAIM###', $idClaim, $bcs);				

	if ( in_array($idClaim, $currBasketIds) )
		$bcs = str_replace('###checked###', 'checked', $bcs);	
?>

			<?
				if (!$isUEFA)
				{
			?>

			<font class="viennacat2">|</font>
			<?=$bcs;?>			
			<font class="viennacat2">|</font>

			<?
				}
			?>
			
			<a href="<?=$printStr;?>" target=_blank class="pgline"><?=strtolower($LANG_SETTINGS['details']['print']);?></a>			

			<font class="viennacat2">|</font>

<?

	if ( $_SESSION['lastAction'] == 'viewbul' || $_SESSION['lastAction'] == 'viewnotices' )
	{
		$backTitle = $LANG_SETTINGS['details']['ppBack'];
		if ( !empty($addDbName) )
			$backTitle = $LANG_SETTINGS['details']['ppBack2'];
		
		$act = 'viewbul';
		$db_name = $_SESSION['lastViewBulDbName'];
		if ( $_SESSION['lastAction'] == 'viewnotices' )
		{
			$act = 'viewnotices';
			$db_name = $currDbName;
			$backTitle = $LANG_SETTINGS['details']['ppBack3'];
			
		}
		
		$backAction = 'search.php?action='.$act.'&dbname='.$db_name.'&section='.$_SESSION['lastViewBulSecName'].'&page='.$_SESSION['lastViewBulPageNumb'].'&from=details';
		$nextAction = '&dbname='.$_SESSION['lastViewBulDbName'];
	}
	elseif ( $_SESSION['lastAction'] == 'viewbasket' )
	{
		$backAction = 'basket.php?action=viewbasket';
		$backTitle = $LANG_SETTINGS['basket']['tobasket'];
	}
	elseif ( $isUEFA && ( $_SESSION['lastAction'] == 'viewall' || $_SESSION['lastAction'] == 'sort' ) )
	{
		$backAction = 'search.php?action=viewall&dbname='.$currDbName;
		$backTitle = $LANG_SETTINGS['euro_headers']['back'];
	}
	else
	{
		$backTitle = $LANG_SETTINGS['res']['backToRes'];
		$backAction = 'search.php?action=viewsearchres';
		$nextAction = '';
	}
		
	if ( (int)count($_SESSION['lastSearchIds']) > 0 || (int)count($_SESSION['lastViewIds']) > 0 || $_GET['from'] == 'notice' || $_SESSION['lastAction'] == 'viewnotices' )
	{
?>
			
			<a class="pgline" href="<?=$backAction;?>"><?=$backTitle;?></a>
			
<?
	}
	else
	{
?>
			<font class="pglinedis"><?=$LANG_SETTINGS['res']['backToRes'];?></font>			
<?
	}
?>

			

			<font class="viennacat2">|</font>
<?
	if ( empty($prevId) )
	{
?>
			
			<font class="pglinedis"><?=$LANG_SETTINGS['res']['back'];?></font>
<?
	}
	else
	{
?>
			<a class="pgline" href="search.php?action=viewdetails&chapter=<?=$currFullBiblioChapter;?>&IdClaim=<?=$prevId;?><?=$nextAction;?>&dbname=<?=$currDbName;?>"><?=$LANG_SETTINGS['res']['back'];?></a>	
<?
	}
?>

			<font class="viennacat2">|</font>
			
<?
	if ( empty($nextId) )
	{
?>
			
			<font class="pglinedis"><?=$LANG_SETTINGS['res']['forw'];?></font>
<?
	}
	else
	{
?>
			<a class="pgline" href="search.php?action=viewdetails&chapter=<?=$currFullBiblioChapter;?>&IdClaim=<?=$nextId;?><?=$nextAction;?>&dbname=<?=$currDbName;?>"><?=$LANG_SETTINGS['res']['forw'];?></a>	
<?
	}
?>
	&nbsp;

			</td>
		</tr>
		</table>
		</td>
	</tr>

	<tr><td height="10"><img src="images/spacer.gif" height="10"></td></tr>
<?
	} // end if printed
?>

<?
	$inv = array(44, 45, 46, 47, 48, 49, 50); // патент на винахід
	$dinv = array(53); // деклараційний патент на винахід
	$um = array(51, 52, 54); // патент на корисну модель
	$dum = array(671); // деклараційний патент на корисну модель
	
	$nn = 'inv';
	if ( in_array($fullBiblio['i_13_code'], $inv))
		$nn = 'inv';
	elseif ( in_array($fullBiblio['i_13_code'], $dinv))
		$nn = 'dinv';
	elseif ( in_array($fullBiblio['i_13_code'], $um))
		$nn = 'um';
	elseif ( in_array($fullBiblio['i_13_code'], $dum))
		$nn = 'dum';
	elseif ( substr($currDbName, 0, 2) == 'pp' )
		$nn = 'pp';
	elseif ( substr($currDbName, 0, 2) == 'tm' && $currDbName != 'tmc' )
		$nn = 'tm';
	elseif ( $currDbName == 'tmc' )
		$nn = 'tmc';
	elseif ( $currDbName == 'madridall' )
		$nn = 'madridall';
	elseif ( $currDbName == 'geoc' && $fullBiblio['app_category'] == 'app-reg' )
		$nn = 'geoc1';
	elseif ( $currDbName == 'geoc' && $fullBiblio['app_category'] == 'app-reg-use' )
		$nn = 'geoc2';
	elseif ( $currDbName == 'geo' )
		$nn = 'geo';
	elseif ( $currDbName == 'geor' )
		$nn = 'geor';
	
		
	$n = '';
	if ( substr($currDbName, 0, 3) == 'inv' || substr($currDbName, 0, 3) == 'wkm' )
		$n = substr($currDbName, 0, 3);
	elseif ( substr($currDbName, 0, 2) == 'pp' || ( substr($currDbName, 0, 2) == 'tm' && $currDbName != 'tmc')  )
		$n = substr($currDbName, 0, 2);
	elseif ( $currDbName == 'tmc' )
		$n = $currDbName;
	elseif ( $currDbName == 'madrid' )
		$n = substr($currDbName, 0, 6);
	elseif ( $currDbName == 'madridall' )
		$n = $currDbName;	
	elseif ( $currDbName == 'geoc' )
		$n = $currDbName;	
	elseif ( $currDbName == 'geo' )
		$n = $currDbName;	
	elseif ( $currDbName == 'geor' )
		$n = $currDbName;	
		
	if ( substr($n, 0, 3) == 'inv' )
	{
		if ( $currDbName == 'invc' )
		{
			if (in_array($fullBiblio['i_13_code'], $um) || in_array($fullBiblio['i_13_code'], $dum) )
				$nn = $currDbName.'_um';
			else
				$nn = $currDbName.'_inv';
		}
		
		$i1 = ( $currDbName == 'invc' ) ? $fullBiblio['i_21'] : $fullBiblio['i_11'];
	}
	elseif ( substr($n, 0, 2) == 'pp' )	
		$i1 = $fullBiblio['i_11'];
	elseif ( substr($n, 0, 2) == 'tm' && $n != 'tmc' )	
		$i1 = $fullBiblio['i_111'];
	elseif ( $n == 'tmc' )
		$i1 = $fullBiblio['i_210'];
	elseif ( $n == 'madridall' )	
		$i1 = $fullBiblio['fi_111'];
  elseif ( $n == 'geoc' )	
		$i1 = $fullBiblio['app_number'];
  elseif ( $n == 'geo' )	
		$i1 = $fullBiblio['reg_number'];
  elseif ( $n == 'geo' )	
		$i1 = $fullBiblio['reguse_number'];

	//print($nn);
	
	//print_r($LANG_SETTINGS['details']);
	if ( $currDbName == 'tmc' )
		$n = 'tm';
	
	//print($nn);
	//print($fullBiblio['i_46']);

	if ($nn == 'um' && ( strtotime($fullBiblio['i_46']) < strtotime('16.02.2007')) )
		$nn = 'dum';

?>

	<tr>
		<td>
			<font style="font-size: 12px" class="viennacat"><?=$LANG_SETTINGS['details']['title_'.$nn];?>&nbsp;#&nbsp;<?=$i1;?></font>
		</td>
	</tr>

	<tr><td height="10"><img src="images/spacer.gif" height="10"></td></tr>
	
	<?
	if ( !($addDbName == 'cert' && $currDbName == 'tm'))
	{
	?>

	<tr>
		<td>
			<font style="font-size: 16px" class="viennacat"><?=strtoupper($_SESSION['lastFullBiblioClaimTitle']);?></font>		
		</td>
	</tr>

	<tr><td height="10"><img src="images/spacer.gif" height="10"></td></tr>
	<?
	}
	?>
	
	<tr>
		<td>
<?

	if ( substr($currDbName, 0, 3) == 'inv' )
		include("./incs/restables/reslisttabdetails_allinv.php.inc");
	else
		include('./incs/restables/reslisttabdetails_'.$n.'.php.inc');				
?>
		</td> <!--конец td-->
	</tr>

    </table>
	</td>
</tr>

</td>
</tr>
</table>
</form>

</td>
</tr>
</table>

