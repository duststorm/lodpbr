

VCGDIR = /home/fmc/workspace/vcglib

MESHLABSRCDIR = /home/fmc/workspace/meshlab/src


# LIBRARIES
unix{
	LIBS = -L/usr/lib64 -lGLEW 
	QMAKE_CXXFLAGS += -fpermissive
}

# Output
unix{
	MOC_DIR = .tmp\.moc
	OBJECTS_DIR = .tmp\.obj
	UI_HEADERS_DIR = .tmp\.ui
}