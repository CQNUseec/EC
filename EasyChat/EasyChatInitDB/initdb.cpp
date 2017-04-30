#include "initdb.h"

bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("EASYCHAT");
    db.setUserName("EASYCHAT");
    db.setPassword("EASYCHAT");
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
               "password VARCHAR(16) NOT NULL, "
               "sex VARCHAR(2) NOT NULL, "
               "age INT NULL, "
               "nickname VARCHAR(32) NULL);");
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
    QSqlQuery query;
    query.exec("DROP TABLE Group");
    query.exec("CREATE TABLE Group("
               "groupAccount VARCHAR(16) NOT NULL PRIMARY KEY,"
               "groupName VARCHAR(32) NOT NULL,"
               "groupOwner VARCHAR(32) NULL);");
}


void createTableGroupLinkman()
{
    QSqlQuery query;
    query.exec("DROP TABLE Group_Linkman");
    query.exec("CREATE TABLE Group_Linkman("
               "groupAccount VARCHAR(16) NOT NULL,"
               "linkmanAccount VARCHAR(16) NOT NULL,"
               "remarkname VARCHAR(32) NULL);");
}


void createTableLinkman_LinkmanGroup()
{
    QSqlQuery query;
    query.exec("DROP TABLE Linkman_LinkmanGroup");
    query.exec("CREATE TABLE Linkman_LinkmanGroup("
               "account VARCHAR(16) NOT NULL,"
               "linkmanAccount VARCHAR(16) NOT NULL,"
               "linkmanGroupname VARCHAR(32) NOT NULL);"
               );
}

void createTableLinkmanGroup()
{
    QSqlQuery query;
    query.exec("DROP TABLE LinkmanGroup");
    query.exec("CREATE TABLE LinkmanGroup("
               "account VARCHAR(16) NOT NULL,"
               "linkmanGroupname VARCHAR(32) NOT NULL);"
               );
}

void createTableOfflineMessage()
{
    QSqlQuery query;
    query.exec("DROP TABLE OfflineMessage");
    query.exec("CREATE TABLE OfflineMessage("
               "account VARCHAR(16) NOT NULL,"
               "message VARCHAR(1024) NOT NULL);"
               );
}



