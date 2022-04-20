import QtQuick
import Snake.GameClient 1.0

Window {
    property int windowWidth: 1280
    property int windowHeight: 720

    width: windowWidth
    height: windowHeight
    maximumWidth: windowWidth
    maximumHeight: windowHeight
    minimumWidth: windowWidth
    minimumHeight: windowHeight

    visible: true
    title: "SnakeClient " + clientId()

    Loader {
        id: mainLoader
        anchors.fill: parent
        focus: true
        source: "qrc:/View/MainWindow.qml"
    }

    function clientId() {
        return GameClient.clientId !== -1
                ? "#" + GameClient.clientId : "";
    }
}
