# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = Kactus2
DESTDIR = ./executable
QT += core gui xml xmlpatterns
CONFIG += debug
DEFINES += _WINDOWS QT_LARGEFILE_SUPPORT QT_DLL QT_XMLPATTERNS_LIB QT_XML_LIB QT_HAVE_MMX QT_HAVE_3DNOW QT_HAVE_SSE QT_HAVE_MMXEXT QT_HAVE_SSE2
INCLUDEPATH += . \
    ./debug \
    ./GeneratedFiles \
    ./vhdlGenerator \
    ./common/widgets/listManager \
    ./common/widgets/dirLineEdit \
    ./IPXactWrapper/ComponentEditor/fileSet \
    ./IPXactWrapper/ComponentEditor/channels \
    ./IPXactWrapper/ComponentEditor/views \
    ./common/delegates \
    ./common/widgets/attributeBox \
    ./common/views/EditableTableView \
    ./common/views/EditableListView \
    ./common/widgets/LibraryPathSelector \
    ./common/widgets/LibraryPathEditor \
    ./common/validators/LibraryPathValidator \
    ./common/widgets/EditorDockWidget \
    ./common/widgets/EditorScrollArea \
    ./common/widgets/ScanProgressWidget \
    ./IPXactWrapper/ComponentEditor/addressSpaces \
    ./common/widgets/ParameterEditor \
    ./common/widgets/ParameterGroupBox \
    ./IPXactWrapper/ComponentEditor/cpus \
    ./common/widgets/NumberLineEdit
LIBS += -L"."
DEPENDPATH += .
MOC_DIR += debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(Kactus2.pri)
win32:RC_FILE = Kactus2.rc
