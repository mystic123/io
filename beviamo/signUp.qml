import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle {
    color: "#101010"

    Image {
        id: icon
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        source: "images/icon/96.png"
    }

    Rectangle {
        id: gap1
        width: parent.width
        height: parent.height/13
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: icon.bottom
        anchors.topMargin: 0
        color: "#101010"
    }

    TextField {
        id: email
        placeholderText: qsTr("E-mail")
        width: parent.width
        height: parent.height/13
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: gap1.bottom
        anchors.topMargin: 0
        textColor: "white"
        style: TextFieldStyle {
            placeholderTextColor: "#A8A8A8"
            background: Rectangle {
                color: "#282828"
            }
        }
    }

    TextField {
        id: username
        placeholderText: qsTr("Username")
        width: parent.width
        height: parent.height/13
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: email.bottom
        anchors.topMargin: 3
        textColor: "white"
        style: TextFieldStyle {
            placeholderTextColor: "#A8A8A8"
            background: Rectangle {
                color: "#282828"
            }
        }
    }

    TextField {
        id: password
        placeholderText: qsTr("password")
        width: parent.width
        height: parent.height/13
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: username.bottom
        anchors.topMargin: 3
        textColor: "white"
        echoMode: TextInput.Password
        style: TextFieldStyle {
            placeholderTextColor: "#A8A8A8"
            background: Rectangle {
                color: "#282828"
            }
        }
    }

    Rectangle {
        id: gap2
        width: parent.width
        height: parent.height/13
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: password.bottom
        anchors.topMargin: 0
        color: "#101010"

        Text {
            id: error
            font.pointSize: 13
            font.bold: true
            font.family: "Helvetica"
            color: "#A80000"
            text: qsTr("")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Rectangle {
        width: parent.width
        height: parent.height/10
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: gap2.bottom
        anchors.topMargin: 0
        color: "#2f7ffa"

        Text {
            font.pointSize: 18
            font.bold: true
            font.family: "Helvetica"
            color: "white"
            text: qsTr("SIGN UP")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                //error.text = qsTr("test");
                sv.push(Qt.resolvedUrl("eventMenu.qml"))
            }
        }
    }
}
