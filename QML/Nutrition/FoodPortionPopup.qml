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
    width: Math.min(parent ? parent.width - 32 : 380, 380)
    x: parent ? (parent.width - width) / 2 : 0
    y: parent ? (parent.height - height) / 2 : 0

    property var nutritionVM
    property var foodItem: null
    property int gramsValue: 100
    property var portionInfo: ({
        name: "",
        grams: 100,
        calories: 0,
        protein: 0,
        carbs: 0,
        fat: 0
    })

    signal addRequested(real grams)

    function setGramsValue(pValue) {
        const tNumericValue = Number(pValue)
        const tSafeValue = isNaN(tNumericValue)
                ? 0
                : Math.max(0, Math.min(1000, Math.round(tNumericValue)))

        if (gramsValue !== tSafeValue)
        {
            gramsValue = tSafeValue
            refreshPreview()
        }

        if (Math.round(portionSlider.value) !== tSafeValue)
        {
            portionSlider.value = tSafeValue
        }

        if (gramsSpinBox.value !== tSafeValue)
        {
            gramsSpinBox.value = tSafeValue
        }
    }

    function refreshPreview() {
        if (!nutritionVM || !foodItem)
        {
            portionInfo = ({
                name: "",
                grams: gramsValue,
                calories: 0,
                protein: 0,
                carbs: 0,
                fat: 0
            })
            return
        }

        portionInfo = nutritionVM.calculateFoodPortion(
            foodItem.name,
            Number(foodItem.calories),
            Number(foodItem.protein),
            Number(foodItem.carbs),
            Number(foodItem.fat),
            gramsValue
        )
    }

    function openForFood(pFoodItem) {
        foodItem = pFoodItem
        setGramsValue(100)
        refreshPreview()
        open()
    }

    onOpened: refreshPreview()
    onFoodItemChanged: refreshPreview()

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

        Rectangle {
            Layout.fillWidth: true
            radius: 18
            color: "#242424"
            implicitHeight: previewContent.implicitHeight + 24

            ColumnLayout {
                id: previewContent
                anchors.fill: parent
                anchors.margins: 12
                spacing: 6

                Label {
                    text: portionInfo.name && portionInfo.name.length > 0
                          ? portionInfo.name
                          : "Selected Food"
                    color: "#FFFFFF"
                    font.pixelSize: 20
                    font.bold: true
                    Layout.fillWidth: true
                    elide: Text.ElideRight
                }

                Label {
                    text: Number(portionInfo.grams).toFixed(0) + " g will be added"
                    color: "#E7B66B"
                    font.pixelSize: 14
                }

                Label {
                    text: Number(portionInfo.calories).toFixed(0) + " Calories"
                    color: "#FFFFFF"
                    font.pixelSize: 22
                    font.bold: true
                }

                Label {
                    text: Number(portionInfo.protein).toFixed(1) + " g protein, "
                        + Number(portionInfo.carbs).toFixed(1) + " g carbs, "
                        + Number(portionInfo.fat).toFixed(1) + " g fat"
                    color: "#BEBEBE"
                    font.pixelSize: 14
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }

                Label {
                    text: foodItem
                          ? "100 g base: "
                            + Number(foodItem.calories).toFixed(0) + " cal, "
                            + Number(foodItem.protein).toFixed(1) + " g protein, "
                            + Number(foodItem.carbs).toFixed(1) + " g carbs, "
                            + Number(foodItem.fat).toFixed(1) + " g fat"
                          : ""
                    color: "#8F8F8F"
                    font.pixelSize: 12
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }
            }
        }

        Label {
            text: "Portion Size"
            color: "#FFFFFF"
            font.pixelSize: 16
            font.bold: true
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Label {
                text: "Grams"
                color: "#BEBEBE"
                font.pixelSize: 14
            }

            SpinBox {
                id: gramsSpinBox
                from: 0
                to: 1000
                value: 100
                editable: true

                validator: IntValidator {
                    bottom: 0
                    top: 1000
                }

                onValueModified: root.setGramsValue(value)
            }

            Label {
                text: "g"
                color: "#8F8F8F"
                font.pixelSize: 14
            }

            Item {
                Layout.fillWidth: true
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                text: "0 g"
                color: "#8F8F8F"
            }

            Item {
                Layout.fillWidth: true
            }

            Label {
                text: "1000 g"
                color: "#8F8F8F"
            }
        }

        Slider {
            id: portionSlider
            Layout.fillWidth: true
            from: 0
            to: 1000
            value: 100
            stepSize: 1
            snapMode: Slider.SnapAlways

            onValueChanged: {
                if (pressed)
                {
                    root.setGramsValue(value)
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Button {
                Layout.fillWidth: true
                text: "Cancel"
                onClicked: root.close()
            }

            Button {
                Layout.fillWidth: true
                text: "Add"
                enabled: Number(portionInfo.grams) > 0

                onClicked: {
                    root.addRequested(Number(portionInfo.grams))
                    root.close()
                }
            }
        }
    }
}
