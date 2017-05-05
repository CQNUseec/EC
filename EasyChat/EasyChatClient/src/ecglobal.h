#ifndef ECGLOBAL_H
#define ECGLOBAL_H
#include <QtGlobal>

#ifdef Q_OS_LINUX
#define EC_SYSTEM_FONT "黑体"
#endif

#ifdef Q_OS_WIN32
#define EC_SYSTEM_FONT "微软雅黑"
#endif

#define  EC_NETWORK_LOGIN                  1
#define  EC_NETWORK_REGISTER               2
#define  EC_NETWORK_FIND_ACCOUNT           3
#define  EC_NETWORK_SEND_MESSAGE           4
#define  EC_NETWORK_FRIEND_LIST            5
#define  EC_NETWORK_ADD_FRIEND             6
#define  EC_NETWORK_AGREE_ADD_FRIEND       7
#define  EC_NETWORK_GROUP_LIST             8
#define  EC_NETWORK_LOGOUT                 9

#define EC_LOGIN_RESULT_WRONG_PASSWORD        -10        //登录密码错误
#define EC_LOGIN_RESULT_INVALID_ACCOUNT       -11        //无效的账号
#define EC_LOGIN_RESULT_SUCCESSFUL             10        //登录成功
#endif // ECGLOBAL_H
