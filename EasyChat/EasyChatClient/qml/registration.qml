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
    property bool bReadOnly: false
    onClosing: {
         loginWindow.visible = true;
    }
    TitleRec {
        id: topRec
        width: parent.width
        height: 27
        window: registerWindow
        titleText: qsTr("账号注册")
        color: "#005791"
        biggestButtonVisible: false
    }
    Rectangle {        //左边框
        width: 1
        anchors.top: topRec.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        color: "#C8C8C8"
        z:5
    }
    Rectangle {        //右边框
        width: 1
        anchors.top: topRec.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        color: "#C8C8C8"
        z:5
    }
    Rectangle {        //底部边框
        height: 1
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        color: "#C8C8C8"
        z:5
    }
    AnimatedImage {
        id: registerBackground
        z: 3
        anchors.centerIn: parent
        source: "/images/loginBackground.gif"
        visible: false
    }
    Rectangle {
        id: mainRec
        anchors.top: topRec.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        focus: true
        Keys.enabled: true
        Keys.onEscapePressed: {
            registerWindow.close();
        }
        //昵称设置
        Text {
            id: nameInputLeft
            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.right: nameInput.left
            anchors.rightMargin: 5
            visible: true
            text: qsTr("昵称: ")
            font.pixelSize: 15
            font.family: SystemFont
        }
        TextField {
            id: nameInput
            anchors.verticalCenter: nameInputLeft.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: 200
            height: 33
            focus: true
            readOnly: bReadOnly
            font.pixelSize: 15
            font.family: SystemFont
            maximumLength: 16
            selectByMouse: true
            placeholderText: qsTr("请输入昵称")
            style: ECTextFieldStyle{}
        }
        //密码设置
        Text {
            id: passwordInputLeft
            anchors.top: nameInput.bottom
            anchors.topMargin: 15
            anchors.right: passwordInput.left
            anchors.rightMargin: 5
            visible: true
            text: qsTr("密码: ")
            font.pixelSize: 15
            font.family: SystemFont
        }
        TextField {
            id: passwordInput
            anchors.verticalCenter: passwordInputLeft.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: 200
            height: 33
            readOnly: bReadOnly
            font.pixelSize: 15
            maximumLength: 16
            selectByMouse: true
            echoMode: TextInput.Password
            placeholderText: qsTr("请输入密码")
            style: ECTextFieldStyle{}
            onFocusChanged: {
                if(passwordInput.focus)
                    passwordInputTips.visible = false;
            }
            onEditingFinished: {
                if(passwordInput.length < 6)
                    passwordInputTips.visible = true;
            }
        }
        Text {
            id: passwordInputTips
            anchors.verticalCenter: passwordInputLeft.verticalCenter
            anchors.left: passwordInput.right
            anchors.leftMargin: 5
            visible: false
            font.pixelSize: 14
            color: "red"
            font.family: SystemFont
            text: qsTr("密码至少6位最多16位")
        }
        //确认密码
        Text {
            id: passwordInputAgainLeft
            anchors.top: passwordInput.bottom
            anchors.topMargin: 15
            anchors.right: passwordInputAgain.left
            anchors.rightMargin: 5
            visible: true
            text: qsTr("确认密码: ")
            font.pixelSize: 15
            font.family: SystemFont
        }
        TextField {
            id: passwordInputAgain
            anchors.verticalCenter: passwordInputAgainLeft.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: 200
            height: 33
            readOnly: bReadOnly
            font.pixelSize: 15
            maximumLength: 16
            selectByMouse: true
            echoMode: TextInput.Password
            placeholderText: qsTr("请再次输入密码")
            style: ECTextFieldStyle{}
            onFocusChanged: {
                if(passwordInputAgain.focus)
                    passwordInputAgainTips.visible = false;
            }
            onEditingFinished: {
                if(passwordInput.text !== passwordInputAgain.text && passwordInputAgain.length > 0)
                    passwordInputAgainTips.visible =true;
            }
        }
        Text {
            id: passwordInputAgainTips
            anchors.verticalCenter: passwordInputAgainLeft.verticalCenter
            anchors.left: passwordInputAgain.right
            anchors.leftMargin: 5
            visible: false
            font.pixelSize: 14
            color: "red"
            font.family: SystemFont
            text: qsTr("两次输入密码不一致")
        }
        //年龄输入
        Text {
            id: ageInputLeft
            anchors.top: passwordInputAgain.bottom
            anchors.topMargin: 15
            anchors.right: ageInput.left
            anchors.rightMargin: 5
            visible: true
            text: qsTr("年龄: ")
            font.pixelSize: 15
            font.family: SystemFont
        }
        TextField {
            id: ageInput
            anchors.verticalCenter: ageInputLeft.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: 200
            height: 33
            readOnly: bReadOnly
            font.pixelSize: 15
            font.family: SystemFont
            maximumLength: 3
            selectByMouse: true
            validator: RegExpValidator{
                regExp: (/^[0-9]*$/)     //限制为数字
            }
            placeholderText: qsTr("请输入年龄")
            style: ECTextFieldStyle{}
        }
        //性别选择
        Text {
            id: sexSelectLeft
            anchors.top: ageInputLeft.bottom
            anchors.topMargin: 15
            anchors.right: ageInput.left
            anchors.rightMargin: 5
            visible: true
            text: qsTr("年龄: ")
            font.pixelSize: 15
            font.family: SystemFont
        }
        GroupBox {
            id: sexSelect
            width: 200
            height: 33
            anchors.verticalCenter: sexSelectLeft.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            RowLayout {
                anchors.verticalCenter: parent.verticalCenter
                spacing: 50
                ExclusiveGroup { id: sexGroup }
                RadioButton {
                    id: man
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    text: "男"
                    exclusiveGroup: sexGroup
                }
                RadioButton {
                    id: woman
                    text: "女"
                    exclusiveGroup: sexGroup
                }
            }
        }
        // 注册结果
        Text {
            id: resultLeft
            visible: false
            anchors.top: sexSelectLeft.bottom
            anchors.topMargin: 15
            anchors.right: result.left
            anchors.rightMargin: 5
            text: qsTr("您的账号: ")
            font.pixelSize: 15
            font.family: SystemFont
        }
        TextField {
            id: result
            visible: false
            anchors.verticalCenter: resultLeft.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: 200
            height: 33
            activeFocusOnPress: false
            readOnly: true
            font.pixelSize: 14
            font.family: SystemFont
            maximumLength: 16
            selectByMouse: true
            style: ECTextFieldStyle{textColor: "red"}
        }
        //注册按钮
        Button {
            id: registerButtom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 17
            property string buttomText: "注  册"
            style: ECButtonStyle{ button: registerButtom; buttonImplicitWidth: 193; buttonImplicitHeight: 33; buttonText: registerButtom.buttomText }
            onClicked: {
                if(registerButtom.buttomText === "注  册")
                    bReadyToRegister();
                else
                    registerWindow.close();
            }
        }
    }
    Connections {
        target: EcInteraction
        onSig_registerAccountResult: {
            result.text = account;
            result.visible = true;
            resultLeft.visible = true;
            mainRec.opacity = 1;
            registerBackground.visible = false;
            registerButtom.buttomText = "返回登录界面";
            registerButtom.enabled = true;
        }
    }
    function bReadyToRegister()   //检测是否满足注册的输入要求后请求注册
    {
        if(nameInput.length <= 0)
            return;
        else if(passwordInput.left <= 0)
            return;
        else if(passwordInputAgain.length <= 0)
            return;
        else if(passwordInputTips.visible || passwordInputAgainTips.visible)
            return;
        else if(ageInput.length <= 0)
            return;
        else if( !(man.checked || woman.checked) )
            return;
        else
        {
            registerBackground.visible = true;
            mainRec.opacity = 0.5;
            bReadOnly = true;
            sexSelect.enabled = false;
            registerButtom.enabled = false;
            var registerData = new Object();
            registerData.purpose = "register";
            registerData.nickName = nameInput.text;
            registerData.password = passwordInput.text;
            registerData.age = ageInput.text;
            registerData.sex = man.checked ? man.text : woman.text;
            console.log(JSON.stringify(registerData));
            EcInteraction.sendMessage(JSON.stringify(registerData));
            return;
        }
    }
}
