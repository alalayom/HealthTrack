import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HealthTrack 1.0

Item {
    id: nutritionRoot
    width: parent ? parent.width : 0
    height: parent ? parent.height : 0

    // Added dummy data for testing qml page design. Later data will be provided from ViewModel
    property int caloriesBurned: 244
    property int caloriesGoal: 2117

    property int carbsGoal: 258
    property int proteinGoal: 103
    property int fatGoal: 68

    property int breakfastGoal: 635
    property int lunchGoal: 847
    property int dinnerGoal: 529
    property int snacksGoal: 106

    property real initialWeightKg : 83.1
    property real weightGoalKg: 78.0

    property int stepsToday: 6421

    //Real properties
    readonly property var dateLocale: Qt.locale("en_US")
    readonly property var minimumSelectableDate: new Date(2026, 0, 1)
    readonly property var maximumSelectableDate: new Date(2027, 0, 31)
    readonly property var appState: appController.appState
    property date currentNutritionDate: appState ? appState.selectedDate : new Date()
    property string selectedDateText: formatHeaderDate(currentNutritionDate)
    property string selectedDateSubtitle: formatHeaderSubtitle(currentNutritionDate)

    property var nutritionVM: appController.nutritionViewModel
    property var waterVM: appController.waterViewModel
    property var bodyMetricsVM: appController.bodyMetricsViewModel

    property int caloriesEaten: Math.round(Number(nutritionVM.totalCalories))
    property int caloriesRemaining: caloriesGoal - caloriesEaten + caloriesBurned

    property int carbsCurrent: 0
    property int proteinCurrent: 0
    property int fatCurrent: 0

    property int breakfastCurrent: 0
    property int lunchCurrent: 0
    property int dinnerCurrent: 0
    property int snacksCurrent: 0

    property int waterCurrentMl: waterVM ? waterVM.currentAmountMl : 0
    property int waterGoalMl: waterVM ? waterVM.goalAmountMl : 0
    property int waterSelectedCupMl: waterVM ? waterVM.selectedCupAmountMl : 250
    property int waterFilledCupCount: waterVM ? waterVM.filledCupCount : 0
    property int waterTargetCupCount: waterVM ? waterVM.targetCupCount : 0
    property int waterVisibleCupCount: Math.max(waterTargetCupCount, waterFilledCupCount < waterTargetCupCount ? waterTargetCupCount : waterFilledCupCount + 1)
    property bool hasShownWaterGoalOverlay: false
    property bool suppressNextWaterGoalAnimation: false

    property bool isWeightLossGoal: true //true for weight loss, false for gain.
    property bool hasShownWeightGoalOverlay: false

    property string greatJobOverlayText: ""
    property color greatJobOverlayColor: "#4DB6FF"


    //Functions
    function normalizedDate(pDate) {
        const tDate = new Date(pDate)
        return new Date(tDate.getFullYear(), tDate.getMonth(), tDate.getDate())
    }

    function sameDay(pLeft, pRight) {
        if (!pLeft || !pRight)
        {
            return false
        }

        return pLeft.getFullYear() === pRight.getFullYear()
                && pLeft.getMonth() === pRight.getMonth()
                && pLeft.getDate() === pRight.getDate()
    }

    function clampSelectableDate(pDate) {
        const tDate = normalizedDate(pDate)
        const tMin = normalizedDate(minimumSelectableDate)
        const tMax = normalizedDate(maximumSelectableDate)

        if (tDate.getTime() < tMin.getTime())
        {
            return new Date(tMin.getTime())
        }

        if (tDate.getTime() > tMax.getTime())
        {
            return new Date(tMax.getTime())
        }

        return tDate
    }

    function setSelectedDate(pDate) {
        if (!appState)
        {
            return
        }

        const tDate = clampSelectableDate(pDate)
        const tCurrent = normalizedDate(currentNutritionDate)

        if (sameDay(tDate, tCurrent))
        {
            return
        }

        appState.selectedDate = tDate
    }

    function shiftSelectedDate(pDays) {
        const tCurrent = normalizedDate(currentNutritionDate)
        setSelectedDate(new Date(tCurrent.getFullYear(), tCurrent.getMonth(), tCurrent.getDate() + pDays))
    }

    function formatHeaderDate(pDate) {
        return pDate ? dateLocale.toString(pDate, "d MMMM yyyy") : ""
    }

    function formatHeaderSubtitle(pDate) {
        return pDate ? dateLocale.toString(pDate, "dddd") + " - Your daily summary" : "Your daily summary"
    }

    function syncWaterGoalOverlayState() {
        hasShownWaterGoalOverlay = waterGoalMl > 0 && waterCurrentMl >= waterGoalMl
    }

    function syncWeightGoalOverlayState() {
        hasShownWeightGoalOverlay = hasReachedWeightGoal(effectiveWeightKg())
    }

    function refreshDailyNutritionTotals() {

        caloriesEaten = Math.round(Number(nutritionVM.totalCalories))
        carbsCurrent = Math.round(Number(nutritionVM.totalCarbs))
        proteinCurrent = Math.round(Number(nutritionVM.totalProtein))
        fatCurrent = Math.round(Number(nutritionVM.totalFat))

        // console.log("Daily totals refreshed:",
        //             "cal:", caloriesEaten,
        //             "carbs:", carbsCurrent,
        //             "protein:", proteinCurrent,
        //             "fat:", fatCurrent
        // )
    }

    function refreshMealSummaries() {
        const tMeals = nutritionVM.meals

        breakfastCurrent = (tMeals.length > 0 && tMeals[0].totals)
                ? Math.round(Number(tMeals[0].totals.calories))
                : 0

        lunchCurrent = (tMeals.length > 1 && tMeals[1].totals)
                ? Math.round(Number(tMeals[1].totals.calories))
                : 0

        dinnerCurrent = (tMeals.length > 2 && tMeals[2].totals)
                ? Math.round(Number(tMeals[2].totals.calories))
                : 0

        snacksCurrent = (tMeals.length > 3 && tMeals[3].totals)
                ? Math.round(Number(tMeals[3].totals.calories))
                : 0

        // console.log("NutritionMain refreshed:", breakfastCurrent, lunchCurrent, dinnerCurrent, snacksCurrent)
    }

    function effectiveWeightKg() {
        if(!bodyMetricsVM)
        {
            return initialWeightKg
        }

        const tWeight = Number(bodyMetricsVM.weightKg)
        return tWeight > 0 ? tWeight : initialWeightKg
    }

    function hasReachedWeightGoal(pWeight) {
        if(isWeightLossGoal)
        {
            return pWeight <= weightGoalKg
        }

        return pWeight >= weightGoalKg
    }

    function shouldResetWeightGoalOverlay(pWeight) {
        if(isWeightLossGoal)
        {
            return pWeight > weightGoalKg
        }

        return pWeight < weightGoalKg
    }

    function showGreatJobOverlay(pText, pColor) {
        greatJobOverlayText = pText
        greatJobOverlayColor = pColor
        greatJobOverlayAnimation.restart()
    }

    function increaseDisplayedWeight() {
        if(!bodyMetricsVM)
        {
            return
        }

        const tCurrent = effectiveWeightKg()
        const tNext = Number((tCurrent + 0.1).toFixed(1))
        bodyMetricsVM.setWeightKg(tNext)

        if(hasReachedWeightGoal(tNext) && !hasShownWeightGoalOverlay)
        {
            hasShownWeightGoalOverlay = true
            showGreatJobOverlay("Great job 🎉", "#FFD54F")
        }
    }

    function decreaseDisplayedWeight() {
        if(!bodyMetricsVM)
        {
            return
        }

        const tCurrent = effectiveWeightKg()
        const tNext = Math.max(0, Number((tCurrent - 0.1).toFixed(1)))
        bodyMetricsVM.setWeightKg(tNext)

        if(hasReachedWeightGoal(tNext) && !hasShownWeightGoalOverlay)
        {
            hasShownWeightGoalOverlay = true
            showGreatJobOverlay("Great job 🎉", "#FFD54F")
        }

        if(shouldResetWeightGoalOverlay(tNext))
        {
            hasShownWeightGoalOverlay = false
        }
    }

    function weightProgressRatio() {
        const tInitial = Number(initialWeightKg)
        const tGoal = Number(weightGoalKg)
        const tCurrent = Number(effectiveWeightKg())

        const tDeltaTotal = tGoal - tInitial
        if(Math.abs(tDeltaTotal) < 0.0001)
        {
            return 1.0
        }

        const tRaw = (tCurrent - tInitial) / tDeltaTotal
        return Math.max(0, Math.min(1, tRaw))
    }

    Component.onCompleted: {
        refreshMealSummaries()
        refreshDailyNutritionTotals()
        syncWaterGoalOverlayState()
        syncWeightGoalOverlayState()

        if(nutritionVM) {
            notesInput.text = nutritionVM.dailyNotes
        }
    }

    Connections {
        target: nutritionVM

        function onMealsChanged() {
            refreshMealSummaries()
        }

        function onTotalCaloriesChanged() {
            refreshDailyNutritionTotals()
        }

        function onTotalCarbsChanged() {
            refreshDailyNutritionTotals()
        }

        function onTotalProteinChanged() {
            refreshDailyNutritionTotals()
        }

        function onTotalFatChanged() {
            refreshDailyNutritionTotals()
        }

        function onDailyNotesChanged() {
            if(notesInput.text !== nutritionVM.dailyNotes) {
                notesInput.text = nutritionVM.dailyNotes
            }
        }
    }

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

    NutritionDatePickerPopup {
        id: datePickerPopup
        minimumDate: nutritionRoot.minimumSelectableDate
        maximumDate: nutritionRoot.maximumSelectableDate

        onDateSelected: function(selectedDate) {
            nutritionRoot.setSelectedDate(selectedDate)
        }
    }

    Connections {
        target: waterVM

        function onDateChanged() {
            suppressNextWaterGoalAnimation = true
        }
    }

    Connections {
        target: bodyMetricsVM

        function onDateChanged() {
            syncWeightGoalOverlayState()
        }
    }

    DragHandler {
        id: daySwipeHandler
        target: null
        acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchScreen | PointerDevice.TouchPad
        xAxis.enabled: true
        yAxis.enabled: false

        onActiveChanged: {
            if (active || datePickerPopup.visible)
            {
                return
            }

            const tDeltaX = centroid.position.x - centroid.pressPosition.x
            const tDeltaY = centroid.position.y - centroid.pressPosition.y

            if (Math.abs(tDeltaX) < 90 || Math.abs(tDeltaX) <= Math.abs(tDeltaY))
            {
                return
            }

            if (tDeltaX < 0)
            {
                nutritionRoot.shiftSelectedDate(1)
            }
            else
            {
                nutritionRoot.shiftSelectedDate(-1)
            }
        }
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

                Item {
                    Layout.fillWidth: true
                    implicitHeight: dateHeaderContent.implicitHeight

                    TapHandler {
                        onTapped: datePickerPopup.openForDate(nutritionRoot.currentNutritionDate)
                    }

                    ColumnLayout {
                        id: dateHeaderContent
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 4

                        Label {
                            text: selectedDateText
                            color: textPrimary
                            font.pixelSize: 36
                            font.bold: true
                        }

                        Label {
                            text: selectedDateSubtitle
                            color: textSecondary
                            font.pixelSize: 14
                        }
                    }
                }

                Button {
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    Layout.preferredWidth: 60
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
                            text: "📅"
                            font.pixelSize: 18
                        }
                    }

                    onClicked: datePickerPopup.openForDate(nutritionRoot.currentNutritionDate)
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
                        onRowClicked: appController.navigationManager.openMealDetails(0, "Breakfast")
                        onAddClicked: appController.navigationManager.openMealDetails(0, "Breakfast")
                    }

                    SeperatorLine {}

                    MealRow {
                        title: "Lunch"
                        subtitle: lunchCurrent + " / " + lunchGoal + " Cal"
                        iconText: "🥗"
                        onAddClicked: appController.navigationManager.openMealDetails(1, "Lunch")
                        onRowClicked: appController.navigationManager.openMealDetails(1, "Lunch")
                    }

                    SeperatorLine {}

                    MealRow {
                        title: "Dinner"
                        subtitle: dinnerCurrent + " / " + dinnerGoal + " Cal"
                        iconText: "🍗️"
                        onAddClicked: appController.navigationManager.openMealDetails(2, "Dinner")
                        onRowClicked: appController.navigationManager.openMealDetails(2, "Dinner")
                    }

                    SeperatorLine {}

                    MealRow {
                        title: "Snacks"
                        subtitle: snacksCurrent + " / " + snacksGoal + " Cal"
                        iconText: "🍎"
                        onAddClicked: appController.navigationManager.openMealDetails(3, "Snacks")
                        onRowClicked: appController.navigationManager.openMealDetails(3, "Snacks")
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

                Connections {
                    target: waterVM

                    function onCurrentAmountMlChanged() {
                        if (!waterVM)
                        {
                            return
                        }

                        if (suppressNextWaterGoalAnimation)
                        {
                            suppressNextWaterGoalAnimation = false
                            syncWaterGoalOverlayState()
                            return
                        }

                        if (waterCurrentMl >= waterGoalMl && !hasShownWaterGoalOverlay)
                        {
                            hasShownWaterGoalOverlay = true
                            showGreatJobOverlay("Great job 💧", "#4DB6FF")
                        }

                        if (waterCurrentMl < waterGoalMl)
                        {
                            hasShownWaterGoalOverlay = false
                        }
                    }
                }

                ColumnLayout {
                    id: waterContent
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 12

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
                                text: (waterCurrentMl / 1000).toFixed(1) + " / "
                                      + (waterGoalMl / 1000).toFixed(1) + " L"
                                color: textSecondary
                                font.pixelSize: 14
                            }
                        }

                        Item {
                            Layout.fillWidth: true
                        }

                        Label {
                            text: Math.min(100, Math.round(waterCurrentMl / Math.max(1, waterGoalMl) * 100)) + "%"
                            color: textSecondary
                            font.pixelSize: 13
                            font.bold: true
                        }
                    }

                    ProgressBar {
                        Layout.fillWidth: true
                        from: 0
                        to: Math.max(1, waterGoalMl)
                        value: Math.min(waterCurrentMl, waterGoalMl)
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        Label {
                            text: waterSelectedCupMl + " mL / cup"
                            color: textSecondary
                            font.pixelSize: 13
                        }

                        Item {
                            Layout.fillWidth: true
                        }

                        Label {
                            text: waterFilledCupCount + " / " + waterTargetCupCount + " cups"
                            color: textSecondary
                            font.pixelSize: 13
                        }
                    }

                    Flow {
                        Layout.fillWidth: true
                        width: parent.width
                        spacing: 8

                        Repeater {
                            model: waterVisibleCupCount

                            delegate: Rectangle {
                                required property int index

                                width: 26
                                height: 26
                                radius: 8

                                readonly property bool isFilled: index < waterFilledCupCount
                                readonly property bool isExtraCup: index >= waterTargetCupCount

                                color: {
                                    if (isFilled && isExtraCup)
                                    {
                                        return "#2DA8FF"
                                    }

                                    if (isFilled)
                                    {
                                        return "#2DA8FF"
                                    }

                                    if (isExtraCup)
                                    {
                                        return Qt.rgba(1, 1, 1, 0.18)
                                    }

                                    return "#F2F2F2"
                                }

                                border.width: 1
                                border.color: {
                                    if (isFilled)
                                    {
                                        return "#2DA8FF"
                                    }

                                    if (isExtraCup)
                                    {
                                        return Qt.rgba(1, 1, 1, 0.25)
                                    }

                                    return "#D0D0D0"
                                }

                                opacity: isExtraCup && !isFilled ? 0.65 : 1.0

                                MouseArea {
                                    anchors.fill: parent

                                    onClicked: {
                                        if (!waterVM)
                                        {
                                            return
                                        }

                                        waterVM.toggleCup(index)
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // =========================
            // WEIGHT CARD
            // =========================
            Rectangle {
                Layout.fillWidth: true
                radius: 18
                color: card
                border.color: "#2A2A2A"
                border.width: 1
                implicitHeight: 210

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 14

                    RowLayout {
                        Layout.fillWidth: true

                        Label {
                            text: "Weight"
                            color: textPrimary
                            font.pixelSize: 20
                            font.bold: true
                        }

                        Item {
                            Layout.fillWidth: true
                        }

                        Label {
                            text: Math.round(weightProgressRatio() * 100) + "%"
                            color: textSecondary
                            font.pixelSize: 13
                            font.bold: true
                        }
                    }

                    Item {
                        Layout.fillWidth: true
                        implicitHeight: 84

                        Button {
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            width: 48
                            height: 48
                            padding: 0

                            background: Rectangle {
                                radius: 24
                                color: parent.down ? "#505050" : "#3A3A3A"
                                border.width: 1
                                border.color: "#4A4A4A"
                            }

                            contentItem: Item {
                                anchors.fill: parent

                                Text {
                                    anchors.centerIn: parent
                                    text: "−"
                                    color: textPrimary
                                    font.pixelSize: 24
                                    font.bold: true
                                }
                            }

                            onClicked: decreaseDisplayedWeight()
                        }

                        Column {
                            anchors.centerIn: parent
                            spacing: 4

                            Label {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: effectiveWeightKg().toFixed(1) + " kg"
                                color: textPrimary
                                font.pixelSize: 36
                                font.bold: true
                            }

                            Label {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: isWeightLossGoal ? "Fat loss goal" : "Gain goal"
                                color: textSecondary
                                font.pixelSize: 13
                            }
                        }

                        Button {
                            anchors.right: parent.right
                            anchors.verticalCenter: parent.verticalCenter
                            width: 48
                            height: 48
                            padding: 0

                            background: Rectangle {
                                radius: 24
                                color: parent.down ? "#505050" : "#3A3A3A"
                                border.width: 1
                                border.color: "#4A4A4A"
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

                            onClicked: increaseDisplayedWeight()
                        }
                    }

                    ProgressBar {
                        Layout.fillWidth: true
                        from: 0
                        to: 1
                        value: weightProgressRatio()
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        Label {
                            text: "Initial: " + initialWeightKg.toFixed(1) + " kg"
                            color: textSecondary
                            font.pixelSize: 13
                        }

                        Item {
                            Layout.fillWidth: true
                        }

                        Label {
                            text: "Goal: " + weightGoalKg.toFixed(1) + " kg"
                            color: textSecondary
                            font.pixelSize: 13
                        }
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

            // =========================
            // NOTES CARD
            // =========================
            Rectangle {
                Layout.fillWidth: true
                radius: 16
                color: card
                border.color: "#2A2A2A"
                border.width: 1
                implicitHeight: notesContent.implicitHeight + 32

                ColumnLayout {
                    id: notesContent
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 12

                    Label {
                        text: "📝 Notes"
                        color: textPrimary
                        font.pixelSize: 18
                        font.bold: true
                    }

                    Label {
                        text: "Write how you feel, how your diet went, or anything important about today."
                        color: textSecondary
                        font.pixelSize: 14
                        wrapMode: Text.WordWrap
                        Layout.fillWidth: true
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 120
                        radius: 12
                        color: card2
                        border.color: "#2A2A2A"
                        border.width: 1

                        TextArea {
                            id: notesInput
                            anchors.fill: parent
                            anchors.margins: 12
                            text: nutritionVM ? nutritionVM.dailyNotes : ""
                            placeholderText: "For example: Felt energetic today, lunch was too heavy, drank less water than usual..."
                            placeholderTextColor: "#7A7A7A"
                            color: textPrimary
                            wrapMode: TextEdit.Wrap
                            font.pixelSize: 14
                            selectByMouse: true
                            background: null
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        Item {
                            Layout.fillWidth: true
                        }

                        Button {
                            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                            Layout.preferredWidth: 88
                            Layout.preferredHeight: 40
                            padding: 0

                            enabled: nutritionVM && notesInput.text.trim() !== nutritionVM.dailyNotes.trim()

                            background: Rectangle {
                                radius: 20
                                color: parent.down ? "#505050" : "#3A3A3A"
                            }

                            contentItem: Item {
                                anchors.fill: parent

                                Text {
                                    anchors.centerIn: parent
                                    text: "Save"
                                    color: textPrimary
                                    font.pixelSize: 14
                                    font.bold: true
                                }
                            }

                            onClicked: {
                                nutritionVM.dailyNotes = notesInput.text
                                nutritionVM.saveCurrentDay()
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

    // Generic greatJob label
    Label {
        id: greatJobOverlay
        anchors.centerIn: parent
        z: 999

        text: greatJobOverlayText
        color: greatJobOverlayColor
        font.pixelSize: 34
        font.bold: true

        opacity: 0
        scale: 0.85

        transform: Translate {
            id: greatJobTranslate
            y: 24
        }
    }

    //Generic greatJob animation
    SequentialAnimation {
        id: greatJobOverlayAnimation

        ScriptAction {
            script: {
                greatJobOverlay.opacity = 0
                greatJobOverlay.scale = 0.85
                greatJobTranslate.y = 24
            }
        }

        ParallelAnimation {
            PropertyAnimation {
                target: greatJobOverlay
                property: "opacity"
                from: 0
                to: 1
                duration: 220
            }

            PropertyAnimation {
                target: greatJobOverlay
                property: "scale"
                from: 0.85
                to: 1.0
                duration: 260
            }

            PropertyAnimation {
                target: greatJobTranslate
                property: "y"
                from: 24
                to: 0
                duration: 260
            }
        }

        PauseAnimation {
            duration: 1100
        }

        ParallelAnimation {
            PropertyAnimation {
                target: greatJobOverlay
                property: "opacity"
                to: 0
                duration: 380
            }

            PropertyAnimation {
                target: greatJobOverlay
                property: "scale"
                to: 0.96
                duration: 380
            }

            PropertyAnimation {
                target: greatJobTranslate
                property: "y"
                to: -14
                duration: 380
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
