/*********************************
 ***   author: RanJT
 ***   date:   2017.3.1
 ***   查找账号界面
 ********************************/
import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQml.Models 2.2

Window {
    id: findFriendWn
    width: 800
    height: 500
    visible: true
    flags: Qt.Window | Qt.FramelessWindowHint
    TitleRec {
        id: topRec
        width: parent.width
        height: 27
        color:"#005791"
        titleText: qsTr("查找账号")
        window: findFriendWn
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
        id: findFriendWindowBackground
        z: 3
        anchors.centerIn: parent
        source: "/images/loginBackground.gif"
        visible: false
    }
    Rectangle {
        id: content
        anchors.top: topRec.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        Text {
            id: accountInputLeft
            anchors.top: parent.top
            anchors.topMargin: 130
            anchors.right: accountInput.left
            anchors.rightMargin: 5
            visible: true
            text: qsTr("账号: ")
            font.pixelSize: 15
            font.family: SystemFont
        }
        TextField {
            id: accountInput
            anchors.verticalCenter: accountInputLeft.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: 200
            height: 33
            focus: true
            font.pixelSize: 15
            font.family: SystemFont
            maximumLength: 11
            selectByMouse: true
            validator: RegExpValidator{
                regExp: (/^[0-9]*$/)     //限制为数字
            }
            style: ECTextFieldStyle{}
            onFocusChanged: {
                if(accountInput.focus)
                {
                    accountInput.visible = false;
                    accountExit.visible = false;
                    resDisplay.visible = fasle;
                }
            }
        }
        Text {
            id: accountInputTips
            anchors.right: accountInput.right
            anchors.rightMargin: 5
            anchors.verticalCenter: accountInput.verticalCenter
            z: 3
            visible: false
            font.pointSize: 11
            font.family: SystemFont
            text: accountInput.length > 0 ? qsTr("账号至少6位") : qsTr("请先输入账号")
        }
        Button {
            id: search
            anchors.verticalCenter:  accountInput.verticalCenter
            anchors.left: accountInput.right
            anchors.leftMargin: 5
            style: ECButtonStyle{ button: search; buttonText: qsTr("查找") }
            onClicked: {
                if(accountInput.length > 5)
                {
                    findFriendWindowBackground.visible = true;
                    content.opacity = 0.5;
                    search.enabled = false;
                    var findData = new Object();
                    findData.purpose = "3";
                    findData.account = accountInput.text;
                    console.log(JSON.stringify(findData));
                    EcInteraction.sendMessage(JSON.stringify(findData));
                }
                else
                    accountInputTips.visible = true;
            }
        }

        Text {
            id: accountExit
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: accountInput.bottom
            anchors.topMargin: 10
            font.pointSize: 11
            font.family: SystemFont
            color: "red"
            text: qsTr("账号不存在!")
            visible: false
        }
        Rectangle {
            id: resDisplay
            width: 200
            height: 40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: accountExit.bottom
            anchors.topMargin: 10
            visible: false
            Text {
                id: accountRes
                anchors.centerIn: parent
                font.pointSize: 11
                font.family: SystemFont
                text: qsTr("账号是")
            }
        }
        Button {
            id: add
            anchors.verticalCenter: resDisplay.verticalCenter
            anchors.left: resDisplay.right
            anchors.leftMargin: 5
            visible: false
            style: ECButtonStyle{ button: add; buttonText: qsTr("添加") }
        }
    }
    //  (QString result, QString nickName, QString age, QString sex)
    Connections {
        target: EcInteraction
        onSig_findAccountResult: {
            if(result === "invalid")
            {
                accountExit.visible = true;
            }
            else
            {
                accountRes.text = "You can add friend!";
                resDisplay.visible = true;
            }
        }
    }
}
