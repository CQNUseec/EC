/*********************************
 ***   author: RanJT
 ***   date:   2017.3.1
 ***   聊天界面（聊天窗口）
 ********************************/
import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQml.Models 2.2


Window {
    id: chatWindows;
    width: 800
    height: 500
    visible: true
    flags: Qt.Window | Qt.FramelessWindowHint
    property string friendName: ""
    property string friendAccount: ""
    property string selfAccount: EcInteraction.selfAccount
    property variant chat: EcInteraction.chat
    property variant messageListModel: chat.messageListModel
    onClosing: {
        chat.clearChatData();
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
        clip: true
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
            font.family: SystemFont
        }
        ListView {
            id: chatingFriendList
            anchors.top: friendListTitle.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: friendListSlideBar.visible ? friendListSlideBar.left : parent.right
            model: chat.chatListModel
            boundsBehavior: Flickable.StopAtBounds
            delegate: ChatListDelegate{}
        }
        ListViewSlideBar {
            id: friendListSlideBar
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
        clip: true
        ListView {
            id: messageListView
            anchors.top:parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: messageListViewSlideBar.visible ? messageListViewSlideBar.left : parent.right
            boundsBehavior: Flickable.StopAtBounds
            model: messageListModel
            delegate: MessageListDelegate{}
            onModelChanged: {
                console.log(messageListView.model);
            }
        }
        ListViewSlideBar {
            id: messageListViewSlideBar
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            view: messageListView
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
        TextArea {
            id: messageInput
            anchors.fill: parent
            focus: true
            font.pixelSize: 15
            wrapMode: TextEdit.Wrap
        }
        Button {
            id: sendButton
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            style: ECButtonStyle { button: sendButton; buttonText: "发送"}
            onClicked: {
                sendMessage();
            }
            Keys.enabled: true
            Keys.onReturnPressed: {
                ecLoader.setSource("registration.qml");
                loginWindow.visible = false;
            }
        }
    }
    function sendMessage() {
        if(messageInput.length < 1)
            return;
        var now = Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss");
        console.log(now.toString());
        chat.loadDataToMessageListModel(selfAccount, friendAccount, messageInput.text, now.toString());
        messageInput.text = "";
    }
}
