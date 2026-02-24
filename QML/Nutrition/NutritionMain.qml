import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: nutritionRoot
    anchors.fill: parent

    // Added dummy data for testing qml page design. Later data will be provided from ViewModel
    property string selectedDateText: "Today"
    property int caloriesEaten: 1291
    property int caloriesBurned: 244
    property int caloriesGoal: 2117
    property int caloriesRemaining: Math.max(0, caloriesGoal - caloriesEaten + caloriesBurned)

    property int carbsCurrent: 206
    property int carbsGoal: 258
    property int proteinCurrent: 35
    property int proteinGoal: 103
    property int fatCurrent: 32
    property int fatGoal: 68

    property int breakfastCurrent: 56
    property int breakfastGoal: 635
    property int lunchCurrent: 856
    property int lunchGoal: 847
    property int dinnerCurrent: 379
    property int dinnerGoal: 529
    property int snacksCurrent: 0
    property int snacksGoal: 106

    property int waterCurrentMl: 1200
    property int waterGoalMl: 2500

    property real weightCurrentKg: 78.4
    property real weightGoalKg: 72.0

    property int stepsToday: 6421

    // Style
    readonly property color bg: "#121212"
    readonly property color card: "#1E1E1E"
    readonly property color card2: "#181818"
    readonly property color textPrimary: "#FFFFFF"
    readonly property color textSecondary: "#A0A0A0"
    readonly property color accent: "#2DA8FF"

    Rectangle {
        anchors.fill: parent
        color: bg
    }

    ScrollView {
        id: scroll
        anchors.fill: parent
        clip: true

        ColumnLayout {
            id: content
            width: scroll.availableWidth
            spacing: 16

            // =========================
            // HEADER (DATE)
            // =========================
            RowLayout {
                Layout.fillWidth: true
                spacing: 12

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 4

                    Label {
                        text: selectedDateText
                        color: textPrimary
                        font.pixelSize: 36
                        font.bold: true
                    }

                    Label {
                        text: "Your daily summary"
                        color: textSecondary
                        font.pixelSize: 14
                    }
                }

                //TODO: Add date change menu to here
                Button {
                    text: "📅"
                    font.pixelSize: 18
                    width: 44
                    height: 44
                    onClicked: {
                        console.log("TODO: date picker")
                    }
                }
            }

            // =========================
            // CALORIES SUMMARY CARD
            // =========================
            Rectangle {
                Layout.fillWidth: true
                radius: 16
                color: card
                border.color: "#2A2A2A"
                border.width: 1
                implicitHeight: 240

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 14

                    // Top row: Eaten / Gauge / Burned
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 12

                        // Eaten
                        ColumnLayout {
                            Layout.preferredWidth: 160
                            spacing: 4

                            Label {
                                text: caloriesEaten.toLocaleString(Qt.locale("en_US"))
                                color: textPrimary
                                font.pixelSize: 16
                                font.bold: true
                            }

                            Label {
                                text: "Eaten"
                                color: textSecondary
                                font.pixelSize: 14
                            }
                        }

                        // Gauge (Remaining)
                        Item {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 110

                            Rectangle {
                                id: gaugeBg
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                width: Math.min(parent.width, 260)
                                height: 16
                                radius: 999
                                color: "#2C2C2C"
                            }

                            Rectangle {
                                anchors.left: gaugeBg.left
                                anchors.verticalCenter: gaugeBg.verticalCenter
                                height: gaugeBg.height
                                radius: 999
                                color: accent
                                width: {
                                    const denom = Math.max(1, caloriesGoal)
                                    const pct = Math.max(0, Math.min(1, caloriesEaten / denom))
                                    return gaugeBg.width * pct
                                }
                            }

                            Column {
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.top: gaugeBg.bottom
                                anchors.topMargin: 12
                                spacing: 2

                                Label {
                                    text: caloriesRemaining
                                    color: textPrimary
                                    font.pixelSize: 28
                                    font.bold: true
                                    horizontalAlignment: Text.AlignHCenter
                                    width: parent.width
                                }

                                Label {
                                    text: "Remaining"
                                    color: textSecondary
                                    font.pixelSize: 14
                                    horizontalAlignment: Text.AlignHCenter
                                    width: parent.width
                                }
                            }
                        }

                        // Burned
                        ColumnLayout {
                            Layout.preferredWidth: 160
                            spacing: 4
                            Layout.alignment: Qt.AlignRight

                            Label {
                                text: caloriesBurned.toLocaleString(Qt.locale("en_US"))
                                color: textPrimary
                                font.pixelSize: 26
                                font.bold: true
                                horizontalAlignment: Text.AlignRight
                                Layout.fillWidth: true
                            }

                            Label {
                                text: "Burned"
                                color: textSecondary
                                font.pixelSize: 14
                                horizontalAlignment: Text.AlignRight
                                Layout.fillWidth: true
                            }
                        }
                    }

                    // Macro progress bars
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 16

                        MacroBar {
                            Layout.fillWidth: true
                            title: "Carbs"
                            currentValue: carbsCurrent
                            goalValue: carbsGoal
                            accentColor: accent
                        }

                        MacroBar {
                            Layout.fillWidth: true
                            title: "Protein"
                            currentValue: proteinCurrent
                            goalValue: proteinGoal
                            accentColor: accent
                        }

                        MacroBar {
                            Layout.fillWidth: true
                            title: "Fat"
                            currentValue: fatCurrent
                            goalValue: fatGoal
                            accentColor: accent
                        }
                    }
                }
            }

            // =========================
            // MEALS CARD
            // =========================
            Rectangle {
                Layout.fillWidth: true
                radius: 16
                color: card
                border.color: "#2A2A2A"
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 12
                    spacing: 0

                    MealRow {
                        title: "Breakfast"
                        subtitle: breakfastCurrent + " / " + breakfastGoal + " Cal"
                        onAddClicked: console.log("TODO: Add breakfast")
                        onRowClicked: console.log("TODO: Open breakfast details")
                    }

                    SeperatorLine {}

                    MealRow {
                        title: "Lunch"
                        subtitle: lunchCurrent + " / " + lunchGoal + " Cal"
                        onAddClicked: console.log("TODO: Add lunch")
                        onRowClicked: console.log("TODO: Open lunch details")
                    }

                    SeperatorLine {}

                    MealRow {
                        title: "Dinner"
                        subtitle: dinnerCurrent + " / " + dinnerGoal + " Cal"
                        onAddClicked: console.log("TODO: Add dinner")
                        onRowClicked: console.log("TODO: Open dinner details")
                    }

                    SeperatorLine {}

                    MealRow {
                        title: "Snacks"
                        subtitle: snacksCurrent + " / " + snacksGoal + " Cal"
                        onAddClicked: console.log("TODO: Add snacks")
                        onRowClicked: console.log("TODO: Open snacks details")
                    }
                }
            }

            // =========================
            // WATER CARD
            // =========================
            Rectangle {
                Layout.fillWidth: true
                radius: 16
                color: card
                border.color: "#2A2A2A"
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 10

                    RowLayout {
                        Layout.fillWidth: true

                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 2

                            Label {
                                text: "Water"
                                color: textPrimary
                                font.pixelSize: 18
                                font.bold: true
                            }

                            Label {
                                text: (waterCurrentMl/1000).toFixed(1) + " / " + (waterGoalMl/1000).toFixed(1) + " L"
                                color: textSecondary
                                font.pixelSize: 14
                            }
                        }

                        Button {
                            text: "+"
                            width: 44
                            height: 44
                            onClicked: console.log("TODO: Add water")
                        }
                    }

                    ProgressBar {
                        Layout.fillWidth: true
                        from: 0
                        to: waterGoalMl
                        value: Math.min(waterGoalMl, waterCurrentMl)
                    }
                }
            }

            // =========================
            // WEIGHT CARD
            // =========================
            Rectangle {
                Layout.fillWidth: true
                radius: 16
                color: card
                border.color: "#2A2A2A"
                border.width: 1

                MouseArea {
                    anchors.fill: parent
                    onClicked: console.log("TODO: Update weight dialog")
                }

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 20

                    RowLayout {
                        Layout.fillWidth: true

                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 2

                            Label {
                                text: "Weight"
                                color: textPrimary
                                font.pixelSize: 18
                                font.bold: true
                            }

                            Label {
                                text: "Current: " + weightCurrentKg.toFixed(1) + " kg. Goal is: " + weightGoalKg.toFixed(1) + " kg"
                                color: textSecondary
                                font.pixelSize: 14
                            }
                        }

                        Label {
                            text: "Edit"
                            color: accent
                            font.pixelSize: 14
                        }
                    }

                    ProgressBar {
                        Layout.fillWidth: true
                        from: 0
                        to: Math.max(weightCurrentKg, weightGoalKg)
                        value: Math.min(weightCurrentKg, Math.max(weightCurrentKg, weightGoalKg))
                    }
                }
            }

            // =========================
            // ACTIVITIES CARD
            // =========================
            Rectangle {
                Layout.fillWidth: true
                radius: 16
                color: card
                border.color: "#2A2A2A"
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 12

                    Label {
                        text: "Activities"
                        color: textPrimary
                        font.pixelSize: 18
                        font.bold: true
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        radius: 12
                        color: card2
                        implicitHeight: 64

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 12

                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 2

                                Label {
                                    text: "Steps"
                                    color: textPrimary
                                    font.pixelSize: 16
                                    font.bold: true
                                }

                                Label {
                                    text: stepsToday + " today"
                                    color: textSecondary
                                    font.pixelSize: 14
                                }
                            }

                            Button {
                                text: "View"
                                onClicked: console.log("TODO: Open steps details")
                            }
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        radius: 12
                        color: card2
                        implicitHeight: 64

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 12

                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 2

                                Label {
                                    text: "Exercise"
                                    color: textPrimary
                                    font.pixelSize: 16
                                    font.bold: true
                                }

                                Label {
                                    text: "Add a workout"
                                    color: textSecondary
                                    font.pixelSize: 14
                                }
                            }

                            Button {
                                text: "+"
                                width: 44
                                height: 44
                                onClicked: console.log("TODO: add exercise")
                            }
                        }
                    }
                }
            }

            // Bottom spacing
            Item {
                Layout.preferredHeight: 24
            }
        }
    }

    // ============================================================
    // LOCAL COMPONENTS
    // ============================================================
    component SeperatorLine : Rectangle {
        Layout.fillWidth: true
        height: 1
        color: "#2A2A2A"
    }

    component MacroBar : Item {
        property string title: ""
        property int currentValue: 0
        property int goalValue: 1
        property color accentColor: "#2DA8FF"

        implicitHeight: 72

        Column {
            anchors.fill: parent
            spacing: 6

            Label {
                text: title
                color: textSecondary
                font.pixelSize: 14
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
            }

            ProgressBar {
                width: parent.width
                from: 0
                to: goalValue
                value: Math.min(goalValue, currentValue)
            }

            Label {
                text: currentValue + " / " + goalValue + " g"
                color: textPrimary
                font.pixelSize: 16
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
            }
        }
    }

    component MealRow : Item  {
        property string title: ""
        property string subtitle: ""
        signal addClicked()
        signal rowClicked()

        implicitHeight: 78

        Rectangle {
            anchors.fill: parent
            color: "transparent"

            MouseArea {
                anchors.fill: parent
                onClicked: rowClicked()
            }

            RowLayout {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 12

                //icon placeholder
                Rectangle {
                    width: 44
                    height: 44
                    radius: 22
                    color: "#2A2A2A"

                    Label {
                        anchors.centerIn: parent
                        text: title.length > 0 ? title[0] : "?"
                        color: textPrimary
                        font.pixelSize: 18
                        font.bold: true
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 2

                    Label {
                        text: title
                        color: textPrimary
                        font.pixelSize: 20
                        font.bold: true
                    }

                    Label {
                        text: subtitle
                        color: textSecondary
                        font.pixelSize: 14
                    }
                }

                Button {
                    text: "+"
                    width: 44
                    height: 44
                    onClicked: addClicked()
                }
            }
        }
    }
}
