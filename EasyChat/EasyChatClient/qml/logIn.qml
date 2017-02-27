import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Window {
    id:loginWindow;
    width: 432;
    height: 330;
    visible: true;
    flags: Qt.Window | Qt.FramelessWindowHint;
    Rectangle {
        id:topRct;
        width: parent.width;
        height: 32
        MouseArea { //为窗口添加鼠标事件
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton //只处理鼠标左键
            property point clickPos: "0,0"
            onPressed: { //接收鼠标按下事件
                clickPos  = Qt.point(mouse.x,mouse.y)
            }
            onPositionChanged: { //鼠标按下后改变位置
                //鼠标偏移量
                var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)

                //如果mainwindow继承自QWidget,用setPos
                loginWindow.setX(loginWindow.x+delta.x)
                loginWindow.setY(loginWindow.y+delta.y)
            }
        }

        anchors.top: parent.top;
        anchors.left: parent.left;
        color:"#005791";
        Text {
            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: parent.left;
            anchors.leftMargin: 15;
            text:qsTr("Easy Chat");
            font.family: "微软雅黑";
            font.pointSize: 9;
            color:"#ffffff"
        }
        Image {      //最小化按钮
            id: minimizeButton;
            source: "/images/mostLittle0.png";
            anchors.verticalCenter: parent.verticalCenter;
            anchors.right: closeButton.left;
            anchors.rightMargin: 8;
            MouseArea {
                anchors.fill: parent;
                hoverEnabled: true;
                onClicked: {
                    minimizeButton.source = "/images/mostLittle1.png"
                    loginWindow.showMinimized();
                }
                onEntered: {
                    minimizeButton.source = "/images/mostLittle1.png"
                }
                onExited: {
                    minimizeButton.source = "/images/mostLittle0.png"
                }
            }
        }
        Image {          // 关闭按钮
            id:closeButton;
            source: "/images/close0.png"
            anchors.right: parent.right;
            anchors.rightMargin: 5;
            anchors.verticalCenter: parent.verticalCenter;
            MouseArea {
                anchors.fill: parent;
                hoverEnabled: true;
                onEntered: {
                    closeButton.source = "/images/close1.png"
                }
                onExited: {
                    closeButton.source = "/images/close0.png"
                }
                onClicked: {
                    closeButton.source = "/images/close1.png"
                    loginWindow.close();
                }
            }
        }
    }
    Rectangle{
        id: loginInfo
        anchors.top: topRct.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        color: "#EBF2F9";
        AnimatedImage {
            id:background;
            anchors.top: loginInfo.top;
            anchors.left: loginInfo.left;
            anchors.right: loginInfo.right;
            anchors.bottom: loginButtom.top;
            source: "/images/loginBackground.gif";
            playing: true;
            visible: true;
            z: 2;
        }
        Rectangle {
            id: loginButtom;
            width: 193;
            height: 33;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 20;
            color: "#09A3DC";
            radius: 3;
            MouseArea {
                anchors.fill: parent;
                hoverEnabled: true;
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
                anchors.centerIn: parent;
                text: qsTr("登  陆");
                color: "white";
            }
        }
    }
}
