<?
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












?>
