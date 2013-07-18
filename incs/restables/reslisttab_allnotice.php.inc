<table width="500" border=0 cellspacing=0 cellpadding=0>

<?
	for($i = 0; $i < count($searchShortBiblioSet); $i++)
	{

		$noticeCode = $searchShortBiblioSet[$i][0];
		$fname = $searchShortBiblioSet[$i][1];		
		$file = $searchShortBiblioSet[$i][2];
		$file = ltrim(rtrim($file));


		// извлекаем то, что между <body></body>
		$s = '<body ';
		$p1 = strpos($file, $s); 
		$p1 = strpos($file, '>', $p1); 
		$p2 = strpos($file, '</body>'); 
		
		$file = substr($file, $p1+1, $p2-$p1);
		

		$file = str_replace('<br>', ' ', $file);
		$file = str_replace('margin-left', '', $file);
		$file = str_replace('margin-top', '', $file);
		$file = str_replace('margin-bottom', '', $file);
		$file = str_replace('text-indent', '', $file);

		$file = str_replace('style="font-family:\'Arial\';font-size:12pt;"', 'class="viennacat"', $file);
		$file = str_replace('style="font-family:\'Arial\';font-size:9pt;"', 'class="viennacat2"', $file);
		$file = str_replace('style="font-family:\'Arial\';font-size:7pt;"', 'class="restitle"', $file);
		$file = str_replace('MsoNormal', 'viennacat2', $file); 
		$file = str_replace('MsoBlockText', 'viennacat2', $file); 
		
		// заменяем в первой паре <tr>...</tr>
		
		$s = '</tr>';
		$p1 = strpos($file, $s); 
		$fileTemp1 = substr($file, 0, $p1);
		$fileTemp1 = str_replace('viennacat2', 'restitle', $fileTemp1); 
		$fileTemp1 = str_replace('viennacat2', 'restitle', $fileTemp1);
		$file = $fileTemp1.substr($file, $p1, strlen($file));
		
		

		
		$file = str_replace('<table border="1"', '<table class="tableborder" border=0 cellpadding=2 cellspacing=0', $file);
		$file = str_replace('<table', '<table class="tableborder" cellpadding=2 cellspacing=0 border=0', $file);


		if ( substr($currDbName, 0, 3) == 'inv' )
		{
			$p2 = strpos($file, '</tr>'); 
			$prevFile = substr($file, 0, $p2);
			$nextFile = substr($file, $p2-1, strlen($file));
			
			$prevFile = str_replace('span class="viennacat2"', 'span class="restitle"', $prevFile);
			$file = $prevFile.$nextFile;
		}
		

		// делаем заголовок синим бекграундом
		$file = substr_replace($file, 'tr bgcolor="#00518F"', strpos($file, 'tr'), 2);


		// устанавливаем для ячейки бордер
		$file = str_replace('<td', '<td class="cellborder"', $file);


		// удаляем все что за </table>
		$s = '</table>';
		$p2 = strpos($file, $s); 
		
		if ( strpos($file, $s, $p2+strlen($s)) )
		{
			$p2 = strpos($file, $s, $p2+strlen($s)); 	
		}
			
		$file = substr($file, 0, $p2+strlen($s));
		
		// удаляем все что между заголовком сповыщення и <table>
		$s = '</p>';
		$p1 = strpos($file, $s); 
		$fileTemp = substr($file, 0, $p1+strlen($s));

		
		$s = '<b>';
		$s2 = '</b>';
		$p1 = strpos($fileTemp, $s); 
		$p2 = strpos($fileTemp, $s2); 
		
		$fileTemp = substr($fileTemp, $p1, $p2+strlen($s2));
		$fileTemp = str_replace('<p>', '', $fileTemp);
		$fileTemp = str_replace('</p>', '', $fileTemp);		
		
		$fileTemp = ltrim(rtrim($fileTemp));
		
		if ( strlen($fileTemp) > 10 )
		{
			$fileTemp = '<table cellspacing=0 cellpadding=0 border=0><tr><td><p class="viennacat">'.$fileTemp.'</p></td></tr><tr><td colspan=9 height="10"><img src="images/spacer.gif" height="10"></td></tr></table>';

			$s = '<table';
			$p1 = strpos($file, $s); 
			$fileTemp = $fileTemp.substr($file, $p1, strlen($file));

			$file = $fileTemp;
		}

		$file = str_replace("<p style=\"\"><span class=\"viennacat\"><b>&nbsp;</b></span></p>", '', $file); 
		$file = str_replace("<p><span class=\"viennacat\"><b>&nbsp;</b></span></p>&lt;</td>", '', $file); 

		
		
?>

<?

	if ( $file != 'tr bgcol' )
	{
?>

	<tr>
		<td><?=$file;?></td>
	</tr>
	
	<tr><td colspan=9 height="10"><img src="images/spacer.gif" height="10"></td></tr>


<?
	} // end if
	} // end for
?>
</table>
