<?php

function getRes($path = '')
{
    $res = getFilesSize($path);
    return $res > 0 ? "${res} байт" : "Путь неверный!";
}

function getFilesSize($path = '')
{
    if(!preg_match('/\.\.\//', $path)) {
        $root = $_SERVER['DOCUMENT_ROOT'];
        $fullPath = $root . $path;
        if (file_exists($fullPath)) {
            $fileSize = 0;
            if (is_dir($fullPath)) {
                $dir = scandir($fullPath);
                if (!empty($dir)) {
                    foreach ($dir as $file) {
                        if (($file != '.') && ($file != '..'))
                            if (is_dir($fullPath . '/' . $file))
                                /*Файл в данном случае будет являться директорией*/
                                $fileSize += getFilesSize($path . '/' . $file);
                            else
                                $fileSize += filesize($fullPath . '/' . $file);
                    }
                    return $fileSize;
                }
    
            } else {
                return filesize($fullPath);
            }
        }
    } else {
        return -1;
    }
    
}