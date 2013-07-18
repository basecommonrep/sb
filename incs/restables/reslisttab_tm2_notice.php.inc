<?

if ($NReg!='') print('<i><font color=green>'.$LANG_SETTINGS['tm_notices2']['tm_nt_inf_svidotstvo'] .$NReg.'</i></font>');
elseif ($PROP!='') print('<i><font color=green>'.$LANG_SETTINGS['tm_notices2']['tm_nt_inf_vlasnik'].$PROP.'</i></font>');
// http://base.uipv.org/sv/searchBul/search.php?action=viewnotices&dbname=tm


// формат вложенного array -- например array('-RegN*', 12,'111','Number')
// [- align=right;  + align=center; по умолч align=left]
// поле из запроса (RegN), * - если есть - поле накапливается, если все остальные поля в след записях одинаковые по значению 
// ширина колонки  (12), 
// имя-заголовка колонки (111)  из incs\langsettings\notices-ukr.ini[tm_notices] созд как tm_tag_111
// имя ужимаемого поля - может быть может не быть. Если есть - то поле из запроса накапливается через запятую при равенстве значения этого ужимаемого поля. Разница между * и этим - при * проверяются на равенство все поля, кроме с *, а при этом варианте - только указанное в этом параметре поле


//формат одной записи (одной строки) - описания таблицы отображения  сповищення определенного типа 
//'тип сповищення'  => array(   array('[-|+]поле из запроса[*]', ширина колонки,'имя тэг-заголовка колонки'[,'имя ужимаемого поля']),...итд для всех колонок таблички на экране для этого сповищення ) , ... );                   
 $TMcaptions = array(
'ChangeOwner'				=> array(array('-RegN*',12,'111'),array('Holder' , 0,'732' )),
'Renewal'					=> array(array('-RegN', 12,'111'),array('+dt'    , 0,'186' )),

'InternationalReplacement'	=> array(array('-RegN', 12,'111'),array('+dt'    , 0,'Mreg')),
'TotalTerminationByOwner'	=> array(array('-RegN', 12,'111'),array('+dt'    , 0,'141')),
'PartialTerminationByOwner'	=> array(array('-RegN*', 12,'111'),array('+dt'    ,15,'141p'),		array('Goods'    , 0,'511c')),

'TerminationNoRenewalFee'	=> array(array('-RegN', 12,'111'),array('+dt'    , 0,'141')),
'TotalInvalidationByAppeal'	=> array(array('-RegN', 12,'111'),array('+dt'    , 0,'Crtdt')),
'TotalInvalidationByCourt'	=> array(array('-RegN', 12,'111'),array('DecisionDetails',75,'Crt'),	array('+dt'    , 0,'Crtdt')),
'PartialInvalidationByAppeal'	=> array(array('-RegN*', 12,'111'),array('Goods' ,75,'511c'),	array('+dt'    , 0,'Crtdtp')),
'PartialInvalidationByCourt'	=> array(array('-RegN*', 12,'111'),array('DecisionDetails',20,'Crt'),	array('Goods' ,55,'511c'),	array('+dt'    , 0,'Crtdtp')),

'ChangeOwnerByCourt'		=> array(array('-RegN', 12,'111'),array('DecisionDetails',35,'Crt'),	array('Holder', 0,'732Crt')),
'ChangesByCourt'			=> array(array('-RegN', 12,'111'),array('DecisionDetails',25,'Crt'),	array('Corrections', 0,'Cor')),
'TerminationGenericized'	=> array(array('-RegN', 12,'111'),array('DecisionDetails',65,'Crt'),	array('+dt'    , 0,'141')),

'TotalTerminationByCourt'	=> array(array('-RegN', 12,'111'),array('DecisionDetails',75,'Crt'),	array('+dt'    , 0,'141')),
'PartialTerminationByCourt'	=> array(array('-RegN', 12,'111'),array('DecisionDetails',20,'Crt'),	array('+dt'    , 12,'141'),	array('Goods' ,0,'511c')),
'TotalTransfer'				=> array(array('-RegN', 11,'111','Number'),array('PreviousHolder',40,'770'),	array('NewHolder',40,'732'),	array('+Number'    , 0,'Decision')), 

'TotalTransferByCourt'		=> array(array('-RegN', 11,'111'),array('PreviousHolder',40,'770'),	array('NewHolder',40,'732'),	array('+DecisionDetails', 0,'Crt')),

'PartialTransfer'			=> array(array('-RegN', 09,'111','Number'),array('+PublicationDetails',10,'450'),array('Holder',18,'732'),	array('Goods'    , 50,'511c'),array('+Number'    , 0,'Decision')),
'Licence'					=> array(array('-RegN', 11,'111','Number'),array('Licensor',35,'Licensor'),	array('Licensee',36,'Licensee'),array('+dt'    , 10,'Licence'),array('+Number'    , 0,'Decision')),

'TotalTransferInvalidationByCourt' => array(array('-RegN', 12,'111'),array('+dt', 12,'ReestrN'),		array('+PublicationDetails',15,'450Crt'),array('Holder',40,'732Crt'),array('DecisionDetails',25,'Crt'),array('+dt'    , 0,'DtNed')),
'AppealsRefusalByCourt'		=> array(array('-AppN', 18,'210'),array('DecisionDetails',25,'Crt'),array('Corrections',0,'Resolut')),
'Reclassification'			=> array(array('-RegN*', 12,'111'),array('Holder' ,25,'732'),		array('Goods'    , 0,'511')),
'Correction'				=> array(array('-RegN', 11,'111'),array('+PublicationDetails',15,'450'),	array('Corrections',0,'ToRead')),

'TotalTransferCorrection'	=> array(array('-RegN*', 12,'111'),array('+dt', 12,'ReestrN'),array('+PublicationDetails',15,'450VCrt'),array('Corrections', 0,'ToRead')),
'PartialTransferCorrection'	=> array(array('-RegN*', 12,'111'),array('Corrections', 0,'ToRead')),
'TotalTerminationCorrection'	=> array(array('-RegN', 12,'111'),array('+PublicationDetails',15,'450'),array('Corrections', 0,'ToRead')),
'PartialTerminationCorrection'	=> array(array('-RegN', 12,'111'),array('+PublicationDetails',15,'450'),array('Corrections', 0,'ToRead')),


'Duplicate'					=> array(array('+RegN', 12,'111')),
'DuplicateByCourt'			=> array(array('+RegN', 12,'111'),array('DecisionDetails',0,'Crt')),
'RestoreByCourt'			=> array(array('-RegN', 12,'111'),array('DecisionDetails',0,'Crt')),
'CourtDecisionCancellation'	=> array(array('+RegN', 12,'111'),array('DecisionDetails',0,'Crt')),

'DisclaimerByAppeal'		=> array(array('-RegN', 12,'111'),array('DecisionDetails', 0,'Crt')),
'ChangeGoodsAndServicesByCourt'	=> array(array('-RegN', 12,'111'),array('DecisionDetails',20,'Crt'),	array('Goods' ,0,'511')),

  );
//=============================================================================
$PPcaptions = Array(

'ChangeOwner'				=> array(array('-RegN*',12,'11'),array('Holder'   , 0,'73' )),
'ChangeCreators'			=> array(array('-RegN*',12,'11'),array('Designer' , 0,'72' )),
'ChangeDesignation'			=> array(array('-RegN*',12,'11'),array('dt' , 0,'54' )),
'Renewal'					=> array(array('-RegN' ,12,'11'),array('+dt'      , 0,'18' )),
'Termination'				=> array(array('-RegN' ,12,'11'),array('+dt'      , 0,'14' )),
'TotalTerminationByOwner'	=> array(array('-RegN' ,12,'11'),array('+dt'      , 0,'Crtdt')),
'PartialTerminationByOwner'	=> array(array('-RegN*',12,'11'),array('+dt'      , 10,'Crtdtp'),array('DesignDetails',0,'ToLimited')),

'TerminationNoRenewalFee'	=> array(array('-RegN' ,12,'11'),array('+dt'      , 0,'18')),    
'TotalInvalidationByAppeal'	=> array(array('-RegN' ,12,'11'),array('+dt'      , 0,'Crtdt')),
'TotalInvalidationByCourt'	=> array(array('-RegN*',12,'11'),array('DecisionDetails',55,'Crt'),	array('+dt'    , 0,'Crtdt')),
'PartialInvalidationByAppeal'	=> array(array('-RegN*',12,'11'),array('DesignDetails',55,'ToLimited'),array('+dt'    , 0,'Crtdtp')),
'PartialInvalidationByCourt'	=> array(array('-RegN*',12,'11'),array('DecisionDetails',25,'Crt'),array('DesignDetails',45,'ToLimited'),array('+dt'    , 0,'Crtdtp')),

'TotalTerminationByCourt'	=> array(array('-RegN*',12,'11'),array('DecisionDetails',75,'Crt'),	array('+dt'    , 0,'14')),
'PartialTerminationByCourt'	=> array(array('-RegN*',12,'11'),array('DecisionDetails',20,'Crt'),	array('+dt'    , 0,'14')),

'ChangeOwnerByCourt'		=> array(array('-RegN*',12,'11'),array('DecisionDetails',35,'Crt'),	array('Holder', 0,'73Crt')),
'StatementToUse'			=> array(array('-RegN', 12,'11'),array('+PublicationDetails',15,'45'),array('dt',25,'54'),array('Holder', 0,'73list')),
'TotalTransfer'				=> array(array('-RegN',11,'11','Number'),array('PreviousHolder',40,'73'),	array('NewHolder',40,'73new'),array('+Number'    , 0,'Decision')),
'Licence'					=> array(array('-RegN*',11,'11','Number'),array('Licensor',35,'Licensor'),	array('Licensee',36,'Licensee'),array('+dt'    , 10,'Licence'),array('+Number'    , 0,'Decision')),
'TotalTransferInvalidationByCourt'=> array(array('-RegN', 12,'11'),array('+dt', 12,'ReestrN'),	array('+PublicationDetails',15,'450VCrt'),array('Holder',40,'732Crt'),array('DecisionDetails',25,'Crt'),array('+dt'    , 0,'DtNed')),

'Correction'				=> array(array('-RegN*',11,'11'),array('+PublicationDetails',15,'45C'),	array('Corrections',0,'ToRead')),
'TotalTransferCorrection'	=> array(array('-RegN*',11,'11'),array('+Number'    , 10,'Decision'),array('+PublicationDetails',25,'45VCrt'),array('Corrections',0,'ToRead')),
'Duplicate'					=> array(array('+RegN', 12,'11')),

'TerminationByAppeal'		=> array(array('+RegN',12,'11'),array('+dt'      , 0,'14' )),
'Restore'					=> array(array('+RegN', 12,'11')),
'RestoreByCourt'			=> array(array('+RegN', 12,'11'),array('DecisionDetails',35,'Crt')),

);
//=============================================================================
// Поля для авто именования при отсутствии шаблона отображения
$TMfields= array(
array('-RegN*'			,12,'111'),
array('DecisionDetails'		,15,'Crt'),
array('PublicationDetails'	,10,'450'),
array('PreviousHolder'		, 0,'770'),
array('Holder' 			, 0,'732'),
array('NewHolder' 		, 0,'732'),
array('Licensor'		, 0,'Licensor'),	
array('Licensee'		, 0,'Licensee'),
array('Goods' 			, 0,'511'),
array('Corrections'		, 0,'ToRead'),
array('+dt'    			,10,'000'),
array('-Number'    		,10,'Decision'),
);
 
$PPfields= array(
array('-RegN*'			,12,'11'),
//array('AppN' 			,18,'21'),
array('DecisionDetails'	,15,'Crt'),
array('PublicationDetails'	,10,'45'),
array('PreviousHolder'	, 0,'77'),
array('Holder' 			, 0,'73'),
array('NewHolder' 		, 0,'73'),
array('Licensor'		, 0,'Licensor'),	
array('Licensee'		, 0,'Licensee'),
array('Designer' 		, 0,'72'),
array('DesigDetails' 	, 0,'DesignDetails'),
array('Corrections'		, 0,'ToRead'),
array('+dt'    			,10,'000'),
array('-Number'    		,10,'Decision'),
);									
$w = '100%'; //600;
$pre= substr($currDbName,0,2);	
//print('$pre='.$pre.'<BR>');
if ($pre=='tm') 
 { $Xcaptions= $TMcaptions; $Xfields=$TMfields;
 }
else 
 { $Xcaptions= $PPcaptions; $Xfields=$PPfields;
 }
?>

<table width="<?=$w;?>" border=0 cellspacing=1 cellpadding=2>

<?
// обеспечение инфы ($sorted) для упорядочивания сповищень (порядок выдачи задается их порядком в $TMcaptions )

      
	//for ($i=0; $i<count($searchShortBiblioSet); $i++)
	// $searchShortBiblioSet[$i]['type'] .= '-New'; 			// test
	//$searchShortBiblioSet[0]['name'] .= '- Якась нова назва сповіщення'; 
	
	$Notype =''; $sorted=Array();
	foreach ($Xcaptions as $tp => $row) 
	   $sor[$tp]=Array();
	for ($i=0; $i<count($searchShortBiblioSet); $i++) //создать группы из номеров сповищень - $sor[noticeCode] - номера из $searchShortBiblioSet
	{  $sor[$searchShortBiblioSet[$i]['type'] ][] = $i; 	
	  
        }
        //print('$sor=');print_r($sor);print('<BR><BR>');
	foreach ($Xcaptions as $tp => $row)
	{ $sorted  = Array_merge($sorted,$sor[$tp]); 
	  $sor[$tp]=Array(); 
	}

	
	foreach ($sor as $tp => $row) // неопределенные типы сповищень в $TMcaptions (их там нет)
	 if(!empty($sor[$tp]))
	 { $sorted  = Array_merge($sorted,$sor[$tp]); $Notype .='|'.$tp.'|';
           //построение авто шаблона отображения
           $avto=Array();
           foreach($Xfields as $key=>$row)
		{ $f=$row[0]; $i=$sor[$tp][0]; $set=$searchShortBiblioSet[$i];
		  //print('$f='.$f.'<br>');  print('$i='.$i.'<br>');  
		  $f=str_replace(array('-','+','*'),'',$f);
		  //print('after $f='.$f.'<br>'); print('$set[$f]='.$set[$f].'<br>'); 
                  if (!empty($set[$f])) $avto[] = $row;
		}
	   $Xcaptions += Array($tp => $avto);
	   //print('$avto=');print_r($avto);print('<BR>===============<BR>');
	 }
	//print('$Xcaptions=');print_r($Xcaptions);print('<BR><BR>');
	
	if (count($sorted)!=count($searchShortBiblioSet))
          print('count($sorted)!=count($searchShortBiblioSet)<br>');


//foreach( $searchShortBiblioSet as $key => $row) $sorted[]  = $key; //ничего не сортировать

// конец подготовки инфы
	
	$prevNoticeCode = '--';
	$prevBulYear = '--';
	$count = 0;
        
	
	for($i = 0; $i <= count($searchShortBiblioSet); $i++)
	{ $set=$searchShortBiblioSet[$sorted[$i]];
	  $noticeCode = $set['type'];
	  $bulYear = $set['bulYear'];
          //print('i='.$i.' noticeCode='.$noticeCode.' prevNoticeCode='.$prevNoticeCode.'<BR>');   

	  if ( ($noticeCode != $prevNoticeCode) || ($bulYear != $prevBulYear))
	  {
		if ( $i > 0 )
		{
			$count = 0;
?>
			<tr><td height="1"><img src="images/spacer.gif" height="1"></td></tr>
			</table><BR>
<?			
			$p=$LANG_SETTINGS[$pre.'_notices'][$pre.'_nt_'.$prevNoticeCode.'_afterTable']; //текст после таблицы сповищ типа ЛН - ліцензія невиключна итд
			if (!empty($p)) print($p.'<BR><BR>');
			if ($i == count($searchShortBiblioSet)) break;
?>
                        <table width="<?=$w;?>" border=0 cellspacing=1 cellpadding=2>	
			
<?
		} // end if ( $i > 0 )

		$bul=''; if (($NReg!='') || ($PROP!='')) $bul=$LANG_SETTINGS['common_viewparts']['bul'].' '.$set['bulYear'];
                $captionNotice= $LANG_SETTINGS[$pre.'_notices'][$pre.'_nt_'.$noticeCode];
		
		if (empty($captionNotice)) 
		  $captionNotice= $set['name'] . '<font color=red><BR><i>(=======no Caption '.$pre.'_nt_'.$noticeCode.')</i></font>';
		if (strpos($Notype,'|'.$noticeCode.'|')!==false )
		  $captionNotice .= '<font color=red><BR><i>(=======no def in '.$pre.'captions '.$noticeCode.')</i></font>';

	/////////////////////////// заголовок таблицы (название таблицы)  //$set['name']
                   
?>          
         

		<tr><td align=left colspan=5>
		   <font color="Green" >    <?=$bul;?>           </font>
                   <font class="viennacat"> <?=$captionNotice;?> </font>
                   <font color=grey> (<?=$noticeCode;?>)          </font>
		  </td>
		

		</tr>

		<tr> 
<?    	///////////////////////////// шапка таблицы (имена колонок)
		  $f=$Xcaptions[$noticeCode];
                  
                  for ($j =0; $j<count($f); $j++) 
                  { $caption_tag=$pre.'_tag_'.$f[$j][2];
                    $caption= $LANG_SETTINGS[$pre.'_notices'][$caption_tag]; //tm_nt_TotalTransferInvalidationByCourt
		    //$caption .= ' '.$caption_tag;
		    $fld=$f[$j][0];
                    $fld=str_replace(array('-','+','*'),'',$fld);
		    if ( ($fld=='dt') && empty($caption) ) // автоматич(если нет) колонки шаблона отображения
			{ $c_tag   = $pre.'_ntf_'.$set['tag'];
			  $caption = $LANG_SETTINGS[$pre.'_notices2'][$c_tag];
			  if (empty($caption)) $caption = $set['tag'];
			}
		    if ( empty($caption) ) // все равно нет 
			{ $caption = $fld;
			}	
                    $width=$f[$j][1]; 
?>
                  <td class="notifyHeader" valign=top width="<?=$width;?>%"><font class="viennacat2white"><?=$caption;?></font></td>			
<?
                  }
?>		     			
		</tr>
			

	
<?
          }
?>
              <tr valign=top> 
 
<?               
        $link0='<a href="search.php?action=viewdetails&dbname='.$pre.'&IdClaim=###idClaim###&from=notice" '
		      . 'class="viennacatchange" > ###v###</a>'; // notifyLineLeft2 viennacatchange
 		 
//print($link0.'<BR>'); 		 

        for ($j =0; $j<count($f); $j++) 
        { $field=$f[$j][0];
          $width=$f[$j][1]; 
          $align='left'; 
		  $accumul='';$accumul1=''; $accumul2='';
          if (substr($field,0,1) == '-') {$field = substr($field,1); $align='right';}   // -regN align=right
		  if (substr($field,0,1) == '+') {$field = substr($field,1); $align='center';}  // +regN align=center
		  if (substr($field,-1) == '*') {$field = substr($field,0,-1); $accumul=$field;}// regN* накапливаемое поле (если ВСЕ друие одинаковы)
		  $accumul1= $f[$j][3]; // ужимаемое поле (остальные тоже ужимаются но не проверяются на равенство - по первому)
		  $value = $set[$field];
		  $v=$value;
		  if($field=='RegN') 
			{ $link=str_replace('###v###',$v,$link0); 
			  //$link=str_replace('###idClaim###',$set['idClaim'],$link);
			  $link=str_replace('###idClaim###',$set['idClaim'],$link);
			  $value = $link;
            }
		    	    
		// проверка надо ли накапл поле (одинаковы ли значения всех остальных полей в след записях)
		  if ($accumul<>'') // * справа от имени поля 
		    { for($k=$i+1; ($k<count($searchShortBiblioSet))&&($searchShortBiblioSet[$sorted[$k]]['type']==$noticeCode)&&($searchShortBiblioSet[$sorted[$k]]['bulYear']==$bulYear); $k++)
			  { $setk = $searchShortBiblioSet[$sorted[$k]]; 
				for ($j1 =0; $j1<count($f); $j1++) 
				{ $fld=$f[$j1][0]; $fld=str_replace(array('-','+'),'',$fld);
				  if (($fld!=$field) && ($setk[$fld]!=$set[$fld])) break;
				}
                if ( $j1 < count($f) ) break;
				// все поля равны
                $v=$searchShortBiblioSet[$sorted[$k]][$field];
				//$link=$v;
                if($field=='RegN') // значение кака и ссылка
				{ $link=str_replace('###v###',$v,$link0); 
				  //$link=str_replace('###idClaim###',$set['idClaim'],$link);
				  $link=str_replace('###idClaim###',$setk['idClaim'],$link);	
				}
				$value .= ',<BR>'.$link ;
				$i = $k;	
			  }
		      $value .='&nbsp;';
		    }			
		    if ($accumul1<>'') 
		    {  for($k=$i+1; ($k<count($searchShortBiblioSet))&&($searchShortBiblioSet[$sorted[$k]]['type']==$noticeCode)&&($searchShortBiblioSet[$sorted[$k]]['bulYear']==$bulYear); $k++)
				{$setk = $searchShortBiblioSet[$sorted[$k]];   
                 if ($searchShortBiblioSet[$sorted[$k]][$accumul1]!=$set[$accumul1]) break;
			     // ужимаемое поле равно
			     $v=$searchShortBiblioSet[$sorted[$k]][$field];
			     $link=$v;
			     if($field=='RegN') // значение кака и ссылка
				 { $link=str_replace('###v###',$v,$link0); 
				   $link=str_replace('###idClaim###',$setk['idClaim'],$link);
                 }
				 $value .=',<BR>'. $link;
				 $i = $k;	
				}
		        $value .='&nbsp;'; 
		    }			    

		    //if (substr($value ,0,3)=='<tr') $value ='<table >'.$value.'</table >';
			// значения колонок - одна строка  //class="notifyLine2" bgcolor=white
			if ($align=='left') $class='notifyLine2'; 
			else if ($align=='right') $class='notifyLineR';
			else if ($align=='center') $class='notifyLineC';
			else $class='notifyLine2';
?>
                <td class="<?=$class;?>"  width="<?=$width;?>%"><?=$value;?></td>
                                
                
<?
		    
                  }
?>                
                </tr>

<?
          $prevNoticeCode=$noticeCode;
		$prevBulYear = $bulYear;
          
        }  
?>

		<tr><td height="5"><img src="images/spacer.gif" height="5"></td></tr>
		
		</table>

