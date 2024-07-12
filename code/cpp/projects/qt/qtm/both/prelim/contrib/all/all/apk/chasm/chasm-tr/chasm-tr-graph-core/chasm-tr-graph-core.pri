
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)

QT -= gui

exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)

CONFIG += c++17


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR

INCLUDEPATH += $$SRC_GROUP_DIR/chasm-tr-parser



CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_AQNS


DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


HEADERS += \
  $$SRC_DIR/kernel/dominion/types.h \
  $$SRC_DIR/kernel/dominion/connectors.h \
  $$SRC_DIR/code/chtr-prep-casement-entry.h \
  $$SRC_DIR/code/chtr-scoped-carrier.h \
  $$SRC_DIR/code/chtr-opaque-token.h \
  $$SRC_DIR/code/chtr-numeric-literal.h \
  $$SRC_DIR/code/chtr-core-macro.h \



SOURCES += \
  $$SRC_DIR/code/chtr-prep-casement-entry.cpp \
  $$SRC_DIR/code/chtr-scoped-carrier.cpp \
  $$SRC_DIR/code/chtr-opaque-token.cpp \
  $$SRC_DIR/code/chtr-numeric-literal.cpp \
  $$SRC_DIR/code/chtr-core-macro.cpp \





HEADERS += \
  $$SRC_DIR/kernel/chtr-dominion.h \
  $$SRC_DIR/kernel/frame/chtr-frame.h \
  $$SRC_DIR/kernel/query/chtr-query.h \
  $$SRC_DIR/kernel/graph/chtr-node.h \
  $$SRC_DIR/kernel/graph/chtr-graph.h \
  $$SRC_DIR/kernel/graph/chtr-asg-position.h \
  $$SRC_DIR/kernel/graph/chtr-connection.h \


SOURCES += \
  $$SRC_DIR/kernel/chtr-dominion.cpp \
  $$SRC_DIR/kernel/frame/chtr-frame.cpp \
  $$SRC_DIR/kernel/query/chtr-query.cpp \
  $$SRC_DIR/kernel/graph/chtr-node.cpp \
  $$SRC_DIR/kernel/graph/chtr-graph.cpp \
  $$SRC_DIR/kernel/graph/chtr-asg-position.cpp \
  $$SRC_DIR/kernel/graph/chtr-connection.cpp \




message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

