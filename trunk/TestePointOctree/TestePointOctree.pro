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
    GLSLKernel \
    interface \
    openGLFrame

# Input
HEADERS += interface/myMainWindow.hpp \
    openGLFrame/GLFrame.hpp \
    math/Vector3.hpp \
    lcgOctree/ocTree.hpp \
    lcgOctree/ocTreeIntersection.hpp \
    math/Point3.hpp \
    math/Matrix3x3.hpp \
    math/BoundingBox3.hpp \
    lcgOctree/ocTreeBox.hpp \
    surfels/surfel.hpp \
    surfels/ply.h \
    surfels/surfels.hpp \
    lcgOctree/ocTreeInternalNode.hpp \
    lcgOctree/ocTreeLeafNode.hpp \
    lcgOctree/ocTreeNode.hpp \
    lcgOctree/ocTreeIterator.hpp \
    lcgOctree/ocTreeRefine.hpp \
    surfels/MergeEllipses.hpp \
    Scene/Camera.hpp \
    Scene/Trackball.hpp \
    math/Color.hpp \
    math/EigenSystem.hpp \
    math/Matrix4x4.hpp \
    math/Vector4.hpp \
    math/Quaternion.hpp \
    math/Math.hpp \
    math/Vector2.hpp \
    math/Point2.hpp \
    math/Vector2.hpp
SOURCES += main.cpp \
    interface/myMainWindow.cpp \
    openGLFrame/GLFrame.cpp \
    openGLFrame/support/arcball.cpp \
    surfels/ply.c \
    Scene/Camera.cpp \
    Scene/Trackball.cpp \
    math/Quaternion.cpp \
    math/Math.cpp \
    math/Vector3.cpp \
    math/Point2.cpp \
    math/Vector4.cpp \
    math/Matrix3x3.cpp \
    math/Matrix4x4.cpp \
    math/Point3.cpp \
    math/Vector2.cpp
QT += opengl
FORMS += ui/interface.ui

# matrixLibrary/Vector3.cpp
# LIBRARIES
unix:LIBS = -LGLSLKernel \
    -lglslKernel

# Output
unix:MOC_DIR = .moc
unix:OBJECTS_DIR = .obj
unix:UI_HEADERS_DIR = .ui
