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
        id: topRec
        width: parent.width
        height: 27
        color:"#005791"
        window: chatWindows
        titleText: friendName
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
    Rectangle {    // 左边显示框
        id: leftTabRec
        anchors.top: topRec.bottom
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
        anchors.top: topRec.bottom
        anchors.left: leftTabRec.right
        anchors.right: parent.right
        height: parent.height * 0.7
        border.color: "red"
        border.width: 2
        radius: 3
        clip: true
        Keys.enabled: true
        Keys.onEscapePressed: {
            chatWindows.close();
        }
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
        Keys.enabled: true
        Keys.onEscapePressed: {
            chatWindows.close();
        }
        TextArea {
            id: messageInput
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: sendButton.top
            focus: true
            font.pixelSize: 15
            wrapMode: TextEdit.Wrap
        }
        Button {
            id: sendButton
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 5
            style: ECButtonStyle { button: sendButton; buttonText: "发送"}
            onClicked: {
                sendMessage();
            }
            Keys.enabled: true
            Keys.onReturnPressed: {
                sendMessage();
            }
        }
    }
    Connections {
        target: chat
        onSig_viewChanged: {
            console.log(chatingFriendList.count);
            if(count === 0)
                chatWindows.close();
            chatingFriendList.forceLayout();
            messageListView.forceLayout();
            messageListView.positionViewAtEnd();
        }
    }
    function sendMessage() {
        if(messageInput.length < 1)
            return;
        var now = Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss");
        var messageData = new Object();
        messageData.purpose = 4;
        messageData.sender = selfAccount;
        messageData.receiver = friendAccount;
        messageData.message = messageInput.text;
        messageData.sendTime = now.toString();
        console.log(JSON.stringify(messageData));
        EcInteraction.sendMessage(JSON.stringify(messageData));
        chat.loadDataToMessageListModel(selfAccount, friendAccount, messageInput.text, now.toString());
        messageInput.text = "";
    }
}
