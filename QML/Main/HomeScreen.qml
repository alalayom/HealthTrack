import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HealthTrack 1.0

Item {
    id: rootHome
    width: parent ? parent.width : 0
    height: parent ? parent.height : 0

    readonly property var nav: appController.navigationManager

    function middleSourceFromPage() {
        const tPage = nav.currentPage

        if (tPage === NavigationManager.Nutrition)
        {
            return "../Nutrition/NutritionMain.qml"
        }
        if (tPage === NavigationManager.MealDetails)
        {
            return "../Nutrition/MealDetails.qml"
        }
        if (tPage === NavigationManager.AddFood)
        {
            return "../Nutrition/AddFood.qml"
        }

        return ""
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // =========================
        // TOP PANEL
        // =========================
        Rectangle {
            id: topPanel
            Layout.fillWidth: true
            Layout.preferredHeight: 80
            color: "#1E1E1E"

            RowLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 40

                // Statistics Section
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 44
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
                    Layout.preferredHeight: 44
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
        Rectangle {
            id: middlePanel
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#181818"

            Loader {
                id: middleLoader
                anchors.fill: parent
                source: rootHome.middleSourceFromPage()

                onStatusChanged: {
                    if(status === Loader.Error)
                    {
                        console.log("Loader error: ", source)
                    }
                }
            }

            Item {
                anchors.fill: parent
                visible: middleLoader.status === Loader.Null

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
            Layout.preferredHeight: 80
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
                    color: nav.currentPage === NavigationManager.Nutrition
                        || nav.currentPage === NavigationManager.MealDetails
                        || nav.currentPage === NavigationManager.AddFood
                        ? "#3A3A3A" : "#2A2A2A"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: nav.navigateToNutrition()
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

    Connections {
        target: nav

        function onCurrentPageChanged() {
            middleLoader.source = rootHome.middleSourceFromPage()
        }
    }

    Component.onCompleted: {
        middleLoader.source = rootHome.middleSourceFromPage()
    }
}
