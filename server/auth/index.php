<?php

require_once "../common/SQL.php";
require_once "../common/HTTP.php";

use codability\common\HTTP as HTTP;
use codability\common\SQL as SQL;

require "../init.php";
global $CROSList, $dbname, $account, $pwd, $LoginOutDay;

$http = new HTTP($CROSList);
$sql = new SQL($dbname, $account, $pwd);

$name = $_POST['name'] ?? '';
$pwd = $_POST['pwd'] ?? '';
$uid = $_POST['uid'] ?? '';

$http->CROSListCheck();

$fh = fopen('./auth.log', 'a');
fwrite($fh, "[" . date('r') . "] : In {$_SERVER['HTTP_ORIGIN']}, {$name} try to Login \n");

$res = array();

if ($uid) {
    $result = $sql->search("Uid", array('uid' => $uid))->fetch();
    if ($result) {
        try {
            $latestDate = new DateTime($result['date']);
            $date = new DateTime(date("Y-m-d"));
            $diff = (int)$date->diff($latestDate)->format("%a");
            if ($diff > $LoginOutDay) {
                $res[] = array('result' => 'error', 'msg' => '登录过期');
                print json_encode($res);
                $sql->delete("Uid", array('uid' => $uid));
                exit();
            }
        } catch (Exception $e) {
            print $e->getMessage();
            exit();
        }
        $name = $result['name'];
    } else {
        $res[] = array('result' => 'error', 'msg' => '用户凭证错误');
        print json_encode($res);
        exit();
    }
}

if ($name && filter_var($name, FILTER_VALIDATE_EMAIL)) {
    $result = $sql->search("User", array('email' => $name))->fetch();
} else if ($name) {
    $result = $sql->search("User", array('name' => $name))->fetch();
} else $result = null;

if (!$result) {
    if (!$uid) $res[] = array('result' => 'error', 'msg' => '账户不存在');
    else $res[] = array('result' => 'error', 'msg' => 'uid不存在');
    print json_encode($res);
    exit();
} else {
    if (password_verify($_POST['pwd'], $result['pwd']) && !$uid) {
        $result = $sql->search("Uid", array('name' => $name))->fetch();
        if (!$result) {
            $uid = hash('md5', $name . $pwd . date('r'));
            $sql->add("Uid", array('uid' => $uid, 'name' => $name, 'date' => date('Y-m-d')));
        } else $uid = $result['uid'];
        $res[] = array('result' => 'success', 'msg' => '登录成功');
        $res[] = array('Id' => $result['Id'], 'name' => $result['name'], 'email' => $result['email'], 'access' => $result['access'], 'uid' => $uid);
    } else if (!$uid) $res[] = array('result' => 'error', 'msg' => '密码错误');
    else {
        $res[] = array('result' => 'success', 'msg' => '登录成功');
        $res[] = array('Id' => $result['Id'], 'name' => $result['name'], 'email' => $result['email'], 'access' => $result['access'], 'uid' => $uid);
    }
}

print json_encode($res);

fclose($fh);