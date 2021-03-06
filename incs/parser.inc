<?
class ExpressionParser { 
  var $pos,    	  // ������� � ������ ��� ������� 
      $length,    // ����� ������ 
      $line,      // ������� ����� ������ 
      $column,    // ������� ����� ������� � ������ 
      $data,      // ����� ������ 
      $brackets,  // ���������� �������� ������ 
      $state,     // ������� ��������� ������� 
      $errorstr,  // ������ ����������� ������ 
      $instates,  // ��� ����� ���������� �� ���� �������� 
      $prevstate, // ���������� ��������� ������� 
      $automat,   // ������� �������� ������� 
      $expr_type; // ��� ���������

  function GetPos() { 
	return ($this->pos);
  }

  function GetLen() { 
  	return $this -> length;
  }

 /********************************************************************** 
  *  �����������  * 
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

	// ���� ����, �������� ��������, ���������� �� ���� ������� 
    // ��������� ����� ����� ��� 1 
    switch( $type )
    {
    	case 1: // �����
    	case 6: // 

    		$this->instates = array($LANG_SETTINGS['logical']['and'] => 0, $LANG_SETTINGS['logical']['or'] => 1, $LANG_SETTINGS['logical']['not'] => 2, "(" => 4, ")" => 5, ">" => 6, "<" => 7, "=" => 8); 

		    $this->automat=array( 
		     "0"	=>	array( -1, -1, -1, 1, -1, -1, -1, -1, -1, 1),	// ��
		     "1"	=>	array( -1, -1, -1, 8, -1, -1, -1, -1, -1, 8),	// ���
//		     "2"	=>	array( -1, 2, -1, 2, -1, -1, -1, -1, -1, -1),	// ��
		     "2"	=>	array( 2, 2, -1, 2, 2, -1, -1, -1, 2, 2),	// ��

		     "3"	=>	array( 3, 3, 3, 3, 3, 3, 3, 3, 3, 3),			// �������
		     "4"	=>	array( 4, 4, 4, 4, 4, -1, -1, -1, 4, 4),		// (
		     "5"	=>	array( -1, -1, -1, 9, -1, -1, -1, -1, -1, 9),	// )
		     "6"	=>	array( 5, 5, 5, 5, 5, -1, 5, -1, 5, 5),			// >
		     "7"	=>	array( 6, 6, 6, 6, 6, -1, -1, -1, 6, 6),		// <
		     "8"	=>	array( 7, 7, 7, 7, 7, 7, 7, -1, 7, 7),			// =
		    ); 

    	break;

    	case 2: // ������
		    $this->automat=array( 
		     "0"	=>	array( -1, -1, -1, -1, 1, -1, 1),	// ��
   		     "1"	=>	array( -1, -1, -1, -1, 2, -1, 2),	// ���
   		     "2"	=>	array( 3, 3, 3, -1, 3, 3, 3),		// ��
   		     "3"	=>	array( 4, 4, 4, 4, 4, 4, 4),		// �����
   		     "4"	=>	array( 5, 5, 5, 5, 5, 5, 5),		// (
   		     "5"	=>	array( -1, -1, -1, -1, 6, -1, 6),	// )
		    ); 

    		$this->instates = array($LANG_SETTINGS['logical']['and'] => 0, $LANG_SETTINGS['logical']['or'] => 1, $LANG_SETTINGS['logical']['not'] => 2, "(" => 4, ")" => 5); 
    	break;

    	case 3: // ����
    		$this->instates = array($LANG_SETTINGS['logical']['and'] => 0, $LANG_SETTINGS['logical']['or'] => 1, $LANG_SETTINGS['logical']['not'] => 2, "(" => 4, ")" => 5, ">" => 6, "<" => 7, "=" => 8); 

		    $this->automat=array( 
		     "0"	=>	array( -1, -1, -1, 1, -1, -1, -1, -1, -1, 1),	// ��
		     "1"	=>	array( -1, -1, -1, 8, -1, -1, -1, -1, -1, 8),	// ���
//		     "2"	=>	array( -1, 2, -1, 2, -1, -1, -1, -1, -1, -1),	// ��
		     "2"	=>	array( 2, 2, -1, 2, 2, -1, -1, -1, 2, 2),	// ��

		     "3"	=>	array( 3, 3, 3, 3, 3, 3, 3, 3, 3, 3),			// �������
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
  *  ������  * 
  **********************************************************************/ 
  function Scan() 
  { 
	// �����������, ������� ���������� 
    $delimiters=array(" ","\t","\r","\n"); 

    $state=0; 
    $word="";
    $prevstate=0;
    
	// ������� �������� 

    switch($this->expr_type)
    {
    	case 1: // �����
    	case 3: // ����
    	case 6: // �����/������
    	
    		// ����� �� ������ ������� 
    		$words = array("(", ")", ">", "<", "=");

		    $automat=array( 
					    /* 
					    -1 ����� ������ ����������
					     0 ������ ������������ 
					     1 �������� ������, ����� ���� �� �����������
					     2 �������� ����� �� 1-��� �������
					    */ 
					    
					    //���������  0,  1,  2
					     "0"=>array( 0, -1, -1 ), 	// �����������
					     "1"=>array( 2, -1, -1 ), 	// ����� - ���� ������
					     "2"=>array( 1, 1, -1 ), 	// ������
					    ); 

			// ���� ������������ 
			while ($this->pos<$this->length) 
			{ 
				
				// ������������� ��� ����������� �� ���� �������� �������. 
				if (in_array($this->data[$this->pos],$delimiters))  
					$instate=0; 
				elseif (in_array($this->data[$this->pos],$words))  
					$instate=1; 
				else 
					$instate=2; 
					
				$prevstate = $state;
				
				// �������� ��������� �������� 
				$state=$automat[$instate][$state];
				
				//print($this->data[$this->pos]." $state (instate=$instate) (prev=$prevstate)<br>");
		
				// ���� �������� �� ���������� �������� 
				switch($state) 
				{ 
					case 0: // ������ ������������ 
						if ($this->data[$this->pos]=="\n") 
						{ 
							$this->line++; 
							$this->column=0; 
						} 
		    		
					$word=""; 
					break; 
					
					case -1: // ����� ������, ���� ���������� 
						if (strlen($word))
						{ 
							//print($word.'<BR>');
							return $word; 
						}
					break; 
		     
					case 1: // �������� ������, ���� ������ ���� ��� ������ 
						$word.=$this->data[$this->pos];
					break; 
		
					case 2: // �������� ���������������� ����� �� ������ ������� 
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
    	case 2: // ������

    		// ����� �� ������ ������� 
    		$words=array("(", ")"); 

		    $automat=array( 
					    /* 
					    -1 ����� ������ 
					     0 ������ ������������ 
					     1 �������� ������ ( �� ����������� � �� ") 
					     2 �������� ������ ", ����� ���� �� �������� ����. " ��� ����� ������ 
					     3 �������� �����������, ����� ���� ����������� 
					     4 �������� (,), ���������� 
					    */ 
					    //���������  0, 1, 2, 3, 4
					     "0"=>array( 3, -1, 2, 3, -1),   // �����������
					     "1"=>array( 2, 2, -1, -1, -1), // "
					     "2"=>array( 1, 1, 2, -1, -1),   // �� " � �����������
					     "3"=>array( 4, -1, 2, -1, -1),  // (, )
					    ); 

			// ���� ������������ 
			while ($this->pos<$this->length) 
			{ 
				// ������������� ��� ����������� �� ���� �������� �������. 
				if (in_array($this->data[$this->pos],$delimiters))  
					$instate=0; 
				elseif ($this->data[$this->pos] == "\"")  
					$instate=1; 
				elseif (in_array($this->data[$this->pos],$words))  
					$instate=3; 
				else 
					$instate=2; 
					
				$prevstate = $state;
				
				// �������� ��������� �������� 
				$state=$automat[$instate][$state];
				
				if ( ( $instate == 1 ) && ( $state == -1 ) && ( $prevstate == 2 ) ) // ��������� �������� "lalsl\"sdlaland"
				{
					if ( ( ($this->pos - 1) >= 0 ) && ( $this->data[$this->pos - 1] == "\\" ) )
						$state = 2;
				}
				else
				if ( ( $instate == 1 ) && ( $state == -1 ) ) // ��������� ��������� \"
				{
					if ( ( ($this->pos - 1) >= 0 ) && ( $this->data[$this->pos - 1] == "\\" ) )
						$state = 1;
				}
		
				//print("$state<br>");
		
				// ���� �������� �� ���������� �������� 
				switch($state) 
				{ 
					case 0: // ������ ������������ 
						if ($this->data[$this->pos]=="\n") 
						{ 
							$this->line++; 
							$this->column=0; 
						} 
		    		
					$word=""; 
					break; 
					
					case -1: // ����� ������, ���� ���������� 
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
		     
					case 1: // �������� ������, ���� ������ ���� ��� ������ 
					case 2: 
					case 3:
						$word.=$this->data[$this->pos];
						//print($this->data[$this->pos]."<br>"); 
					break; 
		
					case 4: // �������� ���������������� ����� �� ������ ������� 
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
    	case 1: // �����
    	case 6: // �����/������
			$res = $this->ParseInt($expr);
    	break;
    	case 2: // ������
    		$res = $this->ParseStr($expr);
    	break;
    	case 3: // ����
    		$res = $this->ParseDate($expr);
    	break;

    }
    
    return $res;
  }

 /********************************************************************** 
  *  ������  * 
  **********************************************************************/ 
  function ParseInt($expr) 
  { 
	// ���������� $first ����� ����, ���� ������� ������� ���� ������� ������ ��� 
	$first = $this->pos;

	// ���� ��������� 
	while(1)
	{ 
		// �������� ����� �� �������� 
		$word = $this->GetNext();
		if ( $this->pos > count($this->expr))
			break;
		
		if (!preg_match("/^[\s]+$/",$word) && !empty($word))
		{
			// ������������� ���, ����������� �� ���� ��������, ����� 
			$instate=isset($this->instates[$word]) ? $this->instates[$word] : 3; 
	       
			// �������� ��������� �������� ������� 
			$this->state=$this->automat[$instate][$this->state];
			//print('word='.$word.';instate='.$instate.';state='.$this->state.'<br>');
			//print($instate.'<br>');
	       
			// ���� ��������� ���������, �� ��������� ���� 
			if ($this->state==-1) 
			{ 
				$this->errorstr=1;
				return false; 
			} 
	       
			// ���� �������� �� ���������� �������� ������� 
			switch($this->state) 
			{ 
	
				case 3: // �������� ������� (���� ��������� ����� �� ���),
	
					// ��������� ����� �� ���? 
					if (!preg_match("/^[0-9]+$/",$word)) 
					{ 
						$this->errorstr=2; 
						return false; 
					} 
				break; 
	
				case 4: // �������� ����� ������, ������� �������� ��� ����� ������ 
	
					// ����������� ���-�� �������� ������ �� 1; 
					$this->brackets++; 
	     
					// ������ ������������ ��������, �.�. ������ � ������� 
					// ����� ������������� ��� ����c���������� ���������. 
					// �� �������� �� ������� � ������ ������, ����� ������ ��� 
					// ����� ��������� �������� ������ 
					if (!$this->ParseInt($expr)) 
						return false; 
				break; 
		
				case 9: // �������� ������ ������, ������� �������� 
	      
					// ��������� ���-�� �������� ������ �� 1 
					$this->brackets--;
					if ( $this->brackets < 0) { $this->errorstr=3; return false; }
					else return true;
				break;
			} // end switch 
	       
			// ���������� ������� ��������� ��� ���������� ���� ����� 
			$this->prevstate=$this->state; 
		} // end if <> ������
	} // end while(1)

    // ��� ��� � ��� ����������� ��������� ����� �������, �� ���� 
    // ��������� � ����� ��������� �� ��������� ������ 
    // ��� ���� ������ ������ ���� ��� � ����� ������ ������ 
    // ������� �������. ��� ������ �����, ���� $first==0 
    // ����, �� ������ ������� ������, ���� � ��� ���� ������ ������, 
    // ��� ���� �� �� �������� ������� �������� ��� ������ ������, 
    // �.�. ������ ���������� "�� ��������". 
     
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
	// ���������� $first ����� ����, ���� ������� ������� ���� ������� ������ ��� 
	$first = $this->pos;

	// ���� ��������� 
	while(1)
	{ 
		// �������� ����� �� �������� 
		$word = $this->GetNext();
		$wlen = strlen($word);
		if ( $this->pos > count($this->expr))
			break;
		
		if (!preg_match("/^[\s]+$/",$word) && !empty($word))
		{
			// ������������� ���, ����������� �� ���� ��������, ����� 
			$instate=isset($this->instates[$word]) ? $this->instates[$word] : 3; 
	       
			// �������� ��������� �������� ������� 
			$this->state=$this->automat[$instate][$this->state];
			//print('word='.$word.';instate='.$instate.';state='.$this->state.'<br>');
			//print($instate.'<br>');
	       
			// ���� ��������� ���������, �� ��������� ���� 
			if ($this->state==-1) 
			{ 
				$this->errorstr=1;
				break; 
			} 
			
			// ���� �������� �� ���������� �������� ������� 
			switch($this->state) 
			{ 
				case 4: // �������� ������� ������
	
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
						
						//if ( !preg_match( "/^[\s\/\'\-\"0-9�-��-�a-zA-Z��������]+$/", $word ) ) 
						if ( !preg_match( "/^[\,\.\=\<\>\\\(\)\{\}\[\]\s\/\'\-\"0-9�-��-�a-zA-Z��������]+$/", $word ) ) 
						{
							$this->errorstr=2; // ������������ ������
							return false; 
						}
						elseif ( ( $quote_count % 2 ) != 0 )
						{
							$this->errorstr=5; // ����� �� ������
							return false; 
						}
						elseif ( ( $quote_count == 2 ) && ( ( $word[0] == '"' && $word[$wlen-1] != '"' ) || ( $word[0] != '"' && $word[$wlen-1] == '"' ) ) )
						{
							$this->errorstr=1; // ����������� ������������
							return false; 
						}
					} // ���� ���� "
*/
					else
					{
						if ( !preg_match( "/^[\-\.\,\/\'\\\"\*\?0-9�-��-�a-zA-Z��������]+$/", $word ) ) 
						{
							$this->errorstr=2; // ������������ ������
							return false; 
						}
						elseif ($word == '?' || preg_match( "/^[\?]+$/", $word ) )
						{
							$this->errorstr=1; // ����������� ������������
							return false; 
						}
					} 
					
				break; 
	
				case 5: // �������� ����� ������, ������� �������� ��� ����� ������ 
	
					// ����������� ���-�� �������� ������ �� 1; 
					$this->brackets++; 
	     
					// ������ ������������ ��������, �.�. ������ � ������� 
					// ����� ������������� ��� ����c���������� ���������. 
					// �� �������� �� ������� � ������ ������, ����� ������ ��� 
					// ����� ��������� �������� ������ 
					if (!$this->ParseStr($expr)) 
						return false; 
				break; 
	
				case 6: // �������� ������ ������, ������� �������� 
	      
					// ��������� ���-�� �������� ������ �� 1 
					$this->brackets--;
					if ( $this->brackets < 0) { $this->errorstr=3; return false; }
					else return true;
				break;
			} // end switch 
	       
			// ���������� ������� ��������� ��� ���������� ���� ����� 
			$this->prevstate=$this->state; 
		} // end if <> ������
	} // end while(1)

    // ��� ��� � ��� ����������� ��������� ����� �������, �� ���� 
    // ��������� � ����� ��������� �� ��������� ������ 
    // ��� ���� ������ ������ ���� ��� � ����� ������ ������ 
    // ������� �������. ��� ������ �����, ���� $first==0 
    // ����, �� ������ ������� ������, ���� � ��� ���� ������ ������, 
    // ��� ���� �� �� �������� ������� �������� ��� ������ ������, 
    // �.�. ������ ���������� "�� ��������". 
    
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
	// ���������� $first ����� ����, ���� ������� ������� ���� ������� ������ ��� 
	$first = $this->pos;

	// ���� ��������� 
	while(1)
	{ 
		// �������� ����� �� �������� 
		$word = $this->GetNext();
		if ( $this->pos > count($this->expr))
			break;
		
		if (!preg_match("/^[\s]+$/",$word) && !empty($word))
		{
			// ������������� ���, ����������� �� ���� ��������, ����� 
			$instate=isset($this->instates[$word]) ? $this->instates[$word] : 3; 
	       
			// �������� ��������� �������� ������� 
			$this->state=$this->automat[$instate][$this->state];
			//print('word='.$word.';instate='.$instate.';state='.$this->state.'<br>');
			//print($instate.'<br>');
	       
			// ���� ��������� ���������, �� ��������� ���� 
			if ($this->state==-1) 
			{ 
				$this->errorstr=1;
				break; 
			} 
	       
			// ���� �������� �� ���������� �������� ������� 
			switch($this->state) 
			{ 
	
				case 3: // �������� ������� (���� ��������� ����� �� ���),
	
					// ��������� ����� �� ���? 
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
	
				case 4: // �������� ����� ������, ������� �������� ��� ����� ������ 
	
					// ����������� ���-�� �������� ������ �� 1; 
					$this->brackets++; 
	     
					// ������ ������������ ��������, �.�. ������ � ������� 
					// ����� ������������� ��� ����c���������� ���������. 
					// �� �������� �� ������� � ������ ������, ����� ������ ��� 
					// ����� ��������� �������� ������ 
					if (!$this->ParseDate($expr)) 
						return false; 
				break; 
	
	
				case 9: // �������� ������ ������, ������� �������� 
	      
					// ��������� ���-�� �������� ������ �� 1 
					$this->brackets--;
					if ( $this->brackets < 0) { $this->errorstr=3; return false; }
					else return true;
				break;
			} // end switch 
	       
			// ���������� ������� ��������� ��� ���������� ���� ����� 
			$this->prevstate=$this->state; 
		} // end if <> ������
	} // end while(1)

    // ��� ��� � ��� ����������� ��������� ����� �������, �� ���� 
    // ��������� � ����� ��������� �� ��������� ������ 
    // ��� ���� ������ ������ ���� ��� � ����� ������ ������ 
    // ������� �������. ��� ������ �����, ���� $first==0 
    // ����, �� ������ ������� ������, ���� � ��� ���� ������ ������, 
    // ��� ���� �� �� �������� ������� �������� ��� ������ ������, 
    // �.�. ������ ���������� "�� ��������". 
     
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
