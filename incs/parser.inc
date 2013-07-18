<?
class ExpressionParser { 
  var $pos,    	  // Позиция в буфере для разбора 
      $length,    // Длина буфера 
      $line,      // Текущий номер строки 
      $column,    // Текущий номер колонки в строке 
      $data,      // Буфер данных 
      $brackets,  // Количество открытых скобок 
      $state,     // Текущее состояние парсера 
      $errorstr,  // Строка диагностики ошибки 
      $instates,  // Код слова подаваемый на вход автомата 
      $prevstate, // Предыдущее состояние парсера 
      $automat,   // Таблица автомата парсера 
      $expr_type; // Тип выражения

  function GetPos() { 
	return ($this->pos);
  }

  function GetLen() { 
  	return $this -> length;
  }

 /********************************************************************** 
  *  Конструктор  * 
  **********************************************************************/ 
  function ExpressionParser($str, $type, $expr) { 
    $this->data			=	$str; 
    $this->length		=	strlen($str); 
    $this->pos			=	0; 
    $this->line			=	1; 
    $this->column		=	0; 
    $this->brackets		=	0; 
    $this->expr_type	=	$type; 
    $this->expr 		= 	$expr;
     
    $LANG_SETTINGS = $GLOBALS['LANG_SETTINGS'];

	// Коды слов, выданных сканером, подаваемых на вход парсера 
    // Остальные слова имеют код 1 
    switch( $type )
    {
    	case 1: // число
    	case 6: // 

    		$this->instates = array($LANG_SETTINGS['logical']['and'] => 0, $LANG_SETTINGS['logical']['or'] => 1, $LANG_SETTINGS['logical']['not'] => 2, "(" => 4, ")" => 5, ">" => 6, "<" => 7, "=" => 8); 

		    $this->automat=array( 
		     "0"	=>	array( -1, -1, -1, 1, -1, -1, -1, -1, -1, 1),	// ТА
		     "1"	=>	array( -1, -1, -1, 8, -1, -1, -1, -1, -1, 8),	// АБО
//		     "2"	=>	array( -1, 2, -1, 2, -1, -1, -1, -1, -1, -1),	// НЕ
		     "2"	=>	array( 2, 2, -1, 2, 2, -1, -1, -1, 2, 2),	// НЕ

		     "3"	=>	array( 3, 3, 3, 3, 3, 3, 3, 3, 3, 3),			// операнд
		     "4"	=>	array( 4, 4, 4, 4, 4, -1, -1, -1, 4, 4),		// (
		     "5"	=>	array( -1, -1, -1, 9, -1, -1, -1, -1, -1, 9),	// )
		     "6"	=>	array( 5, 5, 5, 5, 5, -1, 5, -1, 5, 5),			// >
		     "7"	=>	array( 6, 6, 6, 6, 6, -1, -1, -1, 6, 6),		// <
		     "8"	=>	array( 7, 7, 7, 7, 7, 7, 7, -1, 7, 7),			// =
		    ); 

    	break;

    	case 2: // строка
		    $this->automat=array( 
		     "0"	=>	array( -1, -1, -1, -1, 1, -1, 1),	// ТА
   		     "1"	=>	array( -1, -1, -1, -1, 2, -1, 2),	// АБО
   		     "2"	=>	array( 3, 3, 3, -1, 3, 3, 3),		// НЕ
   		     "3"	=>	array( 4, 4, 4, 4, 4, 4, 4),		// слово
   		     "4"	=>	array( 5, 5, 5, 5, 5, 5, 5),		// (
   		     "5"	=>	array( -1, -1, -1, -1, 6, -1, 6),	// )
		    ); 

    		$this->instates = array($LANG_SETTINGS['logical']['and'] => 0, $LANG_SETTINGS['logical']['or'] => 1, $LANG_SETTINGS['logical']['not'] => 2, "(" => 4, ")" => 5); 
    	break;

    	case 3: // дата
    		$this->instates = array($LANG_SETTINGS['logical']['and'] => 0, $LANG_SETTINGS['logical']['or'] => 1, $LANG_SETTINGS['logical']['not'] => 2, "(" => 4, ")" => 5, ">" => 6, "<" => 7, "=" => 8); 

		    $this->automat=array( 
		     "0"	=>	array( -1, -1, -1, 1, -1, -1, -1, -1, -1, 1),	// ТА
		     "1"	=>	array( -1, -1, -1, 8, -1, -1, -1, -1, -1, 8),	// АБО
//		     "2"	=>	array( -1, 2, -1, 2, -1, -1, -1, -1, -1, -1),	// НЕ
		     "2"	=>	array( 2, 2, -1, 2, 2, -1, -1, -1, 2, 2),	// НЕ

		     "3"	=>	array( 3, 3, 3, 3, 3, 3, 3, 3, 3, 3),			// операнд
		     "4"	=>	array( 4, 4, 4, 4, 4, -1, -1, -1, 4, 4),		// (
		     "5"	=>	array( -1, -1, -1, 9, -1, -1, -1, -1, -1, 9),	// )
		     "6"	=>	array( 5, 5, 5, 5, 5, -1, 5, -1, 5, 5),			// >
		     "7"	=>	array( 6, 6, 6, 6, 6, -1, -1, -1, 6, 6),		// <
		     "8"	=>	array( 7, 7, 7, 7, 7, 7, 7, -1, 7, 7),			// =
		    ); 

    	break;

    }

    $this->state=$this->prevstate=0; 
  } 

 /********************************************************************** 
  *  Сканер  * 
  **********************************************************************/ 
  function Scan() 
  { 
	// Разделители, которые игнорируем 
    $delimiters=array(" ","\t","\r","\n"); 

    $state=0; 
    $word="";
    $prevstate=0;
    
	// автомат сканнера 

    switch($this->expr_type)
    {
    	case 1: // число
    	case 3: // дата
    	case 6: // Номер/Строка
    	
    		// Слова из одного символа 
    		$words = array("(", ")", ">", "<", "=");

		    $automat=array( 
					    /* 
					    -1 Слово готово возвращаем
					     0 Начало сканирования 
					     1 Получили символ, копим пока не разделитель
					     2 Получили слово из 1-ого символа
					    */ 
					    
					    //состояния  0,  1,  2
					     "0"=>array( 0, -1, -1 ), 	// Разделитель
					     "1"=>array( 2, -1, -1 ), 	// слово - один символ
					     "2"=>array( 1, 1, -1 ), 	// символ
					    ); 

			// Цикл сканирования 
			while ($this->pos<$this->length) 
			{ 
				
				// Устанавливаем код подаваемого на вход автомата символа. 
				if (in_array($this->data[$this->pos],$delimiters))  
					$instate=0; 
				elseif (in_array($this->data[$this->pos],$words))  
					$instate=1; 
				else 
					$instate=2; 
					
				$prevstate = $state;
				
				// Получаем состояние автомата 
				$state=$automat[$instate][$state];
				
				//print($this->data[$this->pos]." $state (instate=$instate) (prev=$prevstate)<br>");
		
				// Наши действия по состояниям автомата 
				switch($state) 
				{ 
					case 0: // начало сканирования 
						if ($this->data[$this->pos]=="\n") 
						{ 
							$this->line++; 
							$this->column=0; 
						} 
		    		
					$word=""; 
					break; 
					
					case -1: // слово готово, пора возвращать 
						if (strlen($word))
						{ 
							//print($word.'<BR>');
							return $word; 
						}
					break; 
		     
					case 1: // получили символ, надо копить пока это символ 
						$word.=$this->data[$this->pos];
					break; 
		
					case 2: // получили предопределенное слово из одного символа 
						$word=$this->data[$this->pos];
					break; 
				} // end switch 
		      
				$this->pos++; 
				$this->column++; 
				if ($this->pos==$this->length && strlen($word)) 
				{	
					return $word; 
				}
			} // end while 

    	break;
    	case 2: // строка

    		// Слова из одного символа 
    		$words=array("(", ")"); 

		    $automat=array( 
					    /* 
					    -1 Слово готово 
					     0 Начало сканирования 
					     1 Получили символ ( не разделитель и не ") 
					     2 получили символ ", копим пока не встретим закр. " или конец строки 
					     3 Получили разделитель, копим пока разделитель 
					     4 Получили (,), возвращаем 
					    */ 
					    //состояния  0, 1, 2, 3, 4
					     "0"=>array( 3, -1, 2, 3, -1),   // Разделитель
					     "1"=>array( 2, 2, -1, -1, -1), // "
					     "2"=>array( 1, 1, 2, -1, -1),   // не " и разделитель
					     "3"=>array( 4, -1, 2, -1, -1),  // (, )
					    ); 

			// Цикл сканирования 
			while ($this->pos<$this->length) 
			{ 
				// Устанавливаем код подаваемого на вход автомата символа. 
				if (in_array($this->data[$this->pos],$delimiters))  
					$instate=0; 
				elseif ($this->data[$this->pos] == "\"")  
					$instate=1; 
				elseif (in_array($this->data[$this->pos],$words))  
					$instate=3; 
				else 
					$instate=2; 
					
				$prevstate = $state;
				
				// Получаем состояние автомата 
				$state=$automat[$instate][$state];
				
				if ( ( $instate == 1 ) && ( $state == -1 ) && ( $prevstate == 2 ) ) // описываем ситуацию "lalsl\"sdlaland"
				{
					if ( ( ($this->pos - 1) >= 0 ) && ( $this->data[$this->pos - 1] == "\\" ) )
						$state = 2;
				}
				else
				if ( ( $instate == 1 ) && ( $state == -1 ) ) // описываем появление \"
				{
					if ( ( ($this->pos - 1) >= 0 ) && ( $this->data[$this->pos - 1] == "\\" ) )
						$state = 1;
				}
		
				//print("$state<br>");
		
				// Наши действия по состояниям автомата 
				switch($state) 
				{ 
					case 0: // начало сканирования 
						if ($this->data[$this->pos]=="\n") 
						{ 
							$this->line++; 
							$this->column=0; 
						} 
		    		
					$word=""; 
					break; 
					
					case -1: // слово готово, пора возвращать 
						if (strlen($word)) 
						{
							//if ( $instate == 1 )
							if ( $prevstate == 2 )
							{
								$word .= "\"";
								if ( $prevstate != 3 )
									$this->pos++;
		
								//print("---".$this->pos);
							}
							//print($word."<br>");
							return $word; 
						}
					break; 
		     
					case 1: // получили символ, надо копить пока это символ 
					case 2: 
					case 3:
						$word.=$this->data[$this->pos];
						//print($this->data[$this->pos]."<br>"); 
					break; 
		
					case 4: // получили предопределенное слово из одного символа 
						$word=$this->data[$this->pos];
						//print($word."<br>");
					break; 
				} // end switch 
		      
				$this->pos++; 
				$this->column++; 
				if ($this->pos==$this->length && strlen($word)) 
				{	
					return $word; 
				}
			} // end while 
    	break;
    }

	return false; 
  } // end SCAN 
  
  function GetNext()
  {
  	  ++$this->pos;
	  return $this->expr[$this->pos-1];
  }

  function Parse($expr) 
  {
	switch($this->expr_type)
    {
    	case 1: // число
    	case 6: // номер/строка
			$res = $this->ParseInt($expr);
    	break;
    	case 2: // строка
    		$res = $this->ParseStr($expr);
    	break;
    	case 3: // дата
    		$res = $this->ParseDate($expr);
    	break;

    }
    
    return $res;
  }

 /********************************************************************** 
  *  Парсер  * 
  **********************************************************************/ 
  function ParseInt($expr) 
  { 
	// Переменная $first равна нулю, если функция разбора была вызвана первый раз 
	$first = $this->pos;

	// Цикл состояний 
	while(1)
	{ 
		// Получаем слово от сканнера 
		$word = $this->GetNext();
		if ( $this->pos > count($this->expr))
			break;
		
		if (!preg_match("/^[\s]+$/",$word) && !empty($word))
		{
			// Устанавливаем код, подаваемого на вход автомата, слова 
			$instate=isset($this->instates[$word]) ? $this->instates[$word] : 3; 
	       
			// Получаем состояние автомата парсера 
			$this->state=$this->automat[$instate][$this->state];
			//print('word='.$word.';instate='.$instate.';state='.$this->state.'<br>');
			//print($instate.'<br>');
	       
			// Если ошибочное состояние, то прерываем цикл 
			if ($this->state==-1) 
			{ 
				$this->errorstr=1;
				return false; 
			} 
	       
			// Наши действия по состояниям автомата парсера 
			switch($this->state) 
			{ 
	
				case 3: // Получили операнд (надо проверить число ли это),
	
					// Проверяем число ли это? 
					if (!preg_match("/^[0-9]+$/",$word)) 
					{ 
						$this->errorstr=2; 
						return false; 
					} 
				break; 
	
				case 4: // Получили левую скобку, ожидаем оператор или левую скобку 
	
					// Увеличиваем кол-во открытых скобок на 1; 
					$this->brackets++; 
	     
					// Удобно использовать рекурсию, т.к. данные в скобках 
					// можно рассматривать как самоcтоятельные выражения. 
					// Мы вернемся из функции в случае ошибки, конца данных или 
					// после получения закрытой скобки 
					if (!$this->ParseInt($expr)) 
						return false; 
				break; 
		
				case 9: // Получили правую скобку, ожидаем оператор 
	      
					// Уменьшаем кол-во открытых скобок на 1 
					$this->brackets--;
					if ( $this->brackets < 0) { $this->errorstr=3; return false; }
					else return true;
				break;
			} // end switch 
	       
			// Запоминаем текущее состояние для следующего шага цикла 
			$this->prevstate=$this->state; 
		} // end if <> пробел
	} // end while(1)

    // Так как у нас отсутствует состояние конца разбора, то надо 
    // Проверить в каком состоянии мы завершили разбор 
    // Это надо делать только один раз в самом первом вызове 
    // функции разбора. Это первый вызов, если $first==0 
    // Итак, мы должны вернуть ошибку, если у нас есть лишние скобки, 
    // или если мы не получили правого операнда или правой скобки, 
    // т.е. разбор завершился "на середине". 
     
	if (!$first && ($this->brackets>0) && ( (int)$this->errorstr === 0 ) ) 
	{
		$this->errorstr=3; return false; 
	}
	elseif (!$first && ($this->state!=3 && $this->state!=9) && ( (int)$this->errorstr === 0 ) ) 
	{
		$this->errorstr=4; return false; 
	}

	if ($this->state==-1) return false;
     
    return true; 
  } // end PARSEINT

  function ParseStr($expr) 
  { 
	// Переменная $first равна нулю, если функция разбора была вызвана первый раз 
	$first = $this->pos;

	// Цикл состояний 
	while(1)
	{ 
		// Получаем слово от сканнера 
		$word = $this->GetNext();
		$wlen = strlen($word);
		if ( $this->pos > count($this->expr))
			break;
		
		if (!preg_match("/^[\s]+$/",$word) && !empty($word))
		{
			// Устанавливаем код, подаваемого на вход автомата, слова 
			$instate=isset($this->instates[$word]) ? $this->instates[$word] : 3; 
	       
			// Получаем состояние автомата парсера 
			$this->state=$this->automat[$instate][$this->state];
			//print('word='.$word.';instate='.$instate.';state='.$this->state.'<br>');
			//print($instate.'<br>');
	       
			// Если ошибочное состояние, то прерываем цикл 
			if ($this->state==-1) 
			{ 
				$this->errorstr=1;
				break; 
			} 
			
			// Наши действия по состояниям автомата парсера 
			switch($this->state) 
			{ 
				case 4: // Получили операнд строку
	
					if ( strstr( $word, '"' ) )
					{	
						if ( ( $word[0] == '"' && $word[$wlen-1] != '"') || ( $word[0] != '"' && $word[$wlen-1] == '"' && $wlen > 2) ||
						   ( $word[0] == '"' && $word[$wlen-1] == '"' && $word[$wlen-2] == '\\' ) || ( $word == '"' ) || ( $word == '""')
						) 
						{ 
							$this->errorstr=5;
							return false; 
						} 
					}
					
					


/*
					if ( strstr( $word, '"' ) )
					{	
						$quote_count = 0;
						for($k = 0; $k < strlen( $word ); $k++)
							if ( $word[$k] == '"' )
								++$quote_count;
						
						//if ( !preg_match( "/^[\s\/\'\-\"0-9а-яА-Яa-zA-ZіІїЇґҐєЄ]+$/", $word ) ) 
						if ( !preg_match( "/^[\,\.\=\<\>\\\(\)\{\}\[\]\s\/\'\-\"0-9а-яА-Яa-zA-ZіІїЇґҐєЄ]+$/", $word ) ) 
						{
							$this->errorstr=2; // недопустимий символ
							return false; 
						}
						elseif ( ( $quote_count % 2 ) != 0 )
						{
							$this->errorstr=5; // лапки не закриті
							return false; 
						}
						elseif ( ( $quote_count == 2 ) && ( ( $word[0] == '"' && $word[$wlen-1] != '"' ) || ( $word[0] != '"' && $word[$wlen-1] == '"' ) ) )
						{
							$this->errorstr=1; // недопустима послідовність
							return false; 
						}
					} // если есть "
*/
					else
					{
						if ( !preg_match( "/^[\-\.\,\/\'\\\"\*\?0-9а-яА-Яa-zA-ZіІїЇґҐєЄ]+$/", $word ) ) 
						{
							$this->errorstr=2; // недопустимий символ
							return false; 
						}
						elseif ($word == '?' || preg_match( "/^[\?]+$/", $word ) )
						{
							$this->errorstr=1; // недопустима послідовність
							return false; 
						}
					} 
					
				break; 
	
				case 5: // Получили левую скобку, ожидаем оператор или левую скобку 
	
					// Увеличиваем кол-во открытых скобок на 1; 
					$this->brackets++; 
	     
					// Удобно использовать рекурсию, т.к. данные в скобках 
					// можно рассматривать как самоcтоятельные выражения. 
					// Мы вернемся из функции в случае ошибки, конца данных или 
					// после получения закрытой скобки 
					if (!$this->ParseStr($expr)) 
						return false; 
				break; 
	
				case 6: // Получили правую скобку, ожидаем оператор 
	      
					// Уменьшаем кол-во открытых скобок на 1 
					$this->brackets--;
					if ( $this->brackets < 0) { $this->errorstr=3; return false; }
					else return true;
				break;
			} // end switch 
	       
			// Запоминаем текущее состояние для следующего шага цикла 
			$this->prevstate=$this->state; 
		} // end if <> пробел
	} // end while(1)

    // Так как у нас отсутствует состояние конца разбора, то надо 
    // Проверить в каком состоянии мы завершили разбор 
    // Это надо делать только один раз в самом первом вызове 
    // функции разбора. Это первый вызов, если $first==0 
    // Итак, мы должны вернуть ошибку, если у нас есть лишние скобки, 
    // или если мы не получили правого операнда или правой скобки, 
    // т.е. разбор завершился "на середине". 
    
	if (!$first && ($this->brackets>0) && ( (int)$this->errorstr === 0 ) ) 
	{
		$this->errorstr=3; return false; 
	}
	elseif (!$first && ($this->state!=4 && $this->state!=6) && ( (int)$this->errorstr === 0 ) ) 
	{
		$this->errorstr=4; return false; 
	}

	if ($this->state==-1) return false;
     
    return true; 
  } // end PARSESTR

  function ParseDate($expr) 
  { 
	// Переменная $first равна нулю, если функция разбора была вызвана первый раз 
	$first = $this->pos;

	// Цикл состояний 
	while(1)
	{ 
		// Получаем слово от сканнера 
		$word = $this->GetNext();
		if ( $this->pos > count($this->expr))
			break;
		
		if (!preg_match("/^[\s]+$/",$word) && !empty($word))
		{
			// Устанавливаем код, подаваемого на вход автомата, слова 
			$instate=isset($this->instates[$word]) ? $this->instates[$word] : 3; 
	       
			// Получаем состояние автомата парсера 
			$this->state=$this->automat[$instate][$this->state];
			//print('word='.$word.';instate='.$instate.';state='.$this->state.'<br>');
			//print($instate.'<br>');
	       
			// Если ошибочное состояние, то прерываем цикл 
			if ($this->state==-1) 
			{ 
				$this->errorstr=1;
				break; 
			} 
	       
			// Наши действия по состояниям автомата парсера 
			switch($this->state) 
			{ 
	
				case 3: // Получили операнд (надо проверить число ли это),
	
					// Проверяем число ли это? 
					if (!preg_match("/^([0-9]{2})[.]([0-9]{2})[.]([0-9]{4})$/",$word,$r)) 
					{ 
						$this->errorstr=6; 
						return false; 
					}

					if ( !(((int)$r[1] >= 1) && ((int)$r[1] <= 31)) )
					{ 
						$this->errorstr=7; 
						return false; 
					}
					if ( !(((int)$r[2] >= 1) && ((int)$r[2] <= 12)) )
					{ 
						$this->errorstr=8; 
						return false; 
					}
					if ( !(((int)$r[3] >= 1900) && ((int)$r[3] <= 2100)) )
					{ 
						$this->errorstr=9; 
						return false; 
					}
				
				break; 
	
				case 4: // Получили левую скобку, ожидаем оператор или левую скобку 
	
					// Увеличиваем кол-во открытых скобок на 1; 
					$this->brackets++; 
	     
					// Удобно использовать рекурсию, т.к. данные в скобках 
					// можно рассматривать как самоcтоятельные выражения. 
					// Мы вернемся из функции в случае ошибки, конца данных или 
					// после получения закрытой скобки 
					if (!$this->ParseDate($expr)) 
						return false; 
				break; 
	
	
				case 9: // Получили правую скобку, ожидаем оператор 
	      
					// Уменьшаем кол-во открытых скобок на 1 
					$this->brackets--;
					if ( $this->brackets < 0) { $this->errorstr=3; return false; }
					else return true;
				break;
			} // end switch 
	       
			// Запоминаем текущее состояние для следующего шага цикла 
			$this->prevstate=$this->state; 
		} // end if <> пробел
	} // end while(1)

    // Так как у нас отсутствует состояние конца разбора, то надо 
    // Проверить в каком состоянии мы завершили разбор 
    // Это надо делать только один раз в самом первом вызове 
    // функции разбора. Это первый вызов, если $first==0 
    // Итак, мы должны вернуть ошибку, если у нас есть лишние скобки, 
    // или если мы не получили правого операнда или правой скобки, 
    // т.е. разбор завершился "на середине". 
     
//	print ($this->errorstr);


	if (!$first && ($this->brackets>0) && ( (int)$this->errorstr === 0 ) ) 
	{
		$this->errorstr=3; return false; 
	}
	elseif (!$first && ($this->state!=3 && $this->state!=9) && ( (int)$this->errorstr === 0 ) ) 
	{
		$this->errorstr=4; return false; 
	}

	if ($this->state==-1) return false;
     
    return true; 
  } // end PARSEDATE


} // END CLASS

?>
