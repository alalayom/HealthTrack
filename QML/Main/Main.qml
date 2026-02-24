import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root

    Material.theme: Material.Dark
    Material.accent: Material.Blue

    visible: true
    width: 1200
    height: 800
    title: "HealthTrack"
    color: "#121212"

    StackView {
        id: rootStack
        anchors.fill: parent
        initialItem: LoginPage {}
    }

    Component.onCompleted: console.log("Main.qml loaded")

    Connections {
        target: appController.navigationManager

        function onCurrentPageChanged(pPage) {
            console.log("NAV changed:", pPage)

            if(pPage === appController.navigationManager.Login) {
                rootStack.replace(Qt.resolvedUrl("LoginPage.qml"))
            }

            else if(pPage === appController.navigationManager.Home) {
                rootStack.replace(Qt.resolvedUrl("HomeScreen.qml"))
            }
        }
    }
}
