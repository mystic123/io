import QtQuick 2.0
import QtWebView 1.0
import QtQuick.Layouts 1.1
import Bev 1.0 as Bev

Rectangle {

    WebView {
        id: webview
        z: 1
        anchors.fill: parent
        url: Qt.resolvedUrl(logoutUrl)
        visible: false;

        onLoadingChanged: {
            if (loading == false) {
                console.log("wywolane")
                sv.clear();
                sv.push(Qt.resolvedUrl("FacebookView.qml"));
            }
        }
    }

    Image {
        id: img
        anchors.fill: parent
        anchors.topMargin: 0
        fillMode: Image.Tile
        source: "../images/happy.png"
    }
}

