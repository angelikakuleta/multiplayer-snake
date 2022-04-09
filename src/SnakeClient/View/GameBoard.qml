import QtQuick 2.0
import QtQuick.Window
import GameBoard.Tile 1.0

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

    model: GameBoardVM

    delegate: Rectangle {
        implicitWidth: board.implicitWidth / GameBoardVM.columnCount()
        implicitHeight: board.implicitHeight / GameBoardVM.rowCount()
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
