import QtQuick 2.0

Item {
    id: item
    property var model

    Line {
        id: line
        x1: model.x1
        y1: model.y1
        x2: model.x2
        y2: model.y2
        color: model.color

//        states: State {
//                     name: "visible";
//                     when: model.color !== "transparent";
//                     PropertyChanges { target: line; color: model.color }
//                 }

//         transitions: Transition {
//             reversible: true
//             ColorAnimation { target: line.color; duration: 200 }
//         }
    }

}
