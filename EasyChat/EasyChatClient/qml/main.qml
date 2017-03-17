/*********************************
 ***   author: RanJT
 ***   date:   2017.3.1
 ***   主界面  显示好友列表 以及其他功能的入口
 ********************************/
import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0 as Controls2
import QtQuick.Window 2.2

Window {
    id: mainWindow
    visible: false
    width: 240
    height: 550
    color: "#F0F8FE"
    flags: Qt.Window | Qt.FramelessWindowHint
    Component.onCompleted: {
        chatLoader.setSource("logIn.qml");
    }
    onClosing: {
        chatLoader.source = "";
        EcInteraction.closeClientThread();
    }
    TitleRec {
        id: topRec
        width: parent.width
        height: 27
        window: mainWindow
        biggestButtonVisible: false
        color: "#005791"
    }
    Rectangle {        //左边框
        width: 1
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        color: "#C8C8C8"
        z:5
    }
    Rectangle {        //右边框
        width: 1
        anchors.top: header.bottom
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
    Rectangle {
        id: header
        anchors.top:  topRec.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 35
        color: "#09A3DC"
        Button {
            id: messagePageButon
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            style: ECButtonStyle{ button: messagePageButon; buttonText: qsTr("消息") }
            onClicked: {
                swipeView.currentIndex = 0;
            }
        }
        Button {
            id: friendListPageButton
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            style: ECButtonStyle{ button: friendListPageButton; buttonText: qsTr("好友") }
            onClicked: {
                swipeView.currentIndex = 1;
            }
        }
        Button {
            id: groupListPageButton
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            style: ECButtonStyle{ button: groupListPageButton; buttonText: qsTr("群组") }
            onClicked: {
                swipeView.currentIndex = 2;
            }
        }
    }
    Controls2.SwipeView {
        id: swipeView
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: footer.top
        currentIndex: 1
        Controls2.Page {
            Label {
                text: qsTr("消息")
                anchors.centerIn: parent
            }
        }
        Controls2.Page {
            ListView {
                id: friendListView
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: slideBar.visible ? slideBar.left : parent.right
                anchors.leftMargin: 5
                clip: true
                model:friendListModel
                delegate: FriendListDelegate{itemWidth: slideBar.visible ? mainWindow.width-slideBar.width :mainWindow.width}
                highlightFollowsCurrentItem: true;
                highlightMoveVelocity: 14000;
                cacheBuffer: 10
            }

            ListViewSlideBar {  //使用自定义的滑动条    因为在ScrollView中嵌套ListView有点问题
                id: slideBar
                anchors.top: friendListView.top
                anchors.right: parent.right
                anchors.bottom: friendListView.bottom
                view: friendListView
            }
        }
        Controls2.Page {
            Label {
                text: qsTr("群聊")
                anchors.centerIn: parent
            }
        }
    }
    Rectangle {
        id: footer
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 35
        color: "#09A3DC"
        Button {
            id: zone
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            style: ECButtonStyle { button: zone; buttonText: "ECZone"; }
        }
        Button {
            id: findFriend
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            style: ECButtonStyle { button: findFriend; buttonText: "查找好友"; }
            onClicked: {
                findFriendLoader.setSource("findFriendWindow.qml");
            }
        }
    }

    Loader {
        id: chatLoader
        smooth:true
    }
    Loader {
        id: findFriendLoader
        smooth:true
    }
    Loader {
        id: zoneLoader
        smooth:true
    }
    Connections {
        target: EcInteraction
        onSig_loginResult: {
            if(res === 10)
            {
                mainWindow.visible = true;
                chatLoader.source = "";
                console.log(EcInteraction.selfAccount, "登陆成功");
            }
        }
    }
}

