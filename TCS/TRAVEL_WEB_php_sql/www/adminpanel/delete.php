<?php
session_start();
include_once $_SERVER['DOCUMENT_ROOT'] . '../scriptphp/db.php';
if(!empty($_GET)) 
{
    switch ($_GET)
    {
        case($_GET['case']==="user"):
            {
                deleteUser($_GET['id']);
                $_SESSION['message'] = "Пользователь удален. Наверное. ";
            }
            break;
        case($_GET['case']==="upload"):
            {
                deleteUpload($_GET['id']);
                $_SESSION['message'] = "Информация о загрузке удалена. Наверное. ";
            }
            break;
        default:  
            $_SESSION['message'] = "Не было выполнено никаких действий";
    }
  
}
echo "<script type='text/javascript'>window.location.href = '../adminpanel/admin.php';</script>";
exit();