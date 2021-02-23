import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQml 2.15

Window {
    id: viewerWindow

    width: 800
    height: 600
    visible: true
    title: qsTr("Viewer")

    property string imageSource: "";
    property int _fileWidth: 0;
    property int _fileHeight: 0;
    property string _fileSize: "";

    ColumnLayout {
        id: viewerWindowContainer

        anchors.fill: parent
        spacing: 0

        HeaderViewerWindow {
            id: viewerHeader
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
            Layout.preferredHeight: 50
            fileTitle: title
            fileWidth: _fileWidth
            fileHeight: _fileHeight
            fileSize: _fileSize
        }

        Image {
            id: viewerImage
            source: imageSource
            Layout.alignment: Qt.AlignCenter
            clip: true
        }

        FooterViewerWindow {
            id: viewerFooter
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignBottom
            Layout.preferredHeight: 50
        }
    }
}
