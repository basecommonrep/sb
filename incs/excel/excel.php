<?
class Excel {

        /* variables */

	var $ex;
        var $pathin;
        var $pathout;
        var $workbook;
        var $sheet;
        var $visible;
        var $fformatin;
        var $fformatout;
        var $cell;
        var $rangesens;
        var $range;
        var $ext;
        var $oext;
        

        /* Constructor */

       function excel() 
       {
        	#Instantiate Excel
                $this->ex = new COM("Excel.sheet") or Die ("Did not instantiate Excel");

                return 1;
       } 


	function XL($workbook,$pathin="",$sheet="sheet1")	 
 	{   
 	
 		if ($workbook != "")
 		{
               	 	#Load the workbook
                	$wkb = $this->ex->application->Workbooks->Open($pathin.$workbook) or Die ("Did not open $pathin $workbook");
                	
                }else{
                	#New workbook
                	$wkb = $this->ex->application->Workbooks->Add or Die ("Unable to add a workbook");
                }
 
                if ($sheet != "")
                {
                	#Activate the sheet
               		$sheets = $wkb->Worksheets($sheet) or Die ("Unable to activate $sheet");
               		
               	}else{
               		#new sheet
               		$sheet = "sheet1" ;
               		
               	}
               	#Excel Won't prompt the user when replacing or closing workbooks
               	#Comment the line below if you want Excel to prompt
              	//$this->ex->application->DisplayAlerts = "False";
		return 1;
                
       } 
       

	function readrange($sheet="sheet1",$range)
	{
	
		#Read all the cells in the range to $result and return it
		unset ($result);
		
		$range = trim($range);
		#Determine start and end of range
		$tokstart = strtok($range,":");
		$tokend = strtok(":");
		if ($tokend =="")
		{
			#Read one single cell
			$sheets = $this->ex->Application->Worksheets($sheet);	
			$sheets->activate; 					
			#Select the cell
			$selcell = $sheets->Range($range);
			$selcell->activate;
			return $selcell->value;
		}
		#Read a range of cells
		#determine column and row numbers
		$sheets = $this->ex->Application->Worksheets($sheet);
		$sheets->activate;
		$rgstart = $sheets->range($tokstart);
		$colstart = $rgstart->column;
		$rowstart = $rgstart->row;
		$rgend = $sheets->range($tokend);
		$colend = $rgend->column;
		$rowend = $rgend->row;
		if ($colstart>$colend or $rowstart>$rowend)
		{
			Print ("Notation Error! Cell Column/Row should be increasing.");
			return;
		}
		#Now read each cell
		
		if ($colstart == $colend)
		{
			#Read Vertically
			$j=0;
			For ($i= $rowstart; $i<=$rowend; $i++)
			{
			
				$selcell = $sheets->cells($i,$colstart);
				$selcell->activate;
				$result[$j] = $selcell->value;
				$j++;
			}
		}else 
		{
			#Read horizontally
			$j=0;
			For ($i= $colstart; $i<=$colend; $i++)
			{
			
				$selcell = $sheets->cells($rowstart,$i);
				$selcell->activate;
				$result[$j] = $selcell->value;
				$j++;
			}
		}

			return $result;
	}
	
	
	
	function writerange($sheet="sheet1",$range,$value)
	{
	
		#Fill up all the cells in the range with array
		
		$range = trim($range);
		#Determine start and end of range
		$tokstart = strtok($range,":");
		$tokend = strtok(":");
		if ($tokend =="")
		{
		
			# Write to a single cell in the active sheet
			$cell = trim($range);
			#Select the sheet
			$sheets = $this->ex->Application->Worksheets($sheet);
			$sheets->activate;
			#Select the cell
			$selcell = $sheets->Range($cell);
			$selcell->activate;
			$selcell->value = $value;
			return;
		}
		
		#determine column and row numbers
		$sheets = $this->ex->Application->Worksheets($sheet);
		$sheets->activate;
		$rgstart = $sheets->range($tokstart);
		$colstart = $rgstart->column;
		$rowstart = $rgstart->row;
		$rgend = $sheets->range($tokend);
		$colend = $rgend->column;
		$rowend = $rgend->row;
		if ($colstart>$colend or $rowstart>$rowend)
		{
			Print ("Notation Error! Cell Column/Row should be increasing.");
			return;
		}
		#Now write each cell
		
		if ($colstart == $colend)
		{
			#write Vertically
			$j=0;
			For ($i= $rowstart; $i<=$rowend; $i++)
			{
			
				$selcell = $sheets->cells($i,$colstart);
				$selcell->activate;
				$selcell->value = $value[$j];
				$j++;
			}
		}else 
		{
			#Write horizontally
			$j=0;
			For ($i= $colstart; $i<=$colend; $i++)
			{
			
				$selcell = $sheets->cells($rowstart,$i);
				$selcell->activate;
				$selcell->value = $value[$j];
				$j++;
			}
		}

		return 1;
	}	

        function saveas($workbook,$pathout,$ext)  
        {
        
        	
        	#First get the file format code for the extension $ext
        	$code = $this->fileformater($ext);
        	$basefile = strtok($workbook,".");
        	$newworkbook = $basefile."."."$ext";
        	
        	
        	#If no prompt and file exists it will be replaced.
        	
      	
        	#Save the current workbook as new workbook
        		#The following line will work for converting spreadsheets file to xls
        		#but if the original is an excel file and the new file another format
        		#then it may not work because limitations of excel.(See excel doc)
        		
        		$this->ex->Application->ActiveWorkbook->SaveAS($pathout.$newworkbook,$code); 
        	
        	
        	return 1;
       } 
       


        function fileformater($ext)
        {

		switch(strtolower($ext))
		{
		
			case   "slk":
				return  2;
				break;
				
			case   "xlt":
				return  -4143;
				break;
				
			case   "txt":
				return  -4158;
				break;
				
			case   "csv":
				return  6;
				break;
				
			case   "xlw":
				return  35;
				break;
				
			case   "w4k":
				return  38;
				break;
				
			case   "wq1":
				return  34;
				break;
				
			case   "prn":
				return  -4158;
				break;
				
			case   "dif":
				return  9;
				break;
				
			case   "xla":
				return  -4143;
				break;
				
			case   "wk3":
				return  32;
				break;
				
			case   "xls":
				return -4143;
				break;
				
			case   "htm":
				return  44;
				break;
				
			case   "wks":
				return  4;
				break;
				
			default:
				return  -4143;
				
				
		}
	}
	
	function XLTranslate($pathin,$pathout,$oext,$ext,$kill=0)
	{
	
		#This function will translate automatically all spreadsheets files, with the
		#$oext extension, in the $pathin directory, to another spreadsheet file,
		#with the $ext extension, to the $pathout directory.
		#It will erase the original file if $kill switch = 1.
		#Limitations: Will work always when translating none excel files to
		#excel files(Extension=xl*) and with the translation xls->htm . It will
		#not generally work when translating excel files to other formats because
		#the questions asked by the excel program stop the script.
	
		#Get all files in the source directory $pathin to the $filelist array
		chdir($pathin);
		$dir=dir (".");
		$i=1;
		while($file=$dir->read())
		{
			$filelist [$i] = $file;
			$i++;
		}
		$dir->close;
	
		#Translate each file, with the original extension $oext, in the $filelist
		#to the needed extension $ext.
		
		for ($i=1;$i<= sizeof($filelist); $i++)
		{
		
			$file = $filelist[$i];
			
			$basefile =  strtok($file,".");
			$extension = strtok(".");
			
				
			if (strtolower($extension) == strtolower($oext))
			{
				echo "<BR> $file";
				$this->XL($file,$pathin,$sheet="");
				$this->saveas($file,$pathout,$ext,"");
				#Erase the original file if $kill=1
				if ($kill)
				{
					chmod ($file,0777);
					unlink ($pathin.$file);
				}
				#Close the new workbook
				$this->closeXL();
		        }
		        
		}
		
		return 1;	
	}
        	
	
       
       	function closexl()
       	{
       	
       		#Close active workbook without prompt from Excel
 		
		$this->ex->application->ActiveWorkbook->Close("False");	
		return 1;
		
	}
       
	function runfunction($funct,$arrayparam)
	{
		#Run and return value of an excel function
		
		$params = implode(",",$arrayparam);
		
		eval ("\$result = \$this->ex->application->$funct($params);");
		
		return $result;
		
	}
	
	Function runmacro($workbook,$macroname)
	{
		$this->ex->application->Run("$workbook!$macroname");
		
		return 1;
	}
	
	Function createhyperlink($sheet="sheet1",$cell,$hyperl)
	{
		#Not working as 9/2/00 4:57PM
		print "<br>link = $hyperl <br>";
		$sheets = $this->ex->Application->Worksheets($sheet);
		$sheets->activate;
			#Select the cell
			$selcell = $sheets->Range($cell);
			
			$sheets->hyperlinks->add($selcell,$hyperl);
			
			
			return 1;
	}
	
	function calculate($sheet="sheet1")
	{
		#Calculate (update) the current sheet
		$sheets = $this->ex->Application->Worksheets($sheet);	#Select the sheet
		$sheets->activate; 
		$sheets->Calculate;
		return 1;
		
	}
	

	
 
} /* end of Excel class */
?>
