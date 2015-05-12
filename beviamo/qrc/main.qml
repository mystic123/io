import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("Beviamo")
    width: 640
    height: 480
    visible: true

    Rectangle {
        anchors.fill: parent

        StackView {
            id: sv
            anchors.fill: parent
            focus: true

            initialItem: Qt.resolvedUrl("FacebookView.qml")

            Keys.onReleased: {
//                console.log("KEY_PRESSED: " + event.key)
//                console.log("depth: " + sv.depth)
                if (event.key === Qt.Key_Back) {
                    if (sv.depth > 1) {
                        sv.pop();
                        event.accepted = true;
                        sv.focus = true;
                    } else {
                        Qt.quit();
                    }
                }
            }
        }
    }
}
