import QtQuick 2.0
import QtWebView 1.0
import QtQuick.Layouts 1.1
import Bev 1.0 as Bev

Rectangle {

    WebView {
        id: webview
        z: 1
        width: 640
        height: 480
        anchors.fill: parent
        url: Qt.resolvedUrl(logoutUrl)

        onLoadingChanged: {
                console.log("WYWOLUJE")
                sv.push(Qt.resolvedUrl("FacebookView.qml"));
        }
    }

//    Image {
//        id: img
//        anchors.top: parent.top
//        anchors.topMargin: 0
//        anchors.horizontalCenter: parent.horizontalCenter
//        source: "../images/happy.png"
//        fillMode: Image.Tile
//        z: 2
//    }

//    Timer {
//        interval: 2000; running: true; repeat: false
//        onTriggered: {
//            img.z = 0;
//        }
//    }
}

