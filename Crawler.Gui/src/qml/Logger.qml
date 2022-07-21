import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle {
    border.color: "black"
    border.width: 1

    ListView {
        id: logListView

        anchors {
            fill: parent
            margins: 10
            topMargin: 50
            bottomMargin: 50
        }

        spacing: 5

        ScrollBar.vertical: ScrollBar { active: true; visible: true }
        ScrollBar.horizontal: ScrollBar { active: true; visible: false }

        onCountChanged: {
            logListView.currentIndex = count - 1
        }

        model: myModel

        delegate: Rectangle {
            width: 100
            height: 50

            Text {
                anchors.fill: parent

                text: model.text
                color: model.color
            }
        }
    }
}
