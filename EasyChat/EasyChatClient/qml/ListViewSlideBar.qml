/*********************************
 ***   author: RanJT
 ***   date:   2017.3.1
 ***   自定义的view滑动条
 ********************************/
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4

Rectangle {               //自定义滑动条
    id:slideAreaRec
    width: 11
    property bool upButtonClicked: false
    property bool downButtonClicked: false
    property bool bDrap: false
    property var view
    property bool isEntered: false
    property int yPosSize: 30
    clip: true
    visible: view.contentHeight > slideAreaRec.height ? true : false
    Rectangle {
        id: upButton
        anchors.top: parent.top
        width: parent.width
        height: 12;
        visible: parent.isEntered
        Image {
            id: upButtonImage
            anchors.fill: parent
            visible: slideAreaRec.isEntered
            source: "/images/scrollviewToBegin.png"
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true;
            onEntered: {
                upButtonImage.source = "/images/scrollviewToBeginH.png";
                slideAreaRec.isEntered = true;
            }
            onExited: {
                upButtonImage.source = "/images/scrollviewToBegin.png";
                slideAreaRec.isEntered = false;
            }

            onClicked: {
                if(!view.atYBeginning)
                    view.contentY -= slideAreaRec.yPosSize;
            }
            onPressed: {
                slideAreaRec.upButtonClicked = true;
                scrollUpAndDownHold.start();
            }
            onReleased: {
                scrollUpAndDownHold.stop();
                slideAreaRec.upButtonClicked = true;
            }
        }
    }
    Rectangle {
        id:slideBar
        anchors.right: parent.right
        anchors.top: upButton.bottom;
        anchors.bottom: downButton.top;
        height: view.height - upButton.height - downButton.height
        width: parent.width;
        visible: parent.visible
        color: slideAreaRec.isEntered ? "#DADFE3" : "#F4FBFE"
        // 按钮
        Rectangle {
            id: button
            x: 0
            anchors.horizontalCenter: parent.horizontalCenter
            y: slideAreaRec.bDrap ? button.y : view.visibleArea.yPosition * slideBar.height;
            width: parent.width - 2
            height: view.visibleArea.heightRatio * slideBar.height < 15 ? 15 : view.visibleArea.heightRatio * slideBar.height
            color:slideAreaRec.isEntered ? "#A8A8A8" : "#D1D1D1"
            radius: 10
            visible: parent.visible
            // 鼠标区域
            MouseArea {
                anchors.fill: button
                hoverEnabled: true
                drag.target: button
                drag.axis: Drag.YAxis
                drag.minimumY: 0
                drag.maximumY: slideBar.height - button.height
                // 拖动
                onMouseYChanged: {
                    if(!view.atYEnd)
                        view.contentY -= slideAreaRec.yPosSize;
                    view.contentY = button.y / slideBar.height * view.contentHeight;
                }
                onEntered: {
                    slideAreaRec.isEntered = true;
                }
                onExited: {
                    slideAreaRec.isEntered = false;
                }
                onPressed: {
                    slideAreaRec.bDrap = true;
                }
                onReleased: {
                    slideAreaRec.bDrap = false;
                }
            }
        }
        MouseArea {
            anchors.fill: parent
            propagateComposedEvents: true
            hoverEnabled: true
            onEntered: {
                slideAreaRec.isEntered = true;
            }
            onExited: {
                slideAreaRec.isEntered = false;
            }
            onClicked: {
                console.log("click");
                if(mouseY > button.y+button.height)
                {
                    console.log("down");
                    view.currentIndex += 1;
                }
                else if(mouseY < button.y)
                {
                    console.log("up");
                    view.currentIndex -= 1;
                }
            }
            onMouseYChanged: {
                mouse.accepted = false;
            }
            onPressed: {
                mouse.accepted = true;
                if(mouseY > button.y+button.height)
                {
                    console.log("down");
                    view.contentY += slideAreaRec.yPosSize;
                }
                else if(mouseY < button.y)
                {
                    console.log("up");
                    view.contentY -= slideAreaRec.yPosSize;
                }
            }
        }
    }
    Rectangle {
        id: downButton
        anchors.bottom: parent.bottom
        width: parent.width
        height: 12;
        visible: parent.visible
        Image {
            id: downButtonImage
            anchors.fill: parent
            visible: slideAreaRec.isEntered
            source: "/images/scrollviewToEnd.png"
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true;
            onEntered: {
                downButtonImage.source = "/images/scrollviewToEndH.png";
                slideAreaRec.isEntered = true;
            }
            onExited: {
                downButtonImage.source = "/images/scrollviewToEnd.png";
                slideAreaRec.isEntered = false;
            }

            onClicked: {
                if(!view.atYEnd)
                    view.contentY += slideAreaRec.yPosSize;
            }
            onPressed: {
                slideAreaRec.downButtonClicked = true;
                scrollUpAndDownHold.start();
            }
            onReleased: {
                scrollUpAndDownHold.stop();
                slideAreaRec.downButtonClicked = true;
            }
        }
    }
    Timer {
        id:scrollUpAndDownHold
        interval: 300
        repeat: true
        onTriggered: {
            if(slideAreaRec.downButtonClicked)
            {
                if(!view.atYEnd)
                    view.contentY += slideAreaRec.yPosSize;
            }
            if(slideAreaRec.upButtonClicked)
            {
                if(!view.atYBeginning)
                    view.contentY -= slideAreaRec.yPosSize;
            }
        }
    }
}

