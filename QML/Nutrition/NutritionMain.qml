import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HealthTrack 1.0

Item {
    id: nutritionRoot
    width: parent ? parent.width : 0
    height: parent ? parent.height : 0

    // Added dummy data for testing qml page design. Later data will be provided from ViewModel
    property string selectedDateText: "Today"
    property int caloriesEaten: 5291
    property int caloriesBurned: 244
    property int caloriesGoal: 2117
    property int caloriesRemaining: caloriesGoal - caloriesEaten + caloriesBurned

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
                implicitHeight: 270

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 18

                    // Top row: Eaten / Gauge / Burned
                    RowLayout {
                        id: summaryRow
                        Layout.fillWidth: true
                        spacing: 12

                        property int eatenValue: Math.round(caloriesEaten)
                        property int burnedValue: Math.round(caloriesBurned)

                        property int netCalories: Math.round(caloriesEaten - caloriesBurned)
                        property int remainingValue: Math.round(caloriesGoal - netCalories)

                        property real goalSafe: Math.max(1, caloriesGoal)
                        property real progressRatio: Math.max(0, netCalories / goalSafe)
                        property bool isOverGoal: remainingValue < 0

                        onNetCaloriesChanged: calorieGauge.requestPaint()
                        onRemainingValueChanged: calorieGauge.requestPaint()
                        onProgressRatioChanged: calorieGauge.requestPaint()
                        onIsOverGoalChanged: calorieGauge.requestPaint()

                        // Eaten
                        ColumnLayout {
                            Layout.preferredWidth: 110
                            Layout.alignment: Qt.AlignCenter | Qt.AlignLeft
                            spacing: 4

                            Label {
                                text: summaryRow.eatenValue.toString()
                                color: textPrimary
                                font.pixelSize: 28
                                font.bold: true
                            }

                            Label {
                                text: "🍽️ Eaten"
                                color: textSecondary
                                font.pixelSize: 16
                            }
                        }

                        // Remaining gauge
                        Item {
                            Layout.fillWidth: true
                            Layout.preferredWidth: 180
                            Layout.preferredHeight: 160
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                            Canvas {
                                id: calorieGauge
                                anchors.centerIn: parent
                                width: 150
                                height: 150

                                onPaint: {
                                    const tContext = getContext("2d")
                                    tContext.reset()

                                    const tCenterX = width / 2
                                    const tCenterY = height / 2
                                    const tRadius = 54
                                    const tStrokeWidth = 13
                                    const tStartAngle = Math.PI / 2
                                    const tFullCircle = 2 * Math.PI

                                    // BG ring
                                    tContext.beginPath()
                                    tContext.strokeStyle = "#2C2C2C"
                                    tContext.lineWidth = tStrokeWidth
                                    tContext.lineCap = "round"
                                    tContext.arc(tCenterX, tCenterY, tRadius, 0, tFullCircle, false)
                                    tContext.stroke()

                                    const tRatio = summaryRow.progressRatio

                                    if (!summaryRow.isOverGoal) {
                                        const tProgress = Math.max(0, Math.min(1, tRatio))

                                        if (tProgress > 0) {
                                            tContext.beginPath()
                                            tContext.strokeStyle = accent
                                            tContext.lineWidth = tStrokeWidth
                                            tContext.lineCap = "round"
                                            tContext.arc(
                                                tCenterX,
                                                tCenterY,
                                                tRadius,
                                                tStartAngle,
                                                tStartAngle + (tFullCircle * tProgress),
                                                false
                                            )
                                            tContext.stroke()
                                        }
                                    } else {
                                        // if over-goal, then make it whole red
                                        tContext.beginPath()
                                        tContext.strokeStyle = "rgba(255, 90, 95, 0.55)"
                                        tContext.lineWidth = tStrokeWidth
                                        tContext.lineCap = "round"
                                        tContext.arc(tCenterX, tCenterY, tRadius, 0, tFullCircle, false)
                                        tContext.stroke()

                                        const tFullLaps = Math.floor(tRatio)
                                        const tPartialLap = tRatio - tFullLaps

                                        // Every full lap is red
                                        for (let i = 0; i < tFullLaps; ++i) {
                                            const tAlpha = Math.min(0.45 + i * 0.14, 1.0)

                                            tContext.beginPath()
                                            tContext.strokeStyle = "rgba(255, 90, 95, " + tAlpha + ")"
                                            tContext.lineWidth = tStrokeWidth
                                            tContext.lineCap = "round"
                                            tContext.arc(
                                                tCenterX,
                                                tCenterY,
                                                tRadius,
                                                tStartAngle,
                                                tStartAngle + tFullCircle,
                                                false
                                            )
                                            tContext.stroke()
                                        }

                                        // Last lap remaining part
                                        if (tPartialLap > 0) {
                                            const tAlpha = Math.min(0.45 + tFullLaps * 0.14, 1.0)

                                            tContext.beginPath()
                                            tContext.strokeStyle = "rgba(255, 90, 95, " + tAlpha + ")"
                                            tContext.lineWidth = tStrokeWidth
                                            tContext.lineCap = "round"
                                            tContext.arc(
                                                tCenterX,
                                                tCenterY,
                                                tRadius,
                                                tStartAngle,
                                                tStartAngle + (tFullCircle * tPartialLap),
                                                false
                                            )
                                            tContext.stroke()
                                        }
                                    }
                                }

                                Component.onCompleted: requestPaint()
                            }

                            Column {
                                anchors.centerIn: calorieGauge
                                spacing: 0

                                Label {
                                    text: summaryRow.remainingValue.toString()
                                    color: summaryRow.isOverGoal ? "#FF5A5F" : textPrimary
                                    font.pixelSize: 34
                                    font.bold: true
                                    horizontalAlignment: Text.AlignHCenter
                                    width: 110
                                }

                                Label {
                                    text: "Remaining"
                                    color: textSecondary
                                    font.pixelSize: 12
                                    horizontalAlignment: Text.AlignHCenter
                                    width: 110
                                }
                            }
                        }

                        // Burned
                        ColumnLayout {
                            Layout.preferredWidth: 110
                            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                            spacing: 4

                            Label {
                                text: summaryRow.burnedValue.toString()
                                color: textPrimary
                                font.pixelSize: 28
                                font.bold: true
                                horizontalAlignment: Text.AlignRight
                                Layout.fillWidth: true
                            }

                            Label {
                                text: "⚡ Burned"
                                color: textSecondary
                                font.pixelSize: 16
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
                            title: "🥖 Carbs"
                            currentValue: carbsCurrent
                            goalValue: carbsGoal
                            accentColor: accent
                        }

                        MacroBar {
                            Layout.fillWidth: true
                            title: "🥩 Protein"
                            currentValue: proteinCurrent
                            goalValue: proteinGoal
                            accentColor: accent
                        }

                        MacroBar {
                            Layout.fillWidth: true
                            title: "🌻 Fat"
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
                implicitHeight: mealsContent.implicitHeight + 24

                ColumnLayout {
                    id: mealsContent
                    anchors.fill: parent
                    anchors.margins: 12
                    spacing: 0

                    MealRow {
                        title: "Breakfast"
                        subtitle: breakfastCurrent + " / " + breakfastGoal + " Cal"
                        iconText: "🍳"
                        onAddClicked: console.log("TODO: Add breakfast")
                        onRowClicked: console.log("TODO: Open breakfast details")
                    }

                    SeperatorLine {}

                    MealRow {
                        title: "Lunch"
                        subtitle: lunchCurrent + " / " + lunchGoal + " Cal"
                        iconText: "🥗"
                        onAddClicked: console.log("TODO: Add lunch")
                        onRowClicked: console.log("TODO: Open lunch details")
                    }

                    SeperatorLine {}

                    MealRow {
                        title: "Dinner"
                        subtitle: dinnerCurrent + " / " + dinnerGoal + " Cal"
                        iconText: "🍗️"
                        onAddClicked: console.log("TODO: Add dinner")
                        onRowClicked: console.log("TODO: Open dinner details")
                    }

                    SeperatorLine {}

                    MealRow {
                        title: "Snacks"
                        subtitle: snacksCurrent + " / " + snacksGoal + " Cal"
                        iconText: "🍎"
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
                implicitHeight: waterContent.implicitHeight + 32

                ColumnLayout {
                    id: waterContent
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 10

                    RowLayout {
                        Layout.fillWidth: true

                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 2

                            Label {
                                text: "💧 Water"
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

                        Item {
                            Layout.fillWidth: true
                        }

                        Button {
                            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                            Layout.preferredWidth: 44
                            Layout.preferredHeight: 44
                            padding: 0

                            background: Rectangle {
                                radius: 22
                                color: parent.down ? "#505050" : "#3A3A3A"
                            }

                            contentItem: Item {
                                anchors.fill: parent

                                Text {
                                    anchors.centerIn: parent
                                    text: "+"
                                    color: textPrimary
                                    font.pixelSize: 24
                                    font.bold: true
                                }
                            }

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
                implicitHeight: weightContent.implicitHeight + 32

                MouseArea {
                    anchors.fill: parent
                    onClicked: console.log("TODO: Update weight dialog")
                }

                ColumnLayout {
                    id: weightContent
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 20

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 12

                        ColumnLayout {
                            spacing: 2

                            Label {
                                text: "⏲️ Weight"
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

                        Item {
                            Layout.fillWidth: true
                        }

                        Rectangle {
                            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                            Layout.preferredHeight: 36
                            Layout.preferredWidth: 72
                            radius: 18
                            color: "#3A3A3A"

                            Label {
                                anchors.centerIn: parent
                                text: "Edit"
                                color: textPrimary
                                font.pixelSize: 14
                                font.bold: true
                            }
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
                implicitHeight: activitiesContent.implicitHeight + 32

                ColumnLayout {
                    id: activitiesContent
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 12

                    Label {
                        text: "Activities"
                        color: textPrimary
                        font.pixelSize: 18
                        font.bold: true
                    }

                    //steps
                    Rectangle {
                        Layout.fillWidth: true
                        radius: 12
                        color: card2
                        implicitHeight: 64

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 12
                            spacing: 12

                            ColumnLayout {
                                spacing: 2

                                Label {
                                    text: "👟 Steps"
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

                            Item {
                                Layout.fillWidth: true
                            }

                            Button {
                                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                                Layout.preferredWidth: 76
                                Layout.preferredHeight: 44
                                padding: 0

                                background: Rectangle {
                                    radius: 22
                                    color: parent.down ? "#505050" : "#3A3A3A"
                                }

                                contentItem: Item {
                                    anchors.fill: parent

                                    Text {
                                        anchors.centerIn: parent
                                        text: "View"
                                        color: textPrimary
                                        font.pixelSize: 16
                                        font.bold: true
                                    }
                                }

                                onClicked: console.log("TODO: Open steps details")
                            }
                        }
                    }

                    //Exercise
                    Rectangle {
                        Layout.fillWidth: true
                        radius: 12
                        color: card2
                        implicitHeight: 64

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 12
                            spacing: 12

                            ColumnLayout {
                                spacing: 2

                                Label {
                                    text: "💪 Exercise"
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

                            Item {
                                Layout.fillWidth: true
                            }

                            Button {
                                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                                Layout.preferredWidth: 44
                                Layout.preferredHeight: 44
                                padding: 0

                                background: Rectangle {
                                    radius: 22
                                    color: parent.down ? "#505050" : "#3A3A3A"
                                }

                                contentItem: Item {
                                    anchors.fill: parent

                                    Text {
                                        anchors.centerIn: parent
                                        text: "+"
                                        color: textPrimary
                                        font.pixelSize: 24
                                        font.bold: true
                                    }
                                }

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
        implicitHeight: 1
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
        property string iconText: "🍽️"

        signal addClicked()
        signal rowClicked()

        implicitHeight: 78
        implicitWidth: parent ? parent.width : 0

        Rectangle {
            anchors.fill: parent
            color: "transparent"

            MouseArea {
                anchors.fill: parent
                onClicked: rowClicked()
                propagateComposedEvents: true
            }

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 12
                anchors.rightMargin: 12
                anchors.topMargin: 10
                anchors.bottomMargin: 10
                spacing: 12

                //icon placeholder
                Rectangle {
                    width: 44
                    height: 44
                    radius: 22
                    color: "#2A2A2A"

                    Label {
                        anchors.centerIn: parent
                        text: iconText
                        font.pixelSize: 20
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
                        elide: Text.ElideRight
                        Layout.fillWidth: true
                    }

                    Label {
                        text: subtitle
                        color: textSecondary
                        font.pixelSize: 14
                        elide: Text.ElideRight
                        Layout.fillWidth: true
                    }
                }

                Button {
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                    Layout.preferredWidth: 44
                    Layout.preferredHeight: 44

                    background: Rectangle {
                        radius: 22
                        color: parent.down ? "#505050" : "#3A3A3A"
                    }

                    contentItem: Item {
                        anchors.fill: parent

                        Label {
                            anchors.centerIn: parent
                            text: "+"
                            color: textPrimary
                            font.pixelSize: 24
                            font.bold: true
                        }
                    }

                    onClicked: addClicked()
                }
            }
        }
    }
}
