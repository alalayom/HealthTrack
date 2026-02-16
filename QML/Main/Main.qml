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
        initialItem: LoginPage {
            stack: rootStack
        }
    }
}
