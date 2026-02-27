import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HealthTrack 1.0

Item {
    id: rootHome
    width: parent ? parent.width : 0
    height: parent ? parent.height : 0

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // =========================
        // TOP PANEL
        // =========================
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 120
            color: "#1E1E1E"

            RowLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 40

                // Statistics Section
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 80
                    radius: 8
                    color: "#2A2A2A"

                    //TODO: Add statistics section to it.

                    Label {
                        anchors.centerIn: parent
                        text: "Statistics"
                        color: "white"
                        font.pixelSize: 20
                    }
                }

                // Settings Section
                Rectangle {
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 80
                    radius: 8
                    color: "#2A2A2A"

                    //TODO: Add settings section to it.

                    Label {
                        anchors.centerIn: parent
                        text: "Settings"
                        color: "white"
                        font.pixelSize: 20
                    }
                }
            }
        }

        // =========================
        // MIDDLE PANEL
        // =========================
        StackView {
            id: contentStack
            Layout.fillWidth: true
            Layout.fillHeight: true

            initialItem: Rectangle {
                color: "#181818"

                Label {
                    anchors.centerIn: parent
                    text: "Welcome to HealthTrack"
                    color: "#AAAAAA"
                    font.pixelSize: 26
                }
            }
        }

        // =========================
        // BOTTOM PANEL
        // =========================
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 140
            color: "#1E1E1E"

            RowLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 20

                //Nutrition Section
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: 8
                    color: "#2A2A2A"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            contentStack.replace("../Nutrition/NutritionMain.qml");
                        }
                    }

                    Label {
                        anchors.centerIn: parent
                        text: "Nutrition"
                        color: "white"
                        font.pixelSize: 18
                    }
                }

                // Sport Section
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: 8
                    color: "#2A2A2A"

                    //TODO: Add sport section to it.

                    Label {
                        anchors.centerIn: parent
                        text: "Sport"
                        color: "white"
                        font.pixelSize: 18
                    }
                }

                // Sleep Section
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: 8
                    color: "#2A2A2A"

                    //TODO: Add sleep section to it.

                    Label {
                        anchors.centerIn: parent
                        text: "Sleep"
                        color: "white"
                        font.pixelSize: 18
                    }
                }

                // Profile Section
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: 8
                    color: "#2A2A2A"

                    //TODO: Add profile section to it.

                    Label {
                        anchors.centerIn: parent
                        text: "Profile"
                        color: "white"
                        font.pixelSize: 18
                    }
                }
            }
        }
    }
}
