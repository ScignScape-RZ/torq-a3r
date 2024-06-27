
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


PROJECT_NAME = chtr

include(../build-group.pri)

QT -= gui

exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)

CONFIG += c++17


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$SRC_GROUP_DIR/chasm-tr-graph-core


INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR



CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_AQNS


HEADERS += \
  $$SRC_DIR/chtr-channel-object.h \
  $$SRC_DIR/chtr-channel-package.h \
  $$SRC_DIR/chtr-source-token.h \
  $$SRC_DIR/chtr-carrier.h \
  $$SRC_DIR/chtr-code-statement.h \
  $$SRC_DIR/chvm/chvm-code-generator.h \
  $$SRC_DIR/chvm/chvm-code-block.h \
  $$SRC_DIR/chvm/chvm-code-statement.h \
  $$SRC_DIR/chvm/chvm-procedure.h \
  $$SRC_DIR/chvm/generators/chvm-code-statement-generator.h \
  $$SRC_DIR/eval/chvm-code-runner.h \


SOURCES += \
  $$SRC_DIR/chtr-channel-object.cpp \
  $$SRC_DIR/chtr-channel-package.cpp \
  $$SRC_DIR/chtr-source-token.cpp \
  $$SRC_DIR/chtr-carrier.cpp \
  $$SRC_DIR/chtr-code-statement.cpp \
  $$SRC_DIR/chvm/chvm-code-generator.cpp \
  $$SRC_DIR/chvm/chvm-code-block.cpp \
  $$SRC_DIR/chvm/chvm-code-statement.cpp \
  $$SRC_DIR/chvm/chvm-procedure.cpp \
  $$SRC_DIR/chvm/generators/chvm-code-statement-generator.cpp \
  $$SRC_DIR/chvm/generators/chvm-code-statement-generator.generic.cpp \
  $$SRC_DIR/eval/chvm-code-runner.cpp \







message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

