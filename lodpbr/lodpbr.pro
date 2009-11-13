# #####################################################################
# Automatically generated by qmake (2.01a) Sun Jul 8 12:01:19 2007
# #####################################################################



TARGET = lodpbr
DEPENDPATH += . \
    Qt/UI 	\
    .tmp/.ui 	\
    QtGui 	\
    QtGui/GLWidget\
    ThirdParty/vcglib	\
    ThirdParty/vcglib/vcg \
    ThirdParty/vcglib/wrap	
     

INCLUDEPATH += . \
    Qt/UI	\
    .tmp/.ui 	\
    QtGui 	\
    QtGui/GLWidget \
    ThirdParty/vcglib	

# Input
HEADERS += Math/Math.hpp \
    Math/Color.hpp \
    Math/Vector2.hpp \
    Math/Vector3.hpp \
    Math/Vector4.hpp \
    Math/Point2.hpp \
    Math/Point3.hpp \
    Math/Matrix3x3.hpp \
    Math/Matrix4x4.hpp \
    Math/Quaternion.hpp \
    Math/BoundingBox3.hpp \
    Math/EigenSystem.hpp \
    Scene/Camera.hpp \
    Scene/Trackball.hpp \
    Octree/ocTreeIntersection.hpp \
    Octree/ocTreeBox.hpp \
    Octree/ocTreeIterator.hpp \
    Octree/ocTreeNode.hpp \
    Octree/ocTreeLeafNode.hpp \
    Octree/ocTreeInternalNode.hpp \
    Octree/ocTreeRefine.hpp \
    Octree/ocTree.hpp \
    Kd-Tree/Kd-TreeOfSurfels.hpp \
    Kd-Tree/Kd-TreeOfSurfelsNode.hpp \
    Kd-Tree/Kd-TreeOfSurfelsRefine.hpp \
    Surfels/Surfel.hpp \
    Surfels/IOSurfels.hpp \
    Surfels/MergeEllipses.hpp \
    Clustering/Cluster.hpp \
    Clustering/ClusterCriteria.hpp \
    Qt/Tools/FPSCounter.h\	
    Qt/Tools/BitMask.hpp\
    Qt/GLWidget/GLWidget.hpp \
    Qt/GLWidget/WidgetProxy.hpp \
    Qt/GLWidget/Log/ClusterLog.hpp \
    Qt/GLWidget/Log/LSplatLog.hpp \
    Qt/myMainWindow.hpp \
    ThirdParty/vcglib/wrap/io_trimesh/import_ply.h \
    ThirdParty/vcglib/wrap/io_trimesh/export_ply.h \
    ThirdParty/vcglib/wrap/ply/plylib.h

SOURCES += main.cpp \
    Math/Math.cpp \
    Math/Vector2.cpp \
    Math/Vector3.cpp \
    Math/Vector4.cpp \
    Math/Point2.cpp \
    Math/Point3.cpp \
    Math/Matrix3x3.cpp \
    Math/Matrix4x4.cpp \
    Math/Quaternion.cpp \
    Clustering/Cluster.cpp \
    Scene/Camera.cpp \
    Scene/Trackball.cpp \
    Qt/Tools/FPSCounter.cpp\
    Qt/GLWidget/GLWidget.cpp \
    Qt/GLWidget/WidgetProxy.cpp \
    Qt/GLWidget/Log/ClusterLog.cpp \
    Qt/GLWidget/Log/LSplatLog.cpp \
    Qt/myMainWindow.cpp \
    Qt/myMainWindowInit.cpp \
    ThirdParty/vcglib/wrap/ply/plylib.cpp

QT += opengl
FORMS += Qt/UI/lodpbr.ui

# LIBRARIES
unix{
	LIBS = 
}

# Output
unix{
	MOC_DIR = .tmp\.moc
	OBJECTS_DIR = .tmp\.obj
	UI_HEADERS_DIR = .tmp\.ui
}

