#ifndef CHATLISTMODEL_H
#define CHATLISTMODEL_H
#include <QAbstractListModel>

class ChatListModel : public QAbstractListModel           //聊天界面正在聊天的列表的model
{
    Q_OBJECT
public:
    ChatListModel();
    ~ChatListModel();
    enum ChatItemInfo_Role
    {
        friendAccountRole = Qt::UserRole +1,
        nickNameRole,
        remarksNameRole,
        bSelectedRole,
        bUnreadMessageRole,
    };
    struct ChatItemInfo
    {
        QString   friendAccount;
        QString   nickName;
        QString   remarksName;
        bool      bSelected{true};
        bool      bUnreadMessage{false};
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void loadDataToModel(QString friendAccount, QString nickName, QString remarksName, bool bUnreadMessage=false);
    void clearModelData();
    void setBSelected(QString friendAccount);
    void setBUnreadMessage(QString friendAccount, bool bReaded);
    QString removeData(QString friendAccount);
    bool isEmpty();
    bool isAccountExist(QString friendAccount);
private:
    QHash<int, QByteArray>           m_roleNames;
    QList<ChatItemInfo*>             m_qlChatItemInfo;
    QString                          m_currentSelected{""};
};

#endif // CHATLISTMODEL_H
