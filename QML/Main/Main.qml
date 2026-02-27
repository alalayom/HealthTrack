import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HealthTrack 1.0

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

    Component.onCompleted: {
        console.log("Main completed, nav obj =", appController.navigationManager)
        console.log("Main currentPage =", appController.navigationManager.currentPage)
    }

    Connections {
        target: appController.navigationManager
        enabled: true

        function onCurrentPageChanged() {
            const tPage = appController.navigationManager.currentPage;
            console.log("NAV changed:", tPage)

            if(tPage === NavigationManager.Login) {
                rootStack.replace(Qt.resolvedUrl("LoginPage.qml"))
            }

            else if(tPage === NavigationManager.Home) {
                rootStack.replace(Qt.resolvedUrl("HomeScreen.qml"))
            }
        }
    }
}
