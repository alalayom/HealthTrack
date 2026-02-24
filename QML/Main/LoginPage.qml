import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    anchors.fill: parent

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
                    console.log("Login clicked -> go Home")
                    appController.navigationManager.navigateTo(appController.navigationManager.Home)
                }
            }
        }
    }
}
