/*********************************
 ***   author: RanJT
 ***   date:   2017.3.1
 ***   注册界面
 ********************************/
import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Window {
    id: registerWindow
    width: 500
    height: 350
    visible: true
    modality: Qt.ApplicationModal
    flags: Qt.Window | Qt.FramelessWindowHint
    TitleRec {
        id: topRec
        width: parent.width
        height: 27
        window: registerWindow
        titleText: qsTr("账号注册")
        color: "#005791"
        biggestButtonVisible: false
    }
    Text {
//        anchors.verticalCenter: nameInput.verticalCenter
//        anchors.right: nameInput.left
//        anchors.rightMargin: 5
        anchors.top: topRec.bottom
        anchors.left: topRec.left
        visible: true
        text: qsTr("昵称: ")
        font.family: EcInteraction.getSystemFont()
    }
    TextField {
        id: nameInput
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: topRec.bottom
        anchors.topMargin: 5
        width: 200
        height: 33
        focus: true
        font.pixelSize: 15
        maximumLength: 16
        selectByMouse: true
        placeholderText: qsTr("请输入昵称")
        style: ECTextFieldStyle{}
    }
}
