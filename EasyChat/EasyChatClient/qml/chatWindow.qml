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


Window {
    id: chatWindows;
    width: 800
    height: 500
    visible: true
    flags: Qt.Window | Qt.FramelessWindowHint
    property string friendName: ""
    onClosing: {
        chat.clearModel();
        console.log("关闭聊天窗口， 清空聊天列表");
    }
    TitleRec {
        id: topRct
        width: parent.width
        height: 27
        color:"#005791"
        window: chatWindows
        titleText: friendName
    }
    Rectangle {    // 左边边框
        id: leftTabRec
        anchors.top: topRct.bottom
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
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("聊天列表")
            font.family: "微软雅黑"
        }
            ListView {
                id: chatingFriendList
                anchors.top: friendListTitle.bottom
                anchors.bottom: parent.bottom
                width: parent.width
                height: parent.height - friendListTitle.height
                model: chatFriendList
                delegate: ChatListDelegate{}
            }
            ListViewSlideBar {
                anchors.top: chatingFriendList.top
                anchors.right: parent.right
                anchors.bottom: chatingFriendList.bottom
                view: chatingFriendList
            }
    }
    Rectangle {   //聊天内容显示框
        id: chatContentRec
        anchors.top: topRct.bottom
        anchors.left: leftTabRec.right
        anchors.right: parent.right
        height: parent.height * 0.7
        border.color: "red"
        border.width: 2
        radius: 3
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
        border.width: 2
        radius: 3
        Text {
            anchors.centerIn: parent
            text: qsTr("聊天内容输入框")
        }
    }
}
