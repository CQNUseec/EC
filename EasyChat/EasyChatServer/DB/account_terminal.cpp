#include "account_terminal.h"

account_terminal::account_terminal()
{

}

QString account_terminal::addflag(QString account, QString flag)
{
    QSqlQuery query;
    query.prepare("INSERT INTO account_terminal (account, flag)"
                  "VALUES (:account, :flag)");
    query.bindValue(":account", account);
    query.bindValue(":flag", flag);
    query.exec();
    return "add_flag_success";
}

QString account_terminal::deleteflag(QString account)
{
    QSqlQuery query;
    QString del = QString("DELETE FROM account_terminal "
                          "WHERE account='%1'").arg(account);
    query.exec(del);
    return "delete_flag_success";
}

QString account_terminal::getflag(QString account)
{
    QString infoInDB=QString("SELECT flag FROM account_terminal "
                             "WHERE account = '%1'").arg(account);
    QSqlQuery query;
    query.exec(infoInDB);

    QString flag;
    flag= query.value(0).toString();
    return flag;
}
