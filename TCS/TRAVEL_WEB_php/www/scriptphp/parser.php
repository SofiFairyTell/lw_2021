<?php

function parser()
{
    error_reporting(E_ALL);
    ini_set('display_errors', 1);
    setlocale(LC_ALL, 'ru_RU');

    $html = file_get_contents('https://orange-traveler.com/travel-blog/dostoprimechatelnosti/gebekle-tepe/index.html');
    $html = iconv('utf-8//IGNORE', 'windows-1251//IGNORE', $html);
  

    $doc = phpQuery::newDocument($html);

    $data['h1'] = array();
    
    $entry = $doc->find('h1');
    foreach ($entry as $row) {
        $data['h1'][] = pq($row)->attr('href');
    }

    $results = print_r($data['h1']);

}

