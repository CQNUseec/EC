/*********************************
 ***   author: RanJT
 ***   date:   2017.3.1
 ***   聊天列表样式(Delegate)   Component类型
 ********************************/
import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4

Rectangle {
    id:rec
    width: 115
    height: 35
    z: 1
    color: "#B2DFEE"
    border.color: model.bSelected ? "green" : "white"
    property bool bordeColor: model.bSelected
    onBordeColorChanged: {
        if(bordeColor)
            chatWindows.friendName = model.friendName;
        chatWindows.requestActivate();
    }
    Text {
        anchors.centerIn: parent
        id: name
        text: qsTr(model.friendName)
    }
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            rec.z = 4;
            rec.height = 40;
        }
        onExited: {
            rec.z = 1;
            rec.height = 35;
        }
        onClicked: {
            chatWindows.friendName = model.friendName;
            chatWindows.friendAccount = model.friendAccount;
            chat.setCurrentChatPerson(model.friendAccount);
        }
    }
}
