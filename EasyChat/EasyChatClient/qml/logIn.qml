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
        biggestButtonVisible: false
    }
    Image {
        id:background
        height: 155
        anchors.top: topRct.bottom
        anchors.left: loginWindow.left
        anchors.right: loginWindow.right
        source: "/images/loginBackground.png"
    }
    Rectangle {
        id: accountRow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: background.bottom
        anchors.topMargin: 15
        height: 33
        Text {
            anchors.verticalCenter: accountInput.verticalCenter
            anchors.right: accountInput.left
            anchors.rightMargin: 10
            font.pointSize: 11
            font.family: "微软雅黑"
            text: qsTr("账号:")
        }
        TextField {
            id: accountInput
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            width: 200
            height: 33
            font.pixelSize: 15
            focus: true
            maximumLength: 11
            placeholderText: qsTr("请输入账号")
            selectByMouse: true
            style: TextFieldStyleSelf{}
            validator: RegExpValidator{
                regExp: (/^[0-9]*$/)     //限制为数字
            }
        }
        Button {
            id: registerButton
            anchors.verticalCenter: accountInput.verticalCenter
            anchors.left: accountInput.right
            anchors.leftMargin: 10
            text: qsTr("注册账号")
        }
    }
    Rectangle {
        id: passwordRow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: accountRow.bottom
        height: 33
        Text {
            anchors.verticalCenter: passwordInput.verticalCenter
            anchors.right: passwordInput.left
            anchors.rightMargin: 10
            font.pointSize: 11
            font.family: "微软雅黑"
            text: qsTr("密码:")
        }
        TextField {
            id: passwordInput
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            width: 200
            height: 33
            font.pixelSize: 15
            focus: false
            maximumLength: 16
            selectByMouse: true
            placeholderText: qsTr("请输入密码")
            echoMode: TextInput.Password
            style: TextFieldStyleSelf{}
        }
        Button {
            id: forgetPassword
            anchors.verticalCenter: passwordInput.verticalCenter
            anchors.left: passwordInput.right
            anchors.leftMargin: 10
            text: qsTr("忘记密码")
        }
    }
    Rectangle {
        id: loginButtom
        width: 193
        height: 33
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 17
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
                console.log(accountInput.text, passwordInput.text)
                if(accountInput.length > 0 && passwordInput.length > 0)
                    EcInteraction.logIn(accountInput.text, passwordInput.text);
            }
        }
        Text {
            id:loginButtomText
            anchors.centerIn: parent
            text: qsTr("登  录")
            color: "white"
        }
    }
}
