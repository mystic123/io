import QtQuick 2.0
import Bev 1.0 as Bev

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
                width: friendsmenu.width
                height: friendsmenu.height / 10
                color: "#383838"

                Text {
                    id: who
                    text: fName + " " + lName
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 14
                    font.bold: true
                    font.family: "Helvetica"
                    color: "white"
                }

                Rectangle {
                    anchors.top: parent.top
                    anchors.topMargin: parent.height / 4
                    anchors.right: parent.right
                    anchors.rightMargin: parent.height / 4
                    width: parent.height / 2
                    height: parent.height / 2
                    color: "#FF0033"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            console.log("usuwam friend")
                            sv.pop()
                            sv.push(Qt.resolvedUrl("friendsMenu.qml"))
                            Bev.Client.delFriend(user_id);
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

