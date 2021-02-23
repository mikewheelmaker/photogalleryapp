import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 1.4
import QtQml 2.15

Item {
    id: headerItemContainer

    width: 10
    height: 10

    Rectangle {
        id: headerBackgroundRectangle

        anchors.fill: parent
        color: "#96DDF7"

        RowLayout {
            id: headerContainer

            anchors.fill: parent
            anchors.margins: 5

            Rectangle {
                id: searchContainerBackgroundRectangle

                Layout.fillHeight: true
                Layout.fillWidth: true

                color: "transparent"

                RowLayout {
                    id: searchContainer

                    anchors.fill: parent

                    TextField {
                        id: inputFileName

                        Layout.preferredHeight: 30
                        Layout.fillWidth: true

                        placeholderText: "Enter file name"
                        onTextChanged: {
                            GalleryManager.searchProxy(0, inputFileName.text)
                        }
                    }

                    Button {
                        id: clearSearchField

                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 30
                        text: "X"
                        onClicked: inputFileName.text = ""
                    }
                }
            }

            Rectangle {
                id: sortContainerBackgroundRectangle

                Layout.fillHeight: true
                Layout.fillWidth: true

                color: "transparent"

                RowLayout {
                    id: sortContainer

                    anchors.fill: parent

                    Text {
                        id: labelMenu

                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 50
                        text: "Sort by:"
                    }

                    ComboBox {
                        id: dropdownMenu

                        Layout.preferredHeight: 30
                        Layout.fillWidth: true
                        model: [ "FileName", "Width", "Height", "Size" ]
                        onCurrentIndexChanged: {
                            GalleryManager.sortProxy(dropdownMenu.currentIndex, true)
                        }
                    }

                    Button {
                        id: sortOrderButtonAscending

                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 40
                        text: "A-Z"
                        onClicked: {
                            GalleryManager.sortProxy(dropdownMenu.currentIndex, true)
                        }
                    }

                    Button {
                        id: sortOrderButtonDescending

                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 40
                        text: "Z-A"
                        onClicked: {
                            GalleryManager.sortProxy(dropdownMenu.currentIndex, false)
                        }
                    }
                }
            }
        }
    }

}
