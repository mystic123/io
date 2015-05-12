import QtQuick 2.0
import Bev 1.0 as Bev

Rectangle {
    id: eventmenu
    color: "#101010"

    Rectangle {
        id: friends
        width: parent.width * 4 / 10
        height: parent.height/10
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        z: 1
        color: "#2f7ffa"

        Text {
            font.pointSize: 18
            font.bold: true
            font.family: "Helvetica"
            color: "white"
            text: qsTr("FRIENDS")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                sv.push(Qt.resolvedUrl("friendsMenu.qml"))
            }
        }
    }

    Rectangle {
        id: ce
        width: parent.width * 4 / 10
        height: parent.height/10
        anchors.left: friends.right
        anchors.leftMargin: 1
        anchors.top: parent.top
        anchors.topMargin: 0
        z: 1
        color: "#2f7ffa"

        Text {
            font.pointSize: 18
            font.bold: true
            font.family: "Helvetica"
            color: "white"
            text: qsTr("CREATE EVENT")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                sv.push(Qt.resolvedUrl("createEvent.qml"))
            }
        }
    }


    Rectangle {
        id: logout
        width: parent.width * 2 / 10
        height: parent.height/10
        anchors.left: ce.right
        anchors.leftMargin: 1
        anchors.top: parent.top
        anchors.topMargin: 0
        z: 1
        color: "#2f7ffa"

        Text {
            font.pointSize: 12
            font.bold: true
            font.family: "Helvetica"
            color: "white"
            text: qsTr("LOG OUT")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                Bev.Client.set_logout_url();
                sv.clear();
                sv.push(Qt.resolvedUrl("fbLogOut.qml"))
            }
        }
    }


    ListView {
        id: listView

        Component {
            id: listDelegate
            Rectangle {
                id: wrapper
                height: eventmenu.height/10
                width: eventmenu.width
                color: "#383838"
                Rectangle {
                    color: "#383838"
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width
                    height: infowhat.height + infowhere.height
                    Text {
                        id: infowhat
                        text: desc
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.pointSize: 14
                        font.bold: true
                        font.family: "Helvetica"
                        color: "white"
                    }

                    Text {
                        id: infowhere
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: infowhat.bottom
                        anchors.topMargin: 0
                        font.pointSize: 14
                        font.bold: true
                        font.family: "Helvetica"
                        color: "white"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            Bev.Client.chosenEventModel(event_id)
                            sv.push(Qt.resolvedUrl("event.qml"))
                        }
                    }

                }
            }
        }

        spacing: 3
        highlightRangeMode: ListView.ApplyRange
        width: parent.width
        height: parent.height - ce.height
        anchors.top: ce.bottom
        anchors.topMargin: 3
        model: eventsList
        delegate: listDelegate
    }


}

