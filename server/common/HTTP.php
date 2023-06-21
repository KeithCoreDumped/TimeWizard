<?php

namespace codability\common;

/**
 * HTTP报文处理
 */
class HTTP
{
    private array $_ALLOW_ORIGIN;
    private array $header;

    public function __construct($CROSList)
    {
        $this->header = $this->getHeaders();
        $this->CROSListInit($CROSList);
    }

    public function CROSListInit($CROSList): void
    {
        $this->_ALLOW_ORIGIN = $CROSList;
    }

    private function getHeaders(): array
    {
        $headers = array();
        foreach ($_SERVER as $key => $value) {
            if ('HTTP_' == substr($key, 0, 5)) {
                $headers[substr($key, 5)] = $value;
            }
        }
        if (isset($_SERVER['PHP_AUTH_DIGEST'])) {
            $headers['AUTHORIZATION'] = $_SERVER['PHP_AUTH_DIGEST'];
        } else if (isset($_SERVER['PHP_AUTH_USER']) && isset($_SERVER['PHP_AUTH_PW'])) {
            $headers['AUTHORIZATION'] = base64_encode($_SERVER['PHP_AUTH_USER'] . ':' . $_SERVER['PHP_AUTH_PW']);
        }
        if (isset($_SERVER['CONTENT_LENGTH'])) {
            $headers['CONTENT-LENGTH'] = $_SERVER['CONTENT_LENGTH'];
        }
        if (isset($_SERVER['CONTENT_TYPE'])) {
            $headers['CONTENT-TYPE'] = $_SERVER['CONTENT_TYPE'];
        }
        return $headers;
    }

    public function getHeader($item = NULL): ?string
    {
        if($item == NULL)return $this->header;
        if(in_array($item, $this->header))return $this->header[$item];
        else return NULL;
    }

    public function CROSListAdd($site): void
    {
        if (!in_array($site, $this->_ALLOW_ORIGIN)) {
            $this->_ALLOW_ORIGIN[] = $site;
        }
    }

    public function CROSListDelete($site): void
    {
        if (in_array($site, $this->_ALLOW_ORIGIN)) $this->_ALLOW_ORIGIN = array_diff($this->_ALLOW_ORIGIN, array($site));
    }

    public function CROSListCheck(): bool
    {
        if (in_array($this->getOrigin(), $this->_ALLOW_ORIGIN)) {
            header('Access-Control-Allow-Origin:' . $_ORIGIN);
            header('Access-Control-Allow-Credentials: true');
            header('Access-Control-Expose-Headers: *');
            header('Access-Control-Allow-Headers: *');
            return true;
        } else return false;
    }

    public function getOrigin(): string
    {
        return $_SERVER['HTTP_ORIGIN'] ?? '';
    }

    public function encodingMessage($code, $msg, $data): void
    {

        $res[] = array('code' => $code, 'msg' => $msg);
        $res[] = $data;
        print json_encode($res);
    }
}