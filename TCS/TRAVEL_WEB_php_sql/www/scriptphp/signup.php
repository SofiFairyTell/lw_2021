<?php
    session_start();
    require_once('./db.php');
    $connect = connect();
    $login_post = $_POST['login'];
    $email_post = $_POST['email'];
    $password_post = $_POST['password'];
    $password_confirm_post = $_POST['password_confirm'];


    if($password_post === $password_confirm_post )
    {
        $password_post = md5($password_post);
        $role = 'ordinary';
        addUser($login_post, $password_post, $email_post, $role);
        $_SESSION['message'] = 'Регистрация прошла успешно!';
        if( $_SESSION['user_store']['user_role']==="admin")
        {
            echo "<script type='text/javascript'>window.location.href = '../adminpanel/admin.php';</script>";
        }
        else
        {
           echo "<script type='text/javascript'>window.location.href = '../authorize.php';</script>"; 
        }
        
    }
    else
    {
        $_SESSION['message'] = 'Пароли не совпадают';
        echo "<script type='text/javascript'>window.location.href = '../registrate.php';</script>";
    }
