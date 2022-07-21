import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle {
    property alias searchUrl: _searchUrl.text

    color: 'red'

    TextField {
        id: _searchUrl

        anchors.fill: parent
        rightPadding: 30
        leftPadding: 24

        text: "https://www.wikipedia.org"
        placeholderText: qsTr("Enter root search url ... ")
        cursorVisible: true
    }
}
