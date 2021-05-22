<?php
const DB_HOST = 'localhost';
const DB_USER = 'root';
const DB_PASSWORD = 'root';
const DB_NAME = 'travelblog';
// Функция для подключения к базе данных
function connect()
{
    $mysql = new mysqli(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME);
    if ($mysql->connect_errno) exit('Ошибка подключения к бд!');
    $mysql->set_charset('utf-8');
    return $mysql;
}

function clearSession()
{
    foreach ($_SESSION as $key => $value) {
        if ($key != 'user') {
            unset($_SESSION[$key]);
        }
    }
}

//Функция для поиска изображений и информации к ним для публикации на сайте
function getSliderIMG($slide)
{
    $mysql = connect();
    $result = $mysql->query("select * from img_store where img_slide like '$slide'");
    $mysql->close();
    return $result;
}

function getContactINFO()
{
    $mysql = connect();
    $result = $mysql->query("select * from contact_store");
    $mysql->close();
    return $result;
}

function checkUser($login, $password)
{
    $mysql = connect();
    $result = $mysql->query(
        "select * from `user_store`
        where `user_name` = '$login' and `user_password` = '$password'"
    );
    $mysql->close();
    return $result;
}

function addUser($login = null, $password =null, $email=null,$role=null)
{
    $mysql = connect();

    $result = $mysql->query(
        "INSERT INTO `user_store` (`user_name`,`user_email`,
        `user_password`,`user_role`) values ('$login', '$email', '$password', '$role')");
    $mysql->close();
    return $result;
}