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
            chatWindows.friendName = nickName;
        chatWindows.requestActivate();
    }
    Text {
        id: name
        anchors.centerIn: parent
//        property string remarksName: EcInteraction.getRemarksName(model.friendAccount)
        text: nickName //=== "" ? qsTr(model.friendName) : remarksName
    }
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            rec.z = 4;
            rec.height = 40;
            removeButton.visible = true;
        }
        onExited: {
            rec.z = 1;
            rec.height = 35;
            removeButton.visible = false;
        }
        onClicked: {
            chatWindows.friendAccount = model.friendAccount;
            chat.setCurrentChatPerson(model.friendAccount);
        }
    }
    Rectangle {
        id: removeButton
        width: 20
        height: 20
        visible: false
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 3
        radius: 15
        z: 5
        clip: true
        Image {          // 关闭按钮
            id:closeButton
            source: "/images/close0.png"
            anchors.centerIn: parent
            visible: removeButton.visible
            MouseArea {
                anchors.fill: parent
//                hoverEnabled: true
//                onEntered: {
//                    closeButton.source = "/images/close1.png";
//                }
//                onExited: {
//                    closeButton.source = "/images/close0.png";
//                }
                onClicked: {
                    console.log("remove");
                    EcInteraction.chat.removeDataFromChat(model.friendAccount);
                }
            }
        }
    }
}
