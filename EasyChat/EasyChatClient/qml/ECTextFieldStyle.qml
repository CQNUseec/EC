/*********************************
 ***   author: RanJT
 ***   date:   2017.3.1
 ***   TextFieldStyle   Component类型
 ********************************/
import QtQuick 2.0
import QtQuick.Controls.Styles 1.4

TextFieldStyle {
    textColor: "#000000"
    property string recColor: "#FFFFFF"
    property string borderColor: "#D1D1D1"
    property int borderWidth: 1
    background: Rectangle {
        radius: 3
        color: recColor
        border.color: borderColor
        border.width: borderWidth
    }
}
