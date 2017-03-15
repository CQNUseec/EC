import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4

Rectangle {
    width: parent.width
    property string fontFamily: EcInteraction.getSystemFont()
    Component.onCompleted: {
        if()
    }
    Text {
        id: time
        width: 300
        text: model.sendTime
        font.pointSize: 13
        font.family: fontFamily
    }
    Text {
        id: messageText
        width:300
        anchors.top: time.bottom
        anchors.horizontalCenter: time.horizontalCenter
        text: model.message
        font.pointSize: 13
        font.family: fontFamily
        wrapMode: Text.Wrap
    }
}
