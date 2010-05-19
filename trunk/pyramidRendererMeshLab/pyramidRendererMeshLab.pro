include(shared.pri)

TEMPLATE = app
TARGET = pyramidRendererMeshLab


FORMS += Qt/UI/pyramidRendererMeshLab.ui

DEPENDPATH += Qt/UI	 \
		render_splatpyramid \
		render_splatpyramid/Surfel \
    	.tmp/.ui 	 \
    	$$VCGDIR	 \
    	$$VCGDIR/vcg \
    	$$VCGDIR/wrap
    	
INCLUDEPATH += Qt/UI\
		render_splatpyramid \
		render_splatpyramid/Surfel \
    	.tmp/.ui 	\
    	$$VCGDIR
    
QT += core \
    gui \
    opengl
    
HEADERS += Qt/MainWindow.hpp \
    Qt/GLWidget/GLWidget.hpp \
    Celer/Math/BoundingBox3.hpp \
    Celer/Math/Color.hpp \
    Celer/Math/EigenSystem.hpp \
    Celer/Math/Math.hpp \
    Celer/Math/Matrix3x3.hpp \
    Celer/Math/Matrix4x4.hpp \
    Celer/Math/OrientedBoundingBox3.hpp \
    Celer/Math/Point2.hpp \
    Celer/Math/Point3.hpp \
    Celer/Math/Quaternion.hpp \
    Celer/Math/Vector2.hpp \
    Celer/Math/Vector3.hpp \
    Celer/Math/Vector4.hpp \
    Celer/Scene/Camera.hpp \
    Celer/Scene/Frustum.hpp \
    Celer/Scene/Trackball.hpp\
    render_splatpyramid/Surfels/Surfel.hpp\
    render_splatpyramid/Surfels/IOSurfels.hpp\
    render_splatpyramid/materials.h \
    render_splatpyramid/object.h \
    render_splatpyramid/point_based_renderer.h \
    render_splatpyramid/pyramid_point_renderer.h \
    render_splatpyramid/pyramid_point_renderer_base.h \
    render_splatpyramid/pyramid_point_renderer_color.h \
    render_splatpyramid/shaderStructs.h \
    $$VCGDIR/wrap/io_trimesh/import_ply.h \
    $$VCGDIR/wrap/io_trimesh/export_ply.h \
    $$VCGDIR/wrap/ply/plylib.h
    
    
SOURCES += Qt/MainWindow.cpp \
    Qt/GLWidget/GLWidget.cpp \
    Celer/Math/Math.cpp \
    Celer/Math/Matrix3x3.cpp \
    Celer/Math/Matrix4x4.cpp \
    Celer/Math/OrientedBoundingBox3.cpp \
    Celer/Math/Point2.cpp \
    Celer/Math/Point3.cpp \
    Celer/Math/Quaternion.cpp \
    Celer/Math/Vector2.cpp \
    Celer/Math/Vector3.cpp \
    Celer/Math/Vector4.cpp \
    Celer/Scene/Camera.cpp \
    Celer/Scene/Frustum.cpp \
    Celer/Scene/Trackball.cpp \
    render_splatpyramid/object.cc \
    render_splatpyramid/point_based_renderer.cc \
    render_splatpyramid/pyramid_point_renderer_base.cc \
    render_splatpyramid/pyramid_point_renderer_color.cc \
    render_splatpyramid/pyramid_point_renderer.cc \
    $$VCGDIR/wrap/ply/plylib.cpp\
    main.cpp

message(Qt version: $$[QT_VERSION])

