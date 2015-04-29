import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle {
    id: createevent
    color: "#000000"
    Image {
        id: icon
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        source: "../images/icon/96.png"
    }


    TextField {
        id: what
        placeholderText: qsTr("what?")
        width: parent.width
        height: parent.height/13
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: icon.bottom
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
        id: where
        placeholderText: qsTr("where?")
        width: parent.width
        height: parent.height/13
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: what.bottom
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
        id: when
        placeholderText: qsTr("when?")
        width: parent.width
        height: parent.height/13
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: where.bottom
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
        id: desc
        placeholderText: qsTr("description")
        width: parent.width
        height: parent.height/5
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: when.bottom
        anchors.topMargin: 3
        textColor: "white"
        style: TextFieldStyle {
            placeholderTextColor: "#A8A8A8"
            background: Rectangle {
                color: "#282828"
            }
        }
    }

    Rectangle {
        width: parent.width
        height: parent.height/10
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: createevent.bottom
        anchors.bottomMargin: 0
        color: "#2f7ffa"

        Text {
            font.pointSize: 18
            font.bold: true
            font.family: "Helvetica"
            color: "white"
            text: qsTr("CREATE")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                sv.push(Qt.resolvedUrl("eventMenu.qml"))
            }
        }
    }


}

