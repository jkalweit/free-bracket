import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Free-Bracket Server")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Text {
        anchors.centerIn: parent
        text: "See console for any messages."
    }


//    Button {
//        text: qsTr("Hello Server!")
//        anchors.centerIn: parent
//        onClicked: appData.startServer()
//    }
}
