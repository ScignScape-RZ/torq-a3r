
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)



include(../build-group.pri)


exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)
exists($$ROOT_DIR/../preferred/sysr-c.pri): include($$ROOT_DIR/../preferred/sysr-c.pri)
exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)


INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR



CONFIG += c++17


HEADERS += \
  $$SRC_DIR/chtr-asg-visitor.h \
  $$SRC_DIR/prerun/chtr-prep-prerun-anticipate.h \


SOURCES += \
  $$SRC_DIR/chtr-asg-visitor.cpp \
  $$SRC_DIR/prerun/chtr-prep-prerun-anticipate.cpp \


CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_AQNS


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

