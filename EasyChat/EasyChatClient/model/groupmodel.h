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
    struct GroupMemberInfo
    {
        QString            mAccount;
        QString            mNickName;
        QString            mAge;
        QString            mSex;
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void loadDataToModel(QString groupAccout, QString groupName, QString groupOwner);
    void loadGroupMemberInfo(QString gAccount, QString mAccount, QString mNickName,
                             QString mAge, QString mSex);
    void setSelfAccount(QString selfAccount);
    void setbSelected(QString groupAccout);
    bool isGroupAccount(QString account);
    QString getMemberName(QString account);
signals:
    void sig_flushUI();
private:
    void clearModelData();
private:
    QHash<int, QByteArray>             m_roleNames;
    QList<GroupItemInfo*>              m_qlGroupItemInfo;
    QHash<QString, QList<GroupMemberInfo*>* >    m_qhGroupMember;
    QString                            m_selfAccount;
    int                                m_unReadMessageCount{0};
};

#endif // GROUPCHATMODEL_H
