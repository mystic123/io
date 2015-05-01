import QtQuick 2.0


Rectangle {
    id: eventmenu
    color: "#101010"

    Rectangle {
        id: friends
        width: parent.width/2
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
        width: parent.width/2
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
                        //text: where + ", " + when
                        text: "DUPADUPA"
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

                            sv.push(Qt.resolvedUrl("event.qml"))
                        }
                    }

                }
            }
        }

        ListModel {
            id: listModel

            ListElement { name: "Dota"; where: "gdzie chcesz"; when: "21:00"; who: "User1" }
            ListElement { name: "Frisbee"; where: "Pole Mokotowskie"; when: "16:00"; who: "User2" }
            ListElement { name: "Narty"; where: "W górach"; when: "12:00"; who: "User3"  }
            ListElement { name: "Festiwal Piwa"; where: "Kufle i Kapsle"; when: "20:00"; who: "User4"  }
            ListElement { name: "Siatka"; where: "Orłowskiego 123"; when: "12:00"; who: "User5"  }
            ListElement { name: "Pilka"; where: "Orlik na Ursynowie"; when: "15:00"; who: "User6"  }
            ListElement { name: "Dota"; where: "gdzie chcesz"; when: "21:00"; who: "User1" }
            ListElement { name: "Frisbee"; where: "Pole Mokotowskie"; when: "16:00"; who: "User2" }
            ListElement { name: "Narty"; where: "W górach"; when: "12:00"; who: "User3"  }
            ListElement { name: "Festiwal Piwa"; where: "Kufle i Kapsle"; when: "20:00"; who: "User4"  }
            ListElement { name: "Siatka"; where: "Orłowskiego 123"; when: "12:00"; who: "User5"  }
            ListElement { name: "Pilka"; where: "Orlik na Ursynowie"; when: "15:00"; who: "User6"  }
        }

        spacing: 3
        highlightRangeMode: ListView.ApplyRange
        width: parent.width
        height: parent.height - ce.height
        anchors.top: ce.bottom
        anchors.topMargin: 3
        model: myModel
        delegate: listDelegate
    }
}

