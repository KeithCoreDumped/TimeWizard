<?php

namespace codability\common;

use PDO;
use PDOException;
use PDOStatement;

/**
 * SQL封装
 */
class SQL
{
    /**
     * @var PDO|null
     */
    private ?PDO $conn = null;


    /**
     * 构造函数
     * @param $dbname
     * @param $account
     * @param $pwd
     */
    function __construct($dbname, $account, $pwd)
    {
        $this->init($dbname, $account, $pwd);
    }

    /**
     * 语句过滤
     * @param $str
     * @return string
     */
    public function filter($str): string
    {
        if(!get_magic_quotes_gpc())$post = addslashes($str);
        $str = str_replace("_", "\_", $str);
        $str = str_replace("%", "\%", $str);
        $str = nl2br($str);
        return htmlspecialchars($str);
    }

    /**
     * 初始化
     * @param $dbname
     * @param $account
     * @param $pwd
     * @return void
     */
    public function init($dbname, $account, $pwd)
    {
        $this->conn = new PDO('mysql:host=localhost;dbname=' . $dbname, $account, $pwd);
        $this->conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    }

    /**
     * 添加
     * @param $list
     * @param $data
     * @return int
     */
    public function add($list, $data): int
    {
        if ($this->conn == null) return -1;
        try {
            $sql = "INSERT INTO " . $list . " (";
            $keys = array_keys($data);
            for ($i = 0; $i < count($keys); $i++) {
                $sql .= $keys[$i];
                if ($i != count($keys) - 1) $sql .= ",";
            }
            $sql .= ") VALUES (";
            for ($i = 0; $i < count($keys); $i++) {
                $sql .= "'" . $data[$keys[$i]] . "'";
                if ($i != count($data) - 1) $sql .= ",";
            }
            $sql .= ")";
            $this->conn->exec($this->filter($sql));
        } catch (PDOException $e) {
            print $this->filter($sql);
            print $e->getMessage() . " in SQLAdd";
        }
        return $this->conn->lastInsertId();
    }

    /**
     * 查找
     * @param $list
     * @param $data
     * @return PDOStatement
     */
    public function search($list, $data): PDOStatement
    {
        if ($this->conn == null) return -1;
        try {
            $keys = array_keys($data);
            $sql = "SELECT * FROM " . $list . " WHERE ";
            for ($i = 0; $i < count($keys); $i++) {
                if (is_string($data[$keys[$i]])) $sql .= $keys[$i] . "=" . "'" . $data[$keys[$i]] . "'";
                else $sql .= $keys[$i] . "=" . $data[$keys[$i]];
                if ($i != count($keys) - 1) $sql .= " and ";
            }
            $stmt = $this->conn->prepare($this->filter($sql));
            $stmt->execute();
        } catch (PDOException $e) {
            print $this->filter($sql);
            print $e->getMessage() . " in SQLSearch";
        }
        return $stmt;
    }

    /**
     * 删除
     * @param $list
     * @param $data
     * @return int
     */
    public function delete($list, $data): int
    {
        if ($this->conn == null) return -1;
        try {
            $sql = "DELETE FROM " . $list . " WHERE ";
            $keys = array_keys($data);
            for ($i = 0; $i < count($keys); $i++) {
                if (is_string($data[$keys[$i]])) $sql .= $keys[$i] . "=" . "'" . $data[$keys[$i]] . "'";
                else $sql .= $keys[$i] . "=" . $data[$keys[$i]];
                if ($i != count($keys) - 1) $sql .= " and ";
            }
            $this->conn->exec($this->filter($sql));
        } catch (PDOException $e) {
            print $this->filter($sql);
            print $e->getMessage() . " in SQLDelete";
        }
        return 0;
    }

    /**
     * 修改
     * @param $list
     * @param $data
     * @param $fetch
     * @return int
     */
    public function update($list, $data, $fetch): int
    {
        if ($this->conn == null) return -1;
        try {
            $sql = "UPDATE " . $list . " SET ";

            $keys = array_keys($data);
            for ($i = 0; $i < count($keys); $i++) {
                if (is_string($data[$keys[$i]])) $sql .= $keys[$i] . "=" . "'" . $data[$keys[$i]] . "'";
                else $sql .= $keys[$i] . "=" . $data[$keys[$i]];
                if ($i != count($keys) - 1) $sql .= ",";
            }
            $sql .= " WHERE ";

            $keys = array_keys($fetch);
            for ($i = 0; $i < count($keys); $i++) {
                if (is_string($fetch[$keys[$i]])) $sql .= $keys[$i] . "=" . "'" . $fetch[$keys[$i]] . "'";
                else $sql .= $keys[$i] . "=" . $fetch[$keys[$i]];
                if ($i != count($keys) - 1) $sql .= " and ";
            }
            $stmt = $this->conn->prepare($this->filter($sql));
            $stmt->execute();
        } catch (PDOException $e) {
            print $this->filter($sql);
            print $e->getMessage() . " in SQLUpdate";
        }
        return 0;
    }
}