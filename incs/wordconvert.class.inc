<?php
/* Class to convert any document, that can be read by MS Word, to another format supported by Word.
	 * © Alain M. Samoun 10/2001.
 	* alain@samoun.com
	* Gnu GPL code (see www.fsf.org for more information).
	* Tested on win98 + Apache1.3  PHP 4.8 dev as CGI  - Word 2000
	* This file should be saved in the PHP's include directory.
	*If you try to use COM in XP/win2k or NT, you need to 
         set-up permissions to the application
 	with the program DCOMCNFG.EXE : 
	Run DCOMCNFG.exe, select the application and add permissions
        in Security:
	- Custom Access Permissions: “Allow” 
	Then Edit / Add
	- the “IUSR_<servername>” user access to the object.- The user
          account to run the application: “The interactive user” 
	And close.
	* Usage:
	* Conversion time example: Convert a 33 pages rtf document (133KB)
          to an htm file (268KB)in 6 sec. (300MHz processor). Not a speed 
          daemon, but will work for small files on servers
	  with low hits number (Intranet...).
*/
	class wordconvert
	{

      	  /* variables */
	var $filename;	# Original File name with optional path.
			# If no path provided, will be looked for in 
                        # My Documents.
	var $convert_to=0;  	
                       # Extension (as a string) or number (See Doc on 
                       # SaveAs method below),doc extension is the default.
	var $visible=0;# 0=Hidden, 1= Visible, hidden is the default.
	
     	 /* Constructor */

     		function wordconvert($filename,$convert_to=0,$visible=0) 
       		{
       			if (!file_exists($filename))
			{
				echo "File $filename doesn't exist";
				exit();
			}

       			$filename_path=  substr($filename,0,-4);
			
			if (is_string ($convert_to))
			{
				$convert_to= strtolower($convert_to);
			
				 switch ($convert_to) 
				 {
     					case "doc":
     						$convert_to=0;
     						Break;
     					case "dot":
     						$convert_to=1;
     						Break;
     					case "txt":
     						$convert_to=2;
     						Break;
     					case "rtf":
     						$convert_to=6;
     						Break;
     					case "htm":
     						$convert_to=8;
     						Break;
     					case "html":
     						$convert_to=8;
     						Break;
     					case "asc":
     						$convert_to=9;
     						Break;
     					case "wri":
      						$convert_to=13;
     						Break;
     					case "wps":
      						$convert_to=28;
     						Break;
     					default:
     						$convert_to=0;
     				}
     			}
			# Instantiate MSWord
 			$word=new COM("Word.Application") or die("Cannot start MS Word");
 	
 			$word->visible = $visible ;
 	
			#Open the original file in word.
			$word->Documents->Open($filename)or die("Cannot find file to convert");

/* 
Doc on SaveAs method:
 expression.SaveAs(FileName, FileFormat, LockComments, Password, AddToRecentFiles, WritePassword, ReadOnlyRecommended, EmbedTrueTypeFonts, SaveNativePictureFormat, SaveFormsData, SaveAsAOCELetter)
 Only the two first parameters are supported in this class.
File save format number to use ( WdSaveFormat prop. ):
  wdFormatDocument = 0;  wdFormatTemplate = 1;  wdFormatText = 2;  wdFormatTextLineBreaks = 3;
  wdFormatDOSText = 4;  wdFormatDOSTextLineBreaks = 5;  wdFormatRTF = 6;  wdFormatUnicodeText = 7;
  Extensions=number: doc=0,dot =1,txt=2,htm=8,asc=9,wri=13,doc(word perfect DOS)=24,wps(works)=28
*/


			#Save the new file
			$word->ActiveDocument->SaveAs($filename_path,$convert_to); 

 /*
 Doc on quit method:
 expression.Quit(SaveChanges, Format, RouteDocument)
 */
 
			$word->quit(0); #0: Quit without saving
			# print "done!";
	
		}#End of func
	
	}#End of class
?>

