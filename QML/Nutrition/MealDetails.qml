import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HealthTrack 1.0

Page {
    id: root
    title: "Meal Details"

    property var nutritionVM: appController.nutritionViewModel
    property var nav: appController.navigationManager

    property int mealIndex: nav.selectedMealIndex
    property string mealName: nav.selectedMealName

    property var mealsData: nutritionVM.meals
    property var selectedMeal: {
        if(mealIndex >= 0 && mealIndex < mealsData.length)
        {
            return mealsData[mealIndex]
        }

        return null
    }

    property var mealFoods: selectedMeal && selectedMeal.foods ? selectedMeal.foods : []
    property var mealTotals: selectedMeal && selectedMeal.totals ? selectedMeal.total : ({calories: 0, protein: 0, carbs: 0, fat: 0})

    property var searchResults: []

    function refreshSearch() {
        searchResults = nutritionVM.searchCatalogFoods(searchField.text)
    }

    function addCatalogFoodToMeal(foodItem) {
        if(!foodItem || mealIndex < 0)
        {
            return
        }

        nutritionVM.addFood(
            mealIndex,
            foodItem.name,
            Number(foodItem.calories),
            Number(foodItem.protein),
            Number(foodItem.carbs),
            Number(foodItem.fat)
        )
    }

    background: Rectangle {
        color: "#121212"
    }

    Component.onCompleted: {
        refreshSearch()
    }

    Connections {
        target: nutritionVM

        function onMealsChanged() {
            refreshSearch()
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 14

        //Get details
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Button {
                text: "<-"
                onClicked: nav.navigateToNutrition()
            }

            Label {
                text: mealName.length > 0 ? mealName : "Meal Details"
                color: "#FFFFFF"
                font.pixelSize: 24
                font.bold: true
                Layout.fillWidth: true
            }
        }

        //Search and add foods
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            TextField {
                id: searchField
                Layout.fillWidth: true
                placeholderText: "Search foods..."
                color: "#FFFFFF"
                placeholderTextColor: "#888888"
                selectByMouse: true

                background: Rectangle {
                    radius: 12
                    color: "#1E1E1E"
                    border.color: "#2E2E2E"
                    border.width: 1
                }

                onTextChanged: root.refreshSearch()
            }

            Button {
                text: "Add New"
                onClicked: nav.openAddFoodPage()
            }
        }

        Rectangle {
            Layout.fillWidth: true
            radius: 16
            color: "#1A1A1A"
            border.color: "#2A2A2A"
            border.width: 1
            implicitHeight: summaryContent.implicitHeight + 24

            ColumnLayout {
                id: summaryContent
                anchors.fill: parent
                anchors.margins: 12
                spacing: 8

                Label {
                    text: "Meal Summary"
                    color: "#FFFFFF"
                    font.pixelSize: 18
                    font.bold: true
                }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 16

                    Label {
                        text: "Calories: " + Number(mealTotals.calories).toFixed(0)
                        color: "#EAEAEA"
                    }

                    Label {
                        text: "Protein: " + Number(mealTotals.protein).toFixed(1) + " g"
                        color: "#EAEAEA"
                    }

                    Label {
                        text: "Carbs: " + Number(mealTotals.carbs).toFixed(1) + " g"
                        color: "#EAEAEA"
                    }

                    Label {
                        text: "Fat: " + Number(mealTotals.fat).toFixed(1) + " g"
                        color: "#EAEAEA"
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 180
            radius: 16
            color: "#171717"
            border.color: "#2A2A2A"
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 8

                Label {
                    text: "Search Results"
                    color: "#FFFFFF"
                    font.pixelSize: 18
                    font.bold: true
                }

                ListView {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    clip: true
                    model: searchResults

                    delegate: Rectangle {
                        width: ListView.view.width
                        height: 62
                        color: "transparent"

                        RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 8
                            anchors.rightMargin: 8
                            spacing: 10

                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 2

                                Label {
                                    text: modelData.name
                                    color: "#FFFFFF"
                                    font.pixelSize: 16
                                    font.bold: true
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }

                                Label {
                                    text: Number(modelData.calories).toFixed(0) + " Cal "
                                        + Number(modelData.protein).toFixed(1) + " P "
                                        + Number(modelData.carbs).toFixed(1) + " C "
                                        + Number(modelData.fat).toFixed(1) + " F"
                                    color: "#A0A0A0"
                                    font.pixelSize: 13
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                            }

                            Button {
                                text: "+"
                                Layout.preferredWidth: 40
                                onClicked: root.addCatalogFoodToMeal(modelData)
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 16
            color: "#171717"
            border.color: "#2A2A2A"
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 8

                Label {
                    text: "Added Foods"
                    color: "#FFFFFF"
                    font.pixelSize: 18
                    font.bold: true
                }

                ListView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true
                    model: mealFoods

                    delegate: Rectangle {
                        width: ListView.view.width
                        height: 64
                        color: "transparent"

                        RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 8
                            anchors.rightMargin: 8
                            spacing: 10

                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 2

                                Label {
                                    text: modelData.name
                                    color: "#FFFFFF"
                                    font.pixelSize: 16
                                    font.bold: true
                                    Layout.fillWidth: true
                                    elide: Text.ElideRight
                                }

                                Label {
                                    text: Number(modelData.calories).toFixed(0) + " Cal "
                                        + Number(modelData.protein).toFixed(1) + " P "
                                        + Number(modelData.carbs).toFixed(1) + " C "
                                        + Number(modelData.fat).toFixed(1) + " F"
                                    color: "#A0A0A0"
                                    font.pixelSize: 13
                                    Layout.fillWidth: true
                                    elide: Text.ElideRight
                                }
                            }

                            Button {
                                text: "🗑"
                                Layout.preferredWidth: 44
                                onClicked: nutritionVM.removeFood(mealIndex, index)
                            }
                        }
                    }
                }
            }
        }
    }
}
