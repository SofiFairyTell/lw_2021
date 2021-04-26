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
}
?>



