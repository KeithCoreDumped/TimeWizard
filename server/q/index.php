<?php

require_once "../common/SQL.php";
require_once "../common/HTTP.php";

use codability\common\HTTP as HTTP;
use codability\common\SQL as SQL;

require "../init.php";
global $CROSList, $dbname, $account, $pwd, $LoginOutDay;
$http = new HTTP($CROSList);
$sql = new SQL($dbname, $account, $pwd);

$http->CROSListCheck();

$uid = $_GET['uid'] ?? '';
$action = $_GET['action'] ?? '';

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

if (!$action) {
    $res[] = array('result' => 'error', 'msg' => '非法请求');
    print json_encode($res);
    exit();
}

switch ($action) {
    case 'userInfo':
        if (!$uid) {
            $res[] = array('result' => 'error', 'msg' => '权限不足');
            break;
        }

        $Id = $_GET['Id'] ?? '';
        $result = $sql->search("User", array('Id' => $Id))->fetch();

        if (!$result) {
            $res[] = array('result' => 'error', 'msg' => '用户不存在');
            break;
        }

        $name = $result['name'];
        $email = $result['email'];
        $access = $result['access'];

        $res[] = array('result' => 'success', 'msg' => '成功');
        $res[] = array('name' => $name, 'email' => $email, 'access' => $access);
        break;
    default:
        $res[] = array('result' => 'error', 'msg' => '未知请求');
}

print json_encode($res);