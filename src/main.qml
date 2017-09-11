import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import Qt.labs.controls 1.0

import Models 1.0
import Controllers 1.0

ApplicationWindow {
    id: mainItem
    visible: true
    width: 480
    height: 480
    color: "black"
    title: "fiveteen"

    Popup {
        id: startGame
        x: 0
        y: 0
        width: mainItem.width
        height: mainItem.height
        modal: true
        opacity: 0.9
        closePolicy: Popup.NoAutoClose

        ColumnLayout {
            anchors.fill: parent

            Button {
                id: gameButton
                Layout.alignment: Qt.AlignCenter
                text: "Start"
                Layout.preferredHeight: mainItem.height * 0.1
                Layout.preferredWidth: mainItem.width * 0.8
                onClicked: {
                    gameButton.text = "Continue..."
                    startGame.close();
                }
            }
            Button {
                id: shuffleButton
                Layout.alignment: Qt.AlignCenter
                text: "Shuffle"
                Layout.preferredHeight: mainItem.height * 0.1
                Layout.preferredWidth: mainItem.width * 0.8
                onClicked: {
                    gameButton.text = "Start";
                    grid.model = gController.newModel();
                }
            }
            Button {
                id: exitButton
                Layout.alignment: Qt.AlignCenter
                text: "Exit"
                Layout.preferredHeight: mainItem.height * 0.1
                Layout.preferredWidth: mainItem.width * 0.8
                onClicked: {
                    Qt.quit();
                }
            }
            Text {
                Layout.alignment: Qt.AlignCenter
                text: 'Press "space" for pause.'
                font.pointSize: mainItem.height * 0.03
           }
        }
    }

    Popup {
        id: endGame
        x: 0
        y: 0
        width: mainItem.width
        height: mainItem.height
        modal: true
        opacity: 0.9
        closePolicy: Popup.NoAutoClose

        ColumnLayout {
            anchors.fill: parent

            Text {
                Layout.alignment: Qt.AlignCenter
                id: gameOver
                font.pointSize: mainItem.height * 0.05
                verticalAlignment: Text.AlignVCenter
            }
            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.preferredWidth: 300

                id: restartButton
                text: "Restart"
                onClicked: {
                    mainItem.title = "new game"
                    grid.model = gController.newModel();
                    endGame.close();
                }
            }
            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.preferredWidth: 300

                text: "Exit"
                onClicked: {
                    Qt.quit();
                }
            }
        }
    }

    Component.onCompleted: {
        startGame.open();
    }

    GridView {
        id: grid
        anchors.margins: 0
        anchors.fill: parent
        model: BModel {}
        cellHeight: height / 4
        cellWidth: width / 4
        focus: true
        interactive: false

        delegate: Item {
            id: gridDelegate
            width: grid.cellWidth
            height: grid.cellHeight
            Rectangle {
                anchors.margins: 1
                anchors.fill: parent
                color: model.color
                Text {
                    anchors.centerIn: parent
                    text: model.text
                    color: model.textColor
                    font.pixelSize: {
                        grid.cellHeight < grid.cellWidth ?
                            grid.cellHeight - 25 : grid.cellWidth - 25;
                    }
                }
            }
        }

        move: Transition {
            NumberAnimation { properties: "x,y"; duration: 150 }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                grid.currentIndex = grid.indexAt(mouse.x, mouse.y);
                gController.move(grid.currentIndex);
            }
        }
    }

    GController {
        id: gController
        model: grid.model
        objectName: "gameController"

        onEndGame: {
            gameOver.text = "Game Over!!!(" + turns + ")";
            gameOver.text.pointSize = mainItem.height * 0.1
            endGame.open();
        }

        onAmountChanged: { mainItem.title = a; }
    }
}
