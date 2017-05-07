#ifndef COMMENTARY_H
#define COMMENTARY_H

#include <QString>
#include <string>
#include <QtSql>
#include <iostream>

class Commentary
{
public:
    Commentary();
    bool addCommentary(QString account,QString DynamicId,QString content,QString time,QString commtentor);
};

#endif // COMMENTARY_H
