/*********************************
 ***   author: RanJT
 ***   date:   2017.3.1
 ***   登陆界面
 ********************************/
import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
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
            font.family: EcInteraction.getSystemFont()
            text: qsTr("账号:")
        }
        Text {
            id: accountInputTips
            anchors.right: accountInput.right
            anchors.rightMargin: 5
            anchors.verticalCenter: accountInput.verticalCenter
            z: 3
            visible: false
            font.pointSize: 11
            font.family: EcInteraction.getSystemFont()
            text: qsTr("无效账号")
        }
        TextField {
            id: accountInput
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            width: 200
            height: 33
            font.pixelSize: 15
            maximumLength: 11
            placeholderText: qsTr("请输入账号")
            selectByMouse: true
            style: ECTextFieldStyle{}
            validator: RegExpValidator{
                regExp: (/^[0-9]*$/)     //限制为数字
            }
            onFocusChanged: {
                if(accountInput.focus)
                    accountInputTips.visible = false;
            }
        }
        Button {
            id: registerButton
            anchors.verticalCenter: accountInput.verticalCenter
            anchors.left: accountInput.right
            anchors.leftMargin: 10
            style: ECButtonStyle { button: registerButton; buttonText: "注册账号" }
            onClicked: {
                console.log("zhuce");
                ecLoader.setSource("registration.qml");
            }
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
            font.family: EcInteraction.getSystemFont()
            text: qsTr("密码:")
        }
        Text {
            id: passwordInputTips
            anchors.right: passwordInput.right
            anchors.rightMargin: 5
            anchors.verticalCenter: passwordInput.verticalCenter
            z: 3
            visible: false
            font.pointSize: 11
            font.family: EcInteraction.getSystemFont()
            text: qsTr("无效密码")
        }
        TextField {
            id: passwordInput
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            width: 200
            height: 33
            font.pixelSize: 15
            maximumLength: 16
            selectByMouse: true
            placeholderText: qsTr("请输入密码")
            echoMode: TextInput.Password
            style: ECTextFieldStyle{}
            onFocusChanged: {
                passwordInputTips.visible = false;
            }
        }
        Button {
            id: forgetPassword
            anchors.verticalCenter: passwordInput.verticalCenter
            anchors.left: passwordInput.right
            anchors.leftMargin: 10
            //text: qsTr("忘记密码")
            style: ECButtonStyle{ button:forgetPassword; buttonText: "忘记密码" }
        }
    }
    Button {
        id: loginButtom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 17
        style: ECButtonStyle{ button: loginButtom; buttonImplicitWidth: 193; buttonImplicitHeight: 33; buttonText: "登  录" }
        onClicked: {
            accountInput.focus = false;
            passwordInput.focus = false;
            if(accountInput.length < 6)
                accountInputTips.visible = true;
            if(passwordInput.length < 6)
                passwordInputTips.visible = true;
            else if(accountInput.length > 5 && passwordInput.length > 5)
                EcInteraction.logIn(accountInput.text, passwordInput.text);
        }
    }
    Loader {
        id: ecLoader
        smooth: true
    }
    Component {
        id: test
        ApplicationWindow {
            width: 600
            height: 400
        }
    }
    Connections {
        target: EcInteraction
        onSig_loginResult: {
            if(res === -10)
                passwordInputTips.visible = true;
            else if(res === -11)
                accountInputTips.visible = true;
        }
    }
}
