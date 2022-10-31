add_compile_definitions(CURRENTDIR="${CMAKE_CURRENT_SOURCE_DIR}")

find_package(QT NAMES Qt6 6.2 Qt5 5.12 CONFIG REQUIRED
    Core
    Gui
    Multimedia
    PrintSupport
    Widgets
    Test
)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED
    Core
    Gui
    Multimedia
    PrintSupport
    Widgets
    Test
)

add_executable(wiredpanda-test
    testmain.cpp
    testcommands.cpp
    testelements.cpp
    testfiles.cpp
    testicons.cpp
    testlogicelements.cpp
    testsimulation.cpp
    testwaveform.cpp

    ../app/application.cpp
    ../app/bewaveddolphin.cpp
    ../app/clockdialog.cpp
    ../app/commands.cpp
    ../app/common.cpp
    ../app/elementeditor.cpp
    ../app/elementfactory.cpp
    ../app/elementmapping.cpp
    ../app/enums.cpp
    ../app/graphicelement.cpp
    ../app/graphicelementinput.h
    ../app/graphicsview.cpp
    ../app/ic.cpp
    ../app/itemwithid.cpp
    ../app/lengthdialog.cpp
    ../app/logicelement.cpp
    ../app/mainwindow.cpp
    ../app/recentfiles.cpp
    ../app/scene.cpp
    ../app/serialization.cpp
    ../app/settings.cpp
    ../app/simulation.cpp
    ../app/simulationblocker.cpp
    ../app/thememanager.cpp
    ../app/workspace.cpp
    ../app/trashbutton.cpp
    ../app/elementlabel.cpp

    ../app/arduino/codegenerator.cpp

    ../app/nodes/qneconnection.cpp
    ../app/nodes/qneport.cpp

    ../app/logicelement/logicand.cpp
    ../app/logicelement/logicdemux.cpp
    ../app/logicelement/logicdflipflop.cpp
    ../app/logicelement/logicdlatch.cpp
    ../app/logicelement/logicinput.cpp
    ../app/logicelement/logicjkflipflop.cpp
    ../app/logicelement/logicmux.cpp
    ../app/logicelement/logicnand.cpp
    ../app/logicelement/logicnode.cpp
    ../app/logicelement/logicnor.cpp
    ../app/logicelement/logicnot.cpp
    ../app/logicelement/logicor.cpp
    ../app/logicelement/logicoutput.cpp
    ../app/logicelement/logicsrflipflop.cpp
    ../app/logicelement/logictflipflop.cpp
    ../app/logicelement/logicxnor.cpp
    ../app/logicelement/logicxor.cpp

    ../app/element/and.cpp
    ../app/element/buzzer.cpp
    ../app/element/clock.cpp
    ../app/element/demux.cpp
    ../app/element/dflipflop.cpp
    ../app/element/display_7.cpp
    ../app/element/display_14.cpp
    ../app/element/dlatch.cpp
    ../app/element/inputbutton.cpp
    ../app/element/inputgnd.cpp
    ../app/element/inputrotary.cpp
    ../app/element/inputswitch.cpp
    ../app/element/inputvcc.cpp
    ../app/element/jkflipflop.cpp
    ../app/element/led.cpp
    ../app/element/line.cpp
    ../app/element/mux.cpp
    ../app/element/nand.cpp
    ../app/element/node.cpp
    ../app/element/nor.cpp
    ../app/element/not.cpp
    ../app/element/or.cpp
    ../app/element/srflipflop.cpp
    ../app/element/text.cpp
    ../app/element/tflipflop.cpp
    ../app/element/xnor.cpp
    ../app/element/xor.cpp
	
    ../app/resources/basic/basic.qrc
    ../app/resources/dolphin/dolphin.qrc
    ../app/resources/input/input.qrc
    ../app/resources/memory/dark/memory_dark.qrc
    ../app/resources/memory/light/memory_light.qrc
    ../app/resources/misc/misc.qrc
    ../app/resources/output/output.qrc
    ../app/resources/toolbar/toolbar.qrc
)

target_link_libraries(wiredpanda-test
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::PrintSupport
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Test
)
