#ifndef GROUPCHATMODEL_H
#define GROUPCHATMODEL_H
#include <QAbstractListModel>

struct Message{
    QString             groupAccout;
    QString             groupName;
    QStringList         groupMember;
};
class GroupChatModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit GroupChatModel(QString selfAccount);
    ~GroupChatModel();
    enum MeeageInfo_Role
    {
        groupAccoutRole = Qt::UserRole + 1,        //消息内容
        groupNameRole,
        receiverRole,
        groupMemberRole
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;
private:
    QHash<int, QByteArray>        m_roleNames;
    QString                       m_selfAccount;
};

#endif // GROUPCHATMODEL_H
