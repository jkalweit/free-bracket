import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import FreeBracket 1.0

ApplicationWindow {
    visible: true
    width: 1000
    height: 800
    color: "#222222"
    title: qsTr("Free Bracket")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
//            MenuItem {
//                text: qsTr("Connect")
//                onTriggered: client.connectToServer();
//            }
            MenuItem {
                text: qsTr("Start Tournament")
                onTriggered: client.startTournament();
            }
        }
    }




    Rectangle {
        id: scalingContainer
        anchors.top: parent.top
        anchors.left: parent.left
        width: 200
        height: btnScaleDown.height

        Button {
            id: btnScaleDown
            anchors.left: parent.left
            width: parent.width / 2
            text: qsTr("Zoom Out")
            onClicked: scalingRect.scale -= 0.05
        }
        Button {
            id: btnScaleUp
            anchors.right: parent.right
            width: parent.width / 2
            text: qsTr("Zoom In")
            onClicked: scalingRect.scale += 0.05
        }
    }


    Rectangle {
        id: teams
        width: 200 // Math.round(parent.width / 5.0)
        anchors.top: scalingContainer.bottom
        anchors.bottom: parent.bottom
        color: "#DDDDDD"

        Teams {
            anchors.fill: parent
        }
    }



    Flickable {
        id: page
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: teams.right
        contentWidth: 2400
        contentHeight: 2400
        clip: true        

//        Repeater {
//            model: appData.getLines()
//            Line2 { model: modelData }
//        }

        Rectangle {
            id: scalingRect
            anchors.fill: parent
            transformOrigin: Item.TopLeft
            color: "#555555"

            Repeater {
                id: roundsRepeater
                model: bracket.rounds

                Repeater {
                    id: roundRepeater
                    property var roundModel: modelData
                    model: modelData.matches

                    Match {
                        x: 10 + (roundRepeater.roundModel.round - 1) * (width + 20)
                        y: 10 + (Math.pow(2, roundRepeater.roundModel.round - 1) * height) * (modelData.matchNumber - 1) + ((Math.pow(2, roundRepeater.roundModel.round - 1) - 1) * height/2)
                        roundModel: roundRepeater.roundModel
                        model: modelData
                    }
                }
            }
        }
    }
}
