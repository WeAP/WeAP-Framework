
DROP TABLE IF EXISTS account;
DROP TABLE IF EXISTS account_record;
DROP TABLE IF EXISTS account_transaction;

CREATE DATABASE IF NOT EXISTS account_db;
USE account_db;

CREATE TABLE IF NOT EXISTS account
(
    accountId bigint(20) unsigned NOT NULL,
    accountType smallint(5) unsigned NOT NULL,
    currencyType smallint(5) unsigned NOT NULL,
    balance bigint(20) NOT NULL,
    freezedBalance bigint(20) NOT NULL,
    status smallint(5) unsigned NOT NULL,
    remark varchar(128),
    dtNO varchar(64),
    tNO varchar(64),
    sNO varchar(64),
    dataVersion bigint(20) unsigned NOT NULL,
    dataSign varchar(128) NOT NULL,
    createTime datetime NOT NULL,
    modifyTime datetime NOT NULL,

    PRIMARY KEY(accountId)
)ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS account_record
(
    accountRecordId bigint(20) unsigned NOT NULL AUTO_INCREMENT,
    txnNO varchar(64) NOT NULL,
    accountId bigint(20) unsigned NOT NULL,
    accountType smallint(5) unsigned NOT NULL,
    currencyType smallint(5) unsigned NOT NULL,
    balance bigint(20) NOT NULL,
    freezedBalance bigint(20) NOT NULL,
    status smallint(5) unsigned NOT NULL,
    remark varchar(128),
    opType smallint(5) unsigned NOT NULL,
    opAmount bigint(20) NOT NULL,
    opFreezedAmount bigint(20) NOT NULL,
    accountTransactionId bigint(20) unsigned NOT NULL,
    accountEvidenceId varchar(64),
    dtNO varchar(64),
    tNO varchar(64),
    sNO varchar(64),
    dataVersion bigint(20) unsigned NOT NULL,
    dataSign varchar(128) NOT NULL,
    createTime datetime NOT NULL,
    modifyTime datetime NOT NULL,
    PRIMARY KEY(accountRecordId)
)ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS account_transaction
(
    accountTransactionId bigint(20) unsigned NOT NULL AUTO_INCREMENT,
    txnNO varchar(64) NOT NULL,
    type smallint(5) unsigned NOT NULL,
    status smallint(5) unsigned NOT NULL,

    accountId bigint(20) unsigned NOT NULL,
    currencyType smallint(5) unsigned NOT NULL,
    vsAccountId bigint(20) unsigned NOT NULL,
    vsCurrencyType smallint(5) unsigned NOT NULL,
    amount bigint(20) NOT NULL,
    freezedAmount bigint(20) NOT NULL,
    remark varchar(128),

    dtNO varchar(64),
    tNO varchar(64),
    sNO varchar(64),

    dataVersion bigint(20) unsigned NOT NULL,
    dataSign varchar(128) NOT NULL,
    createTime datetime NOT NULL,
    modifyTime datetime NOT NULL,
    PRIMARY KEY(accountTransactionId)
)ENGINE=InnoDB DEFAULT CHARSET=utf8;



