


SRC_DIR = $$_PRO_FILE_PWD_


GAMBIT_DIR = $${SRC_DIR}/../install

GAMBIT_GSC = $${GAMBIT_DIR}/bin/gsc

SCRIPTS_DIR = $${SRC_DIR}/scripts

DEFINES += SCRIPTS_FOLDER=\\\"$${SCRIPTS_DIR}\\\"

#///home/nlevisrael/docker/scheme/gambit/install/bin/gsc


INCLUDEPATH += \
  $$GAMBIT_DIR/include

#$$SRC_DIR/slib.h \


HEADERS += \
  $$SRC_DIR/chasm-utils.h \
  $$SRC_DIR/chasm-slib.h \
  $$SRC_DIR/chasm-slib-decl.h \


SOURCES += \
  $$SRC_DIR/main.cpp \
  $$SRC_DIR/chasm-utils.cpp \



#CHASM_PRETARGET_GSC_C = .pretarget-gsc
#!exists($$OUT_PWD/$$CHASM_PRETARGET_GSC):system(touch $$OUT_PWD/$$CHASM_PRETARGET_GSC)
#$${CHASM_PRETARGET_GSC_C}.CONFIG = phony
#$${CHASM_PRETARGET_GSC_C}.commands = cd $$SRC_DIR; \
#  $${GAMBIT_GSC} -c chasm-slib.scm; \
#  $${GAMBIT_GSC} -link $$SRC_DIR/chasm-slib.c



QMAKE_EXTRA_TARGETS += $$CHASM_PRETARGET_GSC_C
PRE_TARGETDEPS += $$CHASM_PRETARGET_GSC_C

QMAKE_EXTRA_TARGETS += $$CHASM_PRETARGET_GSC_LINK
PRE_TARGETDEPS += $$CHASM_PRETARGET_GSC_LINK






!exists($$SRC_DIR/chasm-slib.c):system(touch $$SRC_DIR/chasm-slib.c)
!exists($$SRC_DIR/chasm-slib_.c):system(touch $$SRC_DIR/chasm-slib_.c)


SOURCES += \
  $$SRC_DIR/chasm-slib.c \
  $$SRC_DIR/chasm-slib_.c \


DISTFILES += \
  $$SRC_DIR/chasm-slib.scm \


DEFINES += ___LIBRARY


LIBS += \
  -L$$SRC_DIR/../install/lib -lgambit \
  -lm -ldl -lutil  -lssl -lcrypto
