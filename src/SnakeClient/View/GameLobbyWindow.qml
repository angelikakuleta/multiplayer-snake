import QtQuick 2.0
import QtQuick.Controls
import Snake.GameClient 1.0

Item {
    id: lobbyWindow

    property bool isWaiting: false;

    Connections {
        target: GameClient
        function onEnteredRoom() {
            mainLoader.source = "qrc:/View/GameRoomWindow.qml";
        }

        function onErrorMessage(error) {
            errorText.text = error
            lobbyWindow.isWaiting = false;
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
            topMargin: 80
            leftMargin: 80
        }
        color: "white"
        text: "Lobby"
    }

    Text {
        id: joinRoomText
        font.pixelSize: 24
        anchors {
            top: titleText.bottom
            left: titleText.left
            topMargin: 60
        }
        color: "white"
        text: "Join the room"
    }

    ListView {
        id: openRoomList
        model: GameClient.openRooms


        delegate: GameButton {
           buttonColor: "#494D71"
           buttonText: "#" + modelData
           buttonTextPixelSize: 44
           width: 412
           height: 88
           onButtonClicked: {
               if (!openRoomList.isWaiting) {
                   errorText.text = "Joining...";
                   lobbyWindow.isWaiting = true;
                   GameClient.joinRoom(modelData);
               }
           }
        }

        width: 392
        height: 304
        spacing: 10
        clip: true

        anchors {
            top: joinRoomText.bottom
            left: joinRoomText.left
            topMargin: 40
        }

        ScrollBar.vertical: ScrollBar {
            visible: false
        }

        boundsBehavior: Flickable.HorizontalFlick
    }

    Text {
        id: errorText
        font.pixelSize: 24
        font.italic: true
        anchors {
            top: openRoomList.bottom
            left: openRoomList.left
            topMargin: 40
        }

        color: "#D73964"
        text: ""
    }

    GameButton {
        id: createRoomButton
        anchors {
            top: joinRoomText.top
            right: parent.right
            rightMargin: 160
            topMargin: 40
        }

        buttonColor: "#419388"
        buttonText: "New room"
        buttonTextPixelSize: 48
        width: 286
        height: 88
        onButtonClicked: {
            if (!openRoomList.isWaiting) {
                errorText.text = "Joining...";
                lobbyWindow.isWaiting = true;
                GameClient.createRoom();
            }
        }
    }

    GameButton {
        id: quitButton
        anchors {
            top: createRoomButton.bottom
            left: createRoomButton.left
            topMargin: 20
        }

        buttonColor: "#D73964"
        buttonText: "Back"
        buttonTextPixelSize: 48
        width: 286
        height: 88
    }
}
