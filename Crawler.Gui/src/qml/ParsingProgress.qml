import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    property alias progressValue: progressId.value

    color: 'lightgray'

    ProgressBar {
        id: progressId

        anchors.fill: parent

        value: 0
    }
}
