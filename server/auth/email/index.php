<?php
require '../../vendor/autoload.php';
require_once "../../common/SQL.php";
require_once "../../common/HTTP.php";

use codability\common\HTTP as HTTP;
use codability\common\SQL as SQL;
use PHPMailer\PHPMailer\PHPMailer;

require "../../init.php";
global $CROSList, $dbname, $account, $pwd;

$http = new HTTP($CROSList);
$sql = new SQL($dbname, $account, $pwd);

$http->CROSListCheck();

$email = $_POST['email'] ?? '';
$action = $_POST['action'] ?? 'forget';

if (!$action) {
    $res[] = array('result' => 'error', 'msg' => '非法请求');
    print json_encode($res);
    exit();
}

if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
    $res[] = array('result' => 'error', 'msg' => '非法邮箱名');
    print json_encode($res);
    exit();
}

$mail = new PHPMailer(true);

$res = array();
try {
    //服务器配置
    $mail->CharSet = "UTF-8";
    $mail->SMTPDebug = 0;
    $mail->isSMTP();
    $mail->Host = 'smtp.exmail.qq.com';
    $mail->SMTPAuth = true;
    $mail->Username = 'nickwald@bupt.edu.cn';
    $mail->Password = 'Nick870585593';
    $mail->SMTPSecure = 'ssl';
    $mail->Port = 465;

    $result = $sql->search("User", array('email' => $email))->fetch();
    if (!$result && $action == 'forget') {
        $res[] = array('result' => 'error', 'msg' => '邮箱不存在');
        print json_encode($res);
        exit();
    }
    $receiver = $result['name'];

    $mail->setFrom('nickwald@bupt.edu.cn', 'Nickwald');
    $mail->addAddress($email, $receiver);
    $mail->addReplyTo('nickwald@bupt.edu.cn', 'Nickwald');

    //Content
    $mail->isHTML(true);
    $mail->Subject = '邮箱验证' . time();

    $code = str_rand();

    if ($action == 'forget') $mail->Body = "
    <h1>账户找回</h1>
    <p>亲爱的 {$receiver} ，您的找回代码为：</p>
    <p><strong>{$code}</strong></p>
    <p>如果您近期没有在 {$http->getOrigin()} 申请过找回账户，请立即联系客服，注意账户安全。</p>
    ";
    if ($action == 'register') $mail->Body = "
    <h1>账户注册</h1>
    <p>亲爱的新用户 ，您的注册代码为：</p>
    <p><strong>{$code}</strong></p>
    <p>如果您近期没有在 {$http->getOrigin()} 申请过注册账户，请立即联系客服，注意账户安全。</p>
    ";
    $mail->AltBody = 'Dear' . $receiver . ', ' . 'Your Code:' . $code;

    $mail->send();

    $sql->add("Email", array('email' => $email, 'code' => $code, 'date' => date('Y-m-d')));

    $res[] = array('result' => 'success', 'msg' => '验证码已发送');

    print json_encode($res);
} catch (Exception $e) {
    echo $mail->ErrorInfo;
}

function str_rand($length = 6, $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'): string
{
    if (!is_int($length) || $length < 0) return false;
    $len = strlen($characters) - 1;
    $string = '';
    for ($i = $length; $i > 0; $i--) $string .= $characters[mt_rand(0, $len)];
    return $string;
}