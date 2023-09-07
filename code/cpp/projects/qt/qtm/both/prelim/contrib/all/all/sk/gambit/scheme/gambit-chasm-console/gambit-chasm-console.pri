
#           Copyright Nathaniel Christen 2020.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)

QT -= gui

TEMPLATE = app


exists($$ROOT_DIR/../preferred/compiler.pri): include($$ROOT_DIR/../preferred/compiler.pri)
exists($$ROOT_DIR/../preferred/sysr.pri): include($$ROOT_DIR/../preferred/sysr.pri)

exists($$ROOT_DIR/../preferred/gambit.pri): include($$ROOT_DIR/../preferred/gambit.pri)

##
#  gambit.pri should have something like this:
# GAMBIT_INSTALL_DIR = $$system(cat gambit-install)
# GAMBIT_INCLUDE_DIR = $${GAMBIT_INSTALL_DIR}/include
# GAMBIT_LIB_DIR = $${GAMBIT_INSTALL_DIR}/lib
# GAMBIT_BIN_DIR = $${GAMBIT_INSTALL_DIR}/bin
#
#  Then  `cat gambit-install` could also be used for the
#  run-gcc.sh file.
#
#
#  If you want to automate the call to gsc (the gambit scheme compiler), try
#  these lines or something similar:
#
#####
#
# GAMBIT_GSC = $${GAMBIT_INSTALL_DIR}/bin/gsc
#
# CHASM_PRETARGET_GSC = .pretarget-gsc
# !exists($$OUT_PWD/$$CHASM_PRETARGET_GSC):system(touch $$OUT_PWD/$$CHASM_PRETARGET_GSC)
# $${CHASM_PRETARGET_GSC}.CONFIG = phony
# $${CHASM_PRETARGET_GSC}.commands = echo "running gsc ..."; cd $$SRC_DIR; \
#  $${GAMBIT_GSC} -c chasm-slib.scm; \
#  $${GAMBIT_GSC} -link $$SRC_DIR/chasm-slib.c; \
#  echo "gsc done ..."
#
# QMAKE_EXTRA_TARGETS += $$CHASM_PRETARGET_GSC
# PRE_TARGETDEPS += $$CHASM_PRETARGET_GSC
#
####
#
# However, manually invoking gsc only when needed might actually be easier.
#   Sometimes unexpected errors appear otherwise, apparently due to multiple
#   make jobs running in parallel: compiling of the qmake SOURCES starts
#   while gsc hasn't finished.  That can usually be fixes by repeating
#   the build but it's almost easier just to invoke gsc before running
#   a build through Qt Creator.
#
#   Or maybe rig the makefile commands to lock the generated sources,
#   but that seems like overkill.
#
##



INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$GAMBIT_INCLUDE_DIR


SCRIPTS_DIR = $${SRC_GROUP_DIR}/_scm/scripts


DEFINES += SCRIPTS_FOLDER=\\\"$${SCRIPTS_DIR}\\\"


DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"


CONFIG += no_keywords


DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/chasm-utils.h \
  $$SRC_DIR/chasm-slib.h \
  $$SRC_DIR/chasm-slib-decl.h \


SOURCES += \
  $$SRC_DIR/main.cpp \
  $$SRC_DIR/chasm-utils.cpp \


!exists($$SRC_DIR/chasm-slib.c):system(touch $$SRC_DIR/chasm-slib.c)
!exists($$SRC_DIR/chasm-slib_.c):system(touch $$SRC_DIR/chasm-slib_.c)


SOURCES += \
  $$SRC_DIR/chasm-slib.c \
  $$SRC_DIR/chasm-slib_.c \


DISTFILES += \
  $$SRC_DIR/chasm-slib.scm \


DEFINES += ___LIBRARY


LIBS += \
  -L$${GAMBIT_LIB_DIR} -lgambit \
  -lm -ldl -lutil  -lssl -lcrypto


