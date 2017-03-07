/*********************************
 ***   author: RanJT
 ***   date:   2017.3.1
 ***   ButtonStyle   Component类型
 ********************************/

import QtQuick 2.0
import QtQuick.Controls.Styles 1.4

ButtonStyle{
    property int buttonRadius: 3
    property int buttonImplicitWidth: 55
    property int buttonImplicitHeight: 25
    property string buttonText: ""
    property int buttonTextSize: 9
    property string enteredColor: "#3CC3F5"
    property string exitedColor: "#09A3DC"
    property string borderColor: "#004B77"
    property variant button
    background: Rectangle {
        id: backRec
        implicitWidth: buttonImplicitWidth
        implicitHeight: buttonImplicitHeight
        radius: buttonRadius
        color: button.hovered || button.focus ? enteredColor : exitedColor
        border.width: button.hovered || button.focus ? 1 : 0
        border.color: borderColor
        MouseArea {
            onPressed: {
               backRec.color =  borderColor;
            }
            onReleased: {
                 backRec.color = button.hovered ? enteredColor : exitedColor;
            }
        }
        Text {
            anchors.centerIn: parent
            text: qsTr(buttonText)
            font.family: EcInteraction.getSystemFont()
            font.pointSize: buttonTextSize
            color: "white"
        }
    }
}
