#ifndef MAINMESSAGEMODEL_H
#define MAINMESSAGEMODEL_H
#include <QAbstractListModel>

class MainMessageModel : public QAbstractListModel    // 主界面消息列表的model
{
    Q_OBJECT
public:
    explicit MainMessageModel();
    ~MainMessageModel();
    enum MainMessageInfo_Role
    {
        messageRole = Qt::UserRole + 1,
        senderRole,
        receiverRole,
        sendTimeRole,
        operationRole,
        idNumRole
    };
    struct MainMessageInfo
    {
        int idNum;
        QString message;
        QString sender;
        QString receiver;
        QString sendTime;
        int     operation;   // 1:个人聊天消息  2:群聊消息  3:添加好友请求  4: 加入群请求
    };
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    void loadDataToModel(int operation, QString sender, QString receiver, QString message);   //新的聊天消息
    void removeData(int idNum);
    //    void loadDataToModel(int operation, QString message);  //添加好友请求
//    void loadDataToModel(int operation, QString message);  //加入群请求
signals:
    void sig_flushUI();
private:
    QHash<int, QByteArray>               m_roleNames;
    QList<MainMessageInfo*>              m_qlMainMessage;
    int                                  m_idNum{0};
};

#endif // MAINMESSAGEMODEL_H
