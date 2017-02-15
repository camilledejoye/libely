#-------------------------------------------------
#
# Project created by QtCreator 2015-03-08T19:53:39
#
#-------------------------------------------------

CONFIG(debug, debug|release):TARGET = elyd
else:CONFIG(release, debug|release):TARGET = ely
TEMPLATE = lib
CONFIG += staticlib
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

win32:target.path = $(PWD)/lib/
else:unix:target.path = $(PWD)/lib/
INSTALLS += target

win32:INCLUDEPATH += D:/dev/boost_1_57_0/include

SOURCES += \
    ely/date_time/Date.cpp \
    ely/exceptions/ContractException.cpp \
    ely/exceptions/LogicException.cpp \
    ely/file_system/File.cpp \
    ely/file_system/Path.cpp \
    ely/file_system/FilePath.cpp \
    ely/utilities/NoLogPolicy.cpp \
    ely/utilities/DebugLogPolicy.cpp \
    ely/utilities/log.cpp \
    ely/file_system/AbstractFile.cpp

OTHER_FILES += \
    ely/patterns/Factory.tpp \
    ely/patterns/Singleton.tpp \
    ely/patterns/Composite.tpp \
    ely/signals_slots/Signal.tpp \
    ely/signals_slots/Slot.tpp \
    ely/signals_slots/connect.tpp \
    ely/signals_slots/AbstractCallableObject.tpp

HEADERS += \
    ely/date_time/exception/DateException.hpp \
    ely/date_time/exception/DateTimeException.hpp \
    ely/date_time/exception/InvalidMonthException.hpp \
    ely/date_time/Date.hpp \
    ely/date_time/DateIterator.hpp \
    ely/exceptions/ContractException.hpp \
    ely/exceptions/exceptions.hpp \
    ely/exceptions/LogicException.hpp \
    ely/file_system/File.hpp \
    ely/patterns/Cloneable.hpp \
    ely/patterns/Factory.hpp \
    ely/patterns/Singleton.hpp \
    ely/predicates/EqualTo.hpp \
    ely/predicates/IsNull.hpp \
    ely/traits/NullValue.hpp \
    ely/traits/Type.hpp \
    ely/utilities/contracts.hpp \
    ely/utilities/ElyLog.hpp \
    ely/utilities/log.hpp \
    ely/utilities/LogPolicies.hpp \
    ely/utilities/utilities.hpp \
    ely/config.hpp \
    ely/patterns/Composite.hpp \
    ely/file_system/Path.hpp \
    ely/file_system/FilePath.hpp \
    ely/utilities/NoLogPolicy.hpp \
    ely/utilities/DebugLogPolicy.hpp \
    ely/utilities/FileLogPolicy.hpp \
    ely/file_system/AbstractFile.hpp \
    ely/signals_slots/Signal.hpp \
    ely/signals_slots/Slot.hpp \
    ely/signals_slots/connect.hpp \
    ely/signals_slots/AbstractCallableObject.hpp \
    ely/signals_slots/SignalsSlots.hpp \
    ely/utilities/bind.hpp \
    ely/utilities/IntegerSequence.hpp
