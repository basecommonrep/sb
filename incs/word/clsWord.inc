<?

//   
// +------------------------------------------------------------------------+ 
// | PHP version 5.1.4                                         | 
// +------------------------------------------------------------------------+ 
// | Description:                                |      
// | class to make interaction between PHP 5.1.4 and MS Word                | 
// |                                         |     
// +------------------------------------------------------------------------+ 
// | Author        : Neeraj Thakur <neeraj_th@yahoo.com>            | 
// | Created Date         : 28-11-2006                                  | 
// | Last Modified        : 28-11-2006                                  | 
// | Last Modified By     : Neeraj Thakur                              | 
// +------------------------------------------------------------------------+ 

// NOTE: Using COM with windows NT/2000/XP with apache as a service 

   class clsMSWord 
   { 
       // Vars: 
       var $handle; 
       
       // Create COM instance to word 
       function clsMSWord($Visible = false) 
       { 
           $this->handle = new COM("word.application") or die("Unable to instanciate Word"); 
           $this->handle->Visible = $Visible; 
       } 
       
       // Open existing document 
       function Open($File) 
       { 
           $this->handle->Documents->Open($File); 
       } 
       
       // Create new document 
       function NewDocument() 
       { 
           $this->handle->Documents->Add(); 
       } 
       
       // Write text to active document 
       function WriteText( $Text ) 
       { 
           $this->handle->Selection->Typetext( $Text ); 
       } 

       // Write text at specified bookmark 
       function WriteBookmarkText( $Bookmark ,$Text ) 
       { 
    $bookmarkname = $Bookmark; 
    $objBookmark = $this->handle->ActiveDocument->Bookmarks($bookmarkname); 
    $range = $objBookmark->Range; 
    $range->Text = "this is test bhawdeep"; 
       } 
    
       // Number of documents open 
       function DocumentCount() 
       { 
           return $this->handle->Documents->Count; 
       } 
       
       // Save document as another file and/or format 
       function SaveAs($File, $Format = 0 ) 
       { 
           $this->handle->ActiveDocument->SaveAs($File, $Format); 
       } 
       
       // Save active document 
       function Save() 
       { 
           $this->handle->ActiveDocument->Save(); 
       } 
       
       // close active document. 
       function Close() 
       { 
           $this->handle->ActiveDocument->Close(); 
       } 
       
       // Get word version 
       function GetVersion() 
       { 
           return $this->handle->Version; 
       } 
       
       // get handle to word 
       function GetHandle() 
       { 
           return $this->handle; 
       } 
   
       // Clean up instance with word 
       function Quit() 
       { 
           if( $this->handle ) 
           { 
               // close word 
    try  
    { 
               $this->handle->Quit(); 
   
               // free the object 
               $this->handle->Release(); 
               $this->handle = null; 
    } catch ( Exception $e ) {} 
           } 
       } 
   }; 
?>  
