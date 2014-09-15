import QtQuick 2.0

Item {
    id: container
    property var model

    width: 200
    height: 400

    Rectangle {
        id: rectangle
        anchors.fill: parent
        color: "blue"
        border.color: "white"


        Repeater {
            model: container.model.getTeams()

            Team { model: modelData }
        }

    }
}


