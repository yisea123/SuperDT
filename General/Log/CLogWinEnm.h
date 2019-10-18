#ifndef CLOGWINENM_H
#define CLOGWINENM_H

#include <QString>

typedef enum {
    TIME_STYLE_1 = 1,
    TIME_STYLE_2,
    TIME_STYLE_3,
    TIME_STYLE_4,
}EnmDisplayTimeStyle;

typedef enum {
    LEVEL_FATAL = 1,
    LEVEL_ERROR,
    LEVEL_WARNING,
    LEVEL_INFO,
    LEVEL_DEBUG,
}EnmLogLevel;

typedef enum{
    ENM_COUNT = 1,
    ENM_SIZE,
}EnmClearLogStragety;

class CLogWinEnm
{
public:
    //访问协议
    static EnmClearLogStragety getClearLogStragetyFromString(QString strClearLogStragety);
    static QString getClearLogStragetyFromEnm(EnmClearLogStragety enmClearLogStragety);
};

#endif // CLOGWINENM_H
