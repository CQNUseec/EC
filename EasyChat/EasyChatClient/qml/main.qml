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
            anchors.fill: parent
            model:friendList
            delegate: FriendListDelegate{}
            cacheBuffer: 10;
        }
    }
    Loader {
        id: chatLoader
        smooth:true
    }
    Connections {
        target: EcInteraction;
        onSig_loginResult: {
            if(res)
            {
                mainWindow.visible = true;
                chatLoader.source = "";
            }
        }
    }
}

