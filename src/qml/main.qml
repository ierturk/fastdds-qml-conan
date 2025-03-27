import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Fast DDS QML Example"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        // Status bar
        Rectangle {
            Layout.fillWidth: true
            height: 30
            color: "#f0f0f0"
            border.color: "#c0c0c0"
            
            Text {
                anchors.fill: parent
                anchors.margins: 5
                text: ddsManager.status
                verticalAlignment: Text.AlignVCenter
            }
        }

        // Message display panel
        MessagePanel {
            Layout.fillWidth: true
            Layout.fillHeight: true
            messages: ddsManager.messages
        }

        // Message send form
        SendMessageForm {
            Layout.fillWidth: true
            onSendMessage: {
                ddsManager.sendMessage(message);
            }
        }
    }
}