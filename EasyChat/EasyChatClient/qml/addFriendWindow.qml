/*********************************
 ***   author: RanJT
 ***   date:   2017.4.14
 ***   添加好友界面， 添加群成员界面（待定）
 ********************************/

import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQml.Models 2.2
Window {
    id: addFriendWindow
    width: 800
    height: 500
    visible: true
    flags: Qt.Window | Qt.FramelessWindowHint
    property bool bAddFriend: true
    property bool bAddGroupMember: false
    property string initiatedAccount: ""
    property string aimsAccount: ""
    TitleRec {
        id: topRec
        width: parent.width
        height: 27
        color:"#005791"
        titleText: qsTr("查找账号")
        window: addFriendWindow
        biggestButtonVisible: false
    }
    Rectangle {        //左边框
        width: 1
        anchors.top: topRec.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        color: "#C8C8C8"
        z:5
    }
    Rectangle {        //右边框
        width: 1
        anchors.top: topRec.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        color: "#C8C8C8"
        z:5
    }
    Rectangle {        //底部边框
        height: 1
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        color: "#C8C8C8"
        z:5
    }
    Text {
        id: addFriendRec
        anchors.centerIn: parent
        font.pointSize: 11
        font.family: SystemFont
        text: initiatedAccount + " 请求添加您为好友"
    }
    Button {
        id: agree
        anchors.horizontalCenter: addFriendRec.horizontalCenter
        anchors.top: addFriendRec.bottom
        anchors.topMargin: 5
        style: ECButtonStyle{ button: add; buttonText: qsTr("同意") }
        onClicked: {
            agree.enabled = false;
            ignore.enabled =false;
            var jsonData = new Object();
            jsonData.purpose = 7;
            jsonData.initiated = initiatedAccount;
            jsonData.aims = aimsAccount;
        }
    }
    Button {
        id: ignore
        anchors.horizontalCenter: addFriendRec.horizontalCenter
        anchors.top: agree.bottom
        anchors.topMargin: 5
        style: ECButtonStyle{ button: add; buttonText: qsTr("忽略") }
        onClicked: {
            agree.enabled = false;
            ignore.enabled =false;
        }
    }
}
