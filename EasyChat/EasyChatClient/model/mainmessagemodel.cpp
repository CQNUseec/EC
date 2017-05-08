#include "mainmessagemodel.h"

MainMessageModel::MainMessageModel()
{
    m_roleNames.insert(idNumRole, "idNum");
    m_roleNames.insert(messageRole, "message");
    m_roleNames.insert(senderRole, "sender");
    m_roleNames.insert(receiverRole, "receiver");
    m_roleNames.insert(sendTimeRole, "sendTime");
    m_roleNames.insert(operationRole, "operation");
}

MainMessageModel::~MainMessageModel()
{
    foreach(auto var, m_qlMainMessage)
    {
        delete var;
    }
    m_qlMainMessage.clear();
}

int MainMessageModel::rowCount(const QModelIndex &parent) const
{
    return m_qlMainMessage.count();
}

QVariant MainMessageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(m_qlMainMessage.isEmpty())
        return QVariant();
    switch (role)
    {
    case messageRole:
        return m_qlMainMessage.at(index.row())->message;
    case senderRole:
        return m_qlMainMessage.at(index.row())->sender;
    case receiverRole:
        return m_qlMainMessage.at(index.row())->receiver;
    case sendTimeRole:
        return m_qlMainMessage.at(index.row())->sendTime;
    case operationRole:
        return m_qlMainMessage.at(index.row())->operation;
    case idNumRole:
        return m_qlMainMessage.at(index.row())->idNum;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> MainMessageModel::roleNames() const
{
    return m_roleNames;
}

void MainMessageModel::loadDataToModel(int operation, QString sender, QString receiver, QString message)
{
    emit layoutAboutToBeChanged();
    MainMessageInfo* mes = new MainMessageInfo;
    mes->operation = operation;
    mes->sender = sender;
    mes->receiver = receiver;
    mes->message = message;
    mes->idNum = m_idNum;
    m_qlMainMessage.append(mes);
    emit layoutChanged();
    ++m_idNum;
}

void MainMessageModel::removeData(int idNum)
{
    emit layoutAboutToBeChanged();
    for(auto it = m_qlMainMessage.begin(); it != m_qlMainMessage.end(); ++it)
    {
        if((*it)->idNum == idNum)
        {
            delete *it;
            m_qlMainMessage.erase(it);
            emit layoutChanged();
        }
    }
}
