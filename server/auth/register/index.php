<?php

require_once "../../common/SQL.php";
require_once "../../common/HTTP.php";

use codability\common\HTTP as HTTP;
use codability\common\SQL as SQL;

require "../../init.php";
global $CROSList, $dbname, $account, $pwd;

$http = new HTTP($CROSList);
$sql = new SQL($dbname, $account, $pwd);

$http->CROSListCheck();

$name = $_POST['name'] ?? '';
$pwd = password_hash($_POST['pwd'] ?? '', PASSWORD_DEFAULT);
$email = $_POST['email'] ?? '';
$keycode = (isset($_POST['keycode']) && $_POST['keycode'] != "") ? $_POST['keycode'] : 'null';
$code = $_POST['code'] ?? '';
$access = 'guest';
$Id = -1;

$fh = fopen('./auth.log', 'a');
fwrite($fh, "[" . date('r') . "] : In {$_SERVER['HTTP_ORIGIN']}, {$name} try to Register, using email({$email}) and keycode({$keycode}) \n");

$res = array();

$result = $sql->search("User", array('name' => $name))->fetch();
if ($result) {
    $res[] = array('result' => 'error', 'msg' => '用户名已存在');
    print json_encode($res);
    $conn = null;
    fclose($fh);
    exit();
}

$result = $sql->search("User", array('email' => $email))->fetch();
if ($result) {
    $res[] = array('result' => 'error', 'msg' => '邮箱已存在');
    print json_encode($res);
    $conn = null;
    fclose($fh);
    exit();
}

if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
    $res[] = array('result' => 'error', 'msg' => '非法邮箱名');
    print json_encode($res);
    exit();
}

if ($keycode != 'null') {
    $result = $sql->search("Keycode", array('keycode' => $keycode))->fetch();
    if (!$result) {
        $res[] = array('result' => 'error', 'msg' => '注册码不存在');
        print json_encode($res);
        $conn = null;
        fclose($fh);
        exit();
    } else if ($result['active']) {
        $res[] = array('result' => 'error', 'msg' => '注册码已使用');
        print json_encode($res);
        $conn = null;
        fclose($fh);
        exit();
    } else {

        $result = $sql->search("Email", array('email' => $email, 'code' => $code))->fetch();
        if (!$result) {
            $res[] = array('result' => 'error', 'msg' => '验证码错误');
            print json_encode($res);
            $conn = null;
            fclose($fh);
            exit();
        } else {
            $sql->delete("Email", array('email' => $email));
        }

        $access = $result['access'];

        $Id = $sql->add("User", array('name' => $name, 'pwd' => $pwd, 'email' => $email, 'keycode' => $keycode, 'access' => $access));

        $res[] = array('result' => 'success', 'msg' => '注册成功');
        $res[] = array('Id' => $Id, 'name' => $name, 'email' => $email, 'access' => $access);
    }
} else {
    $result = $sql->search("Email", array('email' => $email, 'code' => $code))->fetch();
    if (!$result) {
        $res[] = array('result' => 'error', 'msg' => '验证码错误');
        print json_encode($res);
        $conn = null;
        fclose($fh);
        exit();
    } else {
        $sql->delete("Email", array('email' => $email));
    }

    $Id = $sql->add("User", array('name' => $name, 'pwd' => $pwd, 'email' => $email, 'keycode' => $keycode, 'access' => $access));

    $uid = hash('md5', $name . $pwd . date('r'));
    $sql->add("Uid", array('uid' => $uid, 'name' => $name, 'date' => date('Y-m-d')));

    $res[] = array('result' => 'success', 'msg' => '注册成功');
    $res[] = array('Id' => $Id, 'name' => $name, 'email' => $email, 'access' => $access, 'uid' => $uid);
}

print json_encode($res);
fclose($fh);