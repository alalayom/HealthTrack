import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HealthTrack 1.0

Item {
    id: rootLogin
    width: parent ? parent.width : 0
    height: parent ? parent.height : 0

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
                    appController.navigationManager.navigateTo(NavigationManager.Home)
                }
            }
        }
    }
}
