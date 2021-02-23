import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 1.4
import QtQml 2.15

Item {
    id: footerItemContainer

    width: 10
    height: 10

    property double sliderValue: sizeAdjustmentSlider.value

    Rectangle {
        id: footerBackgroundRectangle

        anchors.fill: parent
        color: "#96DDF7"

        RowLayout {
            id: footerContainer

            anchors.fill: parent
            anchors.margins: 5

            Rectangle {
                id: numberOfItemsBackgroundRectangle
                Layout.fillWidth: true
                Layout.fillHeight: true

                color: "transparent"

                Text {
                    id: numberOfItems

                    anchors.verticalCenter: parent.verticalCenter
                    text: gridViewContainer.count + " items"
                }
            }

            Rectangle {
                id: dbButtonsBackgroundRectangle
                Layout.fillWidth: true
                Layout.fillHeight: true

                color: "transparent"

                RowLayout {
                    id: dbButtonsContainer

                    anchors.centerIn: parent
                    spacing: 5

                    Button {
                        id: importButton

                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 55
                        Layout.alignment: Qt.AlignRight
                        text: "Import"
                        onClicked: GalleryManager.importPhotos()
                    }

                    Button {
                        id: exportButton

                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 55
                        Layout.alignment: Qt.AlignCenter
                        text: "Export"
                        onClicked: GalleryManager.exportPhotos()
                    }

                    Button {
                        id: clearButton

                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 55
                        Layout.alignment: Qt.AlignLeft
                        text: "Clear"
                        onClicked: GalleryManager.clearCache()
                    }
                }
            }

            Rectangle {
                id: sliderContainerBackgroundRectangle
                Layout.fillWidth: true
                Layout.fillHeight: true

                color: "transparent"

                RowLayout {
                    id: sliderContainer

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    spacing: 5

                    Text {
                        id: labelSlider

                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 90
                        Layout.leftMargin: 5
                        text: "Preview Size:"
                        font.pixelSize: 16
                    }

                    Slider {
                        id: sizeAdjustmentSlider

                        minimumValue: 1.0
                        maximumValue: 3.0
                        value: 1

                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 200
                    }
                }
            }
        }
    }
}
