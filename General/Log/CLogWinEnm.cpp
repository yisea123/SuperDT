#include "CLogWinEnm.h"
#include "clog.h"

EnmClearLogStragety CLogWinEnm::getClearLogStragetyFromString(QString strClearLogStragety)
{
    if("ENM_COUNT" == strClearLogStragety){
        return ENM_COUNT;
    }else if("ENM_SIZE" == strClearLogStragety){
        return ENM_SIZE;
    }else{
        logErrorWin()<<"传入错误的参数!";
        return ENM_COUNT;
    }
}

QString CLogWinEnm::getClearLogStragetyFromEnm(EnmClearLogStragety enmClearLogStragety)
{
    switch(enmClearLogStragety){
    case ENM_COUNT:
        return "ENM_COUNT";
    case ENM_SIZE:
        return "ENM_SIZE";
    default:
        logErrorWin()<<"传入错误的参数!";
        return "";
    }
}
