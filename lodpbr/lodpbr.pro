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
    Interface \
    OpenGLFrame

# Input
HEADERS += Interface/myMainWindow.hpp \
    OpenGLFrame/GLFrame.hpp \
    Math/Vector3.hpp \
    Octree/ocTree.hpp \
    Octree/ocTreeIntersection.hpp \
    Math/Point3.hpp \
    Math/Matrix3x3.hpp \
    Math/BoundingBox3.hpp \
    Octree/ocTreeBox.hpp \
    Surfels/surfel.hpp \
    Surfels/ply.h \
    Surfels/surfels.hpp \
    Octree/ocTreeInternalNode.hpp \
    Octree/ocTreeLeafNode.hpp \
    Octree/ocTreeNode.hpp \
    Octree/ocTreeIterator.hpp \
    Octree/ocTreeRefine.hpp \
    Surfels/MergeEllipses.hpp \
    Scene/Camera.hpp \
    Scene/Trackball.hpp \
    Math/Color.hpp \
    Math/EigenSystem.hpp \
    Math/Matrix4x4.hpp \
    Math/Vector4.hpp \
    Math/Quaternion.hpp \
    Math/Math.hpp \
    Math/Vector2.hpp \
    Math/Point2.hpp \
    Math/Vector2.hpp \
    Kd-Tree/Kd-Tree.hpp \
    Kd-Tree/Kd-TreeNode.hpp \
    Kd-Tree/Kd-TreeRefine.hpp \
    Clustering/Cluster.hpp \
    Clustering/ClusterCriteria.hpp \
    GLSLKernel/glslKernel.h \
    GLSLKernel/GLee.h
SOURCES += main.cpp \
    Interface/myMainWindow.cpp \
    OpenGLFrame/GLFrame.cpp \
    OpenGLFrame/support/arcball.cpp \
    Surfels/ply.c \
    Scene/Camera.cpp \
    Scene/Trackball.cpp \
    Math/Quaternion.cpp \
    Math/Math.cpp \
    Math/Vector3.cpp \
    Math/Point2.cpp \
    Math/Vector4.cpp \
    Math/Matrix3x3.cpp \
    Math/Matrix4x4.cpp \
    Math/Point3.cpp \
    Math/Vector2.cpp \
    Clustering/Cluster.cpp \
    GLSLKernel/glslKernel.cc \
    GLSLKernel/GLee.c
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
