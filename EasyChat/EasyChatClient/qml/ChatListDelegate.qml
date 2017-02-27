import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4

Column {
    clip: true
    Rectangle {
        id:rec
        width: 115;
        height: 26;
        z: 1;
        color: "#B2DFEE"
        border.color: model.bSelected ? "green" : "white";
        property bool bordeColor: model.bSelected;
        onBordeColorChanged: {
            if(bordeColor)
                chatWindows.friendName = model.friendName;
        }
        Text {
            anchors.centerIn: parent;
            id: name;
            text: qsTr(model.friendName);
        }
        MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;
            onEntered: {
                rec.z = 4;
                rec.width = 120;
                rec.height = 30;
            }
            onExited: {
                rec.z = 1;
                rec.width = 115;
                rec.height = 26;
            }
            onClicked: {
                chatWindow.friendName = model.friendName;
                chat.setbSelected(model.friendAccount);
            }
        }
    }
}
