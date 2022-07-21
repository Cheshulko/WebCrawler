import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Window {
    id: _root
    visible: true
    width: 800
    height: 750
    title: qsTr("Web Crawler 1.0")

    MainScreen {
        anchors.fill: parent
    }
}
