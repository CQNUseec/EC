#include "initdb.h"

bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
<<<<<<< HEAD
    db.setDatabaseName("easychat");
    db.setUserName("easychat");
    db.setPassword("easychat");
=======
    db.setDatabaseName("EASYCHAT");
    db.setUserName("EASYCHAT");
    db.setPassword("EASYCHAT");
>>>>>>> 008efbef92568ad556fbc6589e9ee854a844217a
    if(!db.open())
    {
         return false;
    }
    return true;
}


void createTableAccount()
{
    QSqlQuery query;
    query.exec("DROP TABLE Account");

    query.exec("DROP TABLE Account");
    query.exec("CREATE TABLE Account ("
               "account VARCHAR(16) NOT NULL PRIMARY KEY, "
<<<<<<< HEAD
               "password VARCHAR(32) NOT NULL, "
               "nickname VARCHAR(32) NOt NULL,"
               "sex VARCHAR(2) NOT NULL, "
               "age INT NULL);");
=======
               "password VARCHAR(16) NOT NULL, "
               "sex VARCHAR(2) NOT NULL, "
               "age INT NULL, "
               "nickname VARCHAR(32) NULL);");
>>>>>>> 008efbef92568ad556fbc6589e9ee854a844217a
}


void createTableAccountTerminal()
{

        QSqlQuery query;
        query.exec("DROP TABLE Account_Terminal");
        query.exec("CREATE TABLE Account_Terminal("
                   "account VARCHAR(16) NOT NULL, "
                   "flag VARCHAR(32) NULL);");
}


void createTableGroup()
{
<<<<<<< HEAD

    QSqlQuery query;

    query.exec("DROP TABLE _group");

    query.exec("CREATE TABLE _group("
=======
    QSqlQuery query;
    query.exec("DROP TABLE Group");
    query.exec("CREATE TABLE Group("
>>>>>>> 008efbef92568ad556fbc6589e9ee854a844217a
               "groupAccount VARCHAR(16) NOT NULL PRIMARY KEY,"
               "groupName VARCHAR(32) NOT NULL,"
               "groupOwner VARCHAR(32) NULL);");
}


void createTableGroupLinkman()
{
    QSqlQuery query;
<<<<<<< HEAD
    query.exec("DROP TABLE group_linkman");
    query.exec("CREATE TABLE group_linkman("
=======
    query.exec("DROP TABLE Group_Linkman");
    query.exec("CREATE TABLE Group_Linkman("
>>>>>>> 008efbef92568ad556fbc6589e9ee854a844217a
               "groupAccount VARCHAR(16) NOT NULL,"
               "linkmanAccount VARCHAR(16) NOT NULL,"
               "remarkname VARCHAR(32) NULL);");
}


void createTableLinkman_LinkmanGroup()
{
    QSqlQuery query;
<<<<<<< HEAD
    query.exec("DROP TABLE linkman_linkmangroup");
    query.exec("CREATE TABLE linkman_linkmangroup("
               "account VARCHAR(16) NOT NULL,"
               "linkmanaccount VARCHAR(16) NOT NULL,"
               "linkmangroupname VARCHAR(32) NOT NULL,"
               "remarkname VARCHAR(32) NULL);"
=======
    query.exec("DROP TABLE Linkman_LinkmanGroup");
    query.exec("CREATE TABLE Linkman_LinkmanGroup("
               "account VARCHAR(16) NOT NULL,"
               "linkmanAccount VARCHAR(16) NOT NULL,"
               "linkmanGroupname VARCHAR(32) NOT NULL);"
>>>>>>> 008efbef92568ad556fbc6589e9ee854a844217a
               );
}

void createTableLinkmanGroup()
{
    QSqlQuery query;
<<<<<<< HEAD
    query.exec("DROP TABLE linkmangroup");
    query.exec("CREATE TABLE linkmangroup("
=======
    query.exec("DROP TABLE LinkmanGroup");
    query.exec("CREATE TABLE LinkmanGroup("
>>>>>>> 008efbef92568ad556fbc6589e9ee854a844217a
               "account VARCHAR(16) NOT NULL,"
               "linkmanGroupname VARCHAR(32) NOT NULL);"
               );
}

void createTableOfflineMessage()
{
    QSqlQuery query;
<<<<<<< HEAD
    query.exec("DROP TABLE offlinemessage");
    query.exec("CREATE TABLE offlinemessage("
               "account VARCHAR(16) NOT NULL,"
               "message VARCHAR(512) NOT NULL);"
=======
    query.exec("DROP TABLE OfflineMessage");
    query.exec("CREATE TABLE OfflineMessage("
               "account VARCHAR(16) NOT NULL,"
               "message VARCHAR(1024) NOT NULL);"
>>>>>>> 008efbef92568ad556fbc6589e9ee854a844217a
               );
}



<<<<<<< HEAD

void createTableDynamic()
{
    QSqlQuery query;
    query.exec("DROP TABLE dynamic");
    query.exec("CREATE TABLE dynamic("
               "dynamicId VARCHAR(32) NOT NULL PRIMARY KEY,"
               "account VARCHAR(16) NOT NULL,"
               "content VARCHAR(512) NOT NULL,"
               "time DATE);"
               );
}
=======
>>>>>>> 008efbef92568ad556fbc6589e9ee854a844217a
