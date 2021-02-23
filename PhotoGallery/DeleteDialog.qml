import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQml 2.15

Dialog {
    id: confirmDeletePhotoDialog

    title: qsTr("Delete photo")
    width: 250
    height: 140
    anchors.centerIn: Overlay.overlay

    ColumnLayout {
        id: dialogWindowContainer

        anchors.fill: parent

        Text {
            id: confirmationText
            text: qsTr("Are you sure?")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 20

            Layout.fillWidth: true
            Layout.preferredHeight: 40
        }

        RowLayout {
            id: deletePhotoOptionsContainer

            Layout.fillWidth: true

            Button {
                id: dialogAcceptButton

                text: "Yes"
                font.pixelSize: 20
                Layout.alignment: Qt.AlignCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                onClicked: {
                    GalleryManager.removePhoto(GalleryManager.photoIndex)
                    confirmDeletePhotoDialog.accept()
                }
            }

            Button {
                id: dialogCancelButton

                text: "No"
                font.pixelSize: 20
                Layout.alignment: Qt.AlignCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                onClicked: confirmDeletePhotoDialog.close()
            }
        }
    }
}
