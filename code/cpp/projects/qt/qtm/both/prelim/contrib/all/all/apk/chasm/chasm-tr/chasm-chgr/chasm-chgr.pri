
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


PROJECT_NAME = chasm-chgr

include(../build-group.pri)


exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)



CONFIG += c++17


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR


INCLUDEPATH += $$SRC_GROUP_DIR/chasm-tr

INCLUDEPATH += $$SRC_PROSET_DIR/chasm-vm
INCLUDEPATH += $$SRC_PROSET_DIR/chasm-lib


CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_AQNS

DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"
DEFINES += DEMO_CVM_FOLDER=\\\"$$ROOT_DIR/../chtr\\\"


HEADERS += \
  $$SRC_DIR/chgr-hypernode.h \
  $$SRC_DIR/chgr-environment.h \
  $$SRC_DIR/chgr-mempad.h \


SOURCES += \
  $$SRC_DIR/chgr-hypernode.cpp \
  $$SRC_DIR/chgr-environment.cpp \
  $$SRC_DIR/chgr-mempad.cpp \


LIBS += -L$$TARGETSDIR -lchasm-tr  -lchasm-tr-parser


LIBS += -L$$TARGETSDIR -lchasm-lib \
  -lchasm-vm -lchasm-runtime-bridge -lchasm-procedure-table \
  -lchasm-lib-X1 -lchasm-lib-X2 \
  -lchasm-lib-33 -lchasm-lib-43




message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
