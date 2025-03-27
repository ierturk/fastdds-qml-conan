import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    property var messages: []
    color: "#ffffff"
    border.color: "#c0c0c0"
    
    ListView {
        id: messageView
        anchors.fill: parent
        anchors.margins: 5
        model: messages
        clip: true
        
        delegate: Rectangle {
            width: messageView.width
            height: messageText.height + 10
            color: modelData.indexOf("Received:") === 0 ? "#e6f7ff" : "#f0f0f0"
            radius: 5
            
            Text {
                id: messageText
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 5
                text: modelData
                wrapMode: Text.Wrap
            }
        }

        // Automatically scroll to the bottom when new messages arrive
        onCountChanged: {
            messageView.positionViewAtEnd();
        }
    }
}