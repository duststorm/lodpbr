# #####################################################################
# Automatically generated by qmake (2.01a) Sun Jul 8 12:01:19 2007
# #####################################################################
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

# Input
HEADERS += . \
    interface/myMainWindow.hpp \
    openGLFrame/GLFrame.hpp \
    openGLFrame/support/arcball.hpp \
    openGLFrame/support/atmatrix.hpp \
    slal/Vector3.hpp \
    lcgOctree/ocTree.hpp \
    lcgOctree/ocTreeIntersection.hpp \
    slal/Point3.hpp \
    slal/Matrix3x3.hpp \
    slal/BoundingBox3.hpp \
    lcgOctree/ocTreeBox.hpp \
    surfels/surfel.hpp \
    surfels/ply.h \
    surfels/surfels.hpp \
    lcgOctree/ocTreeInternalNode.hpp \
    lcgOctree/ocTreeLeafNode.hpp \
    lcgOctree/ocTreeNode.hpp \
    lcgOctree/ocTreeIterator.hpp \
    lcgOctree/ocTreeRefine.hpp \
    slal/Color.hpp \
    slal/EigenSystem.hpp \
    surfels/MergeEllipses.hpp \
    slal/Matrix4x4.hpp \
    slal/Vector4.hpp \
    slal/Camera.hpp \
    slal/Trackball.hpp \
    slal/Trackball.inline.hpp \
    slal/Quaternion.hpp \
    slal/Quaternion.inline.hpp \
    slal/Math.hpp \
    slal/Vector2.hpp \
    slal/Point2.hpp
SOURCES += main.cpp \
    interface/myMainWindow.cpp \
    openGLFrame/GLFrame.cpp \
    openGLFrame/support/arcball.cpp \
    surfels/ply.c \
    slal/Camera.cpp \
    slal/Quaternion.cpp \
    slal/Trackball.cpp \
    slal/Math.cpp
QT += opengl
FORMS += ui/interface.ui

# matrixLibrary/Vector3.cpp
# LIBRARIES
unix:LIBS = -lCGAL \
    -llapack

# Output
unix:MOC_DIR = .moc
unix:OBJECTS_DIR = .obj
unix:UI_HEADERS_DIR = .ui
