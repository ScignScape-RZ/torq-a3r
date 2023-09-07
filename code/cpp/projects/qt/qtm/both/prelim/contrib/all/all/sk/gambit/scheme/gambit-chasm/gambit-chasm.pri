
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)

QT -= gui

TEMPLATE = app


include($$ROOT_DIR/../preferred/sysr.pri)


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR


INCLUDEPATH += $$SRC_DIR/gsc
INCLUDEPATH += $$SRC_DIR/include


DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"


CONFIG += no_keywords


DEFINES += USE_KANS

