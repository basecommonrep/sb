<?
	/*
	$xslt = xslt_create();
	
	$stylesheetfile = 'images/madridall/rom_01.xsl';
	$sourcefile = 'tempdocs/xml_35.xml';

	$sourcehandle = fopen($sourcefile, "r");
	$source = fread($sourcehandle, filesize($sourcefile));
	
    $stylesheethandle = fopen($stylesheetfile, "r");
    $stylesheet = fread($stylesheethandle, filesize($stylesheetfile));
    
    $xml = $source;
    $xsl = $stylesheet;

	$arguments = array(
    '/_xml' => $xml,
    '/_xsl' => $xsl
    );

	$res = xslt_process($xslt,'arg:/_xml', 'arg:/_xsl', NULL, $arguments);
	
	xslt_free($xslt);
	*/
	
	$xslt = xslt_create();

	$stylesheetfile = 'images/madridall/rom_01.xsl';
	$sourcefile = 'tempdocs/xml_35.xml';

	$sourcehandle = fopen($sourcefile, "r");
	$xml = fread($sourcehandle, filesize($sourcefile));
	
    $stylesheethandle = fopen($stylesheetfile, "r");
    $xsl = fread($stylesheethandle, filesize($stylesheetfile));
    
	$arguments = array(
    '/_xml' => $xml,
    '/_xsl' => $xsl
    );

	$res = xslt_process($xslt,'arg:/_xml', 'arg:/_xsl', NULL, $arguments);
	
	xslt_free($xslt);	
	
	print($res);
	
?>
