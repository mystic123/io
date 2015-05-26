import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import Bev 1.0 as Bev

Rectangle {
    id: comm
    color: "#101010"

    Image {
        id: icon
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        source: "../images/icon/96.png"
    }

    ListView {
        id: lView

        Component {
            id: listDelegate
            Rectangle {
                id: wrapper
                height: info1.height + info2.height
                width: comm.width
                color: "#383838"
                Text {
                    id: info1
                    text: author + ", " + date
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 14
                    font.bold: true
                    font.family: "Helvetica"
                    color: "green"
                }

                Text {
                    id: info2
                    text: content
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: info1.bottom
                    anchors.topMargin: 5
                    lineHeight: 1.2
                    font.pointSize: 13
                    font.bold: true
                    font.family: "Helvetica"
                    color: "white"
                }
            }
        }

        spacing: 3
        highlightRangeMode: ListView.ApplyRange
        width: parent.width
        height: parent.height - icon.height - content.height
        anchors.top: icon.bottom
        anchors.topMargin: 5
        model: commentList
        delegate: listDelegate
    }

    TextField {
        id: content
        placeholderText: qsTr("content")
        width: parent.width * 8/10
        height: parent.height/10
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        z: 1
        textColor: "white"
        style: TextFieldStyle {
            placeholderTextColor: "#A8A8A8"
            background: Rectangle {
                color: "#282828"
            }
        }
    }
    Rectangle {
        id: error
        width: parent.width * 2/10
        height: parent.height / 10
        anchors.left: content.right
        anchors.leftMargin: 1
        anchors.bottom: submit.top
        anchors.bottomMargin: 1
        color: "red"
        z: 1
        visible: false;

        Text {
            font.pointSize: 14
            font.bold: true
            font.family: "Helvetica"
            color: "white"
            text: qsTr("TOO LONG!")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Rectangle {
        id: submit
        width: parent.width * 2/10
        height: parent.height/10
        anchors.left: content.right
        anchors.leftMargin: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        color: "#2f7ffa"
        z: 1

        Text {
            font.pointSize: 14
            font.bold: true
            font.family: "Helvetica"
            color: "white"
            text: qsTr("SUBMIT")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (content.displayText.length <= 100) {
                    error.visible = false;
                    Bev.Client.add_comment(content.displayText);
                    Bev.Client.get_event_comments();
                    sv.pop();
                    sv.push(Qt.resolvedUrl("comments.qml"));
                } else {
                    error.visible = true;
                }
            }
        }
    }

}

