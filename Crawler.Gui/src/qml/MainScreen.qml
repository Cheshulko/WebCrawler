import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import WebCrawlerSettings 1.0

import "input"

Item {
    id: mainId

    anchors.fill: parent

    enabled: true

    Binding {
        target: mySettings
        property: "urls"
        value: configId.maxUrlScanned
    }

    Binding {
        target: mySettings
        property: "threads"
        value: configId.threadsCnt
    }

    Connections {
        target: MainScreen_controller
        function onScreenStateChanged(state){
            mainId.enabled = state;
        }
    }

    InputUrl {
        id: searchRectId

        anchors.margins: 5
        width: parent.width
        height: 30
    }

    InputSettings {
        id: configId

        anchors {
            top: searchRectId.bottom
            left: mainId.left
            right: mainId.right
            leftMargin: 20
            rightMargin: 20
            topMargin: 10
        }

        height: 30

        spacing: 5
    }

    Binding {
        target: mySettings
        property: "text"
        value: searchTextRectId.searchText
    }

    InputSearchText {
        id : searchTextRectId

        width: mainId.width
        height: 100

        anchors {
            top: configId.bottom
            left: mainId.left
            right: mainId.right
            leftMargin: 20
            rightMargin: 20
            topMargin: 10
        }
    }

    Connections {
        target: MainScreen_controller
        function onProgressChanged(progress){
            progressRectId.progressValue = progress
        }
    }

    ParsingProgress {
        id: progressRectId
        width: mainId.width
        height: 30

        anchors {
            top: searchTextRectId.bottom
            left: mainId.left
            right: mainId.right
            topMargin: 10
        }
    }

    Connections {
        target: MainScreen_controller
        function onDone() {
            buttonsId.startResumeName = "Start"
            buttonsId.startResumeState = true

            buttonsId.pausedName = "Pause"
            buttonsId.paused = false
            buttonsId.pausedState = false

            buttonsId.stoppedName = "Stop"
            buttonsId.stoppedState = false
        }
    }

    RowLayout {
        id: buttonsId

        anchors {
            top: progressRectId.bottom
            left: mainId.left
            right: mainId.right
            leftMargin: 20
            rightMargin: 20
            topMargin: 10
        }

        spacing: 5

        property bool paused: false

        property alias startResumeName: startResumeButtonId.text
        property alias pausedName: pauseButtonId.text
        property alias stoppedName: stopButtonId.text

        property alias startResumeState: startResumeButtonId.enabled
        property alias pausedState: pauseButtonId.enabled
        property alias stoppedState: stopButtonId.enabled

        Button {
            id: startResumeButtonId

            Layout.fillWidth: true

            text: qsTr("Start")

            onClicked: {
                parent.startResumeState = false
                parent.startResumeName = "Started"

                parent.pausedName = "Pause"
                parent.pausedState = true

                parent.stoppedName = "Stop"
                parent.stoppedState = true

                if (!parent.paused) {
                    MainScreen_controller.start(searchRectId.searchUrl)
                } else {
                    parent.paused = false
                    MainScreen_controller.resume()
                }
            }
        }

        Button {
            id: pauseButtonId

            Layout.fillWidth: true

            enabled: false

            text: qsTr("Pause")

            onClicked: {
                parent.startResumeName = qsTr("Resume")
                parent.startResumeState = true

                parent.pausedName = qsTr("Paused")
                parent.paused = true
                parent.pausedState = false

                MainScreen_controller.pause()
            }
        }

        Button {
            id: stopButtonId

            Layout.fillWidth: true

            enabled: false

            text: qsTr("Stop")

            onClicked: {
                parent.startResumeName = qsTr("Start")
                parent.startResumeState = true

                parent.pausedName = qsTr("Pause")
                parent.paused = false
                parent.pausedState = false

                parent.stoppedName = qsTr("Stopped")
                parent.stoppedState = false

                MainScreen_controller.stop()
            }
        }

        Button {
            id: clearButtonId

            Layout.fillWidth: true

            text: qsTr("Clear")

            onClicked: MainScreen_controller.clearLog()
        }
    }

    Logger {
        width: parent.width

        anchors {
            top: buttonsId.bottom
            bottom: mainId.bottom
            topMargin: 5
            bottomMargin: 5
            left: mainId.left
            right: mainId.right
            leftMargin: 5
            rightMargin: 5
        }
    }
}
