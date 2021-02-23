import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 1.4
import QtQml 2.15

Item {
    id: headerItemContainerViewer

    width: 10
    height: 10

    property string fileTitle;
    property int fileWidth;
    property int fileHeight;
    property string fileSize;

    Rectangle {
        id: headerBackgroundRectangleViewer

        anchors.fill: parent
        color: "#96DDF7"

        RowLayout {
            id: headerContainerViewer

            anchors.fill: parent
            anchors.margins: 5

            Rectangle {
                id: fileTitleBackgroundRectangle
                Layout.fillWidth: true
                Layout.fillHeight: true

                color: "transparent"

                Text {
                    id: title
                    anchors.verticalCenter: parent.verticalCenter
                    text: "FileName: " + fileTitle
                    width: headerBackgroundRectangleViewer.width / 2
                    wrapMode: Text.WordWrap
                }
            }

            Rectangle {
                id: fileWidthBackgroundRectangle
                Layout.preferredWidth: 100
                Layout.fillHeight: true

                color: "transparent"

                Text {
                    id: widthViewer
                    anchors.verticalCenter: parent.verticalCenter
                    text: "FileWidth: " + fileWidth
                    Layout.fillHeight: true
                }
            }

            Rectangle {
                id: fileHeightBackgroundRectangle
                Layout.preferredWidth: 100
                Layout.fillHeight: true

                color: "transparent"

                Text {
                    id: heightViewer
                    anchors.verticalCenter: parent.verticalCenter
                    text: "FileHeight: " + fileHeight
                    Layout.fillHeight: true
                }
            }

            Rectangle {
                id: fileSizeBackgroundRectangle
                Layout.preferredWidth: 100
                Layout.fillHeight: true

                color: "transparent"

                Text {
                    id: sizeViewer
                    anchors.verticalCenter: parent.verticalCenter
                    text: "FileSize: " + fileSize
                    Layout.fillHeight: true
                }
            }
        }
    }
}
