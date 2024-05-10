
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = nj-tox-data

include(../build-group.pri)


QT += gui widgets webenginewidgets location

exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)

exists($$ROOT_DIR/../preferred/openssl.pri): include($$ROOT_DIR/../preferred/openssl.pri)

CONFIG += c++17


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$SRC_PROSET_DIR/../qmt-apache/qmt-native-client/MapGraphics

INCLUDEPATH += $$SRC_DIR/qmt-client


INCLUDEPATH += $$NTXH_SRC_GROUP_DIR
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR/ntxh
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR



CONFIG += no_keywords

DEFINES += USE_KANS

DEFINES += SCREENSHOTS_FOLDER=\\\"$$ROOT_DIR/../dev/zq\\\"
DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"



INCLUDEPATH += /home/nlevisrael/docker/gits/qtcsv/install/include
LIBS += -L/home/nlevisrael/docker/gits/qtcsv/install/lib -lqtcsv



HEADERS += \
  $$SRC_DIR/nj-tox-site.h \
  $$SRC_DIR/nj-tox-site-list.h \
  $$SRC_DIR/nj-tri-site.h \
  $$SRC_DIR/nj-tri-site-list.h \
  $$SRC_DIR/site-list-base.h \


SOURCES += \
  $$SRC_DIR/nj-tox-site.cpp \
  $$SRC_DIR/nj-tox-site-list.cpp \
  $$SRC_DIR/nj-tri-site.cpp \
  $$SRC_DIR/nj-tri-site-list.cpp \

#$$SRC_DIR/site-list-base.cpp \




message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

