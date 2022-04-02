import QtQuick

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("SnakeClient")

    Loader {
        id: mainLoader
        anchors.fill: parent
        source: "qrc:/View/MainWindow.qml"
    }
}
