TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

#QMAKE_CXXFLAGS += -std=c++11

# For libely
INCLUDEPATH += $$PWD/../

LIBS += -L$$PWD/../

CONFIG(debug, debug|release):LIBS += -lelyd
else:CONFIG(release, debug|release):LIBS += -lely

# For boost
win32 {
    INCLUDEPATH += D:/dev/boost_1_57_0/include
    
    LIBS += -LD:/dev/boost_1_57_0/lib
    
    CONFIG(debug, debug|release):LIBS += D:/dev/boost_1_57_0/lib/libboost_unit_test_framework-mgw48-mt-d-1_57.a
    else:CONFIG(release, debug|release):LIBS += D:/dev/boost_1_57_0/lib/libboost_unit_test_framework-mgw48-mt-1_57.a
} else:unix {
    LIBS += -lboost_unit_test_framework
}


SOURCES += main.cpp \
    patterns/Cloneable.cpp \
    patterns/Factory.cpp \
    patterns/Singleton.cpp \
    predicates/EqualTo.cpp \
    predicates/IsNull.cpp \
    patterns/Composite.cpp \
    file_system/FilePath.cpp \
    file_system/Path.cpp \
    utilities/ElyLog.cpp \
    file_system/AbstractFile.cpp \
    signals_slots/SignalsSlots.cpp \
    utilities/IntegerSequence.cpp \
    utilities/bind.cpp

HEADERS +=

