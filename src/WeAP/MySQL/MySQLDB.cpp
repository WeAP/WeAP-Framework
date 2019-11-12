#include "MySQLDB.h"
#include <sys/time.h>
#include "Logger.h"
#include <sstream>
#include "Convert.h"

namespace WeAP { namespace MySQL {


MySQLDB::MySQLDB()
{
    this->mysql = NULL;
    this->isConnected = false;
    this->isTrans = false;
}

MySQLDB::~MySQLDB()
{
    this->Close();

    this->TransEnd();
}

void MySQLDB::Init(const std::string& ip,
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
}

void MySQLDB::Query(const string& sql, KVMap& record, bool removePrefixF)
{
    this->Execute(sql);
    MySQLResult result;
    result.Init(this->FetchResult());
    result.To(record, removePrefixF);
}

void MySQLDB::Query(const string& sql, ObjectList<KVMap>& recordList, bool removePrefixF)
{
    this->Execute(sql);
    MySQLResult result;
    result.Init(this->FetchResult());
    result.To(recordList, removePrefixF);
}

void MySQLDB::Insert(const string& sql)
{
    this->Execute(sql);
}

void MySQLDB::Update(const string& sql)
{
    this->Execute(sql);
}

/*
void MySQLDB::Query(const string& sql)
{
    this->Execute(sql);
}
*/
void MySQLDB::BatchQuery(const string& sql)
{
    this->Execute(sql);
}

void MySQLDB::BatchInsert(const string& sql)
{
    this->Execute(sql);
}

void MySQLDB::BatchUpdate(const string& sql)
{
    this->Execute(sql);
}


void MySQLDB::Execute(const string& sql)
{
    if (!this->isConnected && !this->IsTrans())
    {
        this->Close();
        this->Connect();
    }

    this->Query(sql);
}


void  MySQLDB::Connect()
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

      const char * unix_socket = NULL;
      unsigned long client_flag = 0;
    if (mysql_real_connect(this->mysql, this->ip.c_str(), this->user.c_str(), this->passwd.c_str(), this->dbName.c_str(), port, unix_socket, client_flag))
    {
        string err = this->GetDBError();
        ERROR("mysql_real_connect failed, %s", err.c_str());
        throw Exception(Error::MySQL_Connect_Failed, err);
    }

    this->SetWaitTimeout();

    this->isConnected = true;
}

void MySQLDB::SetWaitTimeout()
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

void  MySQLDB::Close()
{
    if (this->mysql != NULL)
    { 
        mysql_close(this->mysql);
        free(this->mysql); 
        this->mysql = NULL;
    }

    this->isConnected = false;
}

bool MySQLDB::Ping()
{
    int ret = mysql_ping(this->mysql);
    if (ret != 0)
    {
        ERROR("mysql_ping failed, ret:%d", ret);
        return false;
    }
    return true;
}



void MySQLDB::Begin()
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

void MySQLDB::Commit()
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


void MySQLDB::Rollback()
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

bool MySQLDB::IsTrans()
{
    return this->isTrans;
}


void MySQLDB::TransBegin()
{
    this->isTrans = true;
}

void MySQLDB::TransEnd()
{
    this->isTrans = false;
}

void MySQLDB::CheckTrans()
{
    if (!this->IsTrans())
    {
        throw Exception(Error::MySQL_NOT_IN_TRANS, "not in trans");
    }
}

unsigned long MySQLDB::AffectedRows()
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


MYSQL_RES* MySQLDB::FetchResult()
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

int MySQLDB::FetchRows()
{
    MYSQL_RES* res = this->FetchResult();

    int rowsNum = mysql_num_rows(res);
    
    mysql_free_result(res);
    
    return rowsNum;
}


string MySQLDB::GetString(char *str)
{
    if (str == NULL)
    {
        return "";
    }
    return string(str);
}

string MySQLDB::EscapeString(const string& buff)
{
    int len = buff.length();
    char szTmp[len*2 + 1];
    memset(szTmp, 0, sizeof(szTmp));
    mysql_escape_string(szTmp, buff.c_str(), buff.length());
    
    return string(szTmp);
}

void MySQLDB::Query(const string& sql)
{
    if (!this->IsTrans())
    {
        //checkDBAvail(m_strHost, m_iPort);
    }

    int ret = this->RealQuery(sql);
    if (ret != 0)
    {
        unsigned int errno = mysql_errno(this->mysql);
        if (errno != 2013 &&  //ERROR 2013 (HY000): Lost connection to MySQL server during query
            errno != 2006)    //ERROR 2006 (HY000): MySQL server has gone away
        {
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


int MySQLDB::RealQuery(const string& sql)
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


string MySQLDB::GetDBError()
{
    unsigned int errno = mysql_errno(this->mysql);
    const char* error = mysql_error(this->mysql);
    stringstream strstream;
    strstream << "mysql errno:" << errno << ", error:" << error;
    return strstream.str();
}



}}