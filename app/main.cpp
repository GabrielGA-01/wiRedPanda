// Copyright 2015 - 2022, GIBIS-Unifesp and the WiRedPanda contributors
// SPDX-License-Identifier: GPL-3.0-or-later

#include "application.h"
#include "common.h"
#include "mainwindow.h"

#include <QCommandLineParser>
#include <QMessageBox>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

int main(int argc, char *argv[])
{
    Comment::setVerbosity(1); // change to -1 to disable comments

#ifdef Q_OS_WIN
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
#endif

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

    Application app(argc, argv);
    app.setOrganizationName("GIBIS-UNIFESP");
    app.setApplicationName("WiRedPanda");
    app.setApplicationVersion(APP_VERSION);
    app.setStyle("Fusion");

    try {
        QCommandLineParser parser;
        parser.setApplicationDescription(app.applicationName());
        parser.addHelpOption();
        parser.addVersionOption();
        parser.addPositionalArgument("file", QCoreApplication::translate("main", "Circuit file to open."));

        QCommandLineOption arduinoFileOption(
                    {"a", "arduino-file"},
                    QCoreApplication::translate("main", "Export circuit to <arduino-file>"),
                    QCoreApplication::translate("main", "arduino file"));
        parser.addOption(arduinoFileOption);

        QCommandLineOption waveformFileOption(
                    {"w", "waveform"},
                    QCoreApplication::translate("main", "Export circuit to <waveform> text file"),
                    QCoreApplication::translate("main", "waveform text file"));
        parser.addOption(waveformFileOption);

        parser.process(app);

        // TODO: process verbosity level/format

        QStringList args = parser.positionalArguments();
        auto *window = new MainWindow(nullptr, (!args.empty() ? QString(args[0]) : QString()));

        QString arduFile = parser.value(arduinoFileOption);
        if (!arduFile.isEmpty()) {
            if (!args.empty()) {
                window->loadPandaFile(args[0]);
                exit(!window->exportToArduino(arduFile));
            }
            exit(0);
        }
        QString wfFile = parser.value(waveformFileOption);
        if (!wfFile.isEmpty()) {
            if (!args.empty()) {
                window->loadPandaFile(args[0]);
                exit(!window->exportToWaveFormFile(wfFile));
            }
            exit(0);
        }
        window->show();
        if (!args.empty()) {
            window->loadPandaFile(args[0]);
        }
    } catch (std::exception &e) {
        QMessageBox::critical(nullptr, QObject::tr("Error!"), e.what());
        exit(1);
    }

    return app.exec();
}

/*
 * TODO: Tests for all elements
 * TODO: Create arduino version of all elements
 * TODO: Select some elements, and input wires become input buttons, output wires become leds... Connections are then
 * transferred to the IC's ports.
 */
