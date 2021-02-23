import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 1.4
import QtQml 2.15

Item {
    id: itemContainer

    width: 10
    height: 10

    function decideSizeDisplayUnit() {
        if(sizeInBytes > 1000000)
        {
            return sizeInBytes / 1000000 + " MB"
        }
        else if(sizeInBytes > 1000)
        {
            return sizeInBytes / 1000 + " KB"
        }
        else
        {
            return sizeInBytes + " B"
        }
    }

    DeleteDialog {
        id: itemDeleteDialog
    }

    MouseArea {
        id: mouseAreaDelegate

        width: gridViewContainer.cellWidth - 10
        height: gridViewContainer.cellHeight - 10
        onDoubleClicked: {
            var component = Qt.createComponent("ViewerWindow.qml");

            var win = component.createObject(mainWindow);
            win.imageSource = "file:C:/Users/radu.rotariu/OneDrive - Fortech srl/Documents/project3qt/build-PhotoGallery-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/Photos/" + fileName;
            win.title = fileName;

            console.log("fileName: " + fileName);
            console.log("win: " + win);
            if(_width > 800)
            {
                win.width = _width;
            }
            if(_height > 500)
            {
                win.height = _height + 100;
            }

            win._fileWidth = _width;
            win._fileHeight = _height;
            win._fileSize = decideSizeDisplayUnit();
            win.show();
        }
    }

    ColumnLayout {
        id: componentContainer

        width: gridViewContainer.cellWidth - 10
        height: gridViewContainer.cellHeight - 10
        spacing: 0

        Rectangle {
            id: imageRectangle

            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "transparent"

            Image {
                id: thumb
                source: thumbnailURL
                anchors.fill: parent
            }
        }

        Rectangle {
            id: sizeRectangle

            Layout.fillWidth: true
            Layout.preferredHeight: 30
            color: "blue"

            Text {
                id: fileSize

                anchors.centerIn: parent
                text: decideSizeDisplayUnit()
            }

            Button {
                id: deletePhoto

                anchors.right: parent.right
                text: "X"
                width: 30
                height: 30
                onClicked: {
                    GalleryManager.setPhotoIndex(index)
                    itemDeleteDialog.open()
                }
            }
        }
    }
}
