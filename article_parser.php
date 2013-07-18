<?
	function getTagData($parsedXml, $tagName)
	{
		for ($i = 0; $i < count($parsedXml); $i++)
		{
			//print($parsedXml[$i]['name'].'<BR>');
			
			if ( strtoupper($parsedXml[$i]['name']) == strtoupper($tagName) )
			{
				$res = $parsedXml[$i]['children']; 
				break;
			}
			else
			{
				if ( count($parsedXml[$i]['children']) > 0 )
					$res = getTagData($parsedXml[$i]['children'], $tagName);
				else
					if ( count($res) === 0 )
					$res = array();
			}
			
			//if ( count($parsedXml[$i]['children']) > 0 )
			
		} // end for
		
		//print(count($parsedXml).'<BR>');
		//print_r($res);

		return $res;
	} // end function

	function writeToLog($errorPathFile, $str)
	{
		$fh = fopen($errorPathFile, "a" );
		fwrite($fh, $str."\r\n");
		fclose($fh);
	} // end function writeToLog

	function Del_User_Files($dir)
	{
		if ( is_dir( $dir ) )
	 	{
			$handle = opendir($dir); 
			while (false !== ($file = readdir($handle))) 
			{
				if ($file != "." && $file != "..") 
				 { 
					$del_file = $dir.'/'.$file;
					
					//print($del_file.'<BR>'); 
					
				    unlink($del_file);
		         }
		    }
			closedir($handle); 
		}
	} // end function Del_User_Files
	
	function getNameStr($surnames, $names)
	{
		$name = '';
		
		if ( count($surnames) === count($names))
		{
			for ($i = 0; $i < count($surnames); $i++)
				$name .= $surnames[$i].' '.$names[$i].'; ';
			
		}
		
		return $name;
		
	} // end function getNameStr

	function getKwdStr($kwd)
	{
		$k = '';
		
		for ($i = 0; $i < count($kwd); $i++)
			$name .= $kwd[$i].'; ';
			
		return $k;
		
	} // end function getKwdStr
	
?>


<?

	/*	
	$authors = '<surname>Kalra</surname><surname>Kalra2ss</surname><surname2>Kalra2</surname2>';
	preg_match_all("/(?<=<surname>)([\w\d]*)(?=<\/surname>)/", $authors, $matches);
	print_r($matches);
	//exit;
	*/
	

	/*
	$authors = 'sssdd<sec sec-type="methods">Methods We studied four populations of the Lake Malawi Pseudotropheus zebra';
	print($authors.'<BR><BR><BR>');
	print(preg_replace("/(<sec)(.*)(\">)/", '', $authors));
	*/
	//exit;
	
	include('.././searchBul/incs/xml.php.inc');
	include('.././searchBul/incs/common_funcs.inc');
	include('.././searchBul/incs/htmltodoc.inc');
	include('.././searchBul/incs/word/clsWord.inc');


	$objXML = new xml2Array();
	$htmltodoc = new HTML_TO_DOC(); 
	$path = "//u608-pustovit/arch/";	
	$pathMy = "d:/readbook/referats/docs/";
	$pathMy2 = "d:/readbook/referats/pdfs/";
	$path2 = "//ksc-2/articles/temp/";	
	$errorPath = "d:/readbook/referats/log";
	$templatePath = "d:/readbook/referats/pattern.html";
	
	
	// читаем шаблон
	$handle = fopen($templatePath, "r");
	$template = fread($handle, filesize($templatePath));
	fclose($handle);
	
	// подключаемся к БД
	/*
	$host = 'u608-pustovit';
	$login = 'leha';
	$pass = 'leha';
	$database = 'articls';
	*/


	$host = 'u608-drobyazko';
	$login = 'sa';
	$pass = '1980al';
	$database = 'test';
	$database = 'cead';


	$db = mssql_connect($host, $login, $pass);					
	mssql_select_db($database, $db);
	

	$p = 'd:/ReadBOOK/CEAD_EXPORT';
	$docArr = glob($p.'/*.*');
	
	$a = array();
	for ($i = 0; $i < count($docArr); $i++)
	{
		$fn = basename($docArr[$i]);
		$n = strtolower(substr($fn, strpos($fn, '.')));
		
		print($n.'<BR>');
		
		$handle = fopen($docArr[$i], "r");
		$body = fread($handle, filesize($docArr[$i]));
		fclose($handle);

		$body = unpack( "H*hex", $body );

		$query = 'insert into t1(f, 			    type) '.
						'values (0x'.$body['hex'].', \''.$n.'\')';
		$rt = mssql_query($query, $db);

		print($docArr[$i].'<BR>');
	}
	
	// =========================================================================================================================
	// =========================================================================================================================
	// =========================================================================================================================
	exit;
	
	

	$p = 'd:/ReadBOOK/Referats/doc_clear';
	$docArr = glob($p.'/*.doc');
	
	
	$a = array();
	for ($i = 0; $i < count($docArr); $i++)
	{
		$fn = basename($docArr[$i]);
		$n = substr($fn, strpos($fn, '_')+1, strpos($fn, '.')-strpos($fn, '_')-1);
		
		$fn2 = str_replace('.doc', '.html', $fn);
		$p2 = 'd:/ReadBOOK/Referats/html_clear/'.$fn2;
		

		$handle = fopen($docArr[$i], "r");
		$body = fread($handle, filesize($docArr[$i]));
		fclose($handle);
	

		$body = unpack( "H*hex", $body );

		$query = 'insert into files(idArticle, 		filebody, 			    filetype,        ext) '.
						'values ('.$n.',    0x'.$body['hex'].',     \'dirty_doc\',  \'doc\')';

		$rt = mssql_query($query, $db);


		$handle = fopen($p2, "r");
		$body = fread($handle, filesize($p2));
		fclose($handle);
	
	
		$body = unpack( "H*hex", $body );

		$query = 'insert into files(idArticle, 		filebody, 			    filetype,        ext) '.
						'values ('.$n.',    0x'.$body['hex'].',     \'dirty_html\',  \'html\')';
		$rt = mssql_query($query, $db);
						
		print($docArr[$i].'<BR>');
		
	}
	
	exit;

	// =========================================================================================================================
	// =========================================================================================================================
	// =========================================================================================================================


	
	//$query = "select a.idArticle, a.journalTitle, a.journalYear, cast(a.articleTitle as text) [articleTitle], cast(a.articleAuthors as text) [articleAuthors] from dbo.ArticleInfoNew a where a.toTranslation = 1";
	$query = 'select a.idArticle, a.journalTitle, a.journalYear, cast(a.articleTitle as text) [articleTitle], cast(a.articleAuthors as text) [articleAuthors] from dbo.ArticleInfoNew a left join dbo.files f on a.idarticle=f.idarticle and f.filetype=\'dirty_doc\' where f.id is null';
	$rt = mssql_query($query, $db);
	
	$a = array();

	while ($row = mssql_fetch_array($rt, MSSQL_ASSOC))
		$a += array($row['idArticle'] => $row);
		
	$a_k = array_keys($a);
	
	//print_r($a_k);
	

	$i = 0;
	$step = 100;

	
	$c = 0;
	$err_ids = array();
	
	$Word = new clsMSWord; 
	
	while( $i < count($a_k)-1 )
	{
		$at = array_slice($a_k, $i, $step);   
		$str = implode(",", $at);
		
		//print($str.'<BR><BR>');
		
		$query = "select id, idarticle, filebody from files f where f.filetype = 'abstract' and f.idarticle in ($str)";
		$rt = mssql_query($query, $db);
		
		$j = 0;
		while ($row = mssql_fetch_array($rt, MSSQL_ASSOC))
		{
			$input = 'd:/ReadBOOK/Referats/abstract/'.$row['id'].'_'.$row['idarticle'].'.txt';
			
			//writeToLog($input, $row['filebody']);
			
			/*
			if ( strlen($row['filebody']) < 300 )
			{
				array_push($err_ids, $row['idarticle']);	
			}
			*/
			
			if ( stristr($row['filebody'], '</abstract>') )
			{
				array_push($err_ids, $row['idarticle']);	
				
				$row['filebody'] = substr($row['filebody'],  0, strpos($row['filebody'], '</abstract>'));
				
				$output = 'd:/ReadBOOK/Referats/abstract_clear/'.$row['id'].'_'.$row['idarticle'].'.txt';
				//writeToLog($output, $fb);
			}
			
			/*
			if ( strlen($row['filebody']) > 2700 )
			{
				
				if ( !stristr($row['filebody'], '<p>background</p>') && !stristr($row['filebody'], '<p>conclusions</p>') )
				{
					$output = 'd:/ReadBOOK/Referats/abstract_clear/'.$row['id'].'_'.$row['idarticle'].'.txt';
					//writeToLog($output, $row['filebody']);
				}
				
				elseif ( stristr($row['filebody'], '<p>background</p>') && stristr($row['filebody'], '<p>conclusions</p>'))
				{
					$output = 'd:/ReadBOOK/Referats/abstract_clear/'.$row['id'].'_'.$row['idarticle'].'.txt';
					//writeToLog($output, $row['filebody']);
				}
			}
			*/
			
			/*
			if ( stristr($row['filebody'], '<tr') || stristr($row['filebody'], '<td') || stristr($row['filebody'], '<table') )
			{	
				array_push($err_ids, $row['idarticle']);	
			}
			*/
			

			$output = 'd:/ReadBOOK/Referats/abstract_clear/'.$row['id'].'_'.$row['idarticle'].'.txt';
			//writeToLog($output, $row['filebody']);

			
			$journalTitle = $a[$row['idarticle']]['journalTitle'];
			$title = $a[$row['idarticle']]['articleTitle'];
			$authorStr = $a[$row['idarticle']]['articleAuthors'];
			$abstract = $row['filebody'];
			$keyWords = '&nbsp;';
			
			$currTemplate = $template;
			$currTemplate = str_replace('$$$SOURCE$$$', $journalTitle,	$currTemplate);
			$currTemplate = str_replace('$$$NAME$$$', 	$title, 		$currTemplate);
			$currTemplate = str_replace('$$$AUTHOR$$$', $authorStr,		$currTemplate);
			$currTemplate = str_replace('$$$REF$$$', 	$abstract, 		$currTemplate);				
			$currTemplate = str_replace('$$$KEYW$$$', 	$keyWords,		$currTemplate);
			
			$output = 'd:/ReadBOOK/Referats/html_clear/'.$row['id'].'_'.$row['idarticle'].'.html';
			$output2 = 'd:/ReadBOOK/Referats/doc_clear/'.$row['id'].'_'.$row['idarticle'].'.doc';
			
			
			writeToLog($output, $currTemplate);
			
			/*
			if ( strlen($currTemplate) > 5000)
			{	
				array_push($err_ids, $row['idarticle']);	
			}
			*/
		
			$j++;
			
			if ( ($j % 100) == 0 )
			{
				$Word->Quit();
				$Word = new clsMSWord;
			}
			
	   		$Word->Open($output); 
   			$Word->SaveAs($output2); 
		}
		$i = $i + $step;
	}
	
	$Word->Quit(); 
	
	$str = implode(",", $err_ids);
	print($str);
		
	exit;

	// =========================================================================================================================
	// =========================================================================================================================
	// =========================================================================================================================


	/*
	// *************************************************************************************************
	// *************************************************************************************************
	// *************************************************************************************************
	$p = $path.'22648';
		
	$pdfArr = glob($p.'/*.pdf');
	
	print_r($pdfArr);
	
	exit;

	copy('//u608-pustovit/arch/404/gb-2005-6-2-208.pdf', 'd:/1.pdf');
	
	$pdfArr[0] = $pathMy2.'243.pdf';
	
	$handle = fopen($pdfArr[0], "r");
	$pdfarticle = fread($handle, filesize($pdfArr[0]));
	fclose($handle);
	
	
	$pdfarticle = unpack( "H*hex", $pdfarticle );
	
	print(strlen());
	//for ($i = 0; $i < 100; $i++)
	{
		$query = 'insert into files(idArticle, 		[file], 			    filetype) '.
				'values (670,   0x'.$pdfarticle['hex'].', \'pdf\')';
				
		mssql_query($query, $db) or exit('error: ');;
	}
	
	exit;
	*/


	// *************************************************************************************************
	// *************************************************************************************************
	// *************************************************************************************************

	
	/*
	// *************************************************************************************************
	// *************************************************************************************************
	// *************************************************************************************************

	
	$query = 'select file_2, filetype from files2 where idarticle=100';
	$rt = mssql_query($query, $db);
	while ($row = mssql_fetch_array($rt, MSSQL_ASSOC))
	{
		writeToLog('d:/'.$row['filetype'], $row['file_2']);
	}	
	
	exit;
	


	// *************************************************************************************************
	// *************************************************************************************************
	// *************************************************************************************************

	*/

	$data = file('d:/RefSended.txt');
	$s = implode(",", $data);

	$query = 'update ArticleInfo set totranslation=1 where idjournal in ('.$s.')';
	mssql_query($query, $db);

	//print($s);
	exit;	



















	/*
	$query = 'select [file], filetype from files where idarticle=2';
	$rt = mssql_query($query, $db);
	while ($row = mssql_fetch_array($rt, MSSQL_ASSOC))
	{
		writeToLog('d:/'.$row['filetype'], $row['file']);
	}	
	
	exit;
	*/
	
	
	// очищаем таблицу
	$query = 'truncate table dbo.ArticleInfoNew';
	mssql_query($query, $db);

	$query = 'truncate table dbo.files';
	mssql_query($query, $db);

	
	/*
	$query = 'select a.journalTitle, a.articleTitle from ArticleInfo a order by a.idJournal';
	$rt = mssql_query($query, $db);
	
	$articleArr = array();
	while ($row = mssql_fetch_array($rt)
	{
		
	}
	*/
	
	
	// видаляемо лог
	Del_User_Files($errorPath);

	$successCount = 0;
	$allCount = 0;
	
	$i = 1;
		
	while ($i <= 30000)
	{
		//if ( $i == 2053)
		//	++$i;
			
		$allCount++;
		//print('***************** '.$i.'*****************<BR>');
		print($i.', ');
		$errorPathFile = $errorPath.'/'.$i.'.txt';		
		$error = false;
		
		$p = $path.$i;
		if ( is_dir( $p ) )	
		{
			$nxmlArr = glob($p.'/*.nxml');
			$pdfArr = glob($p.'/*.pdf');
			$nxml = $nxmlArr[0];
			$pdf = $pdfArr[0];

			//print('count pdf = '.count($pdfArr).'<BR>');
			//print('count nxml = '.count($nxmlArr).'<BR>');			
			//print($nxml.'<BR>');
			//print($pdf.'<BR>');

			//if ( file_exists($nxml) && file_exists($pdf) && count($pdfArr) === 1 && count($nxmlArr) === 1 )
			if ( file_exists($nxml) && count($nxmlArr) === 1 )
			{
				$handle = fopen($nxml, "r");
				$article = fread($handle, filesize($nxml));
				fclose($handle);
				
				// issn
				if ( strstr($article, '<issn pub-type="ppub">') )
				{
					$s = '<issn pub-type="ppub">';
					$s2 = '</issn>';
					$issn = substr($article, strpos($article, $s)+strlen($s), strpos($article, $s2, strpos($article, $s))-strpos($article, $s)-strlen($s));
					
					//print($issn.'<BR>');
				}
				elseif ( strstr($article, '<issn pub-type="epub">') )
				{
					$s = '<issn pub-type="epub">';
					$s2 = '</issn>';
					$issn = substr($article, strpos($article, $s)+strlen($s), strpos($article, $s2, strpos($article, $s))-strpos($article, $s)-strlen($s));
					
					//print($issn.'<BR>');
				}
				else
				{
					//$error = true;					
					writeToLog($errorPathFile, 'Немає ISSN');
				}

				// ключові слова
				if ( strstr($article, '<kwd-group kwd-group-type="author">') )
				{
					$s = '<kwd-group kwd-group-type="author">';
					$s2 = '</kwd-group>';
					$kwdXmlStr = substr($article, strpos($article, $s)+strlen($s), strpos($article, $s2, strpos($article, $s))-strpos($article, $s)-strlen($s));
					
					preg_match_all("|<kwd>(.*)</kwd>|U", $kwdXmlStr, $kwd);
					
					$keyWords = getKwdStr($kwd);
					
					//print('KWD='.$keyWords.'<BR>');
				}
				else
				{
					//$error = true;					
					//writeToLog($errorPathFile, 'Немає ключових слів');
				}

				// назва журналу (дата публікації)
				if ( strstr($article, '<journal-title>') )
				{
					$s = '<journal-title>';
					$s2 = '</journal-title>';
					$journalTitle = substr($article, strpos($article, $s)+strlen($s), strpos($article, $s2, strpos($article, $s))-strpos($article, $s)-strlen($s));
					
					$s = '<pub-date pub-type="ppub">';
					$s2 = '</pub-date>';
					$journalYearStr = substr($article, strpos($article, $s)+strlen($s), strpos($article, $s2, strpos($article, $s))-strpos($article, $s)-strlen($s));
					
					$s = '<year>';
					$s2 = '</year>';
					$journalYear = substr($article, strpos($article, $s)+strlen($s), strpos($article, $s2, strpos($article, $s))-strpos($article, $s)-strlen($s));
					
					$journalTitle .= ' ('.$journalYear.')';
					
					//print($journalTitle.'<BR>');
				}
				else
				{
					//$error = true;					
					writeToLog($errorPathFile, 'Немає назви журналу та дати публікації');
				}

				
				// автори
				if ( strstr($article, '<contrib-group>') )
				{
					$authors = substr($article, strpos($article, '<contrib-group>')+strlen('<contrib-group>'), strpos($article, '</contrib-group>')-strpos($article, '<contrib-group>')-strlen('<contrib-group>'));;
					
					//preg_match_all("/(?<=<surname>)([^\s]*)(?=<\/surname>)/", $authors, $surnames);					
					//preg_match_all("/(?<=<given-names>)([^\s]*)(?=<\/given-names>)/", $authors, $names);					
					
					preg_match_all("|<surname>(.*)</surname>|U", $authors, $surnames);
					preg_match_all("|<given-names>(.*)</given-names>|U", $authors, $names);
					
					
					$authorStr = getNameStr($surnames[1], $names[1]);
					//$parsedAuthors = $objXML->parse($authors);
					
					//print($authorStr.'<BR>');
					//print_r($parsedAuthors);
				}
				else
				{
					//$error = true;					
					writeToLog($errorPathFile, 'Немає авторів');
				}

				// назва статті
				if ( strstr($article, '<article-title>') )
				{
					$title = substr($article, strpos($article, '<article-title>')+strlen('<article-title>'), strpos($article, '</article-title>')-strpos($article, '<article-title>')-strlen('<article-title>'));;
					//print($title.'<BR>');
				}
				else
				{
					//$error = true;					
					writeToLog($errorPathFile, 'Немає назви статті');
				}
				
				// реферат
				if ( strstr($article, '<abstract>') )
				{
					$abstract = substr($article, strpos($article, '<abstract>')+strlen('<abstract>'), strpos($article, '</abstract>')-strpos($article, '<abstract>')-strlen('<abstract>'));
					$abstract = str_replace('<sec>', '', $abstract);
					
					$abstract = preg_replace("/(<sec)(.*)(\">)/", '', $abstract);
					
					$abstract = str_replace('</sec>', '', $abstract);
					$abstract = str_replace('</title>', '</p>', $abstract);
					
					$abstract = str_replace('<title>', '<p>', $abstract);
					$abstract = preg_replace("/(<title)(.*)(\">)/", '', $abstract);
					//print($abstract.'<BR><BR><BR>');
				}
				else
				{
					//print($article.'<BR>');
					//педет тим, як визнати відстутність реферату, виконуємо пошук першого абзацу тексту статті
					
					$s = '<body>';
					$s2 = '</body>';
					$articleBody = substr($article, strpos($article, $s)+strlen($s), strpos($article, $s2, strpos($article, $s))-strpos($article, $s)-strlen($s));
					
					$s = '<p>';
					$s2 = '</p>';
					if ( strstr($articleBody, $s) && strstr($articleBody, $s2) )
					{
						$articleFirstSection = '';
						$articleFirstSection = substr($articleBody, strpos($articleBody, $s)+strlen($s), strpos($articleBody, $s2, strpos($articleBody, $s))-strpos($articleBody, $s)-strlen($s));
						$abstract = $articleFirstSection;
					}
					else
						writeToLog($errorPathFile, 'Немає реферату');
				}
				
				if ( strstr($article, 'To access the full article, please see PDF') )
					writeToLog($errorPathFile, 'To access the full article, please see PDF');	
				
				
			} // if ( file_exists($nxml) && file_exists($pdf) )
			else
			{
				//$error = true;					
				if ( !file_exists($nxml) )
					writeToLog($errorPathFile, 'Немає nxml');
				elseif ( !file_exists($pdf) )
					writeToLog($errorPathFile, 'Немає pdf');
				elseif ( count($pdfArr) > 1 )
					writeToLog($errorPathFile, 'Декілька pdf, не знаю який брати');
				elseif ( count($nxmlArr) > 1 )
					writeToLog($errorPathFile, 'Декілька nxml, не знаю який брати');
			}
			
			
			//if ( !$error )
			if ( !file_exists($errorPathFile) )
			{
				++$successCount; 
				
				if ( $keyWords == '' )
					$keyWords = '&nbsp;';
					
				$currTemplate = $template;
				$currTemplate = str_replace('$$$SOURCE$$$', $journalTitle,	$currTemplate);
				$currTemplate = str_replace('$$$NAME$$$', 	$title, 		$currTemplate);
				$currTemplate = str_replace('$$$AUTHOR$$$', $authorStr,		$currTemplate);
				$currTemplate = str_replace('$$$REF$$$', 	$abstract, 		$currTemplate);				
				$currTemplate = str_replace('$$$KEYW$$$', 	$keyWords,		$currTemplate);
				
				$dhtml = $pathMy.'/'.$i.'_abstract_2.html';
				$ddoc = $pathMy.'/'.$i.'_abstract.doc';
				
				if ( file_exists($dhtml) )
					unlink($dhtml);
				
				// пишемо тарасу в базу
				//print($dhtml.'<BR><BR>');
				writeToLog($dhtml, $currTemplate);


				
				//print($currTemplate.'<BR>');
				
				$aTemp = $currTemplate;
				$abstract 		= unpack( "H*hex", $abstract );
				$currTemplate 	= unpack( "H*hex", $currTemplate );
				$article		= unpack( "H*hex", $article );
				
				$issn 			= str_replace("'", "''", 	$issn);
				$journalTitle 	= str_replace("'", "''", 	$journalTitle);
				$journalYear 	= str_replace("'", "''", 	$journalYear);
				$title 			= str_replace("'", "''", 	$title);
				$authorStr 		= str_replace("'", "''", 	$authorStr);
				$keyWords 		= str_replace("'", "''", 	$keyWords);

				$query = 'insert into articleinfoNew(idJournal, journalISSN,   journalTitle,           journalYear,         articleTitle, 	  articleAuthors,      articleKwd,   insertDate) '.
										 'values ('.$i.',    \''.$issn.'\', \''.$journalTitle.'\',  \''.$journalYear.'\', \''.$title.'\', \''.$authorStr.'\', \''.$keyWords.'\', getdate() )';
				
				mssql_query($query, $db);
				
				$query = "select @@identity";
		   		$r = mssql_query($query, $db);
		   		$idarticle = mssql_fetch_array($r);
		   		$idarticle = (int)$idarticle[0];

				// пишемо в базу не корегований html
				$query = 'insert into files(idArticle, 		[file], 			    filetype) '.
								'values ('.$idarticle.',   0x'.$currTemplate['hex'].', \'dirty_html\')';
								
				mssql_query($query, $db);
				
				// пишемо в базу реферат
				$query = 'insert into files(idArticle, 		[file], 			    filetype) '.
								'values ('.$idarticle.',   0x'.$abstract['hex'].', \'abstract\')';
								
				mssql_query($query, $db);

				// пишемо в базу nxml
				$query = 'insert into files(idArticle, 		[file], 			    filetype) '.
								'values ('.$idarticle.',   0x'.$article['hex'].', \'nxml\')';
								
				mssql_query($query, $db);

				$htmltodoc->createDoc($dhtml, $ddoc); 			

				$handle = fopen($ddoc, "r");
				$doc = fread($handle, filesize($ddoc));
				fclose($handle);
				
				$doc = unpack( "H*hex", $doc );

				// пишемо в базу nxml
				$query = 'insert into files(idArticle, 		[file], 			    filetype) '.
								'values ('.$idarticle.',   0x'.$doc['hex'].', \'dirty_doc\')';
								
				mssql_query($query, $db);
				
				//print_r($pdfArr);
				//print('<BR><BR>');
				
			} // end if ( !file_exists($errorPathFile) )
			
		} // end if is_dir( $p )
		//else
		//	break;
			
		++$i;
	} // end while
	
	$log = $errorPath.'/log.txt';	
	writeToLog($log, 'Всього статей: '.$allCount.'; успішно оброблено: '.$successCount);


































	/*

	// insertttttttttttttttttttttttttttttt	
	
	$query = 'select a.idarticle, a.idjournal from ArticleInfoNew a order by a.idjournal';
	
	$rt = mssql_query($query, $db);
	$ids = array();
	while ($row = mssql_fetch_array($rt, MSSQL_ASSOC))
		array_push($ids, $row);
	
	//print_r($ids);
	
	for($i = 243; $i < count($ids); $i++)
	{
		$idarticle = $ids[$i]['idarticle'];
		$idjournal = $ids[$i]['idjournal'];
		
		$p = $path.$idjournal;
		
		$pdfArr = glob($p.'/*.pdf');
		
		print($idjournal.','.'<BR>');
		//print($p.'<BR>');
		
			
		// пишемо в базу всі pdf
		for ($p = 0; $p < count($pdfArr); $p++)
		{
			//print($pdfArr[$p].'-'.$pathMy2.$i.'.pdf'.'<BR>');
			
			$pdfarticle = '';
			
			copy($pdfArr[$p], $pathMy2.$i.'.pdf');
			
			$handle = fopen($pdfArr[$p], "r");
			$pdfarticle = fread($handle, filesize($pdfArr[$p]));
			fclose($handle);

			$pdfarticle = unpack( "H*hex", $pdfarticle );
			
			//$sql = "SET TEXTSIZE 2147483647";
			//mssql_query($query, $db); 
			
			$query = 'insert into files(idArticle, 		[file], 			    filetype) '.
						'values ('.$idarticle.',   0x'.$pdfarticle['hex'].', \'pdf\')';
						
			//mssql_query($query, $db) or exit('error: ');
			mssql_query($query, $db) or die(mssql_get_last_message());
		} // end for
		
	} // end for
	*/


	
	
	mssql_close($db);	
	
?>
