import QtQuick 2.0

Item {
    id: container
    property var roundModel
    property var model
    //signal winner(string name)

    width: 200
    height: 50

    Rectangle {
        id: rectangle
        color: "grey"
        anchors.fill: parent

        Rectangle {
            id: matchNumber
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            width: 30
            color: "#DDDDDD"
            border.width: 1
            border.color: "black"

            Text {
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                text:  {
                    //Math.pow(2, container.roundModel.round) - 1 + modelData.matchNumber - 1;
                    var offset = 0;
                    for(var i = 1; i < container.roundModel.round; i++) {
                        offset += Math.pow(2, bracket.numRounds - i);
                    }

                    return offset + modelData.matchNumber;
                }
            }
        }

        Rectangle {
            id: team1
            anchors.left: matchNumber.right
            anchors.right: parent.right
            anchors.top: parent.top
            height: Math.round(parent.height / 2)
            color: "#DDDDDD"
            border.width: 1
            border.color: "black"

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10
                text: model.team1 ? model.team1.name : ""
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log('clicked round:' + roundModel.round + ' match: ' + model.matchNumber + ' team1');
                    bracket.setWinner(roundModel.round, model.matchNumber, 0);
                }
            }
        }

        Rectangle {
            id: team2
            anchors.left: matchNumber.right
            anchors.right: parent.right
            anchors.top: team1.bottom
            anchors.bottom: parent.bottom
            color: "#DDDDDD"
            border.width: 1
            border.color: "black"

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10
                text: model.team2 ? model.team2.name : ""
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log('clicked round:' + roundModel.round + ' match: ' + model.matchNumber + ' team2');
                    bracket.setWinner(roundModel.round, model.matchNumber, 1);
                }
            }
        }
    }
}
