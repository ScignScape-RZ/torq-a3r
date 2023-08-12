

##  Notes: Overall name of project: Chasm-app
#  Name of project (lowercase, for source file names): chasm-app
#  This project's library name (for cmake-based builds): libChasm_app.so


##  Comment this out to link and run against
#  cmake-based builds of the framework
FEATURE_ALL_VIA_QTC = ALL_VIA_QTC


##   This .pri file holds paths specific to the current user
     # (and is not uploaded to git)
include(user-specific.pri)

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
  $$INSTALL_ROOT_DIR/include/chasm-app \
}

INCLUDEPATH += \
  chasm-app \

SRC_DIR = $${APPS_ROOT_DIR}/Chasm-app/Chasm-app/src

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

# note: currently this would be 3
}



## For projects using grantlee from a local installation, uncomment these lines
#  (change the paths if needed)

FEATURE_USE_LOCAL_GRANTLEE = USE_LOCAL_GRANTLEE

defined(FEATURE_USE_LOCAL_GRANTLEE ,var) {

DEFINES += $${FEATURE_USE_LOCAL_GRANTLEE}

GRANTLEE_VERSION_STRING = 5.3


LIBS += -L$$INSTALL_ROOT_DIR/lib/cutelyst$${CUTELYST_MAJOR_VERSION}-qt$${QT_MAJOR_VERSION}-plugins/grantlee/$${GRANTLEE_VERSION_STRING} \
  -lgrantlee-view \

message($$INSTALL_ROOT_DIR/lib/cutelyst$${CUTELYST_MAJOR_VERSION}-qt$${QT_MAJOR_VERSION}-plugins/grantlee/$${GRANTLEE_VERSION_STRING})

# current location of local grantlee -- but this might change ...
LIBS += -L$$ROOT_DIR/-build_/grantlee/install/lib \
  -lGrantlee_Templates
}
