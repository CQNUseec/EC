/*********************************
 ***   author: RanJT
 ***   date:   2017.3.1
 ***   自定标题栏  组件
 ********************************/
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Rectangle {
    id:topRct
    anchors.top: parent.top
    anchors.left: parent.left
    property var window
    property string titleText: qsTr("Easy Chat")
    property bool isDisplayTitleText: true
    property bool minimizeButtonVisible: true
    property bool biggestButtonVisible: true
    property bool closeButtonVisible: true
    MouseArea { //为窗口添加鼠标事件
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton //只处理鼠标左键
        property point clickPos: "0,0"
        onPressed: { //接收鼠标按下事件
            clickPos  = Qt.point(mouse.x,mouse.y);
        }
        onPositionChanged: { //鼠标按下后改变位置
            //鼠标偏移量
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y);

            //如果mainwindow继承自QWidget,用setPos
            window.setX(window.x+delta.x);
            window.setY(window.y+delta.y);
        }
        onDoubleClicked: {
            if(biggestButtonVisible)
                window.visibility=== Window.Maximized ? window.visibility=Window.AutomaticVisibility : window.visibility=Window.Maximized;
        }
    }
    Text {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 15
        visible: topRct.isDisplayTitleText
        text:topRct.titleText
        font.family: "微软雅黑"
        font.pointSize: 9
        color:"#ffffff"
    }
    Row{
        id:buttons
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        Image {      //最小化按钮
            id: minimizeButton
            source: "/images/mostLittle0.png"
            //        anchors.verticalCenter: parent.verticalCenter;
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            visible: topRct.minimizeButtonVisible
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    minimizeButton.source = "/images/mostLittle1.png";
                    window.showMinimized();
                }
                onEntered: {
                    minimizeButton.source = "/images/mostLittle1.png";
                }
                onExited: {
                    minimizeButton.source = "/images/mostLittle0.png";
                }
            }
        }
        Image {       // 最大化/缩小按钮
            id:biggestButton;
            source: "/images/bigest01.png";
            //        anchors.verticalCenter: parent.verticalCenter;
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            visible: topRct.biggestButtonVisible
            MouseArea {
                anchors.fill: parent;
                hoverEnabled: true;
                onEntered: {
                    biggestButton.source = (window.visibility=== Window.Maximized ? "/images/reduction02.png" : "/images/bigest02.png")
                }
                onExited: {
                    biggestButton.source = (window.visibility=== Window.Maximized ? "/images/reduction01.png" : "/images/bigest01.png")
                }
                onClicked: {
                    window.visibility=== Window.Maximized ? window.visibility=Window.AutomaticVisibility : window.visibility=Window.Maximized;
                    biggestButton.source = "/images/reduction01.png"
                }
            }
        }
        Image {          // 关闭按钮
            id:closeButton
            source: "/images/close0.png"
            //        anchors.verticalCenter: parent.verticalCenter;
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            visible: topRct.closeButtonVisible
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    closeButton.source = "/images/close1.png";
                }
                onExited: {
                    closeButton.source = "/images/close0.png";
                }
                onClicked: {
                    closeButton.source = "/images/close1.png";
                    window.close();
                }
            }
        }
    }
}
