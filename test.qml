/* Copyright (c) 2014 Tasuku Suzuki
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Tasuku Suzuki nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL TASUKU SUZUKI BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
import QtQuick 2.0
import me.qtquick.CommandLineOptions 1.0

Rectangle {

    CommandLineOptions {
        id: cmo
        property bool boolOption
        property string stringOption: "default"
        property string string_option: "default"
        default property var options
    }

    width: 300
    height: 100
    Grid {
        anchors.fill: parent
        columns: 2
        spacing: 5
        Text {
            text: 'boolOption:'
        }
        Text {
            text: cmo.boolOption ? 'True' : 'False'
        }
        Text {
            text: 'stringOption:'
        }
        Text {
            text: cmo.stringOption
        }
        Text {
            text: 'string_option:'
        }
        Text {
            text: cmo.string_option
        }
        Text {
            text: '(options)'
        }
        Text {
            text: cmo.options.join(',')
        }
    }
}
