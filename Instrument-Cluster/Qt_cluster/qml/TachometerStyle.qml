/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
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
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
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

import QtQuick 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

// Define a custom style for a dashboard-style gauge
DashboardGaugeStyle {
    id: rpmGaugeStyle

    // Gauge properties
    tickmarkStepSize: 50
    minorTickmarkCount: 3
    labelStepSize: 50
    needleLength: toPixels(0.85)
    needleBaseWidth: toPixels(0.08)
    needleTipWidth: toPixels(0.03)

    // Define the appearance of major tickmarks
    tickmark: Rectangle {
        implicitWidth: toPixels(0.03)
        antialiasing: true
        implicitHeight: toPixels(0.08)
        color: "#c8c8c8"
    }

    // Define the appearance of minor tickmarks
    minorTickmark: Rectangle {
        implicitWidth: toPixels(0.03)
        antialiasing: true
        implicitHeight: toPixels(0.04)
        color: "#c8c8c8"
    }

    // Define the appearance of tickmark labels
    tickmarkLabel: Text {
        font.pixelSize: Math.max(6, toPixels(0.12))
        text: styleData.value
        color: "#c8c8c8"
        antialiasing: true
    }

    // Define the background of the gauge using a Canvas
    background: Canvas {
        // Define a handler for painting the gauge's background
        onPaint: {
            // Get the 2D rendering context
            var ctx = getContext("2d");
            ctx.reset();
            paintBackground(ctx);

            // Draw a warning zone on the background
            ctx.beginPath();
            ctx.lineWidth = rpmGaugeStyle.toPixels(0.08);
            ctx.strokeStyle = Qt.rgba(0.5, 0, 0, 1);
            var warningCircumference = maximumValueAngle - minimumValueAngle * 0.1;
            var startAngle = maximumValueAngle - 86;
            ctx.arc(outerRadius, outerRadius,
                outerRadius - tickmarkInset - ctx.lineWidth / 2,
                degToRad(startAngle - angleRange / 8 + angleRange * 0.015),
                degToRad(startAngle - angleRange * 0.015), false);
            ctx.stroke();
        }

        // Display RPM value and label on the background
        Text {
            id: rpmText
            font.pixelSize: rpmGaugeStyle.toPixels(0.3)
            text: rpmInt
            color: "white"
            horizontalAlignment: Text.AlignRight
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.verticalCenter
            anchors.topMargin: 20

            // Bind the RPM value to the gauge
            readonly property int rpmInt: valueSource.rpm
        }
        Text {
            text: "RPM"
            color: "white"
            font.pixelSize: rpmGaugeStyle.toPixels(0.3)
            anchors.top: rpmText.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
