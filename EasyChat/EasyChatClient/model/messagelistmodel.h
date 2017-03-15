#ifndef MESSAGELISTMODEL_H
#define MESSAGELISTMODEL_H

#include <QAbstractListModel>

struct Message{
    QString message;
    QString sender;
    QString receiver;
    QString sendTime;
    bool    bDisplayLeft{true};
};
class MessageListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MessageListModel(QString selfAccount, QObject *parent = 0);
    ~MessageListModel();
    enum MeeageInfo_Role
    {
        message = Qt::UserRole + 1,        //消息内容
        sender,
        receiver,
        sendTime,
        bDisplayLeft
    };
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const;
    void loadDataToModel(QString sender, QString receiver, QString message, QString sendTime);
    void clearModelData();
private:
    QHash<int, QByteArray>          m_roleNames;
    QList<Message*>                 m_qlMessage;
    QString                         m_selfAccount;
};

#endif // MESSAGELISTMODEL_H
