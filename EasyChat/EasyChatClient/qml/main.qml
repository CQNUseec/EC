/*********************************
 ***   author: RanJT
 ***   date:   2017.3.1
 ***   主界面  显示好友列表 以及其他功能的入口
 ********************************/
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4

ApplicationWindow {
    id: mainWindow
    visible: false
    width: 240
    height: 550
    title: qsTr("Easychat聊天系统")
    color: "#F0F8FE"
    Component.onCompleted: {
        chatLoader.setSource("logIn.qml");
    }
    onClosing: {
        chatLoader.source = "";
    }
    ScrollView {
        id:scrollView
        anchors.fill: parent
        anchors.leftMargin: 30
        clip: true
        ListView {
            id: friendListView
            anchors.fill: parent
            model:friendList
            delegate: FriendListDelegate{}
            cacheBuffer: 10
        }
    }
    Loader {
        id: chatLoader
        smooth:true
    }
    Connections {
        target: EcInteraction
        onSig_loginResult: {
            if(res)
            {
                mainWindow.visible = true;
                chatLoader.source = "";
                console.log("登陆成功");
            }
        }
    }
}

