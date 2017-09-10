import QtQuick 2.5
import QtQuick.Window 2.2

import MyModels 1.0
import Cells 1.0

Item {
    id: mainItem
    visible: true
    width: 480
    height: 480

    TestModel {
        id: dataModel
    }

    GridView {
        id: grid
        anchors.margins: 0
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        model: dataModel
        cellHeight: mainItem.height / 4
        cellWidth: mainItem.width / 4
        focus: true

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
                    renderType: Text.NativeRendering
                    text: model.text
                    font.pixelSize: {
                    grid.width / 4 < grid.height / 4 ?
                        grid.width / 4 - 25 :
                        grid.height / 4 - 25
                    }
                }
            }
        }

        move: Transition {
            NumberAnimation { properties: "x,y"; duration: 500 }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                grid.currentIndex = grid.indexAt(mouse.x, mouse.y);
                dataModel.moveLeft(grid.currentIndex, grid.currentIndex + 1);
            }
        }
    }
}
