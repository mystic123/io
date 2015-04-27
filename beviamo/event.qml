import QtQuick 2.0

Rectangle {
    color: "#101010"
    id: event

    Rectangle {
        id: info
        width: event.width * 9/10
        height: (infocontainer.height) * 6/5
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: event.top
        anchors.topMargin: 5
        color: "#383838"

        Rectangle {
            id: infocontainer
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.widh
            height: info1.height+ info2.height
            Text {
                id: info1
                text: "Dota, by Andrew"
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 16
                font.bold: true
                font.family: "Helvetica"
                color: "white"
            }

            Text {
                id: info2
                text: "gdzie chcesz, 21:00"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: info1.bottom
                anchors.topMargin: 0
                font.pointSize: 16
                font.bold: true
                font.family: "Helvetica"
                color: "white"
            }
        }
    }

    Rectangle {
        id: descheader
        width: parent.width
        height: event.height / 10
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: info.bottom
        anchors.topMargin: 5
        color: "#2f7ffa"

        Text {
            font.pointSize: 14
            font.bold: true
            font.family: "Helvetica"
            color: "white"
            text: qsTr("DESCRIPTION:")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Rectangle {
        id: description
        width: event.width
        height: descriptiontext.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: descheader.bottom
        anchors.topMargin: 5
        color: "#101010"

        Text {
            id: descriptiontext
            font.pointSize: 13
            font.bold: true
            font.family: "Helvetica"
            color: "white"
            text: qsTr("ALE FAJNY OPIS\nALE FAJNY OPIS\nALE FAJNY OPIS\nALE FAJNY OPIS")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Rectangle {
        id: joined
        width: parent.width
        height: event.height/10
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: description.bottom
        anchors.topMargin: 5
        color: "#2f7ffa"
        z: 1

        Text {
            font.pointSize: 14
            font.bold: true
            font.family: "Helvetica"
            color: "white"
            text: qsTr("JOINED IN:")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    ListView {
        id: listView

        Component {
            id: listDelegate
            Rectangle {
                id: wrapper
                height: infowhat.height
                width: event.width
                color: "#101010"
                Text {
                    id: infowhat
                    text: modelData
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 14
                    font.bold: true
                    font.family: "Helvetica"
                    color: "white"
                }
            }
        }

        ListModel {
            id: listModel

            ListElement { name: "Andrzej" }
            ListElement { name: "Pszemek" }
            ListElement { name: "Bartek" }
            ListElement { name: "Maria" }
            ListElement { name: "Leszek" }
        }

        spacing: 3
        highlightRangeMode: ListView.ApplyRange
        width: parent.width
        height: parent.height - info.height - joined.height - join.height
                - descheader.height - description.height - 20
        anchors.top: joined.bottom
        anchors.topMargin: 5
        model: myModel
        delegate: listDelegate
    }

    Rectangle {
        id: join
        width: parent.width
        height: event.height/10
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: event.bottom
        color: "#2f7ffa"
        z: 1

        Text {
            font.pointSize: 14
            font.bold: true
            font.family: "Helvetica"
            color: "white"
            text: qsTr("JOIN")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}

