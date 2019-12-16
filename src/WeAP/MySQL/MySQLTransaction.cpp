#include "MySQLTransaction.h"


namespace WeAP { namespace MySQL {


MySQLTransaction::MySQLTransaction(MySQL* mysql)
{
    this->mysql = mysql;
    this->status = NotBegin;
}

MySQLTransaction::~MySQLTransaction()
{
    if (this->status == Began)
    {
        this->mysql->Rollback();
        this->status = Rollbacked;
    }

}

void MySQLTransaction::Begin()
{
    this->mysql->Begin();
    this->status = Began;
}

void MySQLTransaction::Commit()
{
    this->mysql->Commit();
    this->status = Committed;
}

MySQL* MySQLTransaction::GetMySQL()
{
    return this->mysql;
}

}}