/*********************************
 ***   author: RanJT
 ***   date:   2017.4.5
 ***   未读列表的显示样式(Delegate)   Component类型
 ********************************/
import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
Rectangle {
    id: unreadMessageRec
    clip: true
    width: itemWidth
    height: 50
    radius: 3
    property string messageSender: model.sender
    property string messageReceiver: model.receiver
    property string messageSendTime: model.sendTime
    property int messageType: model.operation
    property int messageId: model.idNum

    color: bEntered ? "#FCF0C1" : "#FFFFFF"
    property int itemWidth: 200
    property bool bEntered: false
    Text {
        id: snederDisplay
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: EcInteraction.getAccountName(model.sender)
        font.family: SystemFont
        font.pointSize: 10
    }
    Text {
        id: messageDisplay
        anchors.horizontalCenter: snederDisplay.horizontalCenter
        anchors.top: snederDisplay.bottom
        text: model.message
        font.family: SystemFont
        font.pointSize: 10
    }
       MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            unreadMessageRec.bEntered = true;
        }
        onExited: {
            unreadMessageRec.bEntered = false;
        }
        onDoubleClicked: {
            readAndDealMessage();
            EcInteraction.removeMainMessageModelData(messageId);
        }
    }
       function readAndDealMessage()
       {
           if(messageType === 4)  //处理未读的聊天消息
           {
               if(EcInteraction.chat.isChatWindowOpen())
               {
                   EcInteraction.chat.loadDataToChat(friendName, messageSender, messageReceiver);
                   console.log("窗口已打开，添加聊天人");
                   return;
               }
               chatLoader.setSource("chatWindow.qml", {"test": messageSender, "friendAccount": messageSender});
               EcInteraction.chat.loadDataToChat("test", messageSender, messageReceiver);
               console.log("打开聊天窗口")
           }
           else if(messageType === 6)  //处理添加好友请求
           {
               addLoader.setSource("addFriendWindow.qml", {"initiatedAccount": messageSender, "aimsAccount": messageReceiver});
           }
       }
}

