import QtQuick 2.0
import QtQuick.Window

Item {
    id: roomWindow

    focus: true
    Keys.onPressed: (event) => {
        switch (event.key) {
            case Qt.Key_Up:
                console.log("Key Up was pressed")
                break;
            case Qt.Key_Down:
                console.log("Key Down was pressed")
                break;
            case Qt.Key_Left:
                console.log("Key Left was pressed")
                break;
            case Qt.Key_Right:
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
        text: "Room #9999";
    }

    Rectangle {
        id: players
        width: 360
        height: 220
        anchors {
            top: roomText.bottom
            right: roomText.right
            topMargin: 40
        }
        color: "#3F3F46"
    }

    Text {
        id: clock
        font.pixelSize: 48
        width: 360
        height: 184 - roomText.height
        anchors {
            top: players.bottom
            right: players.right
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
            right: players.right
            rightMargin: (players.width - readyButton.width)/2
        }

        buttonColor: "#419388"
        buttonText: "Ready"
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
        onButtonClicked: mainLoader.source = "qrc:/View/MainWindow.qml"
    }
}
