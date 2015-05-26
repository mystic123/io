import QtQuick 2.0
import QtWebView 1.0
import QtQuick.Layouts 1.1
import Bev 1.0 as Bev


Rectangle {
    WebView {
        id: webView
        anchors.fill: parent
        url: Qt.resolvedUrl(initialUrl)
        visible: false;
        z: 1;

        onLoadingChanged: {

            if (Bev.Client.fine_url(url)) {
                webView.visible = true;
            } else {
                webView.visible = false;
            }

            if (Bev.Client.access_url(url)) {
                sv.clear();
                sv.push(Qt.resolvedUrl("eventMenu.qml"));
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
