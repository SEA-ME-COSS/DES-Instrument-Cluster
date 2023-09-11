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

// Define a custom style for a CircularGauge
CircularGaugeStyle {
    // Gauge properties
    tickmarkInset: toPixels(0.04)
    minorTickmarkInset: tickmarkInset
    labelStepSize: 20
    labelInset: toPixels(0.23)

    property real xCenter: outerRadius
    property real yCenter: outerRadius
    property real needleLength: outerRadius - tickmarkInset * 1.25
    property real needleTipWidth: toPixels(0.02)
    property real needleBaseWidth: toPixels(0.06)
    property bool halfGauge: false

    // Define a function to convert a percentage to pixels
    function toPixels(percentage) {
        return percentage * outerRadius;
    }

    // Define a function to convert degrees to radians
    function degToRad(degrees) {
        return degrees * (Math.PI / 180);
    }

    // Define a function to convert radians to degrees
    function radToDeg(radians) {
        return radians * (180 / Math.PI);
    }

    // Define a function to paint the gauge's background
    function paintBackground(ctx) {
        // Drawing the gauge's background elements
        if (halfGauge) {
            ctx.beginPath();
            ctx.rect(0, 0, ctx.canvas.width, ctx.canvas.height / 2);
            ctx.clip();
        }
    }

    // Define the gauge's background using a Canvas
    background: Canvas {
        // Define a handler for painting the background
        onPaint: {
            // Get the 2D rendering context
            var ctx = getContext("2d");
            ctx.reset();
            paintBackground(ctx);
        }

        // Text elements for displaying speed value and units
        Text {
            id: speedText
            font.pixelSize: toPixels(0.3)
            text: kphInt
            color: "white"
            horizontalAlignment: Text.AlignRight
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.verticalCenter
            anchors.topMargin: toPixels(0.1)

            readonly property int kphInt: control.value
        }
        Text {
            text: "mm/s"
            color: "white"
            font.pixelSize: toPixels(0.2)
            anchors.top: speedText.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    // Define the gauge's needle using a Canvas
    needle: Canvas {
        implicitWidth: needleBaseWidth
        implicitHeight: needleLength

        property real xCenter: width / 2
        property real yCenter: height / 2

        // Define a handler for painting the needle
        onPaint: {
            // Get the 2D rendering context
            var ctx = getContext("2d");
            ctx.reset();

            // Drawing the gauge's needle
            ctx.beginPath();
            ctx.moveTo(xCenter, height);
            ctx.lineTo(xCenter - needleBaseWidth / 2, height - needleBaseWidth / 2);
            ctx.lineTo(xCenter - needleTipWidth / 2, 0);
            ctx.lineTo(xCenter, yCenter - needleLength);
            ctx.lineTo(xCenter, 0);
            ctx.closePath();
            ctx.fillStyle = Qt.rgba(0.66, 0, 0, 0.66);
            ctx.fill();

            ctx.beginPath();
            ctx.moveTo(xCenter, height)
            ctx.lineTo(width, height - needleBaseWidth / 2);
            ctx.lineTo(xCenter + needleTipWidth / 2, 0);
            ctx.lineTo(xCenter, 0);
            ctx.closePath();
            ctx.fillStyle = Qt.lighter(Qt.rgba(0.66, 0, 0, 0.66));
            ctx.fill();
        }
    }

    // Set the gauge's foreground to null (no additional foreground elements)
    foreground: null
}
