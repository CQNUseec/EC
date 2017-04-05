/*********************************
 ***   author: RanJT
 ***   date:   2017.3.1
 ***   好友列表的显示样式(Delegate)   Component类型
 ********************************/
import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4

Column {
    id: objRecursiveColumn
    clip: true
    property int itemWidth: 200
    Item {
        id: groupName
        height: 20
        width: objRecursiveColumn.itemWidth
        Image {
            id:leftButtonImage
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            source: groupMemberList.visible ? "/images/unfolded.png": "/images/folod.png"
        }
        TextField {
            anchors.left: leftButtonImage.right
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            text: model.groupName
            font.family: SystemFont
            readOnly: true
            font.pointSize: 10
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
            style: ECTextFieldStyle{ borderWidth: 0}

        }
        MouseArea {
            anchors.fill: groupName
            onClicked: {
                groupMemberList.visible = !groupMemberList.visible
                if(groupMemberList.visible)
                {
                    console.log("展开分组");
                }
                else
                {
                    console.log("收起分组");
                }
            }
        }
    }
    ColumnLayout{ //ColumnLayout和ListView的选择使用根据数据条数而定  上千条以下用ColumnLayout
        id:groupMemberList
        visible: false
        spacing: 0
        Repeater {
            model: chs
            delegate: groupListDelegate
            focus: true
        }
        Component {
            id: groupListDelegate
            Rectangle {
                id: memberRec
                height: 50
                width: objRecursiveColumn.itemWidth
                property string friendName: model.nickName
                property string friendAccount: model.account
                property bool bEntered: false
                property bool bEditState: false
                color: model.bSelected ? "#FCEAA3" : (bEntered ? "#FCF0C1" : "#F0F8FD")
                radius: 3
                TextField {
                    id: textField
                    anchors.fill: parent
                    text:model.nickName
                    font.family: SystemFont
                    readOnly: memberRec.bEditState
                    font.pointSize: 10
                    menu: Menu {
                        MenuItem {
                            text: qsTr("发送消息")
                            onTriggered: {
                                chatWithFriend(memberRec.friendName, memberRec.friendAccount, EcInteraction.selfAccount);
                            }
                        }
                        MenuItem {
                            text: qsTr("修改备注")
                            onTriggered: {
//                                memberRec.bEditState = true;
//                                textField.focus = true;
//                                textField.selectAll();
                                console.log("修改备注");
                            }
                        }
                    }
                    style: ECTextFieldStyle{recColor: memberRec.color; borderWidth: 0}
                    onEditingFinished: {
                        memberRec.bEditState = false;
                        textField.focus = false;
                    }
                }
                MouseArea {
                    anchors.fill: memberRec
                    hoverEnabled: true
                    onEntered: {
                        memberRec.bEntered = true;
                    }
                    onExited: {
                        memberRec.bEntered = false;
                    }
                    onClicked: {
                        EcInteraction.friendList.setbSelected(model.groupName, model.account);
                    }
                    onDoubleClicked: {
                        chatWithFriend(memberRec.friendName, memberRec.friendAccount, EcInteraction.selfAccount);
                    }
                }
            }
        }
    }
    //    Component {
    //        id: friendItemMenu
    //        Menu {
    //            MenuItem {
    //                text: qsTr("发送消息")
    //                onTriggered: {
    //                    chatWithFriend(memberRec.friendName, memberRec.friendAccount, EcInteraction.selfAccount);
    //                }
    //            }
    //            MenuItem {
    //                text: qsTr("修改备注")
    //                onTriggered: {
    //                    console.log("修改备注");
    //                }
    //            }
    //        }
    //    }
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

