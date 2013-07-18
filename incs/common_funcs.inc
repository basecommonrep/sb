<?
function generate_password($number)    
{      
	$arr = array(	'a','b','c','d','e','f',                   
					'g','h','i','j','k','l',                   
					'm','n','o','p','r','s',                   
					't','u','v','x','y','z',                   
					'A','B','C','D','E','F',                   
					'G','H','I','J','K','L',                   
					'M','N','O','P','R','S',                   
					'T','U','V','X','Y','Z',                   
					'1','2','3','4','5','6',                   
					'7','8','9','0'	);      

	srand( ((int)((double)microtime()*1000003)) ); // обнуляем счетчик
	// Генерируем пароль      
	$pass = "";      
	for($i = 0; $i < $number; $i++)      
	{        
		// Вычисляем случайный индекс массива        
		$index = rand(0, count($arr) - 1);        
		$pass .= $arr[$index];      
	}     
	
	return $pass;    
} 

function dircopy($srcdir, $dstdir, $verbose = false) {
  $num = 0;
  if(!is_dir($dstdir)) mkdir($dstdir);
  if($curdir = opendir($srcdir)) {
    while($file = readdir($curdir)) {
      if($file != '.' && $file != '..') {
        $srcfile = $srcdir . '\\' . $file;
        $dstfile = $dstdir . '\\' . $file;
        if(is_file($srcfile)) {
          if(is_file($dstfile)) $ow = filemtime($srcfile) - filemtime($dstfile); else $ow = 1;
          if($ow > 0) {
            if($verbose) echo "Copying '$srcfile' to '$dstfile'...";
            if(copy($srcfile, $dstfile)) {
              touch($dstfile, filemtime($srcfile)); $num++;
              if($verbose) echo "OK\n";
            }
            else echo "Error: File '$srcfile' could not be copied!\n";
          }                   
        }
        else if(is_dir($srcfile)) {
          $num += dircopy($srcfile, $dstfile, $verbose);
        }
      }
    }
    closedir($curdir);
  }
  return $num;
} // emd dircopy

function ClearTempFiles($dir, $hours)
{
	// =======================================
	// Удаляем все файлы "старее" $hours часов
	// =======================================
	
    if (is_dir($dir)) {

        $i = 0;
		foreach(glob($dir.'/*') as $sf) {
			$i++;
			
			//$dirile_time = filemtime($sf);
			$dirile_time = filectime($sf);
			$a_file_time = getdate($dirile_time);
			$dirile_time_stamp = $a_file_time[0];
	
			$a_curr_time = getdate();
			$curr_time_stamp = $a_curr_time[0];
			
			$offset = $hours * 60 * 60;
            if (@is_dir($sf) && !@is_link($sf)) {
                ClearTempFiles($sf, $hours);
           		if ( ( $dirile_time_stamp + $offset ) < $curr_time_stamp )
					@rmdir($sf);
            } else {
         		if ( ( $dirile_time_stamp + $offset ) < $curr_time_stamp )   
                	@unlink($sf);
            }
        }
    } else 
        die("Error: not a directory - $dir");

} // end ClearTempFile

function microtime_float()
{
   list($usec, $sec) = explode(" ", microtime());
   return ((float)$usec + (float)$sec);
}

class poliz
{
	var $data=array();
	var $compare=0;
	var $outExpr = array();
	var $operations;
	
	function pop() {
		return array_shift($this->data);
	}
	
	function push($x) {
		array_unshift($this->data, $x);
	}
	
	function count_items() {
		return count($this->data);
	}
	
	function first() {
		return $this->data[0];
	}
	
	function top() {
		return end($this->data);
	} // last element of 
	
	function swap() { 
		$t = $this->data[1];
		$this->data[1] = $this->data[0];
		$this->data[0] = $t;
	} // interchange tow elements 
		
	function dup() {  
	 	array_unshift($this->data, $this->data[0]);
	} // put a copy of X element in the stack
		
	function dump(){ 
		print_r($this->data);
	} // dump array data for debuging
	
	function clear(){ 
		$this->data = array();
	} // dump array data for debuging
	
		
	function getPoliz($expr)
	{
		$this->operations = array('AND', 'OR', 'NOT');		
		
		for($i = 0; $i < count( $expr ); $i++)
		{
			$item = $expr[$i];

			if ( $item == '(' )
				$this->push( $item );
			elseif ( $item == ')' )
			{
				while( ( $top_item = $this->pop() ) != '(' )
				{
					if ( !empty( $top_item ) )
						array_push( $this->outExpr, $top_item);	
					else
						break;
				} // while
			}
			elseif ( in_array( $item, $this->operations ) )
			{
				if ( $this->count_items() === 0 )
					$this->push( $item );
				else
				{
					if ( $this->prior( $this->first() ) < $this->prior( $item ) )
						$this->push( $item );
					else
					{
						$top_item = $this->first();
						while( !empty( $top_item ) && ( $this->prior( $top_item ) >= $this->prior( $item ) ) )
						{
							array_push( $this->outExpr, $this->pop());
							
							$top_item = $this->first();	
						} // while

						$this->push( $item );
					}
				}
			}
			else
				array_push( $this->outExpr, $item);
			
		} // end for
		
		$top_item = $this->first();
		while( !empty( $top_item ) )
		{
			array_push( $this->outExpr, $this->pop());
			
			$top_item = $this->first();	
		} // while
		
		return $this->outExpr;
	}

	function Prior($oper)
	{
		switch ($oper)
		{
			case "NOT":
			return 4;

			case "AND":
			return 3;

			case "OR":
			return 2;

			case ")":
			return 1;

			case "(":
			return 0;
		}
	} // prior

} // class poliz

function turn_red($haystack, $needle, $fontclass, &$istext)
{
	$h 		=	strtoupper($haystack);
	$n 		=	strtoupper($needle);
	$pos 	=	@strpos($h,$n);
	$istext = 	false;
	
	if ($pos !== false)
	{
		$istext = true;
		$classstr = '';
		if ( !empty( $fontclass ) )
			$classstr = 'class="'.$fontclass.'"';
			
		$var  =	substr($haystack,0,$pos)."<font $classstr style=\"background-color: yellow\">".substr($haystack,$pos,strlen($needle))."</font>";
		$var .= substr($haystack,($pos+strlen($needle)));
		$haystack = $var;
		
		//print($haystack.'-'.$needle.'<BR><BR>');
		$haystack = str_replace($needle, "<font $classstr style=\"background-color: yellow\">".$needle."</font>", $haystack);
	}

	return $haystack;
} // end turn_red

function textBlink($dbn, $text, $fname, $isDict)
{
	$s = 'Єгер Дмитро Олександрович (UA); Беккер Михайло Вікторович (UA); Гордієнко Ігор Анатолійович (UA); Колодяжний Валерій Васильович (UA); Пономарьов Юрій Володимирович (UA); Коток Валерій Борисович (UA); Волчков Іван Іванович (UA); Бондарев Сергій Артемович (UA); Лобов Павло Олексійович (UA); Золотарьов Олексій Михайлович (UA); Грінченко Констянтин Миколайович (UA); Бантюков Євген Миколайович (UA)';
		
	$s = str_replace('Беккер', "===", $s);
	//print($s.'<BR><BR><BR>');
	
	//print($dbn);
	
	reset($_SESSION['searchDbsValues'][$dbn]);
	$allFieldValues = $_SESSION['searchDbsValues'][$dbn];
	$oneFieldValues = $allFieldValues[$fname];
	
	if ( $isDict == true )
		$oneFieldValues = $_SESSION['searchDictValue'];
	
	$logicals = $GLOBALS['form_logical_operation_replacement'];
	$logicalsNames = array_keys( $logicals );
	
	if ( !empty($oneFieldValues) && !strstr($oneFieldValues, '<font'))
	{
		preg_match_all( "/[\s\/\'\-0-9а-яА-Яa-zA-ZіІїЇґҐєЄ]+/", $oneFieldValues, $match );
	
		for($k = 0; $k < count( $match[0] ); $k++)
		{
			$oneFieldValues = $match[0][$k];
			$selectedWords = explode(' ', $oneFieldValues);
			
			for($j = 0; $j < count( $selectedWords ); $j++)
			{
				$selectedWords[$j] = ltrim(rtrim($selectedWords[$j]));
				if ( strlen($selectedWords[$j]) > 1 && !in_array($selectedWords[$j], $logicalsNames))
					$text = turn_red($text, $selectedWords[$j], $fontclass, $istext); 
			}
		}
	} // end if 

	return $text;
} // end textBlink

function devidedLongNames($val, $part_number)
{
	$val_parted = '';	
	$parts = explode(' ', $val);
	
	for ($j = 0; $j < count($parts); $j++)
	{
		if ( strlen($parts[$j]) > $part_number )
		{
			for ($k = 0; $k <= (int)(strlen($parts[$j])/$part_number); $k++)
				$val_parted = $val_parted.' '.substr($parts[$j], $k*$part_number, ($k+1)*$part_number).' ';
		}
		else
			$val_parted = $val_parted.' '.$parts[$j];
	}
	
	return $val_parted;

} // devidedLongNames

function getDataByTagName($n, $tagName)
{
	$data = '';
	for($i = 0; $i < count($n); $i++)
	{
		$attrs = $n[$i]['attrs'];
		if ( $n[$i]['name'] == $tagName && $attrs['ISSPOV'] == 'Y' )
		{
			$data = $n[$i]['tagData'];
			break;
		}
	}
	if ( empty($data) )
		$data = '&nbsp;';
		
	return $data;
} // end function getDataByTagName

?>
