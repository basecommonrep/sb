<?
	class mssql 
	{
		var $host;
		var $login;
		var $pass;
		var $database;
		var $dbType;
		var $db;
		var $res;
		
		function connection($host, $login, $pass, $database, $dbType)
		{
			$this->host = $host;
			$this->login = $login;
			$this->pass = $pass;
			$this->database = $database;
			$this->dbType = $dbType;

			if ( $this->dbType == '' )
			{
				$this->db = @mssql_connect($host, $login, $pass);					
				@mssql_select_db($database, $this->db);
			}
			elseif ( $this->dbType == 'odbc' )
			{

				$dsn =  "driver={sql server}; ".
						"server=$host; ".
						"database=$database";
				
				$this->db = @odbc_connect($dsn, $login, $pass);
			}
			
			return $this->db;

		} // end connection
		
		function selectDb($dbn)
		{
			//print('**'.$dbn.'**<BR>');
			if ( $this->dbType == '' )
				@mssql_select_db($dbn, $this->db);
			elseif ( $this->dbType == 'odbc' )
			{
				$q = 'use '.$dbn;
				$this->executeQuery($q);
			}
		} // end selectDb
		
		function executeQuery($query)
		{
			//print($query.'<BR><BR>');
			//print($this->db);
			
			if ( $this->dbType == '' )
				$this->res = @mssql_query($query, $this->db);
			elseif ( $this->dbType == 'odbc' )
				$this->res = @odbc_exec($this->db, $query);
				
			if ( $this->res === false )
				return -1;
			else 
				return true;
		} // end executeQuery
		
		function getRow($type)
		{
			$t = array('num' => MSSQL_NUM, 'assoc' => MSSQL_ASSOC);
			$currType = $t[$type];
			
			//print($this->res);
			
			if ( $this->dbType == '' )
				$row = @mssql_fetch_array($this->res, $currType);
			elseif ( $this->dbType == 'odbc' )
			{
				if ( $type == 'num' )
					@odbc_fetch_into($this->res, $row);
				elseif ( $type == 'assoc' )
					$row = @odbc_fetch_array($this->res);
			}
			
			return $row;
		} // end getRow

		function getRowNums()
		{
			if ( $this->dbType == '' )
				$rowNums = @mssql_num_rows($this->res);
			elseif ( $this->dbType == 'odbc' )
				$rowNums = @odbc_num_rows($this->res);
			
			return (int)$rowNums;
		} // end getRowNums
		

		function disconnection()
		{
			if ( $this->dbType == '' )
				@mssql_close($this->db);
			elseif ( $this->dbType == 'odbc' )
				@odbc_close($this->db);
		} // end disconnection
		
		
	} // end class
?>
