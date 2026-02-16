import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    property StackView stack

    Rectangle {
        anchors.fill: parent
        color: "#121212"

        Column {
            anchors.centerIn: parent
            spacing: 30

            Label {
                text: "HealthTrack"
                color: "white"
                font.pixelSize: 40
            }

            Button {
                text: "Login"
                width: 250
                height: 60

                onClicked: {
                    stack.push("HomeScreen.qml")
                }
            }
        }
    }
}
