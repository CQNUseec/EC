/*********************************
 ***   author: RanJT
 ***   date:   2017.3.1
 ***   聊天界面（聊天窗口）
 ********************************/
import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQml.Models 2.2


ApplicationWindow {
    id: chatWindows;
    property string friendName: ""
    width: 800
    height: 500
    visible: true
    title: qsTr("chat with " + friendName)
    onClosing: {
        chat.clearModel();
        console.log("关闭聊天窗口， 清空聊天列表");
    }
    Rectangle {    // 左边边框
        id: leftTabRec
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: 120
        focus: true
        Keys.enabled: true
        Keys.onEscapePressed: {
            chatWindows.close();
        }
        Text {
            id: friendListTitle
            height: 20
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("聊天列表")
            font.family: "微软雅黑"
        }
        ScrollView {
            id:scrollViewFriendList
            anchors.top: friendListTitle.bottom
            anchors.bottom: parent.bottom
            width: parent.width
            height: parent.height - friendListTitle.height
            ListView {
                id: friendList
                anchors.fill: parent
                model: chatFriendList
                delegate: ChatListDelegate{}
            }
        }
    }
    Rectangle {   //聊天内容显示框
        id: chatContentRec
        anchors.top: parent.top
        anchors.left: leftTabRec.right
        anchors.right: parent.right
        height: 350
        border.color: "blue"
        border.width: 5
        radius: 5
        Text {
            anchors.centerIn: parent
            text: qsTr("聊天内容显示框")
        }
    }
    Rectangle {  // 聊天内容输入框
        id: enterRec
        anchors.top: chatContentRec.bottom
        anchors.bottom: parent.bottom
        anchors.left: leftTabRec.right
        anchors.right: parent.right
        border.color: "yellow"
        border.width: 5
        radius: 5
        Text {
            anchors.centerIn: parent
            text: qsTr("聊天内容输入框")
        }
    }
}
