import QtQuick 2.0
import QtQuick.Window
import Snake.GameBoard 1.0
import Snake.GameBoard.Tile 1.0

TableView {
    id: board
    enabled: false
    interactive: false
    implicitWidth: 800
    implicitHeight: 640
    anchors {
        fill: parent
        topMargin: 40
        leftMargin: 40
    }

    model: GameBoard {
        id: boardmodel
    }

    delegate: Rectangle {
        implicitWidth: board.implicitWidth / boardmodel.columnCount()
        implicitHeight: board.implicitHeight / boardmodel.rowCount()
        color: getColor(model.display)

        Text {
            text: isFood(model.display) ? "✱" : ""
            font.pixelSize: 16
            width: parent.implicitWidth
            height: parent.implicitHeight
            horizontalAlignment: TextInput.AlignHCenter
            verticalAlignment: TextInput.AlignVCenter
            color: "white"
        }
    }

    function getColor(tile) {
        switch(tile) {
        case Tile.Snake: return "#F6BD60"
        default: return "#494D71"
        }
    }

    function isFood(tile) {
        return tile === Tile.Fruit;
    }
}
