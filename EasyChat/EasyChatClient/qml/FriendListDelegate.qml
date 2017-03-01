/*********************************
 ***   author: RanJT
 ***   date:   2017.3.1
 ***   好友列表的显示样式(Delegate)   Component类型
 ********************************/
import QtQuick 2.7
import QtQuick.Controls 2.0
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
        Text {
            anchors.left: leftButtonImage.right
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            text: model.groupName
            font.family: "微软雅黑"
            font.pointSize: 10
        }
        MouseArea {
            anchors.fill: groupName
            onClicked: {
                groupMemberList.visible = !groupMemberList.visible
                if(groupMemberList.visible)
                {
                    console.log("展开");
                }
                else
                {
                    console.log("收起");
                }
            }
        }
    }
    ColumnLayout{ //ColumnLayout和ListView的选择使用根据数据条数而定  上千条以下用ColumnLayout
        id:groupMemberList
        visible: false
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
                property bool bEntered: false
                color: model.bSelected ? "#FCEAA3" : (bEntered ? "#FCF0C1" : "#F0F8FD")
                radius: 3
                Text {
                    anchors.centerIn: parent
                    text:model.nickName
                    color: "black"
                    font.family: "微软雅黑"
                    font.pointSize: 10
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
                        myFriend.setbSelected(model.groupName, model.account);
                    }
                    onDoubleClicked: {
                        if(chat.isChatWindowOpen())
                        {
                            chat.loadDataToModel(model.nickName, model.account);
                            console.log("聊天窗口已打开，双击添加聊天人");
                            chatLoader.forceActiveFocus();
                            return;
                        }
                        chatLoader.setSource("chatWindow.qml", {"friendName": model.nickName});
                        chat.loadDataToModel(model.nickName, model.account);
                        console.log("双击打开聊天窗口")
                        //此处的处理还需根据实际情况设计（这只是个示例）
                    }
                }
            }
        }
    }

    //            ListView {
    //                height: 100
    //                width: 40
    //                id: groupMemberList
    //                delegate: groupListDelegate
    //                model: chs
    //                Component {
    //                    id: groupListDelegate
    //                    Row {
    //                        height: 20
    //                        width: 40
    //                        Item {
    //                            height: 1
    //                            width: 10
    //                        }
    //                        Text {
    //                            text:model.clumn1
    //                        }
    //                    }
    //                }
    //            }
}

