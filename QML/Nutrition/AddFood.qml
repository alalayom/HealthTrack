import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HealthTrack 1.0

Page {
    id: root
    title: "Add Food"

    property var nutritionVM: appController.nutritionViewModel
    property var nav: appController.navigationManager

    function saveFood() {
        const tName = nameField.text.trim()
        const tCalories = Number(caloriesField.text)
        const tProtein = Number(proteinField.text)
        const tCarbs = Number(carbsField.text)
        const tFat = Number(fatField.text)

        if (tName.length === 0)
        {
            statusLabel.text = "Food name is required."
            return
        }

        const tOk = nutritionVM.addCatalogFood(
            tName,
            isNaN(tCalories) ? 0 : tCalories,
            isNaN(tProtein) ? 0 : tProtein,
            isNaN(tCarbs) ? 0 : tCarbs,
            isNaN(tFat) ? 0 : tFat
        )

        if (tOk)
        {
            statusLabel.text = ""
            nav.goBackToMealDetails()
        }
        else {
            statusLabel.text = "Food could not be added. It may already exist."
        }
    }

    background: Rectangle {
        color: "#121212"
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 14

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Button {
                text: "←"
                onClicked: nav.goBackToMealDetails()
            }

            Label {
                text: "Add New Food"
                color: "#FFFFFF"
                font.pixelSize: 24
                font.bold: true
                Layout.fillWidth: true
            }
        }

        Rectangle {
            Layout.fillWidth: true
            radius: 16
            color: "#1A1A1A"
            border.color: "#2A2A2A"
            border.width: 1
            implicitHeight: formContent.implicitHeight + 28

            ColumnLayout {
                id: formContent
                anchors.fill: parent
                anchors.margins: 14
                spacing: 12

                TextField {
                    id: nameField
                    Layout.fillWidth: true
                    placeholderText: "Food name"
                    color: "#FFFFFF"

                    background: Rectangle {
                        radius: 10
                        color: "#222222"
                        border.color: "#333333"
                    }
                }

                TextField {
                    id: caloriesField
                    Layout.fillWidth: true
                    placeholderText: "Calories (per 100 g)"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    color: "#FFFFFF"

                    background: Rectangle {
                        radius: 10
                        color: "#222222"
                        border.color: "#333333"
                    }
                }

                TextField {
                    id: proteinField
                    Layout.fillWidth: true
                    placeholderText: "Protein (g per 100 g)"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    color: "#FFFFFF"

                    background: Rectangle {
                        radius: 10
                        color: "#222222"
                        border.color: "#333333"
                    }
                }

                TextField {
                    id: carbsField
                    Layout.fillWidth: true
                    placeholderText: "Carbs (g per 100 g)"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    color: "#FFFFFF"

                    background: Rectangle {
                        radius: 10
                        color: "#222222"
                        border.color: "#333333"
                    }
                }

                TextField {
                    id: fatField
                    Layout.fillWidth: true
                    placeholderText: "Fat (g per 100 g)"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    color: "#FFFFFF"

                    background: Rectangle {
                        radius: 10
                        color: "#222222"
                        border.color: "#333333"
                    }
                }

                Label {
                    Layout.fillWidth: true
                    color: "#A0A0A0"
                    wrapMode: Text.WordWrap
                    text: "These values are stored as the food's 100 g reference."
                }

                Label {
                    id: statusLabel
                    Layout.fillWidth: true
                    color: "#FF7B7B"
                    wrapMode: Text.WordWrap
                    text: ""
                }

                Button {
                    text: "Save Food"
                    Layout.alignment: Qt.AlignRight
                    onClicked: root.saveFood()
                }
            }
        }
    }
}
