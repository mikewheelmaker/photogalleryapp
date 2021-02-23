import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 1.4
import QtQml 2.15

Window {
    id: mainWindow
    width: 800
    height: 600
    visible: true
    title: qsTr("Photo Gallery")

    property bool startedImport: false

    Connections {
        target: GalleryManager
        function onIsImportStartedChanged() {
            startedImport = GalleryManager.isImportStarted
            importLoadingIndicator.visible = startedImport
        }
    }

    ColumnLayout {
        id: mainWindowContainer

        anchors.fill: parent
        spacing: 0

        HeaderMainWindow {
            id: header

            Layout.fillWidth: true
            Layout.preferredHeight: 50
        }

        Rectangle {
            id: galleryBackgroundRectangle

            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#DFEFF5"

            GridView {
                id: gridViewContainer

                anchors.fill: parent
                anchors.margins: 10
                anchors.bottomMargin: 0
                cellHeight: 150*footer.sliderValue
                cellWidth: 150*footer.sliderValue

                clip: true

                model: GalleryManager.proxyModel
                delegate: GridViewDelegate {}
            }

            BusyIndicator {
                id: importLoadingIndicator

                anchors.centerIn: galleryBackgroundRectangle
                visible: false
            }
        }

        FooterMainWindow {
            id: footer

            Layout.fillWidth: true
            Layout.preferredHeight: 50
        }
    }
}
