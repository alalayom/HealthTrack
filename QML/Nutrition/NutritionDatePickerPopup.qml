import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: root
    parent: Overlay.overlay
    modal: true
    focus: true
    padding: 0
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    width: Math.min(parent ? parent.width - 24 : 380, 380)
    x: parent ? (parent.width - width) / 2 : 0
    y: parent ? (parent.height - height) / 2 : 0

    readonly property var dateLocale: Qt.locale("en_US")
    readonly property var weekdayLabels: ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]

    property var selectedDate: new Date(2026, 0, 1)
    property var minimumDate: new Date(2026, 0, 1)
    property var maximumDate: new Date(2027, 0, 31)
    property var displayedMonth: new Date(2026, 0, 1)
    property var dayCells: []

    signal dateSelected(var selectedDate)

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

    function daysInMonth(pYear, pMonth) {
        return new Date(pYear, pMonth + 1, 0).getDate()
    }

    function monthStartFor(pDate) {
        const tDate = normalizedDate(pDate)
        return new Date(tDate.getFullYear(), tDate.getMonth(), 1)
    }

    function clampDate(pDate) {
        const tDate = normalizedDate(pDate)
        const tMin = normalizedDate(minimumDate)
        const tMax = normalizedDate(maximumDate)

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

    function monthInRange(pYear, pMonth) {
        const tFirstDay = new Date(pYear, pMonth, 1)
        const tLastDay = new Date(pYear, pMonth, daysInMonth(pYear, pMonth))
        const tMin = normalizedDate(minimumDate)
        const tMax = normalizedDate(maximumDate)

        return tLastDay.getTime() >= tMin.getTime()
                && tFirstDay.getTime() <= tMax.getTime()
    }

    function refreshDayCells() {
        const tMonthStart = monthStartFor(displayedMonth)
        const tSelectedDate = normalizedDate(selectedDate)
        const tMin = normalizedDate(minimumDate)
        const tMax = normalizedDate(maximumDate)
        const tMonthStartWeekday = (tMonthStart.getDay() + 6) % 7
        const tGridStart = new Date(tMonthStart.getFullYear(), tMonthStart.getMonth(), 1 - tMonthStartWeekday)
        const tItems = []

        for (let i = 0; i < 42; ++i)
        {
            const tCellDate = new Date(tGridStart.getFullYear(), tGridStart.getMonth(), tGridStart.getDate() + i)
            const tCurrentMonth = tCellDate.getFullYear() === tMonthStart.getFullYear()
                    && tCellDate.getMonth() === tMonthStart.getMonth()
            const tEnabled = tCurrentMonth
                    && tCellDate.getTime() >= tMin.getTime()
                    && tCellDate.getTime() <= tMax.getTime()

            tItems.push({
                date: tCellDate,
                label: tCurrentMonth ? tCellDate.getDate().toString() : "",
                isCurrentMonth: tCurrentMonth,
                isEnabled: tEnabled,
                isSelected: tCurrentMonth && sameDay(tCellDate, tSelectedDate)
            })
        }

        dayCells = tItems
    }

    function openForDate(pDate) {
        selectedDate = clampDate(pDate)
        displayedMonth = monthStartFor(selectedDate)
        refreshDayCells()
        open()
    }

    function goToMonth(pOffset) {
        const tTargetMonth = new Date(displayedMonth.getFullYear(), displayedMonth.getMonth() + pOffset, 1)
        if (!monthInRange(tTargetMonth.getFullYear(), tTargetMonth.getMonth()))
        {
            return
        }

        displayedMonth = tTargetMonth
        refreshDayCells()
    }

    onOpened: refreshDayCells()
    onSelectedDateChanged: refreshDayCells()
    onDisplayedMonthChanged: refreshDayCells()

    Overlay.modal: Rectangle {
        color: "#AA000000"
    }

    background: Rectangle {
        radius: 18
        color: "#1A1A1A"
        border.color: "#303030"
        border.width: 1
    }

    contentItem: ColumnLayout {
        spacing: 14

        RowLayout {
            Layout.fillWidth: true

            Button {
                text: "<"
                enabled: root.monthInRange(root.displayedMonth.getFullYear(), root.displayedMonth.getMonth() - 1)
                onClicked: root.goToMonth(-1)
            }

            Label {
                Layout.fillWidth: true
                text: root.dateLocale.toString(root.displayedMonth, "MMMM yyyy")
                color: "#FFFFFF"
                font.pixelSize: 20
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
            }

            Button {
                text: ">"
                enabled: root.monthInRange(root.displayedMonth.getFullYear(), root.displayedMonth.getMonth() + 1)
                onClicked: root.goToMonth(1)
            }
        }

        GridLayout {
            Layout.fillWidth: true
            columns: 7
            columnSpacing: 6
            rowSpacing: 6

            Repeater {
                model: root.weekdayLabels

                Label {
                    Layout.fillWidth: true
                    horizontalAlignment: Text.AlignHCenter
                    color: "#8F8F8F"
                    font.pixelSize: 13
                    font.bold: true
                    text: modelData
                }
            }
        }

        GridLayout {
            Layout.fillWidth: true
            columns: 7
            columnSpacing: 6
            rowSpacing: 6

            Repeater {
                model: root.dayCells

                delegate: Rectangle {
                    id: dayCell
                    Layout.fillWidth: true
                    Layout.preferredHeight: 42
                    property var popupRoot: root
                    radius: 12
                    color: modelData.isSelected ? "#2DA8FF" : "transparent"
                    border.width: modelData.isEnabled && !modelData.isSelected ? 1 : 0
                    border.color: "#2E2E2E"
                    opacity: modelData.isCurrentMonth ? 1.0 : 0.0

                    Label {
                        anchors.centerIn: parent
                        text: modelData.label
                        color: modelData.isSelected
                               ? "#FFFFFF"
                               : (modelData.isEnabled ? "#EAEAEA" : "#666666")
                        font.pixelSize: 15
                        font.bold: modelData.isSelected
                    }

                    MouseArea {
                        anchors.fill: parent
                        enabled: modelData.isEnabled

                        onClicked: {
                            dayCell.popupRoot.selectedDate = dayCell.popupRoot.normalizedDate(modelData.date)
                            dayCell.popupRoot.dateSelected(dayCell.popupRoot.selectedDate)
                            dayCell.popupRoot.close()
                        }
                    }
                }
            }
        }
    }
}
