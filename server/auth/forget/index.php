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

$email = $_POST['email'];
$pwd = password_hash($_POST['pwd'] ?? '', PASSWORD_DEFAULT);
$code = $_POST['code'];

$fh = fopen('./auth.log', 'a');
$res = array();

if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
    $res[] = array('result' => 'error', 'msg' => '非法邮箱名');
    print json_encode($res);
    exit();
}

$result = $sql->search("User", array('email' => $email))->fetch();

if (!$result) {
    $res[] = array('result' => 'error', 'msg' => '邮箱不存在');
    print json_encode($res);
    $conn = null;
    fclose($fh);
    exit();
}

$name = $result['name'];
$access = $result['access'];

$result = $sql->search("Email", array('email' => $email, 'code' => $code))->fetch();

if (!$result) {
    $res[] = array('result' => 'error', 'msg' => '验证码错误');
    print json_encode($res);
    $conn = null;
    fclose($fh);
    exit();
} else {
    $sql->delete("Email", array('email' => $email));
    $sql->update("User", array('pwd' => $pwd), array('email' => $email));
}

fwrite($fh, "[" . date('r') . "] : In {$_SERVER['HTTP_ORIGIN']}, {$name} try to Register, using email({$email}) and keycode({$keycode}) \n");

$res[] = array('result' => 'success', 'msg' => '更新成功');
$res[] = array('name' => $name, 'email' => $email, 'access' => $access);
print json_encode($res);

fclose($fh);