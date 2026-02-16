import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        //TopPanel
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 120
            color: "#1E1E1E"

            RowLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 40

                //Statistics Section
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 80
                    radius: 8
                    color: "#2A2A2A"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            contentStack.replace("Statistics.qml")
                        }
                    }

                    Label {
                        anchors.centerIn: parent
                        text: "Statistics"
                        color: "white"
                        font.pixelSize: 20
                    }
                }

                //Settings Section
                Rectangle {
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 80
                    radius: 8
                    color: "#2A2A2A"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            contentStack.replace("Settings.qml")
                        }
                    }

                    Label {
                        anchors.centerIn: parent
                        text: "Settings"
                        color: "white"
                        font.pixelSize: 20
                    }
                }
            }
        }

        //Middle Panel
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

        //Bottom Panel
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 140
            color: "#1E1E1E"

            RowLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 20

                Repeater {
                    model: [
                        {text: "Nutrition", page: "Nutrition.qml"},
                        {text: "Sport", page: "Sport.qml"},
                        {text: "Sleep", page: "Sleep.qml"},
                        {text: "Profile", page: "Profile.qml"}
                    ]

                    delegate: Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        radius: 8
                        color: "#2A2A2A"

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                contentStack.replace(modelData.page)
                            }
                        }

                        Label {
                            anchors.centerIn: parent
                            text: modelData.text
                            color: "white"
                            font.pixelSize: 18
                        }
                    }
                }
            }
        }

    }
}
