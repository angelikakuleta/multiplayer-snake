import QtQuick 2.0
import QtQuick.Window
import Snake.GameClient 1.0
import Snake.Direction 1.0

Item {
    id: roomWindow

    focus: true
    Keys.onPressed: (event) => {
        switch (event.key) {
            case Qt.Key_Up:  
                GameClient.changeDirection(Direction.Up);
                console.log("Key Up was pressed")
                break;
            case Qt.Key_Down:
                GameClient.changeDirection(Direction.Down);
                console.log("Key Down was pressed")
                break;
            case Qt.Key_Left:
                GameClient.changeDirection(Direction.Left);
                console.log("Key Left was pressed")
                break;
            case Qt.Key_Right:
                GameClient.changeDirection(Direction.Right);
                console.log("Key Right was pressed")
                break;
            default:
                break;
        }
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: "#252526"
    }

    GameBoard {
        id: gameBoard

        anchors {
            topMargin: 40
            leftMargin: 40
        }
    }

    Text {
        id: roomText
        font.pixelSize: 48
        font.bold: true
        anchors {
            top: parent.top
            right: parent.right
            topMargin: 40
            rightMargin: 40
        }
        color: "white"
        text: "Room #" + GameClient.roomId;
    }

    Rectangle {
        id: playersRec
        width: 360
        height: 220
        anchors {
            top: roomText.bottom
            right: roomText.right
            topMargin: 40
        }
        color: "#3F3F46"

        PlayerList {
            id: players
        }
    }

    Text {
        id: clock
        font.pixelSize: 48
        width: 360
        height: 184 - roomText.height
        anchors {
            top: playersRec.bottom
            right: playersRec.right
        }
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        color: "white"
        text: "05:00";
    }

    GameButton {
        id: readyButton
        anchors {
            top: clock.bottom
            right: playersRec.right
            rightMargin: (playersRec.width - readyButton.width)/2
        }

        property bool isClicked: false;
        buttonColor: "#419388"
        buttonText: "Ready"
        onButtonClicked: {
            if (!isClicked) {
                this.isClicked = true;
                readyButton.buttonColor = "#3F3F46"
                GameClient.readyToPlay();
                GameClient.startGame();
            }
        }
    }

    GameButton {
        id: leaveButton
        anchors {
            top: readyButton.bottom
            left: readyButton.left
            topMargin: 20
        }

        buttonColor: "#D73964"
        buttonText: "Leave"
        onButtonClicked: {
            GameClient.leaveRoom();
            mainLoader.source = "qrc:/View/GameLobbyWindow.qml";
        }
    }
}
