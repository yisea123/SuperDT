#ifndef CENMTOOL_H
#define CENMTOOL_H

#include <QString>
enum EnmAcessProtocal{//访问协议：决定当前进程是客户端还是服务器，以及服务器如何认定
    ENM_ACESS_PROTOCAL_SINGAL = 0,//单机协议,即做服务器又做客户端
    ENM_ACESS_PROTOCAL_UI_ONLY,//纯UI协议，需要外部服务器；或用作纯客户端测试
    ENM_ACESS_PROTOCAL_SERVER_ONLY,//纯服务协议，无UI
    ENM_ACESS_PROTOCAL_DOUBLE,//双机热备协议
    ENM_ACESS_PROTOCAL_DISTRIBUTE,//分布式协议
};

enum EnmServerName{//服务名称，至关重要的枚举值，未经允许严禁做任何改动！！
    ENM_SERVER_ERROR = 0,
    /*特殊服务：涉及的协议在ProtocalCommon.h里*/
    ENM_SERVER_ACCESS_PROXY,//由访问代理处理，比如把数据发给全部服务器及客户端
    ENM_SERVER_ALL_SERVER,//谨慎使用该类型！！对全体服务都有效，比如数据同步命令。
    ENM_SERVER_NOTIFIER_CLIENT_AND_SERVER,//客户端回调和服务器回调均需处理的协议,比如单行数据同步
    ENM_SERVER_NOTIFIER_SERVER,//服务器回调处理的协议，比如数据同步请求
    ENM_SERVER_NOTIFIER_CLIENT,//客户端回调处理的协议，比如整表数据同步
    /*常规服务；这些服务涉及的协议由客户端发出或者服务器发出内容一样，最终执行效果一样*/
    ENM_SERVER_CODEC,
    ENM_SERVER_CentralController,
    ENM_SERVER_SCRIPT,
    ENM_SERVER_AREA,
    ENM_SERVER_AUDIOMATRIX,
    ENM_SERVER_UserManagement,
    ENM_SERVER_Middle,
    ENM_SERVER_Projector,
    ENM_SERVER_Record,
    ENM_SERVER_AUDIOMATRIX_EXTRON,
    ENM_SERVER_VIDEOMATRIX,
    ENM_SERVER_MEDIA,
};

enum EnmDeviceState{
    ENM_DEVICE_STATE_UNAUTHORITY,//设备无权限
    ENM_DEVICE_STATE_CONNECTED,//设备在线
    ENM_DEVICE_STATE_DISCONNECTED,//设备离线
    ENM_DEVICE_STATE_NOSIGNAL,//编解码器无信号源
    ENM_DEVICE_STATE_LSOGIN_HEAT,//投影仪散热中
    ENM_DEVICE_STATE_RUNNING,//投影仪运行中
    ENM_DEVICE_STATE_CLOSED,//投影仪关闭
    ENM_DEVICE_STATE_ERROR,//传入的枚举值错误
};

class CEnmTool
{
public:
    //访问协议
    static EnmAcessProtocal getAcessProtocalEnm(QString strAcessProtocol);
    static QString getEnmAcessProtocal(EnmAcessProtocal enm);
    //服务名称
    static EnmServerName getServerNameEnm(QString str);
    static QString getServerName(EnmServerName enm);
    //设备状态
    static QString getStateTypeFromEnm(EnmDeviceState enm);
    static EnmDeviceState getStateEnmFromString(QString strStateEnm);
};

#endif // CENMTOOL_H
