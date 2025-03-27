import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    height: 50
    color: "#f0f0f0"
    border.color: "#c0c0c0"
    
    signal sendMessage(string message)
    
    RowLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 10
        
        TextField {
            id: messageInput
            Layout.fillWidth: true
            placeholderText: "Enter message to send"
            
            onAccepted: {
                if (text.trim() !== "") {
                    sendMessage(text.trim());
                    text = "";
                }
            }
        }
        
        Button {
            text: "Send"
            
            onClicked: {
                if (messageInput.text.trim() !== "") {
                    sendMessage(messageInput.text.trim());
                    messageInput.text = "";
                }
            }
        }
    }
}