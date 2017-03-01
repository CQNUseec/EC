/*********************************
 ***   author: RanJT
 ***   date:   2017.3.1
 ***   登陆界面
 ********************************/
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Window {
    id:loginWindow
    width: 432
    height: 330
    visible: true
    flags: Qt.Window | Qt.FramelessWindowHint
    TitleRec {
        id: topRct
        width: parent.width
        height: 27
        color:"#005791"
        window: loginWindow
    }
    Rectangle{
        id: loginInfo
        anchors.top: topRct.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "#EBF2F9"
        AnimatedImage {
            id:background
            anchors.top: loginInfo.top
            anchors.left: loginInfo.left
            anchors.right: loginInfo.right
            anchors.bottom: loginButtom.top
            source: "/images/loginBackground.gif"
            playing: true
            visible: true
            z: 2
        }
        Rectangle {
            id: loginButtom
            width: 193
            height: 33
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            color: "#09A3DC"
            radius: 3
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    loginButtom.color = "#3CC3F5";
                }
                onExited: {
                    loginButtom.color = "#09A3DC";
                }
                onClicked: {
                    EcInteraction.logIn("account", "password");
                }
            }
            Text {
                anchors.centerIn: parent
                text: qsTr("登  录")
                color: "white"
            }
        }
    }
}
