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
#include "commandlineoptions.h"

#include <QtCore/QDebug>
#include <QtCore/QMetaProperty>
#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>

CommandLineOptions::CommandLineOptions(QObject *parent)
    : QObject(parent)
    , propertyCount(metaObject()->propertyCount())
    , helpOption(false)
{
}

CommandLineOptions::~CommandLineOptions()
{
}

void CommandLineOptions::classBegin()
{
}

void CommandLineOptions::componentComplete()
{
    const QMetaObject *mo = metaObject();
    QCommandLineParser parser;
    if (helpOption)
        parser.addHelpOption();

    QByteArray defaultPropertyName;
    for (int i = propertyCount; i < mo->propertyCount(); i++) {
        QMetaProperty property = mo->property(i);
        QString optionName = QString::fromUtf8(property.name()).replace(QChar('_'), QChar('-'));
        switch (property.type()) {
        case QVariant::Bool:
            parser.addOption(QCommandLineOption(optionName));
            break;
        case QVariant::String:
            parser.addOption(QCommandLineOption(optionName, QString(), optionName, property.read(this).toString()));
            break;
        case QMetaType::QVariant:
            if (defaultPropertyName.isNull()) {
                int classInfoIndex = mo->indexOfClassInfo("DefaultProperty");
                if (classInfoIndex > -1) {
                    QMetaClassInfo classInfo = mo->classInfo(classInfoIndex);
                    defaultPropertyName = QByteArray(classInfo.value());
                    parser.addPositionalArgument(QString::fromUtf8(defaultPropertyName), QString());
                }
            }
            break;
        default:
            qWarning() << "type" << property.type() << "not supported yet.";
            break;
        }
    }

    QStringList args = QCoreApplication::arguments();
    args.removeFirst();
    parser.process(args);

    for (int i = propertyCount; i < mo->propertyCount(); i++) {
        QMetaProperty property = mo->property(i);
        QString optionName = QString::fromUtf8(property.name()).replace(QChar('_'), QChar('-'));
        if (defaultPropertyName == property.name()) {
            property.write(this, parser.positionalArguments());
        } else if (parser.isSet(optionName)) {
            switch (property.type()) {
            case QVariant::Bool:
                property.write(this, true);
                break;
            case QVariant::String:
                property.write(this, parser.value(optionName));
                break;
            default:
                break;
            }
        }
    }
}
