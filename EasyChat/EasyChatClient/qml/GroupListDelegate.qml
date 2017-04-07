/*********************************
 ***   author: RanJT
 ***   date:   2017.4.5
 ***   群组列表的显示样式(Delegate)   Component类型
 ********************************/
import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
Rectangle {
    id: groupMemberRec
    clip: true
    width: itemWidth
    height: 50
    radius: 3
    color: bSelected ? "#FCEAA3" : (bEntered ? "#FCF0C1" : "#FFFFFF")
    onColorChanged: {
        if(model.bSelected)
            console.log("selected");
    }
    property int itemWidth: 200
    property bool bEntered: false
        TextField {
            anchors.fill: parent
            text: groupAccount + groupName
            font.family: SystemFont
            readOnly: true
            font.pointSize: 10
            selectByMouse: false
            menu: Menu {
                MenuItem {
                    text: qsTr("添加分组")
                    onTriggered: {
                        console.log("添加分组");
                    }
                }
                MenuItem {
                    text: qsTr("修改分组")
                    onTriggered: {
                        console.log("修改分组");
                    }
                }
            }
            style: ECTextFieldStyle{recColor: groupMemberRec.color; borderWidth: 0}
        }
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            groupMemberRec.bEntered = true;
        }
        onExited: {
            groupMemberRec.bEntered = false;
        }
        onClicked: {
            EcInteraction.setGroupSelected(groupAccount);
        }
        onDoubleClicked: {
            chatWithFriend(groupName, groupAccount, EcInteraction.selfAccount);
        }
    }
    function chatWithFriend(friendName, friendAccount, selfAccount)
    {
        if(EcInteraction.chat.isChatWindowOpen())
        {
            EcInteraction.chat.loadDataToChat(friendName, friendAccount, selfAccount);
            console.log("窗口已打开，添加聊天人");
            return;
        }
        chatLoader.setSource("chatWindow.qml", {"friendName": friendName, "friendAccount": friendAccount});
        EcInteraction.chat.loadDataToChat(friendName, friendAccount, selfAccount);
        console.log("打开聊天窗口")
    }
}

