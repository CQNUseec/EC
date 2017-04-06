#ifndef CHATLISTMODEL_H
#define CHATLISTMODEL_H
#include <QAbstractListModel>

struct ChatItemInfo
{
    QString   friendAccount;
    QString   friendName;
    bool      bSelected{true};
    bool      bUnreadMessage{false};
};
class ChatListModel : public QAbstractListModel           //聊天界面正在聊天的列表的model
{
    Q_OBJECT
public:
    ChatListModel();
    ~ChatListModel();
    enum ChatItemInfo_Role
    {
        friendAccountRole = Qt::UserRole +1,
        friendNameRole,
        bSelectedRole,
        bUnreadMessageRole,
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void loadDataToModel(QString friendAccount, QString friendName, bool bUnreadMessage=false);
    void clearModelData();
    void setBSelected(QString friendAccount);
    QString removeData(QString friendAccount);
    bool isEmpty();
private:
    QHash<int, QByteArray>           m_roleNames;
    QList<ChatItemInfo*>             m_qlChatItemInfo;
    QString                          m_currentSelected{""};
};

#endif // CHATLISTMODEL_H
