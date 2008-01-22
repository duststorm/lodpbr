# #####################################################################
# Automatically generated by qmake (2.01a) Sun Jul 8 12:01:19 2007
# #####################################################################
TEMPLATE = app
TARGET = 
DEPENDPATH += . \
    ui \
    .ui \
    interface \
    openGLFrame \
    openGLFrame/suport
INCLUDEPATH += . \
    ui \
    .ui \
    interface \
    openGLFrame \
    openGLFrame/suport
QT += opengl

# Input
HEADERS += interface/myMainWindow.hpp \
    openGLFrame/GLFrame.hpp \
    openGLFrame/support/arcball.hpp \
    openGLFrame/support/atmatrix.hpp \
    mycgal/polyhedron.h \
    mycgal/support/id.h \
    matrixLibrary/Vector3.hpp
FORMS += ui/interface.ui
SOURCES += main.cpp \
    interface/myMainWindow.cpp \
    openGLFrame/GLFrame.cpp \
    openGLFrame/support/arcball.cpp \
    mycgal/polyhedron.cpp \
    mycgal/support/id.cpp \
    matrixLibrary/Vector3.cpp

# matrixLibrary/Vector3.cpp
# LIBRARIES
unix:LIBS = -lCGAL

# Output
unix:MOC_DIR = .moc
unix:OBJECTS_DIR = .obj
unix:UI_HEADERS_DIR = .ui
