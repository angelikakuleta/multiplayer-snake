import QtQuick

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
    title: qsTr("SnakeClient")

    Loader {
        id: mainLoader
        anchors.fill: parent
        focus: true
        source: "qrc:/View/MainWindow.qml"
    }
}
