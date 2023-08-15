

##  Notes: Overall name of project: chasm-vm-demo
#  Name of project (lowercase, for source file names): chasm-vm-demo
#  This project's library name (for cmake-based builds): libchasm_vm_demo.so

##  We can assume that server-side code will rarely if ever
#   need to link against GUI libaries
QT -= gui


##  Comment this out to link and run against
#  cmake-based builds of the framework
FEATURE_ALL_VIA_QTC = ALL_VIA_QTC


##   This .pri file holds paths specific to the current user
     # (and is not uploaded to git)
include(user-specific.pri)

##   If the code for this app gets shared via (e.g.) git,
#    the user-specific.pri file will not be uploaded,
#    so subsequent users could fall back to the following
#    .pri include and/or use it to generate their own
#    user-specific.pri
include(user-neutral.pri)


## comment this out to prevent Cutelyst/Application
#  from defining the "namespace_class" macro
   # (see application.h line 18 ...
# DEFINES += NO_NAMESPACE_CLASS_DEF


DEFINES += INSTALL_ROOT_FOLDER=\\\"$${INSTALL_ROOT_DIR}\\\"
DEFINES += APPS_ROOT_FOLDER=\\\"$${APPS_ROOT_DIR}\\\"
DEFINES += FRAMEWORK_ROOT_FOLDER=\\\"$${FRAMEWORK_ROOT_DIR}\\\"



defined(FEATURE_ALL_VIA_QTC ,var) {

# additional make steps if needed ...

APP_ROOT_DIR = $$_PRO_FILE_PWD_
APP_ROOT_DIR ~= s!/-build_/qt.*!!

DESTDIR = $${APP_ROOT_DIR}/-build_/via-qtc

} else {

cmake_step.commands = cd ../run-cmake/working; \
../run-cmake.sh; make; make copy-install
QMAKE_EXTRA_TARGETS += cmake_step
PRE_TARGETDEPS += cmake_step

}

TEMPLATE = lib


defined(FEATURE_ALL_VIA_QTC ,var) {

DEFINES += $${FEATURE_ALL_VIA_QTC}

INCLUDEPATH += \
  $${FRAMEWORK_ROOT_DIR} \
  $${INSTALL_ROOT_DIR}/include/supplement \

} else {

INCLUDEPATH += \
  $$INSTALL_ROOT_DIR/include/chasm-vm-demo \
}

INCLUDEPATH += \
  chasm-vm-demo \

SRC_DIR = $${APPS_ROOT_DIR}/chasm-vm-demo/chasm-vm-demo/src

include(h+s.pri)

DISTFILES += \
  $$SRC_DIR/../CMakeLists.txt \
  $$SRC_DIR/CMakeLists.txt \


CUTELYST_MAJOR_VERSION = 3

defined(FEATURE_ALL_VIA_QTC ,var) {
LIBS += -L$$INSTALL_ROOT_DIR/lib \
  -lcutelyst-lib \

} else {
LIBS += -L$$INSTALL_ROOT_DIR/lib \
  -lCutelyst$${CUTELYST_MAJOR_VERSION}Qt$${QT_MAJOR_VERSION} \
#
# note: currently CUTELYST_MAJOR_VERSION is 3

}



## For projects using grantlee from a local installation, uncomment these lines
#  (change the paths if needed)

FEATURE_USE_LOCAL_GRANTLEE = USE_LOCAL_GRANTLEE

defined(FEATURE_USE_LOCAL_GRANTLEE ,var) {

DEFINES += $${FEATURE_USE_LOCAL_GRANTLEE}

GRANTLEE_VERSION_STRING = 5.3


LIBS += -L$$INSTALL_ROOT_DIR/lib/cutelyst$${CUTELYST_MAJOR_VERSION}-qt$${QT_MAJOR_VERSION}-plugins/grantlee/$${GRANTLEE_VERSION_STRING} \
  -lgrantlee-view \

# current location of local grantlee -- but this might change ...
LIBS += -L$$ROOT_DIR/-build_/grantlee/install/lib \
  -lGrantlee_Templates
}
