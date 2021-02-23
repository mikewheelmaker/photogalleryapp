import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 1.4
import QtQml 2.15

Item {
    id: footerItemContainerViewer

    width: 10
    height: 10

    Rectangle {
        id: footerBackgroundRectangleViewer

        anchors.fill: parent
        color: "#96DDF7"

        RowLayout {
            id: footerContainerViewer

            anchors.fill: parent
            anchors.margins: 5

            Rectangle {
                id: editingButtonsBackgroundRectangle
                Layout.fillWidth: true
                Layout.fillHeight: true

                color: "transparent"

                RowLayout {
                    id: editingButtonsContainer

                    anchors.centerIn: parent
                    spacing: 5

                    Button {
                        id: rotateLeftButton

                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 50
                        Layout.alignment: Qt.AlignRight
                        text: "R Left"
                    }

                    Button {
                        id: rotateRightButton

                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 50
                        Layout.alignment: Qt.AlignCenter
                        text: "R Right"
                    }

                    Button {
                        id: mirrorVerticalButton

                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 50
                        Layout.alignment: Qt.AlignCenter
                        text: "MirrorV"
                    }

                    Button {
                        id: mirrorHorizontalButton

                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 50
                        Layout.alignment: Qt.AlignCenter
                        text: "MirrorH"
                    }

                    Button {
                        id: cropButton

                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 50
                        Layout.alignment: Qt.AlignLeft
                        text: "Crop"
                    }
                }
            }

            Rectangle {
                id: managementButtonsBackgroundRectangle
                Layout.fillWidth: true
                Layout.fillHeight: true

                color: "transparent"

                RowLayout {
                    id: managementButtonsContainer

                    anchors.centerIn: parent
                    spacing: 5

                    Button {
                        id: saveButton

                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 55
                        Layout.alignment: Qt.AlignRight
                        text: "Save"
                    }

                    Button {
                        id: saveAsButton

                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 55
                        Layout.alignment: Qt.AlignCenter
                        text: "Save as"
                    }

                    Button {
                        id: closeButton

                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 55
                        Layout.alignment: Qt.AlignLeft
                        text: "Close"
                        onClicked: close()
                    }
                }
            }

            Rectangle {
                id: zoomSliderBackgroundRectangle
                Layout.fillWidth: true
                Layout.fillHeight: true

                color: "transparent"
            }
        }
    }
}
