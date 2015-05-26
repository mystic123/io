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
                width: addfriends.width
                height: addfriends.height / 10
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
                    color: "green"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                          console.log("dodaje friends")
                          sv.pop();
                          sv.pop();
                          sv.push(Qt.resolvedUrl("friendsMenu.qml"));
                          Bev.Client.addFriend(user_id);
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
