TEMPLATE = lib

CONFIG += c++11 console
CONFIG -= app_bundle

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/include/GL

SOURCES += src/GLBatch.cpp \
    src/GLShaderManager.cpp \
    src/GLTools.cpp \
    src/GLTriangleBatch.cpp \
    src/math3d.cpp \
    src/glew.c

HEADERS += \
    include/GLBatch.h \
    include/GLBatchBase.h \
    include/GLFrame.h \
    include/GLFrustum.h \
    include/GLGeometryTransform.h \
    include/GLMatrixStack.h \
    include/GLShaderManager.h \
    include/GLTools.h \
    include/GLTriangleBatch.h \
    include/math3d.h \
    include/StopWatch.h

LIBS = -lX11 -lglut -lGL -lGLU -lm
