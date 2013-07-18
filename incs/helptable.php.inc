 <table border=0 cellpadding="0" cellspacing="0" width="100%">

<!--
  <tr>
   <td height="20px" background="images/bg2.jpg">
    <table cellpadding="0" cellspacing="0">
     <tr>
      <td class="helpimg" width="22px" height="20px" align="center">?</td>

      <td style="padding-left: 10px">
       <b><font style="FONT-SIZE: 14px;" class="help"><?=$LANG_SETTINGS['help']['field']?> "<?=$title;?>"</font></b>
      </td>
     </tr>
    </table>
   </td>
   <td align="right" background="images/bg1r.jpg" width="15% " nowrap="true">
    <b><span style="CURSOR: HAND;" class="help" onclick="javascript:printpr();"><?=$LANG_SETTINGS['details']['preview']?></span></b>&nbsp;
    <b><span style="CURSOR: HAND;" class="help" onclick="javascript:print();"><?=$LANG_SETTINGS['details']['print']?></span></b>&nbsp;
   </td>
  </tr>


  <tr>
   <td height="1px" background="images/bg1.jpg" style="padding-left:30px" colspan="2"></td>
  </tr>
-->

  <tr>
   <td colspan="2">
   <table border=0 cellpadding="0" cellspacing="0" width="100%">

   <tr>
   <td>

   <?
   	if ( $inid > 0 )
   	{
   ?>
	<b><font class="help"><?=$LANG_SETTINGS['help']['code'];?>:</font></b>&nbsp;<font class="help"><?=$inid;?></font><br>   
   <?
	}
   ?>

   <b><font class="help"><?=$LANG_SETTINGS['help']['fname'];?>:</font></b>&nbsp;<font class="help"><?=$title;?></font><br>
   <b><font class="help"><?=$LANG_SETTINGS['help']['ftype'];?>:</font></b>&nbsp;<font class="help"><?=$ftype_str;?></font>
   </td>
   </tr>

   <tr><td><img height=10 src="images/spacer.gif"></td></tr>

   <tr>
   <td>

<?
if ( $ftype === 1 ) // число
{
?>
	<font class="help"><?=$LANG_SETTINGS['help'][1];?></font>
<?
}
elseif ( $ftype == 2  ) // строка
{
?>
	<font class="help"><?=$LANG_SETTINGS['help'][11];?></font><br>
<?
}
elseif ( $ftype == 3  ) // дата
{
?>
	<font class="help"><?=$LANG_SETTINGS['help'][111];?>:</font>&nbsp;
	<b><font class="help"><?=$LANG_SETTINGS['help'][112];?>.<?=$LANG_SETTINGS['help'][113];?>.<?=$LANG_SETTINGS['help'][114];?></font></b><font class="help">,&nbsp;</font>
	<b><font class="help"><?=$LANG_SETTINGS['help'][112];?></font></b><font class="help">&nbsp;-&nbsp;<?=$LANG_SETTINGS['help'][115];?>,&nbsp;</font>
	<b><font class="help"><?=$LANG_SETTINGS['help'][113];?></font></b><font class="help">&nbsp;-&nbsp;<?=$LANG_SETTINGS['help'][116];?>,&nbsp;</font>
	<b><font class="help"><?=$LANG_SETTINGS['help'][114];?></font></b><font class="help">&nbsp;-&nbsp;<?=$LANG_SETTINGS['help'][117];?>.&nbsp;</font><br>

	<font class="help"><?=$LANG_SETTINGS['help'][1111];?></font>
<?
}
?>

   </td>
   </tr>

   <tr><td><img height=10 src="images/spacer.gif"></td></tr>
   
   <tr>
   <td>

<?
if ( $ftype === 1 ) // число
{
?>
	<b><font class="help"><?=$LANG_SETTINGS['help'][2];?>:</font></b><font class="help">&nbsp;<?=$LANG_SETTINGS['logical']['and'];?>, <?=$LANG_SETTINGS['logical']['or'];?>, <?=$LANG_SETTINGS['logical']['not'];?>,
	<?=$LANG_SETTINGS['logical']['and'];?>&nbsp;<?=$LANG_SETTINGS['logical']['not'];?>, <?=$LANG_SETTINGS['logical']['or'];?>&nbsp;<?=$LANG_SETTINGS['logical']['not'];?>.
	</font><br>
	<b><font class="help"><?=$LANG_SETTINGS['help'][3];?>:</font></b><font class="help">&nbsp;<, >, =, <=, >=, <>, (,).</font><br><br>
	<font class="help"><&nbsp;<?=$LANG_SETTINGS['help'][4];?>.</font><br>
	<font class="help">>&nbsp;<?=$LANG_SETTINGS['help'][5];?>.</font><br>
	<font class="help">=&nbsp;<?=$LANG_SETTINGS['help'][6];?>.</font><br>
	<font class="help"><=&nbsp;<?=$LANG_SETTINGS['help'][7];?>.</font><br>
	<font class="help">>=&nbsp;<?=$LANG_SETTINGS['help'][8];?>.</font><br>
	<font class="help"><>&nbsp;<?=$LANG_SETTINGS['help'][9];?>.</font><br>
	<font class="help">(,)&nbsp;<?=$LANG_SETTINGS['help'][10];?>.</font><br>
<?
}
elseif ( $ftype == 2  ) // строка
{
?>
	<b><font class="help"><?=$LANG_SETTINGS['help'][2];?>:</font></b><font class="help">&nbsp;<?=$LANG_SETTINGS['logical']['and'];?>, <?=$LANG_SETTINGS['logical']['or'];?>, <?=$LANG_SETTINGS['logical']['not'];?>,
	<?=$LANG_SETTINGS['logical']['and'];?>&nbsp;<?=$LANG_SETTINGS['logical']['not'];?>, <?=$LANG_SETTINGS['logical']['or'];?>&nbsp;<?=$LANG_SETTINGS['logical']['not'];?>.
	</font><br>
	<b><font class="help"><?=$LANG_SETTINGS['help'][3];?>:</font></b><font class="help">&nbsp;*, ?, ", (,).</font><br><br>
	<font class="help">*&nbsp;<?=$LANG_SETTINGS['help'][22];?>.</font><br>
	<font class="help">?&nbsp;<?=$LANG_SETTINGS['help'][221];?>.</font><br>
	<font class="help">"..."&nbsp;<?=$LANG_SETTINGS['help'][222];?>.</font><br>
	<font class="help">(,)</b>&nbsp;<?=$LANG_SETTINGS['help'][10];?>.</font><br>
<?
}
elseif ( $ftype == 3  ) // дата
{
?>
	<b><font class="help"><?=$LANG_SETTINGS['help'][2];?>:</font></b><font class="help">&nbsp;<?=$LANG_SETTINGS['logical']['and'];?>, <?=$LANG_SETTINGS['logical']['or'];?>, <?=$LANG_SETTINGS['logical']['not'];?>,
	<?=$LANG_SETTINGS['logical']['and'];?>&nbsp;<?=$LANG_SETTINGS['logical']['not'];?>, <?=$LANG_SETTINGS['logical']['or'];?>&nbsp;<?=$LANG_SETTINGS['logical']['not'];?>.
	</font><br>
	<b><font class="help"><?=$LANG_SETTINGS['help'][3];?>:</font></b><font class="help">&nbsp;<, >, =, <=, >=, <>, (,).</font><br><br>
	<font class="help"><&nbsp;<?=$LANG_SETTINGS['help'][33];?>.</font><br>
	<font class="help">>&nbsp;<?=$LANG_SETTINGS['help'][331];?>.</font><br>
	<font class="help">=&nbsp;<?=$LANG_SETTINGS['help'][332];?>.</font><br>
	<font class="help"><=&nbsp;<?=$LANG_SETTINGS['help'][333];?>.</font><br>
	<font class="help">>=&nbsp;<?=$LANG_SETTINGS['help'][334];?>.</font><br>
	<font class="help"><>&nbsp;<?=$LANG_SETTINGS['help'][335];?>.</font><br>
	<font class="help">(,)&nbsp;<?=$LANG_SETTINGS['help'][10];?>.</font><br>
<?
}
?>
 		
   </td>
   </tr>

   <tr><td><img height=10 src="images/spacer.gif"></td></tr>


   <tr>
   <td>

<?
if ( $ftype === 1 ) // число
{
?>
	<font class="help"><?=$LANG_SETTINGS['help'][44];?>.</font><br>
<?
}
elseif ( $ftype == 2  ) // строка
{
?>
	<font class="help"><?=$LANG_SETTINGS['help'][55];?> <?=$LANG_SETTINGS['logical']['and'];?>.</font>
<?
}
elseif ( $ftype == 3  ) // дата
{
?>
	<font class="help"><?=$LANG_SETTINGS['help'][66];?>.</font>
<?
}
?>
 		
   </td>
   </tr>

   <tr><td><img height=10 src="images/spacer.gif"></td></tr>
   
   <tr><td><b><font class="help"><?=$LANG_SETTINGS['help']['example']?>:</font></b></td></tr>

   <tr><td><img height=5 src="images/spacer.gif"></td></tr>
      
   <tr><td>

<?

$dbn = $currDbName;
if ( substr($dbn, 0, 3) == 'inv' || substr($dbn, 0, 3) == 'wkm' )
	$dbn = substr($dbn, 0, 3);
elseif ( substr($dbn, 0, 2) == 'pp' || substr($dbn, 0, 2) == 'tm' )
	$dbn = substr($dbn, 0, 2);
elseif ( substr($dbn, 0, 6) == 'madrid' )
	$dbn = substr($dbn, 0, 6);
	
$filename = '../searchBul/help/'.$dbn.'_help_'.$currFieldName.'.txt';

if ( file_exists( $filename ) )
	include( $filename );	
?>
   </td></tr>

   </table>
   </td>
  </tr>

 </table>

