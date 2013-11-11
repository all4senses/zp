<?php

/**
 * @file
 * A specific handler for RU.
 */

$plugin = array(
  'title' => t('Address form (RU add-on)'),
  'format callback' => 'addressfield_format_address_ru_generate',
  'type' => 'address',
  'weight' => -80,
);

function addressfield_format_address_ru_generate(&$format, $address, $context = array()){
   if ($address['country'] == 'RU'){
    $format['locality_block']['administrative_area'] = array(
      '#title' => t('Region'),
      '#size' => 10,
      '#required' => TRUE,
      '#prefix' => ' ',
      '#attributes' => array('class' => array('state')),
    );

    $format['locality_block']['administrative_area']['#options'] = array(
          ""   =>   t("--"),
          "AD" => 	t("Adygeya, Respublika"),
          "AL" => 	t("Altay, Respublika"),
          "BA" => 	t("Bashkortostan, Respublika"),
          "BU" => 	t("Buryatiya, Respublika"),
          "CE" => 	t("Chechenskaya Respublika"),
          "CU" => 	t("Chuvashskaya Respublika"),
          "DA" => 	t("Dagestan, Respublika"),
          "IN" => 	t("Ingushetiya, Respublika"),
          "KB" => 	t("Kabardino-Balkarskaya Respublika"),
          "KL" => 	t("Kalmykiya, Respublika"),
          "KC" => 	t("Karachayevo-Cherkesskaya Respublika"),
          "KR" => 	t("Kareliya, Respublika"),
          "KK" => 	t("Khakasiya, Respublika"),
          "KO" => 	t("Komi, Respublika"),
          "ME" => 	t("Mariy El, Respublika"),
          "MO" => 	t("Mordoviya, Respublika"),
          "SA" => 	t("Sakha, Respublika [Yakutiya]"),
          "SE" => 	t("Severnaya Osetiya-Alaniya, Respublika"),
          "TA" => 	t("Tatarstan, Respublika"),
          "TY" => 	t("Tyva, Respublika [Tuva]"),
          "UD" => 	t("Udmurtskaya Respublika"),
          "ALT" => 	t("Altayskiy kray"),
          "KAM" => 	t("Kamchatskiy kray"),
          "KHA" => 	t("Khabarovskiy kray"),
          "KDA" => 	t("Krasnodarskiy kray"),
          "KYA" => 	t("Krasnoyarskiy kray"),
          "PER" => 	t("Permskiy kray"),
          "PRI" => 	t("Primorskiy kray"),
          "STA" => 	t("Stavropol'skiy kray"),
          "ZAB" => 	t("Zabaykal'skiy kray"),
          "AMU" => 	t("Amurskaya oblast'"),
          "ARK" => 	t("Arkhangel'skaya oblast'"),
          "AST" => 	t("Astrakhanskaya oblast'"),
          "BEL" => 	t("Belgorodskaya oblast'"),
          "BRY" => 	t("Bryanskaya oblast'"),
          "CHE" => 	t("Chelyabinskaya oblast'"),
          "IRK" => 	t("Irkutskaya oblast'"),
          "IVA" => 	t("Ivanovskaya oblast'"),
          "KGD" => 	t("Kaliningradskaya oblast'"),
          "KLU" => 	t("Kaluzhskaya oblast'"),
          "KEM" => 	t("Kemerovskaya oblast'"),
          "KIR" => 	t("Kirovskaya oblast'"),
          "KOS" => 	t("Kostromskaya oblast'"),
          "KGN" => 	t("Kurganskaya oblast'"),
          "KRS" => 	t("Kurskaya oblast'"),
          "LEN" => 	t("Leningradskaya oblast'"),
          "LIP" => 	t("Lipetskaya oblast'"),
          "MAG" => 	t("Magadanskaya oblast'"),
          "MOS" => 	t("Moskovskaya oblast'"),
          "MUR" => 	t("Murmanskaya oblast'"),
          "NIZ" => 	t("Nizhegorodskaya oblast'"),
          "NGR" => 	t("Novgorodskaya oblast'"),
          "NVS" => 	t("Novosibirskaya oblast'"),
          "OMS" => 	t("Omskaya oblast'"),
          "ORE" => 	t("Orenburgskaya oblast'"),
          "ORL" => 	t("Orlovskaya oblast'"),
          "PNZ" => 	t("Penzenskaya oblast'"),
          "PSK" => 	t("Pskovskaya oblast'"),
          "ROS" => 	t("Rostovskaya oblast'"),
          "RYA" => 	t("Ryazanskaya oblast'"),
          "SAK" => 	t("Sakhalinskaya oblast'"),
          "SAM" => 	t("Samarskaya oblast'"),
          "SAR" => 	t("Saratovskaya oblast'"),
          "SMO" => 	t("Smolenskaya oblast'"),
          "SVE" => 	t("Sverdlovskaya oblast'"),
          "TAM" => 	t("Tambovskaya oblast'"),
          "TOM" => 	t("Tomskaya oblast'"),
          "TUL" => 	t("Tul'skaya oblast'"),
          "TVE" => 	t("Tverskaya oblast'"),
          "TYU" => 	t("Tyumenskaya oblast'"),
          "ULY" => 	t("Ul'yanovskaya oblast'"),
          "VLA" => 	t("Vladimirskaya oblast'"),
          "VGG" => 	t("Volgogradskaya oblast'"),
          "VLG" => 	t("Vologodskaya oblast'"),
          "VOR" => 	t("Voronezhskaya oblast'"),
          "YAR" => 	t("Yaroslavskaya oblast'"),
          "MOW" => 	t("Moskva"),
          "SPE" => 	t("Sankt-Peterburg"),
          "YEV" => 	t("Yevreyskaya avtonomnaya oblast'"),
          "CHU" => 	t("Chukotskiy avtonomnyy okrug"),
          "KHM" => 	t("Khanty-Mansiyskiy avtonomnyy okrug-Yugra"),
          "NEN" => 	t("Nenetskiy avtonomnyy okrug"),
          "YAN" => 	t("Yamalo-Nenetskiy avtonomnyy okrug")	
    );
    
    
    
    $format['locality_block']['locality'] = array(
      '#title' => t('City'),
      '#size' => 7,
      '#required' => TRUE,
      '#prefix' => ' ',
      '#attributes' => array('class' => array('locality')),
    );
    
    $format['locality_block']['locality']['#options'] = array(
          ""   =>   t("--"),
          "AD" => 	t("Adygeya, Respublika"),
          "AL" => 	t("Altay, Respublika"),
          "BA" => 	t("Bashkortostan, Respublika"),
      
    );
    
    
    
  }
}