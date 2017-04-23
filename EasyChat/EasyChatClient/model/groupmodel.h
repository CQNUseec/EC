#ifndef GROUPCHATMODEL_H
#define GROUPCHATMODEL_H
#include <QAbstractListModel>

class GroupModel : public QAbstractListModel      //主界面，群组列表的model
{
    Q_OBJECT
public:
    explicit GroupModel(QString selfAccount);
    ~GroupModel();
    enum GroupItemInfo_Role
    {
        groupAccoutRole = Qt::UserRole + 1,
        groupNameRole,
        groupOwnerRole,
        bSelectedRole,
    };
    struct GroupItemInfo
    {
        QString             groupAccount;
        QString             groupName;
        QString             groupOwner;
        bool                bSelected{false};
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void loadDataToModel(QString groupAccout, QString groupName, QString groupOwner, QStringList groupMember);
    void setSelfAccount(QString selfAccount);
    void setbSelected(QString groupAccout);
private:
    void clearModelData();
private:
    QHash<int, QByteArray>         m_roleNames;
    QList<GroupItemInfo*>          m_qlGroupItemInfo;
    QHash<QString, QStringList>    m_qhGroupMember;
    QString                        m_selfAccount;
    int                            m_unReadMessageCount{0};
};

#endif // GROUPCHATMODEL_H
