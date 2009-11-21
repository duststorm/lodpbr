# #####################################################################
# Automatically generated by qmake (2.01a) Sun Jul 8 12:01:19 2007
# #####################################################################

VCGDIR = ../vcglib

TARGET = lodpbr
DEPENDPATH += . \
    Qt/UI 	\
    .tmp/.ui 	\
    QtGui 	\
    QtGui/GLWidget\
    $$VCGDIR	\
    $$VCGDIR/vcg \
    $$VCGDIR/wrap	
     

INCLUDEPATH += . \
    Qt/UI	\
    .tmp/.ui 	\
    QtGui 	\
    QtGui/GLWidget \
    $$VCGDIR	

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
    Surfels/Kd-Tree/Kd-Tree.hpp \
    Surfels/Kd-Tree/Kd-TreeNode.hpp \
    Surfels/Kd-Tree/Kd-TreeRefine.hpp \
    Surfels/Surfel.hpp \
    Surfels/IOSurfels.hpp \
    Surfels/MergeEllipses.hpp \
    Clustering/Cluster.hpp \
    Clustering/ClusterCriteria.hpp \
    Qt/Tools/FPSCounter.h\	
    Qt/Tools/BitMask.hpp\
    Qt/Tools/Settings.hpp\
    Qt/GLWidget/GLWidget.hpp \
    Qt/GLWidget/WidgetProxy.hpp \
    Qt/GLWidget/Log/ClusterLog.hpp \
    Qt/GLWidget/Log/LSplatLog.hpp \
    Qt/myMainWindow.hpp \
    $$VCGDIR/wrap/io_trimesh/import_ply.h \
    $$VCGDIR/wrap/io_trimesh/export_ply.h \
    $$VCGDIR/wrap/ply/plylib.h

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
    Qt/Tools/Settings.cpp\
    Qt/GLWidget/GLWidget.cpp \
    Qt/GLWidget/WidgetProxy.cpp \
    Qt/GLWidget/Log/ClusterLog.cpp \
    Qt/GLWidget/Log/LSplatLog.cpp \
    Qt/myMainWindow.cpp \
    Qt/myMainWindowRun.cpp \
    $$VCGDIR/wrap/ply/plylib.cpp

QT += opengl
FORMS += Qt/UI/lodpbr.ui

# LIBRARIES
unix{
	LIBS = -lboost_filesystem
}

# Output
unix{
	MOC_DIR = .tmp\.moc
	OBJECTS_DIR = .tmp\.obj
	UI_HEADERS_DIR = .tmp\.ui
}


