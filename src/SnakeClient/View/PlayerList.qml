import QtQuick 2.0
import Snake.PlayerList 1.0
import Snake.Tile 1.0

ListView {
    id: playerList
    enabled: false
    interactive: false
    implicitWidth: 300
    implicitHeight: 180
    anchors {
        fill: parent
        topMargin: 20
        leftMargin: 20
    }

    model: PlayerList {
        id: playermodel
    }

    delegate: Rectangle {
        id: player
        implicitWidth: playerList.implicitWidth
        implicitHeight: playerList.implicitHeight / 4
        color: "#3F3F46"

        Rectangle {
            id: isReady
            width: 20;
            height: 20;
            color: model.isReady ? getColor(model.tile) : "#3F3F46"

            anchors {
                left: player.left
                verticalCenter: player.verticalCenter
            }
        }

        Text {
            id: clientId
            text: "#" + model.clientId
            color: "white"
            font.pixelSize: 24

            anchors {
                left: player.left
                leftMargin: 40
                verticalCenter: player.verticalCenter
            }
        }

        Text {
            id: crown
            text: "👑"
            font.pixelSize: 24
            visible: playermodel.isRoomMaster(model.clientId)

            anchors {
                left: clientId.right
                leftMargin: 20
                verticalCenter: player.verticalCenter
            }
        }

        Text {
            id: score
            text: model.score
            color: "white"
            font.pixelSize: 24

            anchors {
                right: player.right
                verticalCenter: player.verticalCenter
            }
        }
    }

    function getColor(tile) {
        switch(tile) {
        case Tile.Snake1: return "#F6BD60"
        case Tile.Snake2: return "#F28482"
        case Tile.Snake3: return "#419388"
        case Tile.Snake4: return "white"
        default: return "#3F3F46"
        }
    }
}
