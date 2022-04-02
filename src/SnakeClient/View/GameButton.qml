import QtQuick 2.0

Rectangle {
    id: gameButton

    property string buttonColor: "#3F3F46"
    property string buttonColorOnPressed: "#3F3F46"
    property string buttonText: ""
    property int buttonTextPixelSize: 48
    property int buttonWidth: 286
    property int buttonHeight: 88

    signal buttonClicked()

    color: buttonColor
    width: buttonWidth
    height: buttonHeight


    Text {
        anchors.centerIn: parent
        color: "white"
        text: buttonText
        font.pixelSize: buttonTextPixelSize
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: gameButton.color = buttonColorOnPressed
        onExited: gameButton.color = buttonColor;
        onClicked: gameButton.buttonClicked()
    }
}
