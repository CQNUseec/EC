#ifndef ECGLOBAL_H
#define ECGLOBAL_H
#include <QtGlobal>

#ifdef Q_OS_LINUX
#define EC_SYSTEM_FONT "黑体"
#endif

#ifdef Q_OS_WIN32
#define EC_SYSTEM_FONT "微软雅黑"
#endif

#define EC_LOGIN_RESULT_WRONG_PASSWORD        -10        //登录密码错误
#define EC_LOGIN_RESULT_INVALID_ACCOUNT       -11        //无效的账号
#define EC_LOGIN_RESULT_SUCCESSFUL             10        //登录成功
#endif // ECGLOBAL_H
