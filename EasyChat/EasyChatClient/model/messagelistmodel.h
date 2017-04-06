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
class MessageListModel : public QAbstractListModel      //聊天窗口正在聊天时的消息实时显示，切换聊天对象的时，切换到对应的model，关闭时清空对应model
{
    Q_OBJECT
public:
    explicit MessageListModel(QString selfAccount);
    ~MessageListModel();
    enum MeeageInfo_Role
    {
        messageRole = Qt::UserRole + 1,        //消息内容
        senderRole,
        receiverRole,
        sendTimeRole,
        bDisplayLeftRole
    };
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void loadDataToModel(QString sender, QString receiver, QString message, QString sendTime);
private:
    void clearModelData();
private:
    QHash<int, QByteArray>          m_roleNames;
    QList<Message*>                 m_qlMessage;
    QString                         m_selfAccount;
};
#endif // MESSAGELISTMODEL_H
