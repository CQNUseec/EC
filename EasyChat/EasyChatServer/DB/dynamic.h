#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <QString>
#include <string>
#include <QtSql>
#include <iostream>

using namespace std;

class Dynamic
{
public:
    Dynamic();
    bool addDynamic(QString dynamicId,QString account,QString content,QString time);
    bool deleteDynamic(QString dynamicId,QString account);
};

#endif // DYNAMIC_H
