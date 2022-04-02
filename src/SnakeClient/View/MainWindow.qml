import QtQuick 2.0

Item {
    id: mainWindow

    Rectangle {
        id: background
        anchors.fill: parent
        color: "#252526"
    }

    Text {
        id: titleText
        font.pixelSize: 48
        font.bold: true
        anchors {
            top: parent.top
            left: parent.left
            topMargin: 120
            leftMargin: 80
        }
        color: "white"
        text: "Multiplayer Snake"
    }

    GameButton {
        id: connectButton
        anchors {
            top: titleText.bottom
            left: titleText.left
            topMargin: 80
        }

        buttonColor: "#419388"
        buttonText: "Connect"
        onButtonClicked: mainLoader.source = "qrc:/View/GameRoomWindow.qml"
    }

    GameButton {
        id: quitButton
        anchors {
            top: connectButton.bottom
            left: connectButton.left
            topMargin: 20
        }

        buttonColor: "#D73964"
        buttonText: "Quit"
        onButtonClicked: Qt.quit();
    }
}
