#include "initdb.h"

bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("easychat");
    db.setUserName("easychat");
    db.setPassword("easychat");
    if(!db.open())
    {
         return false;
    }
    return true;
}


void createTableAccount()
{
    QSqlQuery query;
    query.exec("DROP TABLE account");

    query.exec("DROP TABLE account");
    query.exec("CREATE TABLE Account ("
               "account VARCHAR(16) NOT NULL PRIMARY KEY, "
               
               "password VARCHAR(32) NOT NULL, "
               "nickname VARCHAR(32) NOt NULL,"
               "sex VARCHAR(2) NOT NULL, "
               "age INT NULL);");

              // "password VARCHAR(16) NOT NULL, "
               //"sex VARCHAR(2) NOT NULL, "
               //"age INT NULL, "
              // "nickname VARCHAR(32) NULL);");
}


void createTableAccountTerminal()
{

        QSqlQuery query;
        query.exec("DROP TABLE account_terminal");
        query.exec("CREATE TABLE account_terminal("
                   "account VARCHAR(16) NOT NULL, "
                   "flag VARCHAR(32) NULL);");
}


void createTableGroup()
{

    QSqlQuery query;

    query.exec("DROP TABLE _group");

    query.exec("CREATE TABLE _group("
               "groupaccount VARCHAR(16) NOT NULL PRIMARY KEY,"
               "groupname VARCHAR(32) NOT NULL,"
               "groupowner VARCHAR(32) NULL);");
}


void createTableGroupLinkman()
{
    QSqlQuery query;
<<<<<<< HEAD
    query.exec("DROP TABLE group_linkman");
    query.exec("CREATE TABLE group_linkman("
               "groupAccount VARCHAR(16) NOT NULL,"
               "linkmanaccount VARCHAR(16) NOT NULL,"
               "remarkname VARCHAR(32) NULL);");
}


void createTableLinkman_LinkmanGroup()
{
    QSqlQuery query;

    query.exec("DROP TABLE linkman_linkmangroup");
    query.exec("CREATE TABLE linkman_linkmangroup("
               "account VARCHAR(16) NOT NULL,"
               "linkmanaccount VARCHAR(16) NOT NULL,"
               "linkmangroupname VARCHAR(32) NOT NULL,"
               "remarkname VARCHAR(32) NULL);"

   //query.exec("DROP TABLE Linkman_LinkmanGroup");
   // query.exec("CREATE TABLE Linkman_LinkmanGroup("
           //    "account VARCHAR(16) NOT NULL,"
            //   "linkmanAccount VARCHAR(16) NOT NULL,"
              // "linkmanGroupname VARCHAR(32) NOT NULL);"
               );
}

void createTableLinkmanGroup()
{
    QSqlQuery query;

    query.exec("DROP TABLE linkmangroup");
    query.exec("CREATE TABLE linkmangroup("
    //query.exec("DROP TABLE LinkmanGroup");
   // query.exec("CREATE TABLE LinkmanGroup("
               "account VARCHAR(16) NOT NULL,"
               "linkmanGroupname VARCHAR(32) NOT NULL);"
               );
}

void createTableOfflineMessage()
{
    QSqlQuery query;
    query.exec("DROP TABLE offlinemessage");
    query.exec("CREATE TABLE offlinemessage("
               "account VARCHAR(16) NOT NULL,"
               "message VARCHAR(512) NOT NULL);"
               
   // query.exec("DROP TABLE OfflineMessage");
   // query.exec("CREATE TABLE OfflineMessage("
              // "account VARCHAR(16) NOT NULL,"
              // "message VARCHAR(1024) NOT NULL);"
               );
}


void createTableDynamic()
{
    QSqlQuery query;
    query.exec("DROP TABLE dynamic");
    query.exec("CREATE TABLE dynamic("
               "dynamicid VARCHAR(32) NOT NULL PRIMARY KEY,"
               "account VARCHAR(16) NOT NULL,"
               "content VARCHAR(512) NOT NULL,"
               "time DATE);"
               );
}

