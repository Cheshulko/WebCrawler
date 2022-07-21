import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

RowLayout {
    property alias threadsCnt: threadsCntId.text
    property alias maxUrlScanned: maxUrlScannedId.text

    Rectangle {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignLeft

        color: 'red'

        Label {
            anchors.fill: parent

            text: "Threads "

            font.pixelSize: 12
            font.italic: true

            horizontalAlignment: "AlignHCenter"
            verticalAlignment: "AlignVCenter"
        }
    }

    Rectangle {
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignLeft

        color: 'red'

        TextField {
            id: threadsCntId

            anchors.fill: parent

            validator: IntValidator { bottom: 1; top: 9 }
            text: "1"
            placeholderText: qsTr("Threads")
            cursorVisible: false

            rightPadding: 30
            leftPadding: 24

            horizontalAlignment: "AlignHCenter"
            verticalAlignment: "AlignVCenter"
        }
    }

    Rectangle {
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignLeft

        color: 'red'

        Label {
            anchors.fill: parent

            text: "Urls scanning: "
            font.pixelSize: 12
            font.italic: true

            horizontalAlignment: "AlignHCenter"
            verticalAlignment: "AlignVCenter"
        }
    }

    Rectangle {
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignLeft

        color: 'red'

        TextField {
            id: maxUrlScannedId

            anchors.fill: parent
            rightPadding: 30
            leftPadding: 24

            text: "1"
            validator: IntValidator { bottom: 1; top: 1000 }
            placeholderText: qsTr("Threads")
            cursorVisible: false

            horizontalAlignment: "AlignHCenter"
            verticalAlignment: "AlignVCenter"
        }
    }
}
