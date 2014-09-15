import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Item {

    Rectangle {
        id: addTeamContainer
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: btnAddTeam.height
        color: "#EEEEEE"

        TextInput {
            id: textNewTeam
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: btnAddTeam.left
            text: qsTr("Team")
        }

        Button {
            id: btnAddTeam
            anchors.right: parent.right
            text: qsTr("Add Team")
            onClicked: client.addTeam(textNewTeam.text);
        }
    }


    ListView {
        anchors.top: addTeamContainer.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        model: bracket.teams
        clip: true
        //highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        //focus: true

        delegate: Item {
            width: parent.width;
            height: btnDelete.height
            Text {
                text: (id + 1) + ": " + name
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
            }

            Button {
                id: btnDelete
                anchors.right: parent.right
                width: 40
                text: "X"
                onClicked: client.deleteTeam(id)
            }
    }
}

}
