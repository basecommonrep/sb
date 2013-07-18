<?
  define("TMImageTemplatePath", "//ksc/tmi/");    
  define("PPImageTemplatePath", "//ksc/ppi/");    
  define("INVDocsTemplatePath", "//ksc/dochtm/");    
  define("RarProgPath", "d:/server/project/rar/");
  
  define("connType", ""); // "" - mssql_connect, "odbc" - odnc_connect
  define("isDiskBul", "no"); 
  define("isInvDocFromDb", "yes"); // встановлює джерело завантаження документів для винаходів: yes - завантажуються з БД, no - з диску за шляхом INVDocsTemplatePath
  
  // sourcehost, sourcelogin, sourcepass, sourcedbname - сервер, где формируется база данных.
  // используются для получения даты актуализации.
  
  $connection = array(
						invc => array(
 									'host' => '10.10.16.4', 'login' => 'ndcpe', 'pass'	=> 'ipro', 'dbname' => 'SINV',
									//'host' => 'asdb', 'login' => 'alexey', 'pass'	=> '1', 'dbname' => 'wellknownmarks',
 									'sourcehost' => 'asdbin\\asdbin_2005', 'sourcelogin' => 'alexey', 'sourcepass'	=> 'alexey', 'sourcedbname' => 'SINV2'
  									),
  									
						inv => array(
 									'host' => '10.10.16.4', 'login' => 'ndcpe', 'pass'	=> 'ipro', 'dbname' => 'SINV',
 									'sourcehost' => 'asdbin\\asdbin_2005', 'sourcelogin' => 'alexey', 'sourcepass'	=> 'alexey', 'sourcedbname' => 'SINV2'
									),

						invd => array(
 									'host' => '10.10.16.4', 'login' => 'ndcpe', 'pass'	=> 'ipro', 'dbname' => 'SINV',
 									'sourcehost' => 'asdbin\\asdbin_2005', 'sourcelogin' => 'alexey', 'sourcepass'	=> 'alexey', 'sourcedbname' => 'SINV2'
									),

						invdu => array(
 									'host' => '10.10.16.4', 'login' => 'ndcpe', 'pass'	=> 'ipro', 'dbname' => 'SINV',
 									'sourcehost' => 'asdbin\\asdbin_2005', 'sourcelogin' => 'alexey', 'sourcepass'	=> 'alexey', 'sourcedbname' => 'SINV2'		
  									),
						pp => array(
  									'host' => '10.10.16.4', 'login' => 'ndcpe', 'pass'	=> 'ipro', 'dbname' => 'SPP',
 									'sourcehost' => 'asdb', 'sourcelogin' => 'alexey', 'sourcepass'	=> '1', 'sourcedbname' => 'SPP2' 
  									),

						pp2 => array(
  									'host' => '10.10.16.4', 'login' => 'ndcpe', 'pass'	=> 'ipro', 'dbname' => 'SPP',
 									'sourcehost' => 'asdb', 'sourcelogin' => 'alexey', 'sourcepass'	=> '1', 'sourcedbname' => 'SPP2' 
  									),

						tm => array(
  									'host' => '10.10.16.4', 'login' => 'ndcpe', 'pass'	=> 'ipro', 'dbname' => 'STM',
 									'sourcehost' => 'asdb', 'sourcelogin' => 'alexey', 'sourcepass'	=> '1', 'sourcedbname' => 'STM2' 
  									),

						tm2 => array(
  									'host' => '10.10.16.4', 'login' => 'ndcpe', 'pass'	=> 'ipro', 'dbname' => 'STM',
 									'sourcehost' => 'asdb', 'sourcelogin' => 'alexey', 'sourcepass'	=> '1', 'sourcedbname' => 'STM2' 
  									),
						madrid => array(
									'host' => '10.10.16.4', 'login' => 'ndcpe', 'pass'	=> 'ipro', 'dbname' => 'sromarin',
 									'sourcehost' => 'asdb', 'sourcelogin' => 'alexey', 'sourcepass'	=> '1', 'sourcedbname' => 'SROMARIN2' 
  									),

						wkm => array(
 									'host' => '10.10.16.4', 'login' => 'ndcpe', 'pass'	=> 'ipro', 'dbname' => 'wellknownmarks',
									//'host' => 'asdb', 'login' => 'alexey', 'pass'	=> '1', 'dbname' => 'wellknownmarks',
 									'sourcehost' => 'asdb', 'sourcelogin' => 'alexey', 'sourcepass'	=> '1', 'sourcedbname' => 'wellknownmarks' 
  									),

						geo => array(
 									'host' => '10.10.16.4', 'login' => 'ndcpe', 'pass'	=> 'ipro', 'dbname' => 'sgeographic',
 									'sourcehost' => 'asdbin\\asdbin_2005', 'sourcelogin' => 'alexey', 'sourcepass'	=> 'alexey', 'sourcedbname' => 'sgeographic2'
									),  									

						official => array(
  									'host' => '10.10.16.4', 'login' => 'ndcpe', 'pass'	=> 'ipro', 'dbname' => 'AccBul_New',
 									'sourcehost' => 'asdb', 'sourcelogin' => 'alexey', 'sourcepass'	=> '1', 'sourcedbname' => 'wellknownmarks' 
  									),

						materials => array(
 									'host' => '10.10.16.4', 'login' => 'ndcpe', 'pass'	=> 'ipro', 'dbname' => 'inet_data_docs'
									),
						
						// налаштування для бд "міжнародні реєстрації знаків для товарів і послуг"
						madridall => array(
 									'host' => '10.10.16.4', 'login' => 'ndcpe', 'pass'	=> 'ipro', 'dbname' => 'romarin_2',
 									'sourcehost' => 'asdb', 'sourcelogin' => 'alexey', 'sourcepass'	=> '1', 'sourcedbname' => 'romarin_2' 
									),
						tmc => array(
 									'host' => '10.10.16.4', 'login' => 'ndcpe', 'pass'	=> 'ipro', 'dbname' => 'STM',
 									'sourcehost' => 'asdb', 'sourcelogin' => 'alexey', 'sourcepass'	=> '1', 'sourcedbname' => 'STM2' 
									),
	  				);

	$actualization_connection = array(
									'host' => '10.10.16.4', 'login' => 'ndcpe', 'pass'	=> 'ipro', 'dbname' => 'BackupDB'
						);


?>
