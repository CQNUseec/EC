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
    AnimatedImage {
        id: findFriendWindowBackground
        z: 3
        anchors.centerIn: parent
        source: "/images/loginBackground.gif"
        visible: false
    }
    Rectangle {
        id: addFriendRec
        width: 80
        height: 50
    }
}
