<?
	$LANG_SETTINGS = $GLOBALS['LANG_SETTINGS'];
	
	$claimsPerPageList = array(10, 30, 50, 200);
	
	$in_var_names = array(
						'action', 
						'dbname', 
						'newsearchdbname',
						'page', 
						'section', 
						'claimsperpage', 
						'newclaimsperpage',
						'newviewbulnumb',
						'lang',
						'newinfound',
						'from',
						'print',
						'sortby'
					);

	$actions = array(
					'setsearchcond', 
					'viewbul', 
					'viewsearchres', 
					'sortres', 
					'search', 
					'changelang', 
					'changedb', 
					'changebulnumb',
					'viewdetails',
					'viewhelp',
					'sort',
					'viewnotices'
					);
					
	$dict_actions = array(
					'viewdict',
					'searchdict',
					);

	$basket_actions = array(
					'viewbasket',
					'addtobasket',
					'deletefrombasket',
					'clearbasket'
					);


	$db_names = array(
						'invc' 		=> $LANG_SETTINGS['menu']['invc'], 
						'inv' 		=> $LANG_SETTINGS['menu']['inv'], 
						'invd' 		=> $LANG_SETTINGS['menu']['invd'], 
						'invdu' 	=> $LANG_SETTINGS['menu']['invdu'], 
						'pp'		=> $LANG_SETTINGS['menu']['pp'], 
						'pp2'		=> $LANG_SETTINGS['menu']['pp'], 
						'tm'		=> $LANG_SETTINGS['menu']['tm'], 
            'tm2'		=> $LANG_SETTINGS['menu']['tm'],
						//'geo' 		=> $LANG_SETTINGS['menu']['geo'], 
						'madrid' 	=> $LANG_SETTINGS['menu']['madrid'], 
						'wkm'		=> $LANG_SETTINGS['menu']['wkm'],
						//'madridall'	=> $LANG_SETTINGS['interface']['madridall_cert'],
						'tmc'	=> $LANG_SETTINGS['interface']['tmc'],
						'official'	=> $LANG_SETTINGS['menu']['official'],
						'geoc'	=> $LANG_SETTINGS['menu']['geoc'],
						'geo'	=> $LANG_SETTINGS['menu']['geo'],
						'geor'	=> $LANG_SETTINGS['menu']['geor'],
					);



	$view_sections_list = array(
							'allclaims',
							'ipcindexes',
							'A', 
							'B', 
							'C', 
							'D', 
							'E', 
							'F', 
							'G', 
							'H', 
							'syst', 
							'numc', 
							'nump', 
							'numpussr', 
							'numcert'
							);

	$index_sections = array(
							'syst', 
							'numc', 
							'nump', 
							'numpussr', 
							'numcert', 
							'notice'
							);

	$special_queries = array(
		'invc' => array(
						NBUL 	=> 'select distinct t_nbul.idClaim '.
								   		'from publication t_nbul '.
								   		'###JOINQUERY### '.
										'where (t_nbul.typePub=2 AND ###WHEREEXPR###)',

						PPUBL 	=> 'select distinct t_ppubl.idClaim '.
								   		'from publication t_ppubl '.
								   		'###JOINQUERY### '.
										'where (t_ppubl.typePub=2 AND ###WHEREEXPR###)',

						NPRIOR 	=> 'select distinct t_nprior.idClaim '.
								   		'from convent t_nprior '.
								   		'###JOINQUERY### '.
										'where (t_nprior.code=31 AND ###WHEREEXPR###)',

						DPRIOR 	=> 'select distinct t_dprior.idClaim '.
								   		'from convent t_dprior '.
								   		'###JOINQUERY### '.
										'where (t_dprior.code=31 AND ###WHEREEXPR###)',

						MPK 	=> 'select distinct t_mpk.idClaim '.
								   		'from claim51publ t_mpk '.
								   		'###JOINQUERY### '.
										'where (t_mpk.level=\'A\' AND ###WHEREEXPR###)',

						APP 	=> 'select distinct t_app.idClaim '.
								   		'from claim71 t_app '.
								   		'###JOINQUERY### '.
										'where (t_app.lang=\'UA\' AND ###WHEREEXPR###)',

						INV 	=> 'select distinct t_inv.idClaim '.
								   		'from claim72 t_inv '.
								   		'###JOINQUERY### '.
										'where (t_inv.lang=\'UA\' AND ###WHEREEXPR###)',

						TITLE 	=> 'select distinct t_title.idClaim '.
								   		'from claim54 t_title '.
								   		'###JOINQUERY### '.
										'where (t_title.lang=\'UA\' AND ###WHEREEXPR###)'
		),

		'inv' => array(
						NBUL 	=> 'select distinct t_nbul.idClaim '.
								   		'from publication t_nbul '.
								   		'###JOINQUERY### '.
										'where (t_nbul.typePub in (3,7,11,14,36) AND ###WHEREEXPR###)',

						PPUBL 	=> 'select distinct t_ppubl.idClaim '.
								   		'from publication t_ppubl '.
								   		'###JOINQUERY### '.
										'where (t_ppubl.typePub in (3,7,11,36) AND ###WHEREEXPR###)',

						NPRIOR 	=> 'select distinct t_nprior.idClaim '.
								   		'from convent t_nprior '.
								   		'###JOINQUERY### '.
										'where (t_nprior.code=31 AND ###WHEREEXPR###)',

						DPRIOR 	=> 'select distinct t_dprior.idClaim '.
								   		'from convent t_dprior '.
								   		'###JOINQUERY### '.
										'where (t_dprior.code=31 AND ###WHEREEXPR###)',

						MPK 	=> 'select distinct t_mpk.idClaim '.
								   		'from claim51publ t_mpk '.
								   		'###JOINQUERY### '.
										'where (t_mpk.level=\'A\' AND ###WHEREEXPR###)',

						INV 	=> 'select distinct t_inv.idClaim '.
								   		'from claim72 t_inv '.
								   		'###JOINQUERY### '.
										'where (t_inv.lang=\'UA\' AND ###WHEREEXPR###)',

						PROP 	=> 'select distinct t_prop.idClaim '.
								   		'from claim73 t_prop '.
								   		'###JOINQUERY### '.
										'where (t_prop.lang=\'UA\' AND ###WHEREEXPR###)',

						TITLE 	=> 'select distinct t_title.idClaim '.
								   		'from claim54 t_title '.
								   		'###JOINQUERY### '.
										'where (t_title.lang=\'UA\' AND ###WHEREEXPR###)'
		),

		'invd' => array(
						NBUL 	=> 'select distinct t_nbul.idClaim '.
								   		'from publication t_nbul '.
								   		'###JOINQUERY### '.
										'where (t_nbul.typePub in (3,7,11,14,36) AND ###WHEREEXPR###)',

						PPUBL 	=> 'select distinct t_ppubl.idClaim '.
								   		'from publication t_ppubl '.
								   		'###JOINQUERY### '.
										'where (t_ppubl.typePub in (3,7,11,36) AND ###WHEREEXPR###)',

						NPRIOR 	=> 'select distinct t_nprior.idClaim '.
								   		'from convent t_nprior '.
								   		'###JOINQUERY### '.
										'where (t_nprior.code=31 AND ###WHEREEXPR###)',

						DPRIOR 	=> 'select distinct t_dprior.idClaim '.
								   		'from convent t_dprior '.
								   		'###JOINQUERY### '.
										'where (t_dprior.code=31 AND ###WHEREEXPR###)',

						MPK 	=> 'select distinct t_mpk.idClaim '.
								   		'from claim51publ t_mpk '.
								   		'###JOINQUERY### '.
										'where (t_mpk.level=\'A\' AND ###WHEREEXPR###)',

						INV 	=> 'select distinct t_inv.idClaim '.
								   		'from claim72 t_inv '.
								   		'###JOINQUERY### '.
										'where (t_inv.lang=\'UA\' AND ###WHEREEXPR###)',

						PROP 	=> 'select distinct t_prop.idClaim '.
								   		'from claim73 t_prop '.
								   		'###JOINQUERY### '.
										'where (t_prop.lang=\'UA\' AND ###WHEREEXPR###)',

						TITLE 	=> 'select distinct t_title.idClaim '.
								   		'from claim54 t_title '.
								   		'###JOINQUERY### '.
										'where (t_title.lang=\'UA\' AND ###WHEREEXPR###)'
		),

		'invdu' => array(
						NBUL 	=> 'select distinct t_nbul.idClaim '.
								   		'from publication t_nbul '.
								   		'###JOINQUERY### '.
										'where (t_nbul.typePub in (3,7,11,14,36) AND ###WHEREEXPR###)',

						PPUBL 	=> 'select distinct t_ppubl.idClaim '.
								   		'from publication t_ppubl '.
								   		'###JOINQUERY### '.
										'where (t_ppubl.typePub in (3,7,11,36) AND ###WHEREEXPR###)',

						NPRIOR 	=> 'select distinct t_nprior.idClaim '.
								   		'from convent t_nprior '.
								   		'###JOINQUERY### '.
										'where (t_nprior.code=31 AND ###WHEREEXPR###)',

						DPRIOR 	=> 'select distinct t_dprior.idClaim '.
								   		'from convent t_dprior '.
								   		'###JOINQUERY### '.
										'where (t_dprior.code=31 AND ###WHEREEXPR###)',

						MPK 	=> 'select distinct t_mpk.idClaim '.
								   		'from claim51publ t_mpk '.
								   		'###JOINQUERY### '.
										'where (t_mpk.level=\'A\' AND ###WHEREEXPR###)',

						INV 	=> 'select distinct t_inv.idClaim '.
								   		'from claim72 t_inv '.
								   		'###JOINQUERY### '.
										'where (t_inv.lang=\'UA\' AND ###WHEREEXPR###)',

						PROP 	=> 'select distinct t_prop.idClaim '.
								   		'from claim73 t_prop '.
								   		'###JOINQUERY### '.
										'where (t_prop.lang=\'UA\' AND ###WHEREEXPR###)',

						TITLE 	=> 'select distinct t_title.idClaim '.
								   		'from claim54 t_title '.
								   		'###JOINQUERY### '.
										'where (t_title.lang=\'UA\' AND ###WHEREEXPR###)'
		),

		'pp' => array(
		),


		'tm' => array(
						NBUL 	=> 'select distinct t_nbul.idClaim '.
										'from claim450 t_nbul '.
							   			'inner join ( '.
							   			'select distinct t_nbul.BulletinDate '.
										'	from ref_bulletins t_nbul '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.BulletinDate=t_nbul.BulletinDate'.										
								   		'###JOINQUERY### ',										
				
						DVISTAV => 'select distinct t_dvistav.idClaim '.
							   			'from claim230 t_dvistav '.
							   			'inner join ( '.
							   			'select distinct t_dvistav.idExhibition '.
										'	from ref_exhibitions t_dvistav '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.idExhibition=t_dvistav.idExhibition'.
								   		'###JOINQUERY### ',

						CVISTAV => 'select distinct t_cvistav.idClaim '.
							   			'from claim230 t_cvistav '.
							   			'inner join ( '.
							   			'select distinct c.idExhibition '.
										'	from ref_exhibitions c '.
										'	inner join ref_country t_cvistav on c.idCountry=t_cvistav.idCountry '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.idExhibition=t_cvistav.idExhibition'.
								   		'###JOINQUERY### ',

						PARISN 	=> 'select distinct t_parisn.idClaim '.
							   			'from claim310 t_parisn '.
							   			'inner join ( '.
							   			'select distinct t_parisn.idPriorityClaim '.
										'	from ref_priorityClaims t_parisn '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.idPriorityClaim=t_parisn.idPriorityClaim'.
								   		'###JOINQUERY### ',

						PARISD 	=> 'select distinct t_parisd.idClaim '.
							   			'from claim310 t_parisd '.
							   			'inner join ( '.
							   			'select distinct t_parisd.idPriorityClaim '.
										'	from ref_priorityClaims t_parisd '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.idPriorityClaim=t_parisd.idPriorityClaim'.
								   		'###JOINQUERY### ',


						VIENNA 	=> 'select distinct t_vienna.idClaim '.
							   			'from claim546 t_vienna '.
							   			'inner join ( '.
							   			'select distinct i.idImage '.
										'	from ref_VienClasses t_vienna '.
										'	inner join ImageVienClasses i on i.idVienClass=t_vienna.idVienClass '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.idImage=t_vienna.idImage '.
								   		'###JOINQUERY### ',
										   

						COLORS 	=> 'select distinct t_colors.idClaim '.
							   			'from claim591 t_colors '.
							   			'inner join ( '.
							   			'select distinct t_colors.idColor '.
										'	from ref_colors t_colors '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.idColor=t_colors.idColor'.
								   		'###JOINQUERY### ',

		),

		'madrid' => array(
		),

		'wkm' => array(
						NBUL 	=> 'select distinct t_nbul.idMark '.
							   			'from mark t_nbul '.
							   			'inner join ( '.
							   			'select distinct t_nbul.idBulletin '.
										'	from ref_bulletins t_nbul '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.idBulletin=t_nbul.idBulletin '.
								   		'###JOINQUERY### ',

						PUBL 	=> 'select distinct t_publ.idMark '.
							   			'from mark t_publ '.
							   			'inner join ( '.
							   			'select distinct t_publ.idBulletin '.
										'	from ref_bulletins t_publ '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.idBulletin=t_publ.idBulletin '.
								   		'###JOINQUERY### ',

						PROP 	=> 'select distinct t_prop.idMark '.
							   			'from markOwners t_prop '.
							   			'inner join ( '.
							   			'select distinct t_prop.idOwner '.
										'	from ref_owners t_prop '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.idOwner=t_prop.idOwner '.
								   		'###JOINQUERY### ',
		),
		
		'madridall' => array(
		),


		'tmc' => array(
						DVISTAV => 'select distinct t_dvistav.idClaim '.
							   			'from claim230 t_dvistav '.
							   			'inner join ( '.
							   			'select distinct t_dvistav.idExhibition '.
										'	from ref_exhibitions t_dvistav '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.idExhibition=t_dvistav.idExhibition'.
								   		'###JOINQUERY### ',

						CVISTAV => 'select distinct t_cvistav.idClaim '.
							   			'from claim230 t_cvistav '.
							   			'inner join ( '.
							   			'select distinct c.idExhibition '.
										'	from ref_exhibitions c '.
										'	inner join ref_country t_cvistav on c.idCountry=t_cvistav.idCountry '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.idExhibition=t_cvistav.idExhibition'.
								   		'###JOINQUERY### ',

						PARISN 	=> 'select distinct t_parisn.idClaim '.
							   			'from claim310 t_parisn '.
							   			'inner join ( '.
							   			'select distinct t_parisn.idPriorityClaim '.
										'	from ref_priorityClaims t_parisn '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.idPriorityClaim=t_parisn.idPriorityClaim'.
								   		'###JOINQUERY### ',

						PARISD 	=> 'select distinct t_parisd.idClaim '.
							   			'from claim310 t_parisd '.
							   			'inner join ( '.
							   			'select distinct t_parisd.idPriorityClaim '.
										'	from ref_priorityClaims t_parisd '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.idPriorityClaim=t_parisd.idPriorityClaim'.
								   		'###JOINQUERY### ',
						
						PARISC 	=> 'select distinct t_parisc.idClaim '.
							   			'from claim310 t_parisc '.
							   			'inner join ( '.
							   			'select distinct c.idPriorityClaim '.
										'	from ref_priorityClaims c '.
										'	inner join ref_Country t_parisc on c.idCountry = t_parisc.idCountry '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.idPriorityClaim=t_parisc.idPriorityClaim'.
								   		'###JOINQUERY### ',


						VIENNA 	=> 'select distinct t_vienna.idClaim '.
							   			'from claim546 t_vienna '.
							   			'inner join ( '.
							   			'select distinct i.idImage '.
										'	from ref_VienClasses t_vienna '.
										'	inner join ImageVienClasses i on i.idVienClass=t_vienna.idVienClass '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.idImage=t_vienna.idImage '.
								   		'###JOINQUERY### ',
										   

						COLORS 	=> 'select distinct t_colors.idClaim '.
							   			'from claim591 t_colors '.
							   			'inner join ( '.
							   			'select distinct t_colors.idColor '.
										'	from ref_colors t_colors '.
										'	where (###WHEREEXPR###) '.
										') rc on rc.idColor=t_colors.idColor'.
								   		'###JOINQUERY### ',

		),

		
	);

	$params_table_content = array(
	/*
	[КОД БД] => (
	[ІМ'Я ПОЛЯ] => ([ТИП ПОЛЯ], 
					[ИМЯ ТАБЛИЦЫ], 
					[ИМЯ ПОЛЯ В ТАБЛИЦЕ], 
					[НАЗВАНИЕ ПОЛЯ], 
					[КОД INID ПОЛЯ], 
					[ПРИМЕР ЗАПРОСА], 
					[ПОЛЕ ОДИН-КО-МНОГИМ?],
					[ТИП ВЫРАВНИВАНИЯ В СЛОВАРИКЕ],
					[КОД ПОЛЯ В INET_STATISTICS..QUERIES]
					)
				)
	*/	
		// Відомості про заявки на винаходи, які прийняті до розгляду
		'invc' => array(
						NBUL 	=> array(2, 'publication',	'bullStr',		$LANG_SETTINGS['inv_fields']['NBUL'], 	41, '6/2006', 						0, center, 	201),
						PPUBL 	=> array(3, 'publication',	'bulletinDate',	$LANG_SETTINGS['inv_fields']['PUBL'], 	41, '15.07.2002', 					0, center, 	202),
						NC 		=> array(2, 'maininfo',		'i_21',			$LANG_SETTINGS['inv_fields']['NC'], 	21, '20040706122', 					0, center, 	203),
						FD 		=> array(3, 'maininfo',		'i_22',			$LANG_SETTINGS['inv_fields']['FD'], 	22, '21.01.2008', 					0, center, 	204),
						NPRIOR 	=> array(2, 'convent',		'inputNumber',	$LANG_SETTINGS['inv_fields']['NPRIOR'],	31, '08/780,025', 					0, center, 	205),
						DPRIOR 	=> array(3, 'convent',		'appDate',		$LANG_SETTINGS['inv_fields']['DPRIOR'],	32, '07.11.2006', 					0, center, 	206),
						MPK 	=> array(2, 'claim51publ',	'ipc_string',	$LANG_SETTINGS['inv_fields']['MPK'], 	51, 'F16J 15/34', 					1, center, 	207),
						PCTDN	=> array(3, 'maininfo',		'i_85',			$LANG_SETTINGS['inv_fields']['PCTDN'], 	85, '21.01.2008', 					0, center, 	204),
						PCTN 	=> array(2, 'maininfo',		'pctnumber',	$LANG_SETTINGS['inv_fields']['PCTN'], 	86, 'PCT/EP97/03841',				0, center, 	208),
						PCTD 	=> array(3, 'maininfo',		'pctdate',		$LANG_SETTINGS['inv_fields']['PCTD'], 	86, '24.07.2006', 					0, center, 	209),
						APP 	=> array(2, 'claim71',		'name',			$LANG_SETTINGS['inv_fields']['APP'], 	71, 'МЕТАЛУРГІЙНИЙ КОМБІНАТ', 		0, left, 	210),
						INV 	=> array(2, 'claim72',		'name',			$LANG_SETTINGS['inv_fields']['INV'], 	72, 'Бойко Володимир Семенович',	0, left, 	211),
						TITLE 	=> array(2, 'claim54',		'i_54',			$LANG_SETTINGS['inv_fields']['TITLE'], 	54, 'спосіб виробництва', 			0, left,	212),						
						),
	
		// Відомості про видачу патентів України на винаходи
		'inv'  => array(
						NBUL 	=> array(2, 'publication',	'bullStr',		$LANG_SETTINGS['inv_fields']['NBUL'], 	46, '7/2006', 						0, center,	301),
						PPUBL 	=> array(3, 'publication',	'bulletinDate',	$LANG_SETTINGS['inv_fields']['PPUBL'],	46, '17.04.2006', 					0, center,	302),
						UPN 	=> array(2, 'maininfo',		'ussrac',		$LANG_SETTINGS['inv_fields']['UPN'], 	10, '1437039', 						0, center,	303),
						NP 		=> array(1, 'maininfo',		'i_11',			$LANG_SETTINGS['inv_fields']['NP'], 	11, '75556', 						0, center,	304),
						DATECOM => array(3, 'maininfo',		'rightsDate',	$LANG_SETTINGS['inv_fields']['DATECOM'],24, '17.04.2006', 					0, center,	305),
						NC 		=> array(2, 'maininfo',		'i_21',			$LANG_SETTINGS['inv_fields']['NC'], 	21, '2003098763',					0, center,	306),
						FD 		=> array(3, 'maininfo',		'i_22',			$LANG_SETTINGS['inv_fields']['FD'], 	22, '30.03.2005', 					0, center,	307),
						NPRIOR 	=> array(2, 'convent',		'inputNumber',	$LANG_SETTINGS['inv_fields']['NPRIOR'],	31, '06254102.4', 					0, center,	308),
						DPRIOR 	=> array(3, 'convent',		'appDate',		$LANG_SETTINGS['inv_fields']['DPRIOR'],	32, '04.08.2006', 					0, center,	309),
						MPK 	=> array(2, 'claim51publ',	'ipc_string',	$LANG_SETTINGS['inv_fields']['MPK'], 	51, 'C30B 29/20', 					1, center,	310),
						PCTN 	=> array(2, 'maininfo',		'pctnumber',	$LANG_SETTINGS['inv_fields']['PCTN'], 	86, 'PCT/CU02/00003', 				0, center,	311),
						PCTD 	=> array(3, 'maininfo',		'pctdate',		$LANG_SETTINGS['inv_fields']['PCTD'], 	86, '24.01.2003', 					0, center,	312),
						//ANALOG 	=> array(2, 'analog',		'text',			$LANG_SETTINGS['inv_fields']['ANALOG'], 56, 'US 5263835',					1, left,	313),
						INV 	=> array(2, 'claim72',		'name',			$LANG_SETTINGS['inv_fields']['INV'], 	72, 'Швець Іван Софронович', 		0, left,	314),
						PROP 	=> array(2, 'claim73',		'name',			$LANG_SETTINGS['inv_fields']['PROP'], 	73, 'Лі Юанхе', 					0, left,	315),
						TITLE 	=> array(2, 'claim54',		'i_54',			$LANG_SETTINGS['inv_fields']['TITLE'], 	54, 'електричний конденсатор', 		0, left,	316),
						),
	
		// Відомості про видачу деклараційних патентів України на винаходи
		'invd' => array(
//						UPN 	=> array(2, 'maininfo',		'ussrac',		$LANG_SETTINGS['inv_fields']['UPN'], 	10, '1437039', 						0, center,	401),
						NBUL 	=> array(2, 'publication',	'bullStr',		$LANG_SETTINGS['inv_fields']['NBUL'], 	46, '19/2007', 						0, center,	402),
						PPUBL 	=> array(3, 'publication',	'bulletinDate',	$LANG_SETTINGS['inv_fields']['PPUBL'],	46, '26.11.2007', 					0, center,	403),
						NP 		=> array(1, 'maininfo',		'i_11',			$LANG_SETTINGS['inv_fields']['NP'], 	11, '80942', 						0, center,	404),
						DATECOM => array(3, 'maininfo',		'rightsDate',	$LANG_SETTINGS['inv_fields']['DATECOM'],24, '26.11.2007', 					0, center,	405),
						NC 		=> array(2, 'maininfo',		'i_21',			$LANG_SETTINGS['inv_fields']['NC'], 	21, '20031211485', 					0, center,	406),
						FD 		=> array(3, 'maininfo',		'i_22',			$LANG_SETTINGS['inv_fields']['FD'], 	22, '12.12.2003', 					0, center,	407),
						NPRIOR 	=> array(2, 'convent',		'inputNumber',	$LANG_SETTINGS['inv_fields']['NPRIOR'],	31, '06254102.4', 					0, center,	408),
						DPRIOR 	=> array(3, 'convent',		'appDate',		$LANG_SETTINGS['inv_fields']['DPRIOR'],	32, '04.08.2006', 					0, center,	409),
						MPK 	=> array(2, 'claim51publ',	'ipc_string',	$LANG_SETTINGS['inv_fields']['MPK'], 	51, 'G01G 13/00', 					1, center,	410),
						//PCTN 	=> array(2, 'maininfo',		'pctnumber',	$LANG_SETTINGS['inv_fields']['PCTN'], 	86, 'PCT/CU02/00003',				0, center,	411),
						//PCTD 	=> array(3, 'maininfo',		'pctdate',		$LANG_SETTINGS['inv_fields']['PCTD'], 	86, '24.01.2003', 					0, center,	412),
						//ANALOG 	=> array(2, 'analog',	'text',			$LANG_SETTINGS['inv_fields']['ANALOG'], 56, 'SU 716711', 					1, left,	413),
						INV 	=> array(2, 'claim72',		'name',			$LANG_SETTINGS['inv_fields']['INV'], 	72, 'Браз Давид Леонідович', 		0, left,	414),
						PROP 	=> array(2, 'claim73',		'name',			$LANG_SETTINGS['inv_fields']['PROP'], 	73, 'ТОВАРИСТВО ОЛМА', 				0, left,	415),
						TITLE 	=> array(2, 'claim54',		'i_54',			$LANG_SETTINGS['inv_fields']['TITLE'], 	54, 'бункерні ваги', 				0, left,	416),
						),
		
		// 	Відомості про видачу деклараційних патентів України на корисні моделі			
		'invdu' => array(
						NBUL 	=> array(2, 'publication',	'bullStr',		$LANG_SETTINGS['inv_fields']['NBUL'], 	46, '12/2006', 				0, center,	501),
//						UPN 	=> array(2, 'maininfo',		'ussrac',		$LANG_SETTINGS['inv_fields']['UPN'], 	10, '1437039', 				0, center,	502),
						PPUBL 	=> array(3, 'publication',	'bulletinDate',	$LANG_SETTINGS['inv_fields']['PPUBL'],	46, '10.11.2008',			0, center,	503),
						NP 		=> array(1, 'maininfo',		'i_11',			$LANG_SETTINGS['inv_fields']['NP'], 	11, '19344', 				0, center,	504),
						DATECOM => array(3, 'maininfo',		'rightsDate',	$LANG_SETTINGS['inv_fields']['DATECOM'],24, '15.12.2006', 			0, center,	505),
						NC 		=> array(2, 'maininfo',		'i_21',			$LANG_SETTINGS['inv_fields']['NC'], 	21, 'u200606357', 			0, center,	506),
						FD 		=> array(3, 'maininfo',		'i_22',			$LANG_SETTINGS['inv_fields']['FD'], 	22, '08.06.2006', 			0, center,	507),
						NPRIOR 	=> array(2, 'convent',		'inputNumber',	$LANG_SETTINGS['inv_fields']['NPRIOR'],	31, '20077124332', 			0, center,	508),
						DPRIOR 	=> array(3, 'convent',		'appDate',		$LANG_SETTINGS['inv_fields']['DPRIOR'],	32, '28.06.2007', 			0, center,	509),
						MPK 	=> array(2, 'claim51publ',	'ipc_string',	$LANG_SETTINGS['inv_fields']['MPK'], 	51, 'F24J 2/06', 			1, center,	510),
						PCTN 	=> array(2, 'maininfo',		'pctnumber',	$LANG_SETTINGS['inv_fields']['PCTN'], 	86, 'PCT/IB2004/051800', 	0, center,	511),
						PCTD 	=> array(3, 'maininfo',		'pctdate',		$LANG_SETTINGS['inv_fields']['PCTD'], 	86, '20.09.2004', 			0, center,	512),
						ANALOG 	=> array(2, 'analog',		'text',			$LANG_SETTINGS['inv_fields']['ANALOG'], 56, 'AU 374037', 			1, left,	513),
						INV 	=> array(2, 'claim72',		'name',			$LANG_SETTINGS['inv_fields']['INV'], 	72, 'Секей Шандор', 		0, left,	514),
						PROP 	=> array(2, 'claim73',		'name',			$LANG_SETTINGS['inv_fields']['PROP'], 	73, 'Пустаі Ґабор', 		0, left,	515),
						TITLE 	=> array(2, 'claim54',		'i_54',			$LANG_SETTINGS['inv_fields']['TITLEU'], 	54, 'тепловий колектор', 	0, left,	516),
						),
		// Відомості про видачу патентів України на промислові зразки
		'pp' 	=> array(
						NBUL 	=> array(2, 'claim450',		'bullStr',		$LANG_SETTINGS['pp_fields']['NBUL'], 	45, '3/2007', 													0, center,	601),
						PPUBL 	=> array(3, 'claim450',		'bulletindate',	$LANG_SETTINGS['pp_fields']['PPUBL'], 	45, '10.11.2008', 												0, center,	602),
						NUSSR 	=> array(2, 'claim100',		'i_100',		$LANG_SETTINGS['pp_fields']['NUSSR'],	10, '32837', 													0, center,	603),
						TUSSR 	=> array(2, 'claim100',		'guardType',	$LANG_SETTINGS['pp_fields']['TUSSR'],	10, 'A1', 														0, center,	604),
						NP 		=> array(1, 'claim111',		'i_111',		$LANG_SETTINGS['pp_fields']['NP'], 		11, '13095', 													0, center,	605),
						NAUSSR	=> array(2, 'claim200',		'i_200N',		$LANG_SETTINGS['pp_fields']['NAUSSR'], 	20, 'Р3600424', 												0, center,	606),
						DAUSSR	=> array(3, 'claim200',		'i_200D',		$LANG_SETTINGS['pp_fields']['DAUSSR'], 	20, '15.06.1993', 												0, center,	606),
						NC 		=> array(2, 'claim210',		'i_210',		$LANG_SETTINGS['pp_fields']['NC'], 		21, 's200600007', 												0, center,	606),
						FD 		=> array(3, 'claim220',		'i_220',		$LANG_SETTINGS['pp_fields']['FD'], 		22, '03.01.2006', 												0, center,	607),
						DVISTAV	=> array(3, 'claim230',		'exhibitionDate',$LANG_SETTINGS['pp_fields']['DVISTAV'],23, '12.06.2007', 												0, center,	608),
						// можно убрать, в деталях к патенту не отображается
						//CVISTAV	=> array(2, 'claim230',		'countryCode',	$LANG_SETTINGS['pp_fields']['CVISTAV'], 23, 'UA', 													0, center,	609),
						DATECOM => array(3, 'claim240',		'i_240',		$LANG_SETTINGS['pp_fields']['DATECOM'],	24, '15.11.2006', 												0, center,	610),
						NVAR 	=> array(1, 'claim280',		'i_280',		$LANG_SETTINGS['pp_fields']['NVAR'],	28, '>3 '.$LANG_SETTINGS['logical']['and'].' <10', 				0, center,	611),						
						NPRIOR 	=> array(2, 'claim310',		'claimNumber',	$LANG_SETTINGS['pp_fields']['NPRIOR'],	31, '200730003403.2', 											0, center,	612),
						DPRIOR 	=> array(3, 'claim310',		'claimDate',	$LANG_SETTINGS['pp_fields']['DPRIOR'],	32, '19.03.2008', 												0, center,	613),
						CPRIOR 	=> array(2, 'claim310',		'countryCode',	$LANG_SETTINGS['pp_fields']['CPRIOR'],	33, 'UA', 														0, center,	614),
						MKPZ 	=> array(2, 'claim510',		'ClassStr',		$LANG_SETTINGS['pp_fields']['MKPZ'], 	51, '09-07', 													1, center,	615),
						TITLE 	=> array(2, 'claim540',		'i_540',		$LANG_SETTINGS['pp_fields']['TITLE'], 	54, 'контейнер '.$LANG_SETTINGS['logical']['or'].' цистерна', 	0, left,	616),						
						APP 	=> array(2, 'claim710',		'name',			$LANG_SETTINGS['pp_fields']['APP'], 	71, 'Інтер ІКЕА',				 								0, left,	617),
						AUTH 	=> array(2, 'claim720',		'name',			$LANG_SETTINGS['pp_fields']['AUTH'], 	72, 'Ендрю Хайнкл', 											0, left,	618),
						PROP 	=> array(2, 'claim730',		'name',			$LANG_SETTINGS['pp_fields']['PROP'], 	73, 'Міхал Сінярскі', 											0, left,	619),
						PATP 	=> array(2, 'claim740',		'name',			$LANG_SETTINGS['pp_fields']['PATP'], 	74, 'Собко Ніна Іванівна',				 						0, left,	620),
						ADDR 	=> array(2, 'claim980',		'name',			$LANG_SETTINGS['pp_fields']['ADDR'], 	98, 'Грановська',				 								0, left,	621),
						),

	
		// Відомості про видачу свідоцтв України на знаки для товарів і послуг
		'tm' 	=> array(
						NBUL 	=> array(2, 'ref_bulletins','bulletinNumber',$LANG_SETTINGS['tm_fields']['NBUL'], 	450, '10/2007', 											0, center,	701),
						PPUBL 	=> array(3, 'claim450',		'bulletindate',	$LANG_SETTINGS['tm_fields']['PPUBL'], 	450, '10.11.2008', 											0, center,	702),
						TUSSR 	=> array(2, 'claim100',		'i_100',		$LANG_SETTINGS['tm_fields']['TUSSR'],	100, '68824', 												0, center,	603),
						NUSSR 	=> array(2, 'claim200',		'i_200n',		$LANG_SETTINGS['tm_fields']['NUSSR'],	200, '93041450', 											0, center,	604),
						DUSSR 	=> array(3, 'claim200',		'i_200d',		$LANG_SETTINGS['tm_fields']['DUSSR'],	200, '16.04.1993', 											0, center,	604),
						NCERT 	=> array(2, 'claim111',		'i_111',		$LANG_SETTINGS['tm_fields']['NCERT'], 	111, '78687', 												0, center,	703),
						EXPD 	=> array(3, 'claim141',		'i_141',		$LANG_SETTINGS['tm_fields']['EXPD'], 	141, '14.05.2007',											0, center,	704),
						REGD 	=> array(3, 'claim151',		'i_151',		$LANG_SETTINGS['tm_fields']['REGD'], 	151, '10.07.2007', 											0, center,	705),
						EXPDEND	=> array(3, 'claim181',		'i_181',		$LANG_SETTINGS['tm_fields']['EXPDEND'], 181, '10.07.2013', 											0, center,	706),
						NC 		=> array(2, 'claim210',		'i_210',		$LANG_SETTINGS['tm_fields']['NC'], 		210, 'm200504620', 											0, center,	707),
						FD 		=> array(3, 'claim220',		'i_220',		$LANG_SETTINGS['tm_fields']['FD'], 		220, '26.04.2005', 											0, center,	708),
						DVISTAV => array(3, 'claim230',		'exhibitionDate',$LANG_SETTINGS['tm_fields']['DVISTAV'],230, '25.10.2006', 											0, center,	709),
						CVISTAV => array(2, 'claim230', 	'countryCode',	$LANG_SETTINGS['tm_fields']['CVISTAV'], 230, 'UA', 													0, center,	710),
						PARISN 	=> array(2, 'claim310',		'claimNumber', 	$LANG_SETTINGS['tm_fields']['PARISN'], 	310, 'm200613440', 											0, center,	711),
						PARISD 	=> array(3, 'claim310', 	'claimDate',	$LANG_SETTINGS['tm_fields']['PARISD'], 	320, '30.01.2004', 											0, center,	712),
						NICE 	=> array(1, 'claim510',		'classNumber',	$LANG_SETTINGS['tm_fields']['NICE'], 	511, '1 '.$LANG_SETTINGS['logical']['and'].' 3', 			1, center,	713),
						VIENNA 	=> array(2, 'claim546',		'vienClassStr',	$LANG_SETTINGS['tm_fields']['VIENNA'], 	531, '01.01.15',											1, center,	714),
						KEYW 	=> array(2, 'claim539',		'i_539',		$LANG_SETTINGS['tm_fields']['KEYW'], 	539, 'gold reserve', 										1, left,	715),
						COLORS 	=> array(2, 'claim591',		'color',		$LANG_SETTINGS['tm_fields']['COLORS'], 	591, 'червоний '.$LANG_SETTINGS['logical']['and'].' синій', 1, left,	716),
						APP 	=> array(2, 'claim731',		'name',			$LANG_SETTINGS['tm_fields']['APP'], 	731, 'завод ЛІТ', 											0, left,	717),
						PROP 	=> array(2, 'claim732',		'name',			$LANG_SETTINGS['tm_fields']['PROP'], 	732, 'Лєщинський Олександр Олегович', 						0, left,	718),
						PATP 	=> array(2, 'claim740',		'name',			$LANG_SETTINGS['tm_fields']['PATP'], 	740, 'Рибак Тамара Василівна', 								0, left,	719),						
						ADDR 	=> array(2, 'claim750',		'name',			$LANG_SETTINGS['tm_fields']['ADDR'], 	750, 'Черепов', 											0, left,	720),						
						),
	
		// Інформація про міжнародні знаки, яким надана охорона в Україні
		'madrid' => array(
						NBUL 	=> array(2, 'maininfo',	'bulStr',		$LANG_SETTINGS['madrid_fields']['NBUL'], 	0, 	 '5/2008', 										0, center,	801),
						NREG	=> array(2, 'maininfo',	'i_111',		$LANG_SETTINGS['madrid_fields']['NREG'], 	111, '852963', 										0, center,	802),
						DREG 	=> array(3, 'maininfo',	'i_151',		$LANG_SETTINGS['madrid_fields']['DREG'], 	151, '15.04.2005', 									0, center,	803),
						DPUBLD	=> array(3, 'maininfo',	'i_450', 		$LANG_SETTINGS['madrid_fields']['DPUBLD'], 	450, '24.01.2008', 									0, center,	804),
						DPUBLN	=> array(2, 'maininfo',	'i_450_gaz', 	$LANG_SETTINGS['madrid_fields']['DPUBLN'], 	450, '2007/51 Gaz', 								0, center,	805),
						NICE 	=> array(2, 'maininfo',	'i_511',		$LANG_SETTINGS['madrid_fields']['NICE'], 	511, '06 '.$LANG_SETTINGS['logical']['and'].' 20', 	0, left,	806),
						KEYW 	=> array(2, 'maininfo',	'i_540',		$LANG_SETTINGS['madrid_fields']['KEYW'], 	540, 'fiat', 										0, left,	807),
						DM 		=> array(3, 'maininfo',	'i_580',		$LANG_SETTINGS['madrid_fields']['DM'], 		580, '20.04.2006', 									0, center,	808),
						),

		// Відомості про добре відомі знаки в Україні
		'wkm' 	=> array(
						NBUL 	=> array(2, 'ref_bulletins',	'bullstr',			$LANG_SETTINGS['wkm_fields']['NBUL'], 	0, '15/2006', 										0, center,	901),
						NDD 	=> array(3, 'mark',				'decisionDate',		$LANG_SETTINGS['wkm_fields']['D'], 		0, '14.11.2007', 									0, center,	902),
//						NDDD	=> array(3, 'mark',				'orderDate',		$LANG_SETTINGS['wkm_fields']['NDDD'], 	0, '18.02.2008', 									0, center,	903),
//						NDDN	=> array(2, 'mark',				'orderNumber',		$LANG_SETTINGS['wkm_fields']['NDDN'], 	0, '19', 											0, center,	904),
						DWKM 	=> array(3, 'mark',				'rightsDate',		$LANG_SETTINGS['wkm_fields']['DWKM'], 	0, '01.01.2006', 									0, center,	905),
						PUBL 	=> array(3, 'ref_bulletins',	'bulletindate',		$LANG_SETTINGS['wkm_fields']['PUBL'], 	0, '26.11.2007', 									0, center,	906),
						PROP 	=> array(2, 'markOwners',		'ownerName',		$LANG_SETTINGS['wkm_fields']['PROP'], 	0, 'Черняк', 										0, left,	907),
						LGS 	=> array(2, 'markProducts',		'products',			$LANG_SETTINGS['wkm_fields']['LGS'], 	0, 'журнали готування', 							1, left,	908),
//						NICE 	=> array(1, 'markProducts',		'classNumber',		$LANG_SETTINGS['wkm_fields']['NICE'], 	0, '16 '.$LANG_SETTINGS['logical']['and'].' 35', 	1, center,	909),
						NICE 	=> array(1, 'markclasses',		'classNumber',		$LANG_SETTINGS['wkm_fields']['NICE'], 	0, '16 '.$LANG_SETTINGS['logical']['and'].' 35', 	1, center,	910),
						MARK	=> array(2, 'mark',				'keyWords',			$LANG_SETTINGS['wkm_fields']['KEYW'], 	0, 'infocom', 										0, left,	911),
						TYPE	=> array(2, 'v_mark',			'publish_type',		$LANG_SETTINGS['wkm_fields']['TYPE'], 	0, $LANG_SETTINGS['wkm_fields']['TYPE_NAME_COURT'],								0, left,	912),
						),

    'geoc'  => array(
						NC 			=> array(2, 'geo_app',		'app_number',				$LANG_SETTINGS['geo_fields']['NC'], 		0, 	'2002120009', 		0, center,	1003),
						FD 			=> array(3, 'geo_app',		'app_date',				$LANG_SETTINGS['geo_fields']['FD'], 		0, 	'18.12.2002', 		0, center,	1004),
            NBUL  	=> array(2, 'geo_app',	'bulStr',		    $LANG_SETTINGS['madrid_fields']['NBUL'], 	0, 	 '05/2008', 			0, center,	801),
						DPUBL 	=> array(3, 'geo_app',		'bulletinDate',		$LANG_SETTINGS['geo_fields']['DPUBL'],		0, 	'15.03.2007', 		0, center,	1005),
            APP 	  => array(2, 'geo_app',		'Holder',			$LANG_SETTINGS['tm_fields']['APP'], 	0, 'завод ЛІТ', 							0, left,	717),
						KZPNAME 	=> array(2, 'geo_app',		'indication',			$LANG_SETTINGS['geo_fields']['KZPNAME'],	0, 	'МИРГОРОДСЬКА', 	0, left,	1006),
						GOODNAME 	=> array(2, 'geo_app',		'product_name',			$LANG_SETTINGS['geo_fields']['GOODNAME'],	0, 	'Мінеральна вода', 	0, left,	1007),
						),
                       
		'geo'  => array(
            NP 			=> array(1, 'geo_reg',		'regNumb',			$LANG_SETTINGS['geo_fields']['NP'], 		0,  '2', 				0, center,	1001),
						REGD		=> array(3, 'geo_reg',		'regDate',			$LANG_SETTINGS['geo_fields']['REGD'], 		0, 	'15.03.2007', 		0, center,	1002),
						NC 			=> array(2, 'geo_reg',		'i_21',				$LANG_SETTINGS['geo_fields']['NC'], 		0, 	'2002120009', 		0, center,	1003),
						FD 			=> array(3, 'geo_reg',		'i_22',				$LANG_SETTINGS['geo_fields']['FD'], 		0, 	'18.12.2002', 		0, center,	1004),
            NBUL  	=> array(2, 'geo_reg',	'bulStr',		    $LANG_SETTINGS['madrid_fields']['NBUL'], 	0, 	 '5/2008', 			0, center,	801),
						DPUBL 	=> array(3, 'geo_reg',		'bulletinDate',		$LANG_SETTINGS['geo_fields']['DPUBL'],		0, 	'15.03.2007', 		0, center,	1005),
            APP 	  => array(2, 'geo_reg',		'name',			$LANG_SETTINGS['tm_fields']['APP'], 	731, 'завод ЛІТ', 							0, left,	717),
						KZPNAME 	=> array(2, 'geo_reg',		'kzpName',			$LANG_SETTINGS['geo_fields']['KZPNAME'],	0, 	'МИРГОРОДСЬКА', 	0, left,	1006),
						KZPTYPE 	=> array(2, 'geo_reg',		'kzpType',			$LANG_SETTINGS['geo_fields']['KZPTYPE'],	0, 	'', 	0, left,	1007),
						GOODNAME 	=> array(2, 'geo_reg',		'goodName',			$LANG_SETTINGS['geo_fields']['GOODNAME'],	0, 	'Мінеральна вода', 	0, left,	1007),
						),
            
		'geor'  => array(
						NP 			=> array(1, 'geo_reguse',		'regNumb',			$LANG_SETTINGS['geo_fields']['NP'], 		0,  '2', 				0, center,	1001),
						REGD		=> array(3, 'geo_reguse',		'regDate',			$LANG_SETTINGS['geo_fields']['REGD'], 		0, 	'15.03.2007', 		0, center,	1002),
						NC 			=> array(2, 'geo_reguse',		'i_21',				$LANG_SETTINGS['geo_fields']['artem1'], 		0, 	'1', 		0, center,	1003),
            NBUL  	=> array(2, 'geo_reguse',	'bulStr',		    $LANG_SETTINGS['madrid_fields']['NBUL'], 	0, 	 '5/2008', 			0, center,	801),
						DPUBL 	=> array(3, 'geo_reguse',		'bulletinDate',		$LANG_SETTINGS['geo_fields']['DPUBL'],		0, 	'15.03.2007', 		0, center,	1005),
            APP 	  => array(2, 'geo_reguse',		'name',			$LANG_SETTINGS['tm_fields']['artem7'], 	731, 'завод ЛІТ', 							0, left,	717),
						KZPNAME 	=> array(2, 'geo_reguse',		'kzpName',			$LANG_SETTINGS['geo_fields']['KZPNAME'],	0, 	'МИРГОРОДСЬКА', 	0, left,	1006),
						KZPTYPE 	=> array(2, 'geo_reguse',		'kzpType',			$LANG_SETTINGS['geo_fields']['KZPTYPE'],	0, 	'', 	0, left,	1007),
						GOODNAME 	=> array(2, 'geo_reguse',		'goodName',			$LANG_SETTINGS['geo_fields']['GOODNAME'],	0, 	'Мінеральна вода', 	0, left,	1007),
						),

		// налаштування для бд "міжнародні реєстрації знаків для товарів і послуг"
		'madridall'  => array(
						NREG		=> array(2, 'trademarks',			'regnumber',	$LANG_SETTINGS['madrid_fields']['NREG'], 		111, '852963', 													0, center,	1101),
						DREG 		=> array(3, 'trademarks',			'regdate',		$LANG_SETTINGS['madrid_fields']['DREG'], 		151, '15.04.2005', 												0, center,	1102),
						KEYW 		=> array(2, 'mark_image',			'imagetext',	$LANG_SETTINGS['madrid_fields']['KEYW'], 		539, 'fiat', 													0, left,	1103),
						PROP 		=> array(2, 'holder_data',			'data',			$LANG_SETTINGS['madrid_fields']['PROP'], 		732, 'BeteiligungsgmbH', 										0, left,	1104),
						PATP 		=> array(2, 'representative_data',	'data',			$LANG_SETTINGS['madrid_fields']['PATP'], 		740, 'Meisser Partners',										0, left,	1105),
						NICE 		=> array(2, 'mergedata',			'niceclass',	$LANG_SETTINGS['madrid_fields']['NICE'], 		511, '02 '.$LANG_SETTINGS['logical']['and'].' 03', 				0, center,	1106),
						VIENNA 		=> array(2, 'mergedata',			'vienclass',	$LANG_SETTINGS['madrid_fields']['VIENNA'], 		531, '05.01.05 '.$LANG_SETTINGS['logical']['and'].' 29.01.03', 	0, center,	1107),
						CONC 		=> array(2, 'designations_dcpcd',	'office',		$LANG_SETTINGS['madrid_fields']['CONC'], 		880, 'AG', 														1, center,	1108),
						PREVPROP	=> array(2, 'previous_holder_data',	'data',			$LANG_SETTINGS['madrid_fields']['PREVPROP'], 	770, 'ZONGCHANG', 												0, left,	1109),
						PRIOR		=> array(2, 'priority_data',		'data',			$LANG_SETTINGS['madrid_fields']['PRIOR'], 		300, 'M0701356', 												0, center,	1110),						
						),

		// Заявки на знаки для товарів і послуг, прийняті до розгляду
		'tmc' 	=> array(
						NC 		=> array(2, 'claim210',		'i_210',		$LANG_SETTINGS['tm_fields']['NC'], 		210, 'm200504620', 											0, center,	1201),
						FD 		=> array(3, 'claim220',		'i_220',		$LANG_SETTINGS['tm_fields']['FD'], 		220, '26.04.2005', 											0, center,	1202),
						DVISTAV => array(3, 'claim230',		'exhibitionDate',$LANG_SETTINGS['tm_fields']['DVISTAV'],230, '25.10.2006', 											0, center,	1203),
						CVISTAV => array(2, 'claim230', 	'countryCode',	$LANG_SETTINGS['tm_fields']['CVISTAV'], 230, 'UA', 													0, center,	1204),
						PARISN 	=> array(2, 'claim310',		'claimNumber', 	$LANG_SETTINGS['tm_fields']['PARISN'], 	310, 'm200613440', 											0, center,	1205),
						PARISD 	=> array(3, 'claim310', 	'claimDate',	$LANG_SETTINGS['tm_fields']['PARISD'], 	320, '30.01.2004', 											0, center,	1206),
						PARISC 	=> array(2, 'claim310', 	'countryCode',	$LANG_SETTINGS['tm_fields']['PARISC'], 	330, 'UA', 													0, center,	1217),
						NICE 	=> array(1, 'claim510',		'classNumber',	$LANG_SETTINGS['tm_fields']['NICE'], 	511, '1 '.$LANG_SETTINGS['logical']['and'].' 3', 			1, center,	1208),
						VIENNA 	=> array(2, 'claim546',		'vienClassStr',	$LANG_SETTINGS['tm_fields']['VIENNA'], 	531, '01.01.15',											1, center,	1209),
						KEYW 	=> array(2, 'claim539',		'i_539',		$LANG_SETTINGS['tm_fields']['KEYW'], 	539, 'gold reserve', 										1, left,	1210),
						COLORS 	=> array(2, 'claim591',		'color',		$LANG_SETTINGS['tm_fields']['COLORS'], 	591, 'червоний '.$LANG_SETTINGS['logical']['and'].' синій', 1, left,	1211),
						APP 	=> array(2, 'claim731',		'name',			$LANG_SETTINGS['tm_fields']['APP'], 	731, 'завод ЛІТ', 											0, left,	1212),
						PATP 	=> array(2, 'claim740',		'name',			$LANG_SETTINGS['tm_fields']['PATP'], 	740, 'Рибак Тамара Василівна', 								0, left,	1213),						
						ADDR 	=> array(2, 'claim750',		'name',			$LANG_SETTINGS['tm_fields']['ADDR'], 	750, 'Черепов', 											0, left,	1214),						
						),
	);
	
	$search_idfield_names = array(
		'invc' 		=> 'idclaim',
		'inv' 		=> 'idclaim',
		'invd' 		=> 'idclaim',
		'invdu' 	=> 'idclaim',
		'pp' 		=> 'idclaim',
		'tm' 		=> 'idclaim',
		'madrid' 	=> 'idclaim',
		'wkm' 		=> 'idmark',	
		'madridall'	=> 'idtrademark',
		'tmc' 		=> 'idclaim',
    'geoc'	=> 'id',
		'geo'	=> 'id',
		'geor'	=> 'id',
	);
	
	$chapterTitles = array(	
		'invc'	=> array(
							'biblio' 		=> 	$LANG_SETTINGS['details']['biblio'], 
						), // claim - формула, abstract - реферат

		'inv'	=> array(
							'biblio' 	=> 	$LANG_SETTINGS['details']['biblio'], 
							'claim' 	=> 	$LANG_SETTINGS['details']['formula'], // формула
						), // claim - формула

		'invd'	=> array(
							'biblio' 	=> 	$LANG_SETTINGS['details']['biblio'], 
							'claim' 	=> 	$LANG_SETTINGS['details']['formula'], // формула
						), // claim - формула

		'invdu'	=> array(
							'biblio' 	=> 	$LANG_SETTINGS['details']['biblio'], 
							'claim' 	=> 	$LANG_SETTINGS['details']['formula'], // формула
						), // claim - формула

		'pp'	=> array(
							'biblio' 		=> 	$LANG_SETTINGS['details']['biblio'], 
							'variants' 		=> 	$LANG_SETTINGS['details']['ppImage'] 
						),

		'tm'	=> array(
							'biblio' 		=> 	$LANG_SETTINGS['details']['biblio'], 
							'signimage' 	=> 	$LANG_SETTINGS['details']['tmImage'] 
						),

		'madridall'	=> array(
							'biblio' 		=> 	$LANG_SETTINGS['details']['biblio'], 
							'signimage' 	=> 	$LANG_SETTINGS['details']['tmImage'] 
						),

		'tmc'	=> array(
							'biblio' 		=> 	$LANG_SETTINGS['details']['biblio'], 
							'signimage' 	=> 	$LANG_SETTINGS['details']['tmImage'] 
						),
	);

	
	
	
	
	
	
	$view_db_sections = array(
	// [КОД БД] => ([ІМ'Я РОЗДІЛУ] => ([ПІДРОЗДІЛ?], [INFO=], [НАЗВА РОЗДІЛУ/ПІДРОЗДІЛУ]))
		
		// Відомості про заявки на винаходи, які прийняті до розгляду
		'invc' => array(
						all		 	=> array(0, 'all', 		$LANG_SETTINGS['common_viewparts']['allclaims']),
						ipcindexes 	=> array(0, '', 		$LANG_SETTINGS['common_viewparts']['ipcindexes']),
						ipcA 		=> array(1, 'ipcA', 	$LANG_SETTINGS['common_viewparts']['A']),
						ipcB 		=> array(1, 'ipcB', 	$LANG_SETTINGS['common_viewparts']['B']),
						ipcC 		=> array(1, 'ipcC', 	$LANG_SETTINGS['common_viewparts']['C']),
						ipcD 		=> array(1, 'ipcD', 	$LANG_SETTINGS['common_viewparts']['D']),
						ipcE 		=> array(1, 'ipcE', 	$LANG_SETTINGS['common_viewparts']['E']),
						ipcF 		=> array(1, 'ipcF', 	$LANG_SETTINGS['common_viewparts']['F']),
						ipcG 		=> array(1, 'ipcG', 	$LANG_SETTINGS['common_viewparts']['G']),
						ipcH 		=> array(1, 'ipcH', 	$LANG_SETTINGS['common_viewparts']['H']),
						ind			=> array(0, '', 		$LANG_SETTINGS['common_viewparts']['pointers']),
						syst		=> array(1, 'syst',		$LANG_SETTINGS['invc_viewparts']['syst']),
						numc		=> array(1, 'numc', 	$LANG_SETTINGS['invc_viewparts']['num']),
						),
	
		// Відомості про видачу патентів України на винаходи
		'inv'  => array(
						all		 	=> array(0, 'all',		$LANG_SETTINGS['common_viewparts']['allpatents']),
						ipcindexes 	=> array(0, '', 		$LANG_SETTINGS['common_viewparts']['ipcindexes']),
						ipcA 		=> array(1, 'ipcA', 	$LANG_SETTINGS['common_viewparts']['A']),
						ipcB 		=> array(1, 'ipcB', 	$LANG_SETTINGS['common_viewparts']['B']),
						ipcC 		=> array(1, 'ipcC', 	$LANG_SETTINGS['common_viewparts']['C']),
						ipcD 		=> array(1, 'ipcD', 	$LANG_SETTINGS['common_viewparts']['D']),
						ipcE 		=> array(1, 'ipcE', 	$LANG_SETTINGS['common_viewparts']['E']),
						ipcF 		=> array(1, 'ipcF', 	$LANG_SETTINGS['common_viewparts']['F']),
						ipcG 		=> array(1, 'ipcG', 	$LANG_SETTINGS['common_viewparts']['G']),
						ipcH 		=> array(1, 'ipcH', 	$LANG_SETTINGS['common_viewparts']['H']),
						ind			=> array(0, '', 		$LANG_SETTINGS['common_viewparts']['pointers']),
						syst		=> array(1, 'syst',		$LANG_SETTINGS['inv_viewparts']['syst']),
						numc		=> array(1, 'numc', 	$LANG_SETTINGS['inv_viewparts']['num']),
						nump		=> array(1, 'nump',		$LANG_SETTINGS['inv_viewparts']['nump']),
						numpussr	=> array(1, 'numpussr',	$LANG_SETTINGS['inv_viewparts']['numpussr']),
						numcert		=> array(1, 'numcert',	$LANG_SETTINGS['inv_viewparts']['numcert']),
						notice 		=> array(0, 'notice',	$LANG_SETTINGS['common_viewparts']['allnotice2'])
					    ),
		
		// Відомості про видачу деклараційних патентів України на винаходи
		'invd' => array(
						all		 	=> array(0, 'all',		$LANG_SETTINGS['common_viewparts']['allpatents']),
						ipcindexes 	=> array(0, '', 		$LANG_SETTINGS['common_viewparts']['ipcindexes']),
						ipcA 		=> array(1, 'ipcA', 	$LANG_SETTINGS['common_viewparts']['A']),
						ipcB 		=> array(1, 'ipcB', 	$LANG_SETTINGS['common_viewparts']['B']),
						ipcC 		=> array(1, 'ipcC', 	$LANG_SETTINGS['common_viewparts']['C']),
						ipcD 		=> array(1, 'ipcD', 	$LANG_SETTINGS['common_viewparts']['D']),
						ipcE 		=> array(1, 'ipcE', 	$LANG_SETTINGS['common_viewparts']['E']),
						ipcF 		=> array(1, 'ipcF', 	$LANG_SETTINGS['common_viewparts']['F']),
						ipcG 		=> array(1, 'ipcG', 	$LANG_SETTINGS['common_viewparts']['G']),
						ipcH 		=> array(1, 'ipcH', 	$LANG_SETTINGS['common_viewparts']['H']),
						ind			=> array(0, '', 		$LANG_SETTINGS['common_viewparts']['pointers']),
						syst		=> array(1, 'syst',		$LANG_SETTINGS['invd_viewparts']['syst']),
						numc		=> array(1, 'numc', 	$LANG_SETTINGS['invd_viewparts']['num']),
						nump		=> array(1, 'nump',		$LANG_SETTINGS['invd_viewparts']['nump']),
						notice 		=> array(0, 'notice',	$LANG_SETTINGS['common_viewparts']['allnotice2'])
						),
		
		// Відомості про видачу деклараційних патентів України на корисні моделі				
		'invdu' => array(
						all		 	=> array(0, 'all',		$LANG_SETTINGS['common_viewparts']['allpatents']),
						ipcindexes 	=> array(0, '', 		$LANG_SETTINGS['common_viewparts']['ipcindexes']),
						ipcA 		=> array(1, 'ipcA', 	$LANG_SETTINGS['common_viewparts']['A']),
						ipcB 		=> array(1, 'ipcB', 	$LANG_SETTINGS['common_viewparts']['B']),
						ipcC 		=> array(1, 'ipcC', 	$LANG_SETTINGS['common_viewparts']['C']),
						ipcD 		=> array(1, 'ipcD', 	$LANG_SETTINGS['common_viewparts']['D']),
						ipcE 		=> array(1, 'ipcE', 	$LANG_SETTINGS['common_viewparts']['E']),
						ipcF 		=> array(1, 'ipcF', 	$LANG_SETTINGS['common_viewparts']['F']),
						ipcG 		=> array(1, 'ipcG', 	$LANG_SETTINGS['common_viewparts']['G']),
						ipcH 		=> array(1, 'ipcH', 	$LANG_SETTINGS['common_viewparts']['H']),
						ind			=> array(0, '', 		$LANG_SETTINGS['common_viewparts']['pointers']),
						syst		=> array(1, 'syst',		$LANG_SETTINGS['invdu_viewparts']['syst']),
						numc		=> array(1, 'numc', 	$LANG_SETTINGS['invdu_viewparts']['num']),
						nump		=> array(1, 'nump',		$LANG_SETTINGS['invdu_viewparts']['nump']),
						notice 		=> array(0, 'notice',	$LANG_SETTINGS['common_viewparts']['allnotice2'])
						),
	
		// Відомості про видачу патентів України на промислові зразки
		'pp' 	=> array(
						all		 	=> array(0, 'all', 		$LANG_SETTINGS['common_viewparts']['allpatents']),
						ind			=> array(0, '', 		$LANG_SETTINGS['common_viewparts']['pointers']),
						nump		=> array(1, 'nump',		$LANG_SETTINGS['pp_viewparts']['nump']),
						numc		=> array(1, 'numc', 	$LANG_SETTINGS['pp_viewparts']['num']),
						syst		=> array(1, 'syst',		$LANG_SETTINGS['pp_viewparts']['syst']),
						notice 		=> array(0, 'notice',	$LANG_SETTINGS['common_viewparts']['allnotice2'])
						),
	
		// Відомості про видачу свідоцтв України на знаки для товарів і послуг
		'tm' 	=> array(
						all		 	=> array(0, 'all', 		$LANG_SETTINGS['common_viewparts']['allcerts']),
						ind			=> array(0, '', 		$LANG_SETTINGS['common_viewparts']['pointers']),
						nump		=> array(1, 'nump',		$LANG_SETTINGS['tm_viewparts']['nump']),
						numc		=> array(1, 'numc', 	$LANG_SETTINGS['tm_viewparts']['num']),
						syst		=> array(1, 'syst',		$LANG_SETTINGS['tm_viewparts']['syst']),
						notice 		=> array(0, 'notice',	$LANG_SETTINGS['common_viewparts']['allnotice2'])
						),
		
		// Інформація про міжнародні знаки, яким надана охорона в Україні
		'madrid' => array(
						all		 	=> array(0, 'all', 		$LANG_SETTINGS['common_viewparts']['allmarks']),
						ind			=> array(0, '', 		$LANG_SETTINGS['common_viewparts']['pointers']),
						nump		=> array(1, 'nump',		$LANG_SETTINGS['madrid_viewparts']['nump']),
						syst		=> array(1, 'syst', 	$LANG_SETTINGS['madrid_viewparts']['syst']),
						),

		// Відомості про добре відомі знаки в Україні
		'wkm' 	=> array(
						all		 	=> array(0, 'all', 		$LANG_SETTINGS['common_viewparts']['allmarks']),
						),

		// Інформація про офіційні повідомлення
		'official' => array(
						all		 	=> array(0, 'all', 		$LANG_SETTINGS['common_viewparts']['allofficial']),
						),
						
		'tmc'		=> array(
						all		 	=> array(0, 'all', 		$LANG_SETTINGS['common_viewparts']['allclaims']),
            ),
						
		'geo'		=> array(
						all		 	=> array(0, 'all', 		$LANG_SETTINGS['common_viewparts']['allcerts']),
            pointer			=> array(0, 'pointer', 		$LANG_SETTINGS['common_viewparts']['pointers'])
            ),
						
		'geoc'		=> array(
						all		 	=> array(0, 'all', 		$LANG_SETTINGS['common_viewparts']['allclaims']),
						pointer			=> array(0, 'pointer', 		$LANG_SETTINGS['common_viewparts']['pointers'])
            ),
						
		'geor'		=> array(
						all		 	=> array(0, 'all', 		$LANG_SETTINGS['common_viewparts']['allcerts']),
						pointer			=> array(0, 'pointer', 		$LANG_SETTINGS['common_viewparts']['pointers'])
            ),


	);
	
	
	// [ТИП SQL ПОЛЯ]
	$search_field_types = array(
		1 => "Число",
		2 => "Строка",
		3 => "Дата",
		4 => "Номер бюлетня",
		5 => "Країна",
		6 => "Номер/Строка"  // Поля, которые в БД представлены как VARCHAR, а по смыслу - целые значения
	);
	
	
	$form_logical_operation_replacement = array(
		$LANG_SETTINGS['logical']['and'] 	=> 'AND', 
		$LANG_SETTINGS['logical']['or'] 	=> 'OR', 
		$LANG_SETTINGS['logical']['not'] 	=> 'NOT' 
	);
	
	
	$parser_errors = array(
		1 => $LANG_SETTINGS['errors'][1], 
		2 => $LANG_SETTINGS['errors'][2], 
		3 => $LANG_SETTINGS['errors'][3], 
		4 => $LANG_SETTINGS['errors'][4], 
		5 => $LANG_SETTINGS['errors'][5], 
		6 => $LANG_SETTINGS['errors'][6], 
		7 => $LANG_SETTINGS['errors'][7], 
		8 => $LANG_SETTINGS['errors'][8], 
		9 => $LANG_SETTINGS['errors'][9], 
		10 => $LANG_SETTINGS['errors'][10], 
		11 => $LANG_SETTINGS['errors'][11], 
	
	);
	
	// типи сортування
	$sortOrderTypes = array('asc', 'desc');
	
	// таблиця налаштуваня, щодо сортування
	// join - строка на t-sql. Допомагає при запиті "шукати в знайденому". Вказує, як підключити пошук по цьому полю. Якщо знаечення пусте значит вже підключене
	$sortordertable = array(
							'invc' => array(
									'nc' 		=> array('title' => $LANG_SETTINGS['sort']['nc'], 		// сортувати за номером заявки
														'fcode' => '21', 
														'sortexpr' => 'mi.i_21',
														'join' => 'inner join maininfo mi on infound.idclaim=mi.idclaim'
													),	
									'fd' 		=> array('title' => $LANG_SETTINGS['sort']['fd'], 		// сортувати за датою подання
														'fcode' => '22', 
														'sortexpr' => 'mi.i_22',
														'join' => ''
													),
									'pdclaim' 	=> array('title' => $LANG_SETTINGS['sort']['pdclaim'], 	// сортувати за датою публікації патенту			
														'fcode' => '41', 
														'sortexpr' => 'p.bulletindate',
														'join' => 'inner join publication p on infound.idclaim=p.idClaim and p.typePub=2'														
													),
											
									),

							'inv' => array(
									'np' => array('title' => $LANG_SETTINGS['sort']['np'], 	// сортувати за номером патенту
												'fcode' => '11', 
												'sortexpr' => 'mi.i_11',
												'join' => 'inner join maininfo mi on infound.idclaim=mi.idclaim'
												),						
									'nc' => array('title' => $LANG_SETTINGS['sort']['nc'], // сортувати за номером заявки
												'fcode' => '21', 
												'sortexpr' => 'mi.i_21',
												'join' => ''
												),	
									'fd' => array('title' => $LANG_SETTINGS['sort']['fd'], // сортувати за датою подання
												'fcode' => '22', 
												'sortexpr' => 'mi.i_22',
												'join' => ''
												),	
									'pd' => array('title' => $LANG_SETTINGS['sort']['pd'], // сортувати за датою публікації патенту
												'fcode' => '46', 
												'sortexpr' => 'mi.i_46',
												'join' => ''
												),			
									),

							'invd' => array(
									'np' => array('title' => $LANG_SETTINGS['sort']['np'], // сортувати за номером патенту
												'fcode' => '11', 
												'sortexpr' => 'mi.i_11',
												'join' => 'inner join maininfo mi on infound.idclaim=mi.idclaim'
												),	
									'nc' => array('title' => $LANG_SETTINGS['sort']['nc'], // сортувати за номером заявки
												'fcode' => '21', 
												'sortexpr' => 'mi.i_21',
												'join' => ''
												),	
									'fd' => array('title' => $LANG_SETTINGS['sort']['fd'], // сортувати за датою подання
												'fcode' => '22', 
												'sortexpr' => 'mi.i_22',
												'join' => ''
												),	
									'pd' => array('title' => $LANG_SETTINGS['sort']['pd'], // сортувати за датою публікації патенту
												'fcode' => '46', 
												'sortexpr' => 'mi.i_46',
												'join' => ''
												),				
									),

							'invdu' => array(
									'np' => array('title' => $LANG_SETTINGS['sort']['np'], // сортувати за номером патенту
												'fcode' => '11', 
												'sortexpr' => 'mi.i_11',
												'join' => 'inner join maininfo mi on infound.idclaim=mi.idclaim'												
												),	
									'nc' => array('title' => $LANG_SETTINGS['sort']['nc'], // сортувати за номером заявки
												'fcode' => '21', 
												'sortexpr' => 'mi.i_21',
												'join' => ''
												),	
									'fd' => array('title' => $LANG_SETTINGS['sort']['fd'], // сортувати за датою подання
												'fcode' => '22', 
												'sortexpr' => 'mi.i_22',
												'join' => ''												
												),	
									'pd' => array('title' => $LANG_SETTINGS['sort']['pd'], // сортувати за датою публікації патенту	
												'fcode' => '46', 
												'sortexpr' => 'mi.i_46',
												'join' => ''												
												),			
									),

							'pp' => array(
									'np' => array('title' => $LANG_SETTINGS['sort']['np'], // сортувати за номером патенту
												'fcode' => '11', 
												'sortexpr' => 'c111.i_111',
												'join' => 'inner join claim111 c111 on c111.idclaim=infound.idclaim'												
												),		
									'nc' => array('title' => $LANG_SETTINGS['sort']['nc'], // сортувати за номером заявки
												'fcode' => '21', 
												'sortexpr' => 'c210.i_210',
												'join' => 'inner join claim210 c210 on c210.idclaim=infound.idclaim'												
												),		
									'fd' => array('title' => $LANG_SETTINGS['sort']['fd'], // сортувати за датою подання
												'fcode' => '22', 
												'sortexpr' => 'c220.i_220',
												'join' => 'inner join claim220 c220 on c220.idclaim=infound.idclaim'
												),		
									'pd' => array('title' => $LANG_SETTINGS['sort']['pd'], // сортувати за датою публікації патенту		
												'fcode' => '45', 
												'sortexpr' => 'c450.bulletinDate',
												'join' => 'inner join claim450 c450 on c450.idclaim=infound.idclaim'												
												),		
									),

							'tm' => array(
									'ncert' => array('title' => $LANG_SETTINGS['sort']['ncert'], // сортувати за номером свідоцтва
													'fcode' => '111', 
													'sortexpr' => 'replicate(\'.\', 10-len(c111.i_111))+ltrim(c111.i_111)',
													'join' => 'inner join claim111 c111 on c111.idclaim=infound.idclaim'												
													),		
									'nc' 	=> array('title' => $LANG_SETTINGS['sort']['nc'], 	// сортувати за номером заявки
													'fcode' => '210', 
													'sortexpr' => 'c210.i_210',
													'join' => 'inner join claim210 c210 on c210.idclaim=infound.idclaim'
													),			
									'fd'	=> array('title' => $LANG_SETTINGS['sort']['fd'], 	// сортувати за датою подання
													'fcode' => '220', 
													'sortexpr' => 'c220.i_220',
													'join' => 'inner join claim220 c220 on c220.idclaim=infound.idclaim'
													),			
									'pdc'	=> array('title' => $LANG_SETTINGS['sort']['pdc'], 	// сортувати за датою публікації свідоцтва	
													'fcode' => '450', 
													'sortexpr' => 'c450.bulletinDate',
													'join' => 'inner join claim450 c450 on c450.idclaim=infound.idclaim'									
													),
									),

							'madrid' => array(
									'nreg' 	=> array('title' => $LANG_SETTINGS['sort']['nreg'],	// сортувати за номером міжнародної регистрації
													'fcode' => '111', 
													'sortexpr' => 'replicate(\'.\', 10-len(mi.i_111))+ltrim(mi.i_111)',
													'join' => 'inner join maininfo mi on infound.idclaim=mi.idclaim'
													),		
									'dreg' 	=> array('title' => $LANG_SETTINGS['sort']['dreg'], // сортувати за датою міжнародної регистрації
													'fcode' => '151', 
													'sortexpr' => 'mi.i_151',
													'join' => ''
													),	
									'denter'=> array('title' => $LANG_SETTINGS['sort']['denter'], // сортувати за датою міжнародної регистрації
													'fcode' => '580', 
													'sortexpr' => 'mi.i_580',
													'join' => ''
													),	
									),

							'wkm' => array(
									),

							'madridall' => array(
									'nreg' 	=> array('title' => $LANG_SETTINGS['sort']['nreg'],	// сортувати за номером міжнародної регистрації
													'fcode' => '111', 
													'sortexpr' => 'tm.regnumber',
													'join' => 'inner join trademarks tm on infound.idtrademark=tm.idtrademark'
													),		

									'dreg' 	=> array('title' => $LANG_SETTINGS['sort']['dreg'], // сортувати за датою міжнародної регистрації
													'fcode' => '151', 
													'sortexpr' => 'tm.regdate',
													'join' => ''
													),	
									),


							'tmc' => array(
									'nc' 	=> array('title' => $LANG_SETTINGS['sort']['nc'], 	// сортувати за номером заявки
													'fcode' => '210', 
													'sortexpr' => 'c210.i_210',
													'join' => 'inner join claim210 c210 on c210.idclaim=infound.idclaim'
													),			
									'fd'	=> array('title' => $LANG_SETTINGS['sort']['fd'], 	// сортувати за датою подання
													'fcode' => '220', 
													'sortexpr' => 'c220.i_220',
													'join' => 'inner join claim220 c220 on c220.idclaim=infound.idclaim'
													),			
									),
                  
              'geoc' => array(
									'nc' 	=> array('title' => $LANG_SETTINGS['sort']['nc'], 	// сортувати за номером заявки
													'fcode' => 'NC', 
													'sortexpr' => 't_NC.app_number'
													),			
									'fd'	=> array('title' => $LANG_SETTINGS['sort']['fd'], 	// сортувати за датою подання
													'fcode' => 'FD', 
													'sortexpr' => 't_NC.app_date'
													),			
									),
	);
	
	
	// Розшифрування кодів дивись файл notice_ukr.ini
	// сповіщення. винаходи
	$inv_notice_order = array(
								52, 54, 53, 62, 41, 42, 43, 44, 37, 64, 45, 46, 63, 50, 75, 78, 70, 69, 76, 158, 73, 72, 131, 48, 49, 77, 159, 47
							 );
	// сповіщення. корисні моделі
	$inv_notice_order = array(
								52, 54, 53, 41, 42, 43, 44, 45, 46, 63, 50, 75, 78, 70, 69, 76, 158, 73, 72, 131, 48, 49, 77, 159, 47
							 );

	
?>
