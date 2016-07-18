/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtEnginio module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtQuick.Window 2.2
import QtQml.Models 2.1

Window {
    id:loginWindow
    width : 430
    height : 330
    property real scaleFactor: Screen.pixelDensity / 5.0
    property int intScaleFactor: Math.max(1, scaleFactor)
    visible: true
    property string username
    property string password

    Rectangle {
        width: parent.width
        height: parent.height

        color: "lavender"

        Rectangle {

            id: header
            height: 180
            anchors.top: parent.top
            width: parent.width
            color: "#6495ED"
            visible: true

            Text {
                id: headText
                anchors.centerIn: parent
                color: "white"
                font.family: "微软雅黑"
                font.pointSize: 40
                text: "Niao Air"
            }
        }

        Column {
            id: inputcol
            anchors.top: header.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 15
            anchors.alignWhenCentered: true
            spacing: 0

            TextField {
                id: nameInput
                onAccepted: passwordInput.forceActiveFocus()
                placeholderText: "Username"
                KeyNavigation.tab: passwordInput
            }

            TextField {
                id: passwordInput
                onAccepted: login()
                placeholderText: "Password"
                echoMode: TextInput.Password
                KeyNavigation.tab: loginButton
            }
        }

        TouchButton {
            id: loginButton
            text: "Login"
            baseColor: "dodgerblue"
            width: 193
            height: 30
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: inputcol.bottom
            anchors.topMargin: 10
            onClicked: login()
            enabled: (nameInput.text.length > 0) && (passwordInput.text.length > 0)
            KeyNavigation.tab: registerButton
        }
    }

    Text {
        id: statusText
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 5 * scaleFactor
        font.pixelSize: 15 * scaleFactor
        color: "mediumslateblue"
        font.family: "微软雅黑"
    }

    function login() {
        statusText.text = "Logging in..."
        username = nameInput.text
        password = passwordInput.text

        //logData.refresh()
        //controller.trySendMessage()
        var result =loginController.tryLogin(username,password)
        statusText.text = result
        if(result){
            Qt.createComponent("main.qml").createObject();
            loginWindow.visible=false;
            //parent.destroy();
            //QT.quit();
        }
    }

    // Register a new user and add her to the group "allUsers"
    function registerAndLogin() {
        statusText.text = "Creating user account..."

    }
}


