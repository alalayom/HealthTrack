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

    property var mealFoods: []
    property var mealTotals: ({ calories: 0, protein: 0, carbs: 0, fat: 0 })

    function refreshMealData() {
        const meals = nutritionVM.meals

        console.log("refreshMealData -> mealIndex:", mealIndex, "meal count:", meals.length)

        if (mealIndex >= 0 && mealIndex < meals.length)
        {
            const meal = meals[mealIndex]

            mealFoods = meal && meal.foods ? meal.foods : []
            mealTotals = meal && meal.totals
                       ? meal.totals
                       : ({ calories: 0, protein: 0, carbs: 0, fat: 0 })

            console.log("mealFoods count:", mealFoods.length)
            console.log("mealTotals calories:", Number(mealTotals.calories))
        }
        else
        {
            mealFoods = []
            mealTotals = ({ calories: 0, protein: 0, carbs: 0, fat: 0 })

            console.log("Invalid mealIndex:", mealIndex)
        }
    }

    property var searchResults: []

    function refreshSearch() {
        searchResults = nutritionVM.searchCatalogFoods(searchField.text)
    }

    function addCatalogFoodToMeal(foodItem) {
        console.log("addCatalogFoodToMeal called -> mealIndex:", mealIndex,
                    "name:", foodItem ? foodItem.name : "null")

        if (!foodItem || mealIndex < 0)
        {
            console.log("Add aborted: invalid foodItem or mealIndex")
            return
        }

        nutritionVM.addFoodToMeal(
            mealIndex,
            foodItem.name,
            Number(foodItem.calories),
            Number(foodItem.protein),
            Number(foodItem.carbs),
            Number(foodItem.fat)
        )

        refreshMealData()
    }

    background: Rectangle {
        color: "#121212"
    }

    Component.onCompleted: {
        refreshSearch()
        refreshMealData()
        console.log("Page opened. mealIndex =", mealIndex, ", mealName =", mealName)
    }

    Connections {
        target: nutritionVM

        function onMealsChanged() {
            console.log("mealsChanged received")
            refreshSearch()
            refreshMealData()
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

        //Meal summary
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
                                    text: Number(modelData.calories).toFixed(0) + " Calories, "
                                        + Number(modelData.protein).toFixed(1) + " g protein, "
                                        + Number(modelData.carbs).toFixed(1) + " g carbs, "
                                        + Number(modelData.fat).toFixed(1) + " g fat"
                                    color: "#A0A0A0"
                                    font.pixelSize: 13
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                            }

                            Button {
                                Layout.preferredWidth: 40
                                Layout.preferredHeight: 40
                                padding: 0

                                background: Rectangle {
                                    radius: width / 2
                                    color: parent.down ? "#5A5A5A" : "#4A4A4A"
                                    border.width: 0
                                }

                                contentItem: Item {
                                    anchors.fill: parent

                                    Text {
                                        anchors.centerIn: parent
                                        text: "+"
                                        color: "#FFFFFF"
                                        font.pixelSize: 22
                                        font.bold: true
                                    }
                                }

                                onClicked: {
                                    console.log("Plus clicked ->", modelData.name, "mealIndex:", mealIndex)
                                    root.addCatalogFoodToMeal(modelData)
                                }
                            }
                        }
                    }
                }
            }
        }

        //Added foods to meal
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
                                    text: Number(modelData.calories).toFixed(0) + " Calories, "
                                        + Number(modelData.protein).toFixed(1) + " g protein, "
                                        + Number(modelData.carbs).toFixed(1) + " g carbs,  "
                                        + Number(modelData.fat).toFixed(1) + " g fat"
                                    color: "#A0A0A0"
                                    font.pixelSize: 13
                                    Layout.fillWidth: true
                                    elide: Text.ElideRight
                                }
                            }

                            Button {
                                Layout.preferredWidth: 40
                                Layout.preferredHeight: 40
                                padding: 0

                                background: Rectangle {
                                    radius: width / 2
                                    color: parent.down ? "#5A5A5A" : "#4A4A4A"
                                    border.width: 0
                                }

                                contentItem: Item {
                                    anchors.fill: parent

                                    Text {
                                        anchors.centerIn: parent
                                        text: "🗑️"
                                        color: "#FFFFFF"
                                        font.pixelSize: 24
                                        font.bold: true
                                    }
                                }

                                onClicked: nutritionVM.removeFood(mealIndex, index)
                            }
                        }
                    }
                }
            }
        }
    }
}
