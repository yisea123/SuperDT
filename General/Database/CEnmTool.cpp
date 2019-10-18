#include "CEnmTool.h"
#include "clog.h"

EnmAcessProtocal CEnmTool::getAcessProtocalEnm(QString strAcessProtocol){
    if("ENM_ACESS_PROTOCAL_SINGAL" == strAcessProtocol){
        return ENM_ACESS_PROTOCAL_SINGAL;
    }else if("ENM_ACESS_PROTOCAL_UI_ONLY" == strAcessProtocol){
        return ENM_ACESS_PROTOCAL_UI_ONLY;
    }else if("ENM_ACESS_PROTOCAL_SERVER_ONLY" == strAcessProtocol){
        return ENM_ACESS_PROTOCAL_SERVER_ONLY;
    }else if("ENM_ACESS_PROTOCAL_DOUBLE" == strAcessProtocol){
        return ENM_ACESS_PROTOCAL_DOUBLE;
    }else if("ENM_ACESS_PROTOCAL_DISTRIBUTE" == strAcessProtocol){
        return ENM_ACESS_PROTOCAL_DISTRIBUTE;
    }else{
        logErrorWin()<<"CEnmTool:getAcessProtocalEnm，错误的参数："<<strAcessProtocol<<flushWin;
        return ENM_ACESS_PROTOCAL_UI_ONLY;
    }
}

QString CEnmTool::getEnmAcessProtocal(EnmAcessProtocal enm)
{
    switch (enm) {
    case ENM_ACESS_PROTOCAL_SINGAL:
        return "ENM_ACESS_PROTOCAL_SINGAL";
    case ENM_ACESS_PROTOCAL_UI_ONLY:
        return "ENM_ACESS_PROTOCAL_UI_ONLY";
    case ENM_ACESS_PROTOCAL_SERVER_ONLY:
        return "ENM_ACESS_PROTOCAL_SERVER_ONLY";
    case ENM_ACESS_PROTOCAL_DOUBLE:
        return "ENM_ACESS_PROTOCAL_DOUBLE";
    case ENM_ACESS_PROTOCAL_DISTRIBUTE:
        return "ENM_ACESS_PROTOCAL_DISTRIBUTE";
    default:
        logErrorWin()<<"CEnmTool::getEnmAcessProtocal 错误的枚举值"<<flushWin;
        return "";
    }
}

EnmServerName CEnmTool::getServerNameEnm(QString str)
{
    if("ENM_SERVER_ACCESSPORXY" == str){
        return ENM_SERVER_ACCESS_PROXY;
    }else if("ENM_SERVER_ALL_SERVER" == str){
        return ENM_SERVER_ALL_SERVER;
    }else if("ENM_SERVER_NOTIFIER_CLIENT_AND_SERVER" == str){
        return ENM_SERVER_NOTIFIER_CLIENT_AND_SERVER;
    }else if("ENM_SERVER_NOTIFIER_SERVER" == str){
        return ENM_SERVER_NOTIFIER_SERVER;
    }else if("ENM_SERVER_NOTIFIER_CLIENT" == str){
        return ENM_SERVER_NOTIFIER_CLIENT;
    }else if("ENM_SERVER_CODEC" == str){
        return ENM_SERVER_CODEC;
    }else if("ENM_SERVER_CentralController" == str){
        return ENM_SERVER_CentralController;
    }else if("ENM_SERVER_SCRIPT" == str){
        return ENM_SERVER_SCRIPT;
    }else if("ENM_SERVER_AREA" == str){
        return ENM_SERVER_AREA;
    }else if("ENM_SERVER_AUDIOMATRIX" == str){
        return ENM_SERVER_AUDIOMATRIX;
    }else if("ENM_SERVER_UserManagement" == str){
        return ENM_SERVER_UserManagement;
    }else if("ENM_SERVER_Projector" == str){
        return ENM_SERVER_Projector;
    }else if("ENM_SERVER_Record" == str){
        return ENM_SERVER_Record;
    }else if("ENM_SERVER_AUDIOMATRIX_EXTRON" == str){
        return ENM_SERVER_AUDIOMATRIX_EXTRON;
    }else if("ENM_SERVER_VIDEOMATRIX" == str){
        return ENM_SERVER_VIDEOMATRIX;
    }else if("ENM_SERVER_MEDIA" == str){
        return ENM_SERVER_MEDIA;
    }
    else{
        logErrorWin()<<"CEnmTool::getServerNameEnm 不识别的类型"<<flushWin;
        return ENM_SERVER_ERROR;
    }
}

QString CEnmTool::getServerName(EnmServerName enm)
{
    switch(enm){
    case ENM_SERVER_ACCESS_PROXY:
        return "ENM_SERVER_ACCESSPORXY";
    case ENM_SERVER_ALL_SERVER:
        return "ENM_SERVER_ALL_SERVER";
    case ENM_SERVER_NOTIFIER_CLIENT_AND_SERVER:
        return "ENM_SERVER_NOTIFIER_CLIENT";
    case ENM_SERVER_NOTIFIER_SERVER:
        return "ENM_SERVER_NOTIFIER_SERVER";
    case ENM_SERVER_NOTIFIER_CLIENT:
        return "ENM_SERVER_NOTIFIER_CLIENT";
    case ENM_SERVER_CODEC:
        return "ENM_SERVER_CODEC";
    case ENM_SERVER_CentralController:
        return "ENM_SERVER_CentralController";
    case ENM_SERVER_SCRIPT:
        return "ENM_SERVER_SCRIPT";
    case ENM_SERVER_AREA:
        return "ENM_SERVER_AREA";
    case ENM_SERVER_AUDIOMATRIX:
        return "ENM_SERVER_AUDIOMATRIX";
    case ENM_SERVER_UserManagement:
        return "ENM_SERVER_UserManagement";
    case ENM_SERVER_Projector:
        return "ENM_SERVER_PROJECTOR";
    case ENM_SERVER_Record:
        return "ENM_SERVER_Record";
    case ENM_SERVER_AUDIOMATRIX_EXTRON:
        return "ENM_SERVER_AUDIOMATRIX";
    case ENM_SERVER_VIDEOMATRIX:
        return "ENM_SERVER_VIDEOMATRIX";
    case ENM_SERVER_MEDIA:
        return "ENM_SERVER_MEDIA";
    default:
        logErrorWin()<<"CEnmTool::getServerName 不识别的类型"<<flushWin;
        return "ENM_SERVER_ERROR";
    }
}

QString CEnmTool::getStateTypeFromEnm(EnmDeviceState enm){
    switch(enm){
    case ENM_DEVICE_STATE_UNAUTHORITY://设备无权限
        return "ENM_DEVICE_STATE_UNAUTHORITY";
    case ENM_DEVICE_STATE_CONNECTED://设备在线
        return "ENM_DEVICE_STATE_CONNECTED";
    case ENM_DEVICE_STATE_DISCONNECTED://设备离线
        return "ENM_DEVICE_STATE_DISCONNECTED";
    case ENM_DEVICE_STATE_NOSIGNAL://编解码器无信号源
        return "ENM_DEVICE_STATE_NOSIGNAL";
    case ENM_DEVICE_STATE_LSOGIN_HEAT://投影仪散热中
        return "ENM_DEVICE_STATE_LSOGIN_HEAT";
    case ENM_DEVICE_STATE_RUNNING://投影仪运行中
        return "ENM_DEVICE_STATE_RUNNING";
    case ENM_DEVICE_STATE_CLOSED://投影仪关闭
        return "ENM_DEVICE_STATE_CLOSED";
    default:
        return "ENM_DEVICE_STATE_ERROR";
    }
}

EnmDeviceState CEnmTool::getStateEnmFromString(QString strStateEnm){
    if("ENM_DEVICE_STATE_UNAUTHORITY" == strStateEnm)//设备无权限
        return ENM_DEVICE_STATE_UNAUTHORITY;
    if("ENM_DEVICE_STATE_CONNECTED" == strStateEnm)//设备在线
        return ENM_DEVICE_STATE_CONNECTED;
    if("ENM_DEVICE_STATE_DISCONNECTED" == strStateEnm)//设备离线
        return ENM_DEVICE_STATE_DISCONNECTED;
    if("ENM_DEVICE_STATE_NOSIGNAL" == strStateEnm)//编解码器无信号源
        return ENM_DEVICE_STATE_NOSIGNAL;
    if("ENM_DEVICE_STATE_LSOGIN_HEAT" == strStateEnm)//投影仪散热中
        return ENM_DEVICE_STATE_LSOGIN_HEAT;
    if("ENM_DEVICE_STATE_RUNNING" == strStateEnm)//投影仪运行中
        return ENM_DEVICE_STATE_RUNNING;
    if("ENM_DEVICE_STATE_CLOSED" == strStateEnm)//投影仪关闭
        return ENM_DEVICE_STATE_CLOSED;

    return ENM_DEVICE_STATE_ERROR;
}

