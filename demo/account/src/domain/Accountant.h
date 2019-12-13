#ifndef __WeAP_Accountant_H__
#define __WeAP_Accountant_H__

#include "Handler.h"
#include "Account.h"

using namespace WeAP::Framework;

class Accountant : public Handler
{

public:
    Accountant();
    virtual ~Accountant();

    void OpenAccount(Account& account);
    void CloseAccount(Account& account);
    void FreezeAccount(Account& account);

    void Transfer(Account& fromAccount, Account& toAccount);


protected:

};



#endif 
