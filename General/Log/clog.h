#ifndef CLOG_H
#define CLOG_H

#include "CLogWin.h"


#define logWin()            CLogWin()::getInstance()->log(__FILE__,__FUNCTION__,__LINE__)
#define logFatalWin()       CLogWin::getInstance()->logFatal(__FILE__,__FUNCTION__,__LINE__)
#define logErrorWin()       CLogWin::getInstance()->logError(__FILE__,__FUNCTION__,__LINE__)
#define logWarnningWin()    CLogWin::getInstance()->logWarning(__FILE__,__FUNCTION__,__LINE__)
#define logImpInfoWin()     CLogWin::getInstance()->logInfo(__FILE__,__FUNCTION__,__LINE__)
#define logDebugWin()       CLogWin::getInstance()->logDebug(__FILE__,__FUNCTION__,__LINE__)


/**
注意！！如果使用继承打印的方式，在一个对象同时运行多个线程且多个线程同时通过继承打印打印日志时，将引起日志混乱。
此时，推荐主要的线程使用继承打印；其他线程采用宏打印

V2 张睿俊 2018年9月13日

类的功能：
1、宏打印：通过logWin等宏，及重载后的符号<<的方式，打印日志。注意，末尾必须用flushWin宏
2、继承打印：通过继承CLog类，并使用log()等函数，及重载后的符号<<的方式打印日志。末尾也需要用flushWin宏
3、判断是否处在测试状态（非测试状态不打印，而是对Error及ImpInfo写文件）
4、判断数据库信息是否打印
5、判断网络信息是否打印
6、在继承打印方式下，判断本对象及关联对象（若控件的子控件）的日志信息是否打印
**/

#endif
