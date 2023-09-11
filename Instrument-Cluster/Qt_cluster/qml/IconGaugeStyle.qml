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
    id: batteryGaugeStyle

    // Gauge properties
    minimumValueAngle: -60
    maximumValueAngle: 60
    tickmarkStepSize: 25
    labelStepSize: 1
    labelInset: toPixels(-0.25)
    minorTickmarkCount: 3

    needleLength: toPixels(0.85)
    needleBaseWidth: toPixels(0.08)
    needleTipWidth: toPixels(0.03)

    halfGauge: true

    // Custom properties for warnings and icons
    property string icon: ""
    property color minWarningColor: "transparent"
    property color maxWarningColor: "transparent"
    readonly property real minWarningStartAngle: minimumValueAngle - 90
    readonly property real maxWarningStartAngle: maximumValueAngle - 90

    // Define the appearance of major tickmarks
    tickmark: Rectangle {
        implicitWidth: toPixels(0.05)
        antialiasing: true
        implicitHeight: toPixels(0.15)
        color: "#c8c8c8"
    }

    // Define the appearance of minor tickmarks
    minorTickmark: Rectangle {
        implicitWidth: toPixels(0.03)
        antialiasing: true
        implicitHeight: toPixels(0.10)
        color: "#c8c8c8"
    }

    // Define the background of the gauge
    background: Item {
        // Use a Canvas for custom drawing
        Canvas {
            anchors.fill: parent
            // Define a handler for painting the gauge's background
            onPaint: {
                var ctx = getContext("2d");
                ctx.reset();
                paintBackground(ctx);

                // Draw warning zones if specified
                if (minWarningColor != "transparent") {
                    // Draw the minimum warning zone
                    ctx.beginPath();
                    ctx.lineWidth = batteryGaugeStyle.toPixels(0.08);
                    ctx.strokeStyle = minWarningColor;
                    ctx.arc(outerRadius, outerRadius,
                        // Start the line in from the decorations, and account for the width of the line itself.
                        outerRadius - tickmarkInset - ctx.lineWidth / 2,
                        degToRad(minWarningStartAngle),
                        degToRad(minWarningStartAngle + angleRange / (minorTickmarkCount + 1)), false);
                    ctx.stroke();
                }
                if (maxWarningColor != "transparent") {
                    // Draw the maximum warning zone)
                    ctx.beginPath();
                    ctx.lineWidth = batteryGaugeStyle.toPixels(0.08);
                    ctx.strokeStyle = maxWarningColor;
                    ctx.arc(outerRadius, outerRadius,
                        // Start the line in from the decorations, and account for the width of the line itself.
                        outerRadius - tickmarkInset - ctx.lineWidth / 2,
                        degToRad(maxWarningStartAngle - angleRange / (minorTickmarkCount + 1)),
                        degToRad(maxWarningStartAngle), false);
                    ctx.stroke();
                }
            }
        }

        // Display an image (icon) on the background
        Image {
            source: icon
            anchors.bottom: parent.verticalCenter
            anchors.bottomMargin: toPixels(0)
            anchors.horizontalCenter: parent.horizontalCenter
            width: toPixels(0.8)
            height: width
            fillMode: Image.PreserveAspectFit
        }
    }
}
