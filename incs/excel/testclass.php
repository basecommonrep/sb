<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<!-- saved from url=(0071)http://www.phpclasses.org/browse/download/1/file/275/name/testclass.php -->
<HTML><HEAD>
<META http-equiv=Content-Type content="text/html; charset=windows-1251">
<META content="MSHTML 6.00.2800.1634" name=GENERATOR></HEAD>
<BODY><PRE>&lt;?php 
/* Test for Excel.php: A class for use with PHP4 scripts only*/


/*
 * This is a test file for Excel class to create,load,read,write,save and use some of the 
 * internal functionalities of workbooks and sheets.
 * Tested with Windows 98 - MS Office 2000
 * Apache 1.3.9 PHP4.02 Running as CGI
 * (c) Alain M. Samoun 09/2000.
 * alain@sonic.net
 * Gnu GPL code (see www.fsf.org for more information ).
 */
 
 /* Set up files and directories for the test. Change as you wish.*/
 
 # Put the include file in your php include directory
	require ("excel.php");
 # Put the test.xls file in the C:\My Documents\ directory
	$workbook = "test.xls";
	$pathin = "C:\\My Documents\\";
	$sheet = "test";
	$pathout = "c:\\My Documents\\"; #The directory to save your files

 /* Instantiate Excel and open the test file. */

 #Instantiate Excel
    	$E = new Excel;

 #Open the workbook
    	$E-&gt;XL($workbook,$pathin,$sheet); 
    	Print "Test starting..&lt;br&gt;";

    	
 /* Read the content of a cell or range of cells */

  # Read the A1 cell
    	Print "The content of cell A1 is: ". $E-&gt;readrange($sheet,"A1")."&lt;br&gt;";
    
  # Read the content of cells A1,A2,A3,A4
    	$content = $E-&gt;readrange($sheet,"A1:A4");
		if (is_array($content))
		{
			$count = sizeof($content);
			for ($num=0; $num&lt;$count; $num++)
			{
				$num2=$num+1;
   				print "Got Cell A$num2 Content = ". $content[$num] . "&lt;br&gt;";
   			}
		}
	
 /* Write to a cell or range of cells  */
 
  # Change the content of cell A1
    	$E-&gt;writerange($sheet,"A1","New content");
  # Read the new content  
    	Print "The content of cell A1 now is: ". $E-&gt;readrange($sheet,"A1")."&lt;br&gt;";
    
  # Write an array of numbers to the cells B1,C1,D1,E1
    	$array = array("1","2","3","4");
    	$E-&gt;writerange($sheet,"B1:E1",$array);
  # Read the new content for the range:
    	$content = $E-&gt;readrange($sheet,"B1:E1");
   	if (is_array($content))
    	{
		$count = sizeof($content);
		for ($num=0; $num&lt;$count; $num++)
		{
			$letter= chr(66+$num);
   			print "Set cell $letter"."1 Content= ". $content[$num] . "&lt;br&gt;";
   		}
    	}
    
    
 /* Write a formula in cell B3  */
 
    	$E-&gt;writerange($sheet,"B3",'=SUM(B1..E1)');
  # Read the B3 content  
    	Print "The content of cell B3=SUM(B1..D1) is: ". $E-&gt;readrange($sheet,"B3")."&lt;br&gt;";

 /* Execute a macro */
 
 #The following will run the macro Macro2 that will put a string on cell D6
 #content of cell D6 before macro
 	Print"Cell D6 before macro:". $E-&gt;readrange($sheet,"D6")." &lt;br&gt;";
 	$E-&gt;runmacro($workbook,"Macro2");
 #Read the macro result:
 	$result = $E-&gt;readrange($sheet,"D6");
 	print "Cell D6 content after running Macro2 = $result &lt;br&gt;"; 
    
 /* Read the result of a build-in excel function */

 #Example: PMT financial function
 	$arrayparam = array("0.08/12","10","10000"); 
 	$result = $E-&gt;runfunction("PMT",$arrayparam);
 	print "&lt;br&gt;Financial function PMT result using the \"run function \" method: ".sprintf("%.2f",$result);


 /* Convert all files in a directory */
/* (Uncoment to run this part)
 #File to convert from extension "xls" to extension "csv"
 	if ($E-&gt;XLTranslate($pathin,$pathout,"xls","csv",0))
 	{
 		print "&lt;br&gt;All 'xls' files in $pathin have been converted to 'csv files in $pathout.&lt;br&gt;";
 	}
*/ 
 /* Save the workbook */     

 #Save the current workbook as a quattro pro file:
 	$E-&gt;saveas($workbook,$pathout,"WQ1");
 	print "&lt;br&gt; $workbook has been saved as a WQ1 file. &lt;br&gt;";

 /* Close workbook  and exit excel */
 	$E-&gt;closexl();
 	unset ($E);
 
 /* Start a new instance of excel with a new workbook */ 
     	$E = new Excel;
    	$E-&gt;XL("",$pathin,"sheet1"); #Note the empty name for workbook
    	Print "&lt;br&gt;Starting a new workbook&lt;br&gt;";
  # Write something in cell A1
    	$E-&gt;writerange("sheet1","A1","Cell A1 in the new workbook");
  # Read the new content  
    	Print "The content of cell A1 in the new workbook is: ". $E-&gt;readrange("sheet1","A1")."&lt;br&gt;";
  # Save the new workbook as an xls file
  	$E-&gt;saveas("newwkb",$pathout,"xls");
  # And close it
 	 $E-&gt;closexl();
         unset ($E);


 	echo "&lt;br&gt; Test finished!";
 
?&gt;</PRE></BODY></HTML>
