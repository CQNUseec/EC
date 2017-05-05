
#include <QtSql>
#include <iostream>
#include <QString>

#include <vector>



//建立与postgre数据库的连接
bool createConnection();

//帐号相关的表（Account）
void createTableAccount();

//帐号与终端(Account_Terminal)
void createTableAccountTerminal();

//群聊(Group)
void createTableGroup();

//群聊-成员(Group_Linkman)
void createTableGroupLinkman();


//分组-成员(Linkman_LinkmanGroup)
void createTableLinkman_LinkmanGroup();

//联系人组(LinkmanGroup)
void createTableLinkmanGroup();

//离线消息(OfflineMessage)
void createTableOfflineMessage();

<<<<<<< HEAD
//动态（Dynamic）
void createTableDynamic();
=======
//
>>>>>>> 008efbef92568ad556fbc6589e9ee854a844217a
