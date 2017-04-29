#include "account.h"

extern int number;
account::account()
{
}

QString account::registerAcount(QString account, QString password, QString nickname, QString sex, QString age)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Account(account, password,nickname, sex, age)"
                  "VALUES (:account, :password,:nickname, :sex, :age)");
    query.bindValue(":account", account);
    query.bindValue(":password", password);
    query.bindValue(":nickname", nickname);
    query.bindValue(":sex", sex);
    query.bindValue(":age", age);
    query.exec();
    return "regist_success";
}

QString account::assignAccount()
{
    int act=number+1;
    QString ret=QString(act);
    return ret;
}

QString account::login(QString account, QString password)
{
    QString infoInDB=QString("SELECT account,password FROM Account "
                             "WHERE account = '%1'").arg(account);
    QSqlQuery query;
    query.exec(infoInDB);

    if(query.next())
    {
        QString pwd = query.value(1).toString();
        if(password == pwd)
            return "ok";
        else
            return "wrong_password";
    }
    else
        return "invalid_user";
}

//按帐号，昵称，性别，年龄返回
vector<QString> account::find(QString account)
{
    QString infoInDB=QString("SELECT account,nickname,sex,age"
                             "FROM Account WHERE account ='%1'").arg(account);
    QSqlQuery query;
    query.exec(infoInDB);

    vector<QString> ret;
    if(query.next())
    {
           for(int i=0;i<query.size();i++)
           {
               QString tmpvalue = query.value(i).toString();
               ret.push_back(tmpvalue);
           }
    }
    return ret;
}

