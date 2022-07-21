import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle {
    property alias searchText: searchTextId.text

    ScrollView {
        anchors.fill: parent
        wheelEnabled: true

        TextArea {
            id: searchTextId
            placeholderText: qsTr("Text to search ... ")

            anchors.fill: parent
        }
    }
}
