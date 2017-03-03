/*********************************
 ***   author: RanJT
 ***   date:   2017.3.1
 ***   主界面  显示好友列表 以及其他功能的入口
 ********************************/
import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
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
    }
    TitleRec {
        id: topRec
        width: parent.width
        height: 27
        window: mainWindow
        biggestButtonVisible: false
        color: "#005791"
    }
    ListView {
        id: friendListView
        anchors.top: topRec.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: slideBar.visible ? slideBar.left : parent.right
        anchors.leftMargin: 5
        clip: true
        model:friendList
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
    Loader {
        id: chatLoader
        smooth:true
    }
    Connections {
        target: EcInteraction
        onSig_loginResult: {
            if(res === 10)
            {
                mainWindow.visible = true;
                chatLoader.source = "";
                console.log("登陆成功");
            }
        }
    }
}

