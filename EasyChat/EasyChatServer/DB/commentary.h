#ifndef COMMENTARY_H
#define COMMENTARY_H

#include <QString>
#include <string>
#include <QtSql>
#include <iostream>

class commentary
{
public:
    commentary();
    bool addCommentary(QString account,QString DynamicId,QString content,QString time,QString commtentor);
};

#endif // COMMENTARY_H
