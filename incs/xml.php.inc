<?php

/* Usage
 Grab some XML data, either from a file, URL, etc. however you want. Assume storage in $strYourXML;

 $objXML = new xml2Array();
 $arrOutput = $objXML->parse($strYourXML);
 print_r($arrOutput); //print it out, or do whatever!
  
*/
class xml2Array {
    
    var $arrOutput = array();
    var $resParser;
    var $strXmlData;
    
    function parse($strInputXML) {
   
            $strInputXML = utf8_encode($strInputXML);
            
			$this->resParser = xml_parser_create();
            
            xml_set_object($this->resParser,$this);
            xml_set_element_handler($this->resParser, "tagOpen", "tagClosed");
            
            xml_set_character_data_handler($this->resParser, "tagData");
            
            //xml_parser_set_option ($this->resParser, XML_OPTION_TARGET_ENCODING, 'ISO-8859-1');
        
            $this->strXmlData = xml_parse($this->resParser, $strInputXML );
            if(!$this->strXmlData) 
               sprintf("XML error: %s at line %d", xml_error_string(xml_get_error_code($this->resParser)), xml_get_current_line_number($this->resParser));
                            
            xml_parser_free($this->resParser);
            
            //print_r($this->arrOutput);
            
			return $this->arrOutput;
    }
    function tagOpen($parser, $name, $attrs) {
       $tag=array("name"=>$name,"attrs"=>$attrs); 
       array_push($this->arrOutput,$tag);
    }
    
    function tagData($parser, $tagData) {
       if(trim($tagData)) {
            if(isset($this->arrOutput[count($this->arrOutput)-1]['tagData'])) {
                $this->arrOutput[count($this->arrOutput)-1]['tagData'] .= $tagData;
            } 
            else {
                $this->arrOutput[count($this->arrOutput)-1]['tagData'] = $tagData;
            }
       }
    }
    
    function tagClosed($parser, $name) {
       $this->arrOutput[count($this->arrOutput)-2]['children'][] = $this->arrOutput[count($this->arrOutput)-1];
       array_pop($this->arrOutput);
    }
    
    function clearXML()
    {
	    $this->arrOutput = array();
    	$this->resParser = '';
    	$this->strXmlData = '';
    }
}
?>

<?

/*
//$parser = xml_parser_create ("UTF-8");
//print($parser);
$xmlRaw='<xml><patentnumber isreestr="Y" isdop="N" isspov="Y">7345</patentnumber><inputnumber isreestr="Y" isdop="N" isspov="Y">20041209907</inputnumber><inid_72 isreestr="N" isdop="Y" isspov="N">Козьолкін Олександр Анатолійович, Нерянова Юлія Миколаївна, Нікуліна Римма Петрівна</inid_72><inid_98 isreestr="Y" isdop="N" isspov="N">Медичний університет, патентний відділ, пр. Маяковського, буд. 26, м. Запоріжжя, 69035, Україна</inid_98><reason>[Р21] КД про внесення змін у склад винахідників на підставі заяви власника від 13.02.2006 № 1564/п</reason></xml>';
// here are the xml field names
$xmlFieldNames=array(
	TERRITORIES, RIGHTS, REASON, PATENTNUMBER, LICENSIATS, LICENSIARS, LICENSETYPE, INPUTNUMBER, INID_98, INID_74, INID_73,
	INID_72, INID_71, INID_57, INID_54, INID_51, INID_11, INID_11, DURATION, DATEPLANSTOP, DATEFACTSTOP, DATE, 
	COURTNAME, COURTDOCNUMBER, COURTDOCDATE, CONTRACTNUMBER, CONTRACTDATE, BULLETIN
);

// for each xml field...
foreach ($xmlFieldNames as $xmlField) {
	$xmlField = strtolower($xmlField);
    if(strpos($xmlRaw,$xmlField)!==false){
        // I've broken 1 single line into 4 for display purposes
        $parsedXML[$xmlField]=substr($xmlRaw,
        strpos($xmlRaw,"<$xmlField>")+strlen("<$xmlField>"),
        strpos($xmlRaw,"</$xmlField>")-strlen("<$xmlField>")
        -strpos($xmlRaw,"<$xmlField>"));
    }
}
//print_r($parsedXML);

print('<br>');

$objXML = new xml2Array();
$arrOutput = $objXML->parse($xmlRaw);
print_r($arrOutput); //print it out, or do whatever!
*/
?>
