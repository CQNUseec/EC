#include "account_terminal.h"

account_terminal::account_terminal()
{

}

bool account_terminal::addflag(QString account, QString flag)
{
    QSqlQuery query;
    query.prepare("INSERT INTO account_terminal (account, flag) "
                  "VALUES (:account, :flag)");
    query.bindValue(":account", account);
    query.bindValue(":flag", flag);
    if(query.exec())
        return true;
    else
        return false;
}

bool account_terminal::deleteflag(QString account)
{
    QSqlQuery query;
    QString del = QString("DELETE FROM account_terminal "
                          "WHERE account='%1'").arg(account);
    if (query.exec(del))
        return true;
    else
        return false;
}

string account_terminal::getflag(QString account)
{
    QString infoInDB=QString("SELECT * FROM account_terminal "
                             "WHERE account = '%1'").arg(account);
    QSqlQuery query;
    query.exec(infoInDB);

    string flag;
    if(query.next())
    {
        flag= query.value(1).toString().toStdString();
    }
    return flag;
}

bool account_terminal::isOnline(QString account)
{
    QString infoInDB=QString("SELECT * FROM account_terminal "
                             "WHERE account = '%1'").arg(account);
    QSqlQuery query;
    query.exec(infoInDB);

    if(query.next())
        return true;
    else
        return false;
}
