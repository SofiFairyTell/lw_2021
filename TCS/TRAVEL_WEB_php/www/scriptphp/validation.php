<?php

function checkRegularName(): bool
{
    if (!empty($_POST)) {
        if (preg_match('/^[а-я]{2,}+$/iu', trim($_POST['name']))) {
            return true;
        }
    }
    return false;

}
function checkRegularSurName(): bool
{
    if (!empty($_POST)) {
        if (!preg_match('/^[а-я]{2,}+$/iu', trim($_POST['surname']))) {
            return 'Только символы кириллицы!';
        }
    }
    return false;

}

function checkRegularPhone(): bool
{
    if (!empty($_POST)) {
        if (!preg_match('/^\+7 \([0-9][0-9][0-9]\) [0-9][0-9][0-9] [0-9][0-9] [0-9][0-9]/', $_POST['phone'])) {
            return true;
        }
    }
    return false;
}

function checkRegularEmail(): bool
{
    if (!empty($_POST)) {
        if (!preg_match('/^[a-z]([a-z0-9_\.-])+@[a-z0-9-]+\.([a-z]{2,4}\.)?[a-z]{2,4}$/i', $_POST['email'])) {
            return true;
        }
    }
    return false;

}

function checkRegularPassword(): bool
{
    if (!empty($_POST)) {
        if (!preg_match(    '/[0-9a-zA-Z!@#$%^&*]{6,}/', $_POST['password'])) {
            return true;
        }
    }
    return false;

}
function comparisonOfPasswords(): bool
{
    if (!empty($_POST)) {
        if ($_POST['password'] !== $_POST['password2']) {
            return true;
        }
    }
    return false;
}

function checkSubject(): bool
{
    if(!empty($_POST)) {
        if(strlen($_POST['subject']) < 5) {
            return true;
        }
    }
    return false;

}

function checkTextBox(): bool
{
    if(!empty($_POST)) {
        if(strlen($_POST['message']) < 30) {
            return true;
        }
    }
    return false;

}

function success(): bool
{
    foreach ($_POST as &$value) {
        $value = '';
    }
    return true;
}