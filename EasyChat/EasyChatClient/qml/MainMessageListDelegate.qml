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

    color: model.bSelected ? "#FCEAA3" : (bEntered ? "#FCF0C1" : "#FFFFFF")
    property int itemWidth: 200
    property bool bEntered: false
    Text {
        anchors.centerIn: parent
        id: messageDisplay
        text: model.message
        font.family: SystemFont
        font.pointSize: 10
    }
       MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            groupMemberRec.bEntered = true;
        }
        onExited: {
            groupMemberRec.bEntered = false;
        }
        onClicked: {
            EcInteraction.setGroupSelected(groupAccount);
        }
        onDoubleClicked: {
            chatWithFriend(groupName, groupAccount, EcInteraction.selfAccount);
        }
    }
}

