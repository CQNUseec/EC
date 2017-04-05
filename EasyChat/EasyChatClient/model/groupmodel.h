#ifndef GROUPCHATMODEL_H
#define GROUPCHATMODEL_H
#include <QAbstractListModel>

struct GroupItemInfo{
    QString             groupAccount;
    QString             groupName;
    bool                bSelected{false};
};
class GroupModel : public QAbstractListModel      //主界面，群组列表的model
{
    Q_OBJECT
public:
    explicit GroupModel(QString selfAccount);
    ~GroupModel();
    enum GroupItemInfo_Role
    {
        groupAccoutRole = Qt::UserRole + 1,        //消息内容
        groupNameRole,
        bSelectedRole,
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;
    void loadDataToModel(QString groupAccout, QString groupName, QStringList groupMember);
    void setSelfAccount(QString selfAccount);
    void setbSelected(QString groupAccout);
private:
    void clearModelData();
private:
    QHash<int, QByteArray>         m_roleNames;
    QList<GroupItemInfo*>          m_qlGroupItemInfo;
    QHash<QString, QStringList>    m_qhGroupMember;
    QString                        m_selfAccount;
};

#endif // GROUPCHATMODEL_H
