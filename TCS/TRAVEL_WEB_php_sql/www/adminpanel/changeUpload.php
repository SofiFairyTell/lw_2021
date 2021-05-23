<?php
session_start();
include_once $_SERVER['DOCUMENT_ROOT'] . '../scriptphp/db.php';

function comparison($field1, $field2): bool
{
    if ($field1 !== $field2) {
        return true;
    }
    return false;
}



$name_check = comparison($_SESSION['upload_imgname'], $_POST['uploadname']);
$path_check = comparison($_SESSION['upload_path'], $_POST['uploadpath']);
$user_check = comparison($_SESSION['upload_user'], $_POST['uploaduser']);



if ($name_checkk && $path_check && $user_check){

    $_SESSION['message'] = "Никаких изменений не произошло";
    echo "<script type='text/javascript'>window.location.href = '../adminpanel/admin.php';</script>";
    exit();
} else {
    editUpload(
        $_SESSION['upload_id'],
        $_POST['uploadname'],
        $_POST['uploadpath'],
        $_POST['uploaduser']);
    $_SESSION['message'] = 'Загруженное изображение с ID: '.$_SESSION['upload_id'].' было изменено профилем: '. $_SESSION['user_store']['user_name'];
    echo "<script type='text/javascript'>window.location.href = '../adminpanel/admin.php';</script>";
    exit();
}
