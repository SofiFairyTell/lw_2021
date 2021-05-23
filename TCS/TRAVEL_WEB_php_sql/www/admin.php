<?php
session_start();
if (empty($_SESSION['user_store'])) 
{
    echo "<script type='text/javascript'>window.location.href = '../travelblog.php';</script>";
    exit();
}
$title_page = 'Управление сайтом';
require('header.php');
?>


