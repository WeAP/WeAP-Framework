#include "MySQL.h"
#include <sys/time.h>
#include "Logger.h"
#include <sstream>
#include "Convert.h"

namespace WeAP { namespace MySQL {


MySQL::MySQL()
{
    this->mysql = NULL;
    this->isConnected = false;
    this->isTrans = false;
}

MySQL::~MySQL()
{
    this->Close();

    this->TransEnd();
}

void MySQL::Init(const std::string& ip,
                    int port,
                    const std::string& user, 
                    const std::string& passwd, 
                    int waitTimeoutS,              
                    int connTimeoutS,
                    int rwTimeoutS,
                    const std::string& charset, 
                    const std::string& dbName)
{
    this->ip = ip;
    this->port = port;
    this->user = user;
    this->passwd = passwd; 
    this->dbName = dbName;
    this->connTimeoutS = connTimeoutS;
    this->rwTimeoutS = rwTimeoutS;
    this->waitTimeoutS = waitTimeoutS;
    this->charset = charset;

    INFO("ip:%s", this->ip.c_str());
    INFO("port:%d", this->port);
    INFO("user:%s", this->user.c_str());
    //INFO("passwd:%s", this->passwd.c_str());
    INFO("dbName:%s", this->dbName.c_str());
    INFO("connTimeoutS:%d", this->connTimeoutS);
    INFO("rwTimeoutS:%d", this->rwTimeoutS);
    INFO("waitTimeoutS:%d", this->waitTimeoutS);
    INFO("charset:%s", this->charset.c_str());

    this->Connect();

}


void  MySQL::Connect()
{
    if(this->mysql == NULL)
    {
        this->mysql = (MYSQL *)malloc(sizeof(MYSQL));
    }

    if (mysql_init(this->mysql) == NULL)
    {
        string err = this->GetDBError();
        ERROR("mysql_init failed, %s", err.c_str());
        throw Exception(Error::MySQL_Init_Failed, err);
    }


    mysql_options(this->mysql, MYSQL_SET_CHARSET_NAME, this->charset.c_str());

    mysql_options(this->mysql, MYSQL_OPT_CONNECT_TIMEOUT,  (char *)&this->connTimeoutS);
    mysql_options(this->mysql, MYSQL_OPT_READ_TIMEOUT,  (char *)&this->rwTimeoutS);
    mysql_options(this->mysql, MYSQL_OPT_WRITE_TIMEOUT,  (char *)&this->rwTimeoutS);
    //mysql_options(m_SqlHandle, MYSQL_OPT_RECONNECT, &reconnect);

    const char * unix_socket = NULL;
    unsigned long client_flag = 0;
    MYSQL* handle = mysql_real_connect(this->mysql, this->ip.c_str(), this->user.c_str(), this->passwd.c_str(), this->dbName.c_str(), this->port, unix_socket, client_flag);
    if (handle == NULL)
    {
        string err = this->GetDBError();
        ERROR("mysql_real_connect failed, %s", err.c_str());
        throw Exception(Error::MySQL_Connect_Failed, err);
    }

    this->SetWaitTimeout();

    INFO("mysql is connected.");
    this->isConnected = true;
}

void MySQL::SetWaitTimeout()
{
    if (this->idleTime <= 0)
    {
        return;
    }
    //wait_timeout针对非交互式连接。所谓的交互式连接，即在mysql_real_connect()函数中使用了CLIENT_INTERACTIVE选项。
    std::string sql = std::string("set wait_timeout=") + Convert::ToString(this->waitTimeoutS);
    this->Query(sql);

    //interactive_timeout针对交互式连接，
    sql = std::string("set interactive_timeout=") + Convert::ToString(this->waitTimeoutS);
    this->Query(sql);
}

void  MySQL::Close()
{
    if (this->mysql != NULL)
    { 
        mysql_close(this->mysql);
        free(this->mysql); 
        this->mysql = NULL;
    }

    this->isConnected = false;
}

bool MySQL::Ping()
{
    int ret = mysql_ping(this->mysql);
    if (ret != 0)
    {
        ERROR("mysql_ping failed, ret:%d", ret);
        return false;
    }
    return true;
}


void MySQL::Query(const string& sql, KVMap& record, bool removePrefixF)
{
    this->Execute(sql);
    MySQLResult result;
    result.Init(this->FetchResult());
    result.To(record, removePrefixF);
}

void MySQL::Query(const string& sql, ObjectList<KVMap>& recordList, bool removePrefixF)
{
    this->Execute(sql);
    MySQLResult result;
    result.Init(this->FetchResult());
    result.To(recordList, removePrefixF);
}

void MySQL::Insert(const string& sql)
{
    this->Execute(sql);
}

void MySQL::Update(const string& sql)
{
    this->Execute(sql);
}

/*
void MySQL::Query(const string& sql)
{
    this->Execute(sql);
}
*/
void MySQL::BatchQuery(const string& sql)
{
    this->Execute(sql);
}

void MySQL::BatchInsert(const string& sql)
{
    this->Execute(sql);
}

void MySQL::BatchUpdate(const string& sql)
{
    this->Execute(sql);
}


void MySQL::Execute(const string& sql)
{
    if (!this->isConnected && !this->IsTrans())
    {
        this->Close();
        this->Connect();
        INFO("=========connect");
    }

    this->Query(sql);
}



void MySQL::Begin()
{
    if (!this->isConnected)
    {
        this->Close();
        this->Connect();
    }

    if (this->IsTrans())
    {
        string err = this->GetDBError();
        ERROR("Begin: last trans unfinished, %s,", err.c_str());
        throw Exception(Error::MySQL_Begin_Failed, err);
    }

    string sql = "BEGIN";
    this->Query(sql);

    this->TransBegin();
}

void MySQL::Commit()
{
    if (!this->isConnected)
    {
        string err = this->GetDBError();
        ERROR("Commit: lost connection, %s,", err.c_str());
        throw Exception(Error::MySQL_Commit_Lost_Connection, err);
    }

    this->CheckTrans();
    
    string sql = "COMMIT";
    this->Query(sql);
    
    this->TransEnd();
}


void MySQL::Rollback()
{
    if (!this->isConnected)
    {
        this->Close();
        this->Connect();
    }

    // CheckTrans();

    string sql = "ROLLBACK";
    this->Query(sql);

    this->TransEnd();
}

bool MySQL::IsTrans()
{
    return this->isTrans;
}


void MySQL::TransBegin()
{
    this->isTrans = true;
}

void MySQL::TransEnd()
{
    this->isTrans = false;
}

void MySQL::CheckTrans()
{
    if (!this->IsTrans())
    {
        throw Exception(Error::MySQL_NOT_IN_TRANS, "not in trans");
    }
}

unsigned long MySQL::AffectedRows()
{
    my_ulonglong rownum = mysql_affected_rows(this->mysql);
    if (rownum == (my_ulonglong) -1)
    {
        string err = this->GetDBError();
        ERROR("mysql_affected_rows failed, %s", err.c_str());
        throw Exception(Error::MySQL_Affected_Rows_Error, err);
    }

    return rownum;
}


MYSQL_RES* MySQL::FetchResult()
{
    MYSQL_RES* res = mysql_store_result(this->mysql);
    if (res == NULL)
    {
        string err = this->GetDBError();
        ERROR("mysql_store_result is null, %s", err.c_str());
        throw Exception(Error::MySQL_Result_NULL, err);
    }
    
    return res;
}

int MySQL::FetchRows()
{
    MYSQL_RES* res = this->FetchResult();

    int rowsNum = mysql_num_rows(res);
    
    mysql_free_result(res);
    
    return rowsNum;
}


string MySQL::GetString(char *str)
{
    if (str == NULL)
    {
        return "";
    }
    return string(str);
}

string MySQL::EscapeString(const string& buff)
{
    int len = buff.length();
    char szTmp[len*2 + 1];
    memset(szTmp, 0, sizeof(szTmp));
    mysql_escape_string(szTmp, buff.c_str(), buff.length());
    
    return string(szTmp);
}

void MySQL::Query(const string& sql)
{
    if (!this->IsTrans())
    {
        //checkDBAvail(m_strHost, m_iPort);
    }

    int ret = this->RealQuery(sql);
    if (ret != 0)
    {
        unsigned int errNo = mysql_errno(this->mysql);
        if (errNo != 2013 &&  //ERROR 2013 (HY000): Lost connection to MySQL server during query
            errNo != 2006)    //ERROR 2006 (HY000): MySQL server has gone away
        {
            ERROR("=========RealQuery ret:%d, errno:%d", ret, errNo);
            throw Exception(Error::MySQL_Unknown_Error, this->GetDBError());
        }

        this->isConnected = false;
        this->Close();
        this->Connect();

        if (this->IsTrans())
        {
            throw Exception(Error::MySQL_Connection_Lost, this->GetDBError());
        }

        if (this->RealQuery(sql) !=  0)
        {
            throw Exception(Error::MySQL_Connection_Lost, this->GetDBError());
        }

    }
}


int MySQL::RealQuery(const string& sql)
{
    int ret = mysql_real_query(this->mysql, sql.c_str(), sql.size());
    if (ret != 0)
    {
        string err = this->GetDBError();
        ERROR("mysql_real_query failed, %s, sql:%s", err.c_str(), sql.c_str());
        //throw Exception(Error::MySQL_Query_Failed, err);
        return ret;
    }

    return 0;
}


string MySQL::GetDBError()
{
    unsigned int errNo = mysql_errno(this->mysql);
    const char* errorMsg = mysql_error(this->mysql);
    stringstream strstream;
    strstream << "mysql error:[" << errNo << "]" << errorMsg;
    return strstream.str();
}



}}