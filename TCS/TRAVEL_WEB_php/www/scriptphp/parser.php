<?php

class Parser
{
    function parsHtml()
    {
        $link = file_get_contents('https://it-blog.ru/php/parser-sajtov-na-phpquery/'); // Указываем ссылку на сайт
        $document = phpQuery::newDocument($link);
        $div = $document->find('p'); // Ищем нужный тег
        $text = $div->text(); // Получаем содержимое
        echo $text;
    }
    
    function statParser()
    {
        $handle = @fopen("./zad2.html", "r");
        if ($handle) {
            while (($buffer = fgets($handle, 4096)) !== false) 
            {
                echo $this->cleanString($buffer);
            }
            if (!feof($handle))
            {
                echo "Ошибка: fgets() неожиданно потерпел неудачу\n";
            }
            fclose($handle);
        }
    }

    function cleanString($buffer = '')
    {
        // $str = '';
        // $isMatched = preg_match('/<(\S*?)[^>]*>.*?|<.*?/>/i', $str, $matches);
        // var_dump($isMatched, $matches);
        // $keywords = preg_split($isMatched,$buffer);
        // return $keywords;
        $tag = 'p';
        $tag = preg_quote($tag);
        preg_match_all('<'.$tag.'[^>]*>(.*?)</'.$tag.'>.',$buffer,$matches,PREG_PATTERN_ORDER);
        return $matches[1];
    }


    function get_tag( $attr, $value, $xml, $tag=null ) {
        if( is_null($tag) )
          $tag = '\w+';
        else
          $tag = preg_quote($tag);
       
        $attr = preg_quote($attr);
        $value = preg_quote($value);
       
        $tag_regex = "/<(".$tag.")[^>]*$attr\s*=\s*".
                      "(['\"])$value\\2[^>]*>(.*?)<\/\\1>/"
       
        preg_match_all($tag_regex,
                       $xml,
                       $matches,
                       PREG_PATTERN_ORDER);
       
        return $matches[3];
}
///<p.*?class?= ?['\\\"]([^'\\\"]*)(.*?)<\/p>/
function get_tag( $tag, $xml ) {
    $tag = 'p';
    $tag = preg_quote($tag);
    preg_match_all('{<'.$tag.'[^>]*>(.*?)</'.$tag.'>.'}',
                     $xml,
                     $matches,
                     PREG_PATTERN_ORDER);
   
    return $matches[1];
  }

?>



