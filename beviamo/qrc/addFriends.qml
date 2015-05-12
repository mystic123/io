import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import Bev 1.0 as Bev

Rectangle {
    id: addfriends
    color: "#101010"
    Image {
        id: icon
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        source: "../images/icon/96.png"
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
                        id: infowhat
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
                            color: green
                        }

                        onClicked: {
                            Bev.Client.addFriend(user_id)
                        }
                    }

                }
            }
        }

        spacing: 3
        highlightRangeMode: ListView.ApplyRange
        width: parent.width
        height: parent.height - icon.height
        anchors.top: icon.bottom
        anchors.topMargin: 3
        model: facebookFriendsList
        delegate: listDelegate
    }

}

