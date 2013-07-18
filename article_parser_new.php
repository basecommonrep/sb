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
1. Запусити даний скрипт.
-- в папке $path дожны быть папки, содержащие материалы к статье
-- например, g:/!!!_refs/навзание статьи-1/, ... ,g:/!!!_refs/навзание статьи-N/
2. Видалити дуюлікати, використовуючи скрипт:
delete from articleinfonew
where idarticle in (
	select distinct a.idarticle
	from articleinfonew a
	inner join articleinfonew a2 on a.articletitle = a2.articletitle 
	where a.insertdate > convert(datetime, '01.07.2012', 104) and a2.insertdate < convert(datetime, '01.07.2012', 104)
),
де 01.07.2012 - дата завантаження даних.
*/


	include('.././searchBul/incs/xml.php.inc');
	include('.././searchBul/incs/common_funcs.inc');
	include('.././searchBul/incs/htmltodoc.inc');
	include('.././searchBul/incs/word/clsWord.inc');
	
	//error_reporting(E_ALL);

	$objXML = new xml2Array();
	$htmltodoc = new HTML_TO_DOC(); 
	$path = "g:/!!!_refs/";	
	$pathMy_htmls = "g:/readbook/htmls/";
	$pathMy_docs = "g:/readbook/docs/";
	$pathMy_pdfs = "g:/readbook/pdfs/";
	$errorPath = "g:/readbook/log";
	$templatePath = "g:/readbook/pattern.html";
	$min_file_size = 3000;
	$max_file_size = 7500;

	
	// видаляемо лог
	Del_User_Files($errorPath);
	Del_User_Files($pathMy_htmls);
	Del_User_Files($pathMy_docs);
	Del_User_Files($pathMy_pdfs);	

	// читаем шаблон
	$handle = fopen($templatePath, "r");
	$template = fread($handle, filesize($templatePath));
	fclose($handle);
		
	$template_len = strlen($template);
	
	// подключаемся к БД
/*
	$host = 'u608-pustovit';
	$login = 'leha';
	$pass = 'leha';
	$database = 'articls';
*/

/*
	$host = 'u608-drobyazko';
	$login = 'sa';
	$pass = '1980al';
	$database = 'test';
	$database = 'cead';
*/

	$host = 'ella\ella_2005';
	$login = 'lesha';
	$pass = 'lesha';
	$database = 'articles';

	$db = mssql_connect($host, $login, $pass);					
	mssql_select_db($database, $db);


	// ================================================================================
	// Вивантаження реквізитів статей: назва статті, назва журналу, рік, ключові слова.
	// Створення реферату до статті в форматі DOC, HTML.
	// Завантаження до БД nxml статті.
	// ================================================================================
	
	$successCount = 0;
	$allCount = 0;
	
	$dir_names = scandir($path);
	
	for ($i = 2; $i < count($dir_names); $i++) // 2 - because of first two dirs are . and ..
	{
		$dn = $dir_names[$i];
		//if ( $i == 2053)
		//	++$i;
			
		$allCount++;
		//print('***************** '.$i.'*****************<BR>');
		print($i.', ');
		$errorPathFile = $errorPath.'/'.$dn.'.txt';		
		$error = false;
		
		$p = $path.$dn;
		if ( is_dir( $p ) )	
		{
			$nxmlArr = glob($p.'/*.nxml');
			$pdfArr = glob($p.'/*.pdf');
			$nxml = $nxmlArr[0];
			$pdf = $pdfArr[0];

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
				
				$currTemplate_len = strlen($currTemplate);
				$curr_text_len =  $currTemplate_len - $template_len;
				
				$dhtml = $pathMy_htmls.'/'.$dn.'_'.$curr_text_len.'.html';
				$ddoc = $pathMy_docs.'/'.$dn.'.doc';
				
				if ( file_exists($dhtml) )
					unlink($dhtml);
					
				if (!($currTemplate_len > $min_file_size and $currTemplate_len < $max_file_size))
				{
					writeToLog($errorPathFile, '----------- Файл реферату занадто великий або малий');
					--$successCount;
					continue;
				}
				
				writeToLog($dhtml, $currTemplate);
			

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

				// пишемо в базу некорегований html
				$query = 'insert into files(idArticle, 		[filebody], 			    filetype,		ext) '.
								'values ('.$idarticle.',   0x'.$currTemplate['hex'].', \'dirty_html\',	\'html\')';
				mssql_query($query, $db);
				
				// пишемо в базу реферат
				$query = 'insert into files(idArticle, 		[filebody], 			    filetype,		ext) '.
								'values ('.$idarticle.',   0x'.$abstract['hex'].', 		\'abstract\',	\'txt\')';
				mssql_query($query, $db);

				// пишемо в базу nxml
				$query = 'insert into files(idArticle, 		[filebody], 			    filetype,	ext) '.
								'values ('.$idarticle.',   0x'.$article['hex'].', 		\'nxml\',	\'xml\')';
				mssql_query($query, $db);

				$htmltodoc->createDoc($dhtml, $ddoc); 			

				$handle = fopen($ddoc, "r");
				$doc = fread($handle, filesize($ddoc));
				fclose($handle);
				
				$doc = unpack( "H*hex", $doc );

				// пишемо в базу не корегований doc
				$query = 'insert into files(idArticle, 		[filebody], 		filetype,		ext) '.
								'values ('.$idarticle.',   0x'.$doc['hex'].', 	\'dirty_doc\',	\'doc\')';
								
				mssql_query($query, $db);
				
				//print($pdf);
				
				/*
				if (!empty($pdf))
				{
					// пишемо в базу оригінальний pdf
					$handle = fopen($pdf, "r");
					$pdf_content = fread($handle, filesize($pdf));
					fclose($handle);
					
					$pdf_content = unpack( "H*hex", $pdf_content );

					// пишемо в базу не корегований pdf
					$query = 'insert into files(idArticle, 		[filebody], 		filetype,		ext) '.
									'values ('.$idarticle.',   0x'.$pdf_content['hex'].', 	\'pdf\',	\'pdf\')';
									
					mssql_query($query, $db);

				}
				*/

				//print_r($pdfArr);
				//print('<BR><BR>');
				
			} // end if ( !file_exists($errorPathFile) )
			
		} // end if is_dir( $p )
		//else
		//	break;

	} // end while
	
	$log = $errorPath.'/!!!_log.txt';	
	writeToLog($log, 'Всього статей: '.$allCount.'; успішно оброблено: '.$successCount);
	

	// ================================================================================
	// вивантаження PDF
	// ================================================================================

	$dir_names = scandir($path);
	for ($i = 2; $i < count($dir_names); $i++) {
		$dn = $dir_names[$i];
		$p = $path.$dn;
		
		if ($i <= 7596)
			continue;
			
		if ( is_dir( $p ) )	{
			$nxmlArr = glob($p.'/*.nxml');
			$nxml = $nxmlArr[0];
			$pdfArr = glob($p.'/*.pdf');
			$pdf = $pdfArr[0];
			
			if ( file_exists($nxml) && count($nxmlArr) === 1 ) {
				$handle = fopen($nxml, "r");
				$article = fread($handle, filesize($nxml));
				fclose($handle);

				if ( strstr($article, '<article-title>') ) {
					$title = substr($article, strpos($article, '<article-title>')+strlen('<article-title>'), strpos($article, '</article-title>')-strpos($article, '<article-title>')-strlen('<article-title>'));;
					$title = str_replace("'", "''", $title);
					$query = "select idarticle from articleinfonew where insertdate > convert(datetime, '01.07.2012', 104) and articletitle = '$title'";
					$res = mssql_query($query, $db);
					$row = mssql_fetch_array($res);
					$id = (int)$row[0];
					
					if ($id > 0 && !empty($pdf)) {
						print($i.'<BR>');
						print($title.'<BR>');
						print($id.'<BR>');
						print($pdf.'<BR>');
						print('==========================================================================<br>');

						// пишемо в базу оригінальний pdf
						$handle = fopen($pdf, "r");
						$pdf_content = fread($handle, filesize($pdf));
						fclose($handle);
						
						$pdf_content = unpack( "H*hex", $pdf_content );

						// пишемо в базу не корегований pdf
						$query = 'insert into files(idArticle, 		[filebody], 		filetype,		ext) '.
										'values ('.$id.',   0x'.$pdf_content['hex'].', 	\'pdf\',	\'pdf\')';
										
						//$r = mssql_query($query, $db) or die("Помилка");
						mssql_query($query, $db) or print("Помилка<br>");
					}
				}
			}
		}
	} // end for
	

	mssql_close($db);	
	
?>
