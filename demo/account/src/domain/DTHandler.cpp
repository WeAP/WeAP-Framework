#include "DTHandler.h"


DTHandler::DTHandler()
{

}

DTHandler::~DTHandler()
{

}

void DTHandler::Parse(const string& params)
{
    KVMap kvParams;
    kvParams.Parse(params);
    this->dtContext.txnNO = kvParams["txnNO"];
    this->dtContext.dtNO = kvParams["dtNO"];
    this->dtContext.params.Parse(kvParams["data"]);

    this->dtContext.dtCMD = this->dtCMD;
    this->dtContext.currentStep = 0; 
    this->dtContext.lastTime = "";
    this->dtContext.stNum = 0;

}


