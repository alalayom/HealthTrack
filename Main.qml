import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    visible: true
    width: 1200
    height: 800
    title: "HealthTrack"
    color: "#121212"

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        //Top Panel
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

                    Label {
                        anchors.centerIn: parent
                        text: "Settings"
                        color: "white"
                        font.pixelSize: 18
                    }
                }
            }
        }

        //Mid Panel
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#181818"

            Label {
                anchors.centerIn: parent
                text: "Main section for main applications"
                color: "#AAAAAA"
                font.pixelSize: 26
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

                //Nutrition Section
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: 8
                    color: "#2A2A2A"

                    Label {
                        anchors.centerIn: parent
                        text: "Nutrition"
                        color: "white"
                        font.pixelSize: 18
                    }
                }

                //Sport Section
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: 8
                    color: "#2A2A2A"

                    Label {
                        anchors.centerIn: parent
                        text: "Sport"
                        color: "white"
                        font.pixelSize: 18
                    }
                }

                //Sleep Section
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: 8
                    color: "#2A2A2A"

                    Label {
                        anchors.centerIn: parent
                        text: "Sleep"
                        color: "white"
                        font.pixelSize: 18
                    }
                }

                //Profile Section
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: 8
                    color: "#2A2A2A"

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
