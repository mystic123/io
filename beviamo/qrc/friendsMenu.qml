import QtQuick 2.0

Rectangle {
    id: friendsmenu
    color: "#101010"

    Rectangle {
        id: add
        width: parent.width
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
            text: qsTr("ADD NEW FRIENDS")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                sv.push(Qt.resolvedUrl("addFriends.qml"))
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
                    height: parent.height * 1 / 20

                    Text {
                        id: who
                        text: fName + " " + lName
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.pointSize: 14
                        font.bold: true
                        font.family: "Helvetica"
                        color: "white"
                    }

                    MouseArea {
                        anchors.right: parent.right
                        anchors.rightMargin: parent.height / 2
                        width: parent.height / 2
                        height: parent.height / 2

                        Rectangle {
                            anchors.fill: parent
                            color: red
                        }

                        onClicked: {
                            Bev.Client.addFriend(user_id)
                            sv.pop()
                            sv.push(Qt.resolvedUrl("friendsMenu.qml"))
                        }
                    }

                }
            }
        }

        spacing: 3
        highlightRangeMode: ListView.ApplyRange
        width: parent.width
        height: parent.height - add.height
        anchors.top: add.bottom
        anchors.topMargin: 3
        model: friendsList
        delegate: listDelegate
    }
}

