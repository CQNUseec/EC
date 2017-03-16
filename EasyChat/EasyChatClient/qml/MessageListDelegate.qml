/*********************************
 ***   author: RanJT
 ***   date:   2017.3.16
 ***   聊天时 消息实时显示列表样式(Delegate)   Component类型
 ********************************/
import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4

Rectangle {
    id: rec
    width: parent.width - 24
    anchors.horizontalCenter: parent.horizontalCenter
    height: 50
    Component.onCompleted: {
        if(model.bDisplayLeft)
            time.anchors.left =  rec.left;
        else
            time.anchors.right =  rec.right;
    }
    Text {
        id: time
        anchors.top: parent.top
        text: model.sendTime
        font.pointSize: 13
        font.family: SystemFont
    }
    Text {
        id: messageText
        width: parent.width
        anchors.top: time.bottom
        anchors.right: parent.right
        text: model.message
        horizontalAlignment: Text.AlignRight
        font.pointSize: 13
        font.family: SystemFont
        wrapMode: Text.Wrap
    }
}
