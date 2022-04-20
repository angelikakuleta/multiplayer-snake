import QtQuick 2.0
import Snake.GameClient 1.0

Item {
    id: mainWindow

    Connections {
        target: GameClient
        function onConnected() {
            mainLoader.source = "qrc:/View/GameLobbyWindow.qml"
        }

        function onErrorMessage(error) {
            errorText.text = error
            connectButton.isWaiting = false;
        }
    }

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

        property bool isWaiting: false;
        buttonColor: "#419388"
        buttonText: "Connect"
        onButtonClicked: {
            if (!this.isWaiting) {
                errorText.text = "Connecting...";
                this.isWaiting = true;
                GameClient.connectToServer();
            }
        }
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

    Text {
            id: errorText
            font.pixelSize: 24
            font.italic: true
            anchors {
                top: quitButton.bottom
                left: quitButton.left
                topMargin: 80
            }

            color: "#D73964"
            text: ""
        }
}
