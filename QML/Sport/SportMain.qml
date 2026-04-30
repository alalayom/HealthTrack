import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HealthTrack 1.0

Item {
    id: sportRoot
    width: parent ? parent.width : 0
    height: parent ? parent.height : 0

    property string currentSection: "home"

    readonly property var sportVM: appController.sportViewModel

    readonly property color bg: "#121212"
    readonly property color card: "#1E1E1E"
    readonly property color cardSoft: "#242424"
    readonly property color borderColor: "#2E2E2E"
    readonly property color textPrimary: "#FFFFFF"
    readonly property color textSecondary: "#A8A8A8"
    readonly property color accent: "#4DB6FF"

    readonly property var muscleGroups: [
        "Chest", "Triceps", "Biceps", "Back",
        "Shoulders", "Core", "Quadriceps", "Hamstrings",
        "Hips", "Calves", "Forearms", "Neck", "Cardio"
    ]

    component SportTabButton : Button {
        id: tabButton

        property bool selected: false

        Layout.fillWidth: true
        Layout.preferredHeight: 46
        padding: 0
        font.pixelSize: 15
        font.bold: selected

        contentItem: Label {
            text: tabButton.text
            color: tabButton.selected ? "#FFFFFF" : "#B8B8B8"
            font.pixelSize: tabButton.font.pixelSize
            font.bold: tabButton.font.bold
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            radius: 8
            color: tabButton.down ? "#3A3A3A" : tabButton.selected ? "#2E4A5C" : "#1E1E1E"
            border.width: 1
            border.color: tabButton.selected ? "#4DB6FF" : "#2E2E2E"
        }
    }

    component SummaryMetric : Rectangle {
        property string title: ""
        property string value: ""
        property string unit: ""

        Layout.fillWidth: true
        Layout.fillHeight: true
        radius: 8
        color: "#242424"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 14
            spacing: 4

            Label {
                Layout.fillWidth: true
                text: title
                color: "#A8A8A8"
                font.pixelSize: 13
                elide: Text.ElideRight
            }

            Label {
                Layout.fillWidth: true
                text: value
                color: "#FFFFFF"
                font.pixelSize: 25
                font.bold: true
                elide: Text.ElideRight
            }

            Label {
                Layout.fillWidth: true
                text: unit
                color: "#4DB6FF"
                font.pixelSize: 13
                elide: Text.ElideRight
            }
        }
    }

    component SessionCard : Rectangle {
        property string title: ""
        property string dayText: ""
        property string details: ""

        implicitHeight: 122
        radius: 8
        color: "#1E1E1E"
        border.width: 1
        border.color: "#2E2E2E"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 10

            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                Label {
                    Layout.fillWidth: true
                    text: title
                    color: "#FFFFFF"
                    font.pixelSize: 19
                    font.bold: true
                    elide: Text.ElideRight
                }

                Label {
                    text: dayText
                    color: "#A8A8A8"
                    font.pixelSize: 13
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 1
                color: "#303030"
            }

            Label {
                Layout.fillWidth: true
                text: details
                color: "#A8A8A8"
                font.pixelSize: 14
                wrapMode: Text.WordWrap
                maximumLineCount: 2
                elide: Text.ElideRight
            }
        }
    }

    component MuscleCard : Rectangle {
        id: muscleCard

        property string label: ""
        property bool selected: false
        signal clicked()

        width: 154
        height: 100
        radius: 8
        color: muscleCard.selected ? "#2E4A5C" : "#1E1E1E"
        border.width: 1
        border.color: muscleCard.selected ? "#4DB6FF" : "#2E2E2E"

        MouseArea {
            anchors.fill: parent
            onClicked: muscleCard.clicked()
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 12
            spacing: 8

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                radius: 6
                color: muscleCard.selected ? "#36596E" : "#292929"
                border.width: 1
                border.color: muscleCard.selected ? "#62C3FF" : "#383838"
            }

            Label {
                Layout.fillWidth: true
                text: label
                color: "#FFFFFF"
                font.pixelSize: 14
                font.bold: muscleCard.selected
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
            }
        }
    }

    component ExerciseRow : Rectangle {
        id: exerciseRow

        property string exerciseName: ""
        property string muscleGroup: ""
        property int rowHeight: 74

        implicitHeight: exerciseRow.rowHeight
        radius: exerciseRow.rowHeight > 0 ? 8 : 0
        color: "#1E1E1E"
        border.width: exerciseRow.rowHeight > 0 ? 1 : 0
        border.color: "#2E2E2E"
        clip: true

        RowLayout {
            anchors.fill: parent
            anchors.margins: exerciseRow.rowHeight > 0 ? 14 : 0
            spacing: 12

            Rectangle {
                Layout.preferredWidth: 44
                Layout.preferredHeight: 44
                radius: 8
                color: "#292929"
                border.width: 1
                border.color: "#383838"
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 3

                Label {
                    Layout.fillWidth: true
                    text: exerciseName
                    color: "#FFFFFF"
                    font.pixelSize: 17
                    font.bold: true
                    elide: Text.ElideRight
                }

                Label {
                    Layout.fillWidth: true
                    text: muscleGroup
                    color: "#A8A8A8"
                    font.pixelSize: 13
                    elide: Text.ElideRight
                }
            }
        }
    }

    component PlaceHolderPage : Item {
        property string title: ""
        property string subtitle: ""

        Rectangle {
            anchors.fill: parent
            radius: 8
            color: "#1E1E1E"
            border.width: 1
            border.color: "#2E2E2E"

            ColumnLayout {
                anchors.centerIn: parent
                width: Math.min(parent.width - 40, 420)
                spacing: 10

                Label {
                    Layout.fillWidth: true
                    text: title
                    color: "#FFFFFF"
                    font.pixelSize: 32
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WordWrap
                }

                Label {
                    Layout.fillWidth: true
                    text: subtitle
                    color: "#A8A8A8"
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WordWrap
                }
            }
        }
    }

    ListModel {
        id: previousSessionsModel

        ListElement { title: "Push Workout"; dayText: "Today"; details: "Exercises, sets and weights will be listed here." }
        ListElement { title: "Pull Workout"; dayText: "Yesterday"; details: "Exercises, sets and weights will be listed here." }
        ListElement { title: "Leg Day"; dayText: "2 days ago"; details: "Exercises, sets and weights will be listed here." }
        ListElement { title: "Core and Cardio"; dayText: "4 days ago"; details: "Exercises, sets and weights will be listed here." }
        ListElement { title: "Upper Body"; dayText: "Last week"; details: "Exercises, sets and weights will be listed here." }
    }

    Rectangle {
        anchors.fill: parent
        color: bg
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 16

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            SportTabButton {
                text: "Home"
                selected: sportRoot.currentSection === "home"
                onClicked: sportRoot.currentSection = "home"
            }

            SportTabButton {
                text: "Explore"
                selected: sportRoot.currentSection === "discover"
                onClicked: sportRoot.currentSection = "discover"
            }

            SportTabButton {
                text: "Workout"
                selected: sportRoot.currentSection === "workout"
                onClicked: sportRoot.currentSection = "workout"
            }

            SportTabButton {
                text: "Progress"
                selected: sportRoot.currentSection === "progress"
                onClicked: sportRoot.currentSection = "progress"
            }
        }

        StackLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: sportRoot.currentSection === "home" ? 0
                          : sportRoot.currentSection === "discover" ? 1
                          : sportRoot.currentSection === "workout" ? 2 : 3

            ScrollView {
                id: homeScroll
                clip: true

                ColumnLayout {
                    width: homeScroll.availableWidth
                    spacing: 16

                    Label {
                        Layout.fillWidth: true
                        text: "Your weekly summary"
                        color: textPrimary
                        font.pixelSize: 34
                        font.bold: true
                        wrapMode: Text.WordWrap
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        implicitHeight: 132
                        radius: 8
                        color: card
                        border.color: borderColor
                        border.width: 1

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 18
                            spacing: 10

                            SummaryMetric {
                                title: "Workouts"
                                value: "4"
                                unit: "sessions"
                            }

                            SummaryMetric {
                                title: "Duration"
                                value: "3h 45m"
                                unit: "total"
                            }

                            SummaryMetric {
                                title: "Total Volume"
                                value: "12,450"
                                unit: "kg"
                            }
                        }
                    }

                    Label {
                        Layout.fillWidth: true
                        Layout.topMargin: 6
                        text: "Previous workout sessions"
                        color: textPrimary
                        font.pixelSize: 22
                        font.bold: true
                    }

                    Repeater {
                        model: previousSessionsModel

                        delegate: SessionCard {
                            Layout.fillWidth: true
                            title: model.title
                            dayText: model.dayText
                            details: model.details
                        }
                    }
                }
            }

            ScrollView {
                id: discoverScroll
                clip: true

                ColumnLayout {
                    width: discoverScroll.availableWidth
                    spacing: 16

                    Label {
                        Layout.fillWidth: true
                        text: "Search exercises"
                        color: textPrimary
                        font.pixelSize: 34
                        font.bold: true
                        wrapMode: Text.WordWrap
                    }

                    TextField {
                        id: exerciseSearch
                        Layout.fillWidth: true
                        Layout.preferredHeight: 52
                        placeholderText: "Search exercises"
                        text: sportRoot.sportVM ? sportRoot.sportVM.searchText : ""
                        color: textPrimary
                        placeholderTextColor: "#777777"
                        font.pixelSize: 16
                        leftPadding: 18
                        rightPadding: 18
                        selectionColor: accent
                        selectedTextColor: "#0B0B0B"

                        background: Rectangle {
                            radius: 8
                            color: card
                            border.width: 1
                            border.color: exerciseSearch.activeFocus ? accent : borderColor
                        }

                        onTextChanged: {
                            if(sportRoot.sportVM && sportRoot.sportVM.searchText !== text)
                            {
                                sportRoot.sportVM.searchText = text
                            }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Layout.topMargin: 4

                        Label {
                            text: "Muscle groups"
                            color: textPrimary
                            font.pixelSize: 22
                            font.bold: true
                        }

                        Item {
                            Layout.fillWidth: true
                        }

                        Button {
                            visible: sportRoot.sportVM && sportRoot.sportVM.selectedMuscleGroup.length > 0
                            text: "Clear"
                            flat: true
                            onClicked: sportRoot.sportVM.selectedMuscleGroup = ""
                        }
                    }

                    Flow {
                        id: muscleFlow
                        Layout.fillWidth: true
                        Layout.preferredHeight: childrenRect.height
                        spacing: 10

                        Repeater {
                            model: sportRoot.muscleGroups

                            delegate: MuscleCard {
                                label: modelData
                                selected: sportRoot.sportVM && sportRoot.sportVM.selectedMuscleGroup === modelData
                                onClicked: {
                                    if(sportRoot.sportVM)
                                    {
                                        sportRoot.sportVM.selectedMuscleGroup = modelData
                                    }
                                }
                            }
                        }
                    }

                    Label {
                        Layout.fillWidth: true
                        Layout.topMargin: 8
                        text: sportRoot.sportVM && sportRoot.sportVM.selectedMuscleGroup.length > 0
                              ? sportRoot.sportVM.selectedMuscleGroup + " exercises"
                              : "Exercises"
                        color: textPrimary
                        font.pixelSize: 22
                        font.bold: true
                    }

                    Repeater {
                        model: sportRoot.sportVM ? sportRoot.sportVM.filteredExercises : []

                        delegate: ExerciseRow {
                            Layout.fillWidth: true
                            exerciseName: modelData.name
                            muscleGroup: modelData.muscleGroup
                        }
                    }
                }
            }

            PlaceHolderPage {
                title: "Workout"
                subtitle: "The workout screen area is ready."
            }

            PlaceHolderPage {
                title: "Progress"
                subtitle: "The progress screen area is ready."
            }
        }
    }
}
