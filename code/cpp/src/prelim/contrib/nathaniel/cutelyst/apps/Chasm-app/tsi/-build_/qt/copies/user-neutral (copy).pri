

STRIP_PATH = $$_PRO_FILE_PWD_

## assuming the apps are under the proper folder,
   # this should work to find the "pin" root ...
STRIP_PATH ~= s!/apps/.*!!

_PIN_ROOT_DIR = $${STRIP_PATH}

exists($${_PIN_ROOT_DIR}/user-specific-pin.pri) {

_PIN_ROOT_DIR = $$system(cat "$${PIN_ROOT_DIR}/user-specific-pin.pri")

} else {

_PIN_ROOT_DIR ~= s!/apps!!

}


## auto-generated defines:
# INSTALL_ROOT_FOLDER: $$PIN_ROOT_DIR/-build_/install (build via cmake)
#  or $$PIN_ROOT_DIR/-build_/via-qtc (build via Qt Creator)
# APPS_ROOT_FOLDER: $$PIN_ROOT_DIR/apps
# FRAMEWORK_ROOT_FOLDER: $$PIN_ROOT_DIR/framework

## Other Notes
   # in user-specific.pri this would be hard-coded.
   # QTDIR is an environment variable specific to the current build.
   # uncomment the following message line to see the current value
   # message(QTDIR is: $$(QTDIR))
#
#  Qt libraries: $$(QTDIR)


!defined(USER_SPECIFIC_INFO ,var) {

  PIN_ROOT_DIR = $$_PIN_ROOT_DIR
  APPS_ROOT_DIR = $$PIN_ROOT_DIR/apps
  FRAMEWORK_ROOT_DIR = $$PIN_ROOT_DIR/framework

}


defined(FEATURE_ALL_VIA_QTC ,var) {
 !defined(USER_SPECIFIC_INFO ,var) {
  INSTALL_ROOT_DIR = $$PIN_ROOT_DIR/-build_/via-qtc
 }
}

} else {
 !defined(USER_SPECIFIC_INFO ,var) {
  INSTALL_ROOT_DIR=$$PIN_ROOT_DIR/-build_/install
 }
}


###  Paste this into the custom executable to run the server from Qt Creator ...

## For cmake-based builds
# executable path:
#
#   %{sourceDir}/../../../../../-build_/install/bin/cutelyst-console
#    or
#   $$PIN_ROOT_DIR/-build_/install/bin/cutelyst3-qt5
#    (write the substitution manually)
#

# command line arguments:
#   --server --app-file %{sourceDir}/../lib/libChasm-app.so
#    or
#   --server --app-file $$PIN_ROOT_DIR/-build_/install/Chasm-app/tsi/-build_/lib/libChasm_app.so
#    (write the substitution manually)

# working directory:
#   $$PIN_ROOT_DIR/apps/Chasm-app/Chasm-app
#    or
#   %{sourceDir}/../../../Chasm-app

#
# add to the environment:
#
#   (batch script mode)
# For the first line, check contents of the user-specific-pin.pri file or the following message output
  # (uncomment)
  # message(PIN_ROOT_DIR is: $${PIN_ROOT_DIR})
# PIN_ROOT_DIR=
# LD_LIBRARY_PATH=${QTDIR}/lib:${PIN_ROOT_DIR}/-build_/install/lib:${THIS_APP_EXTRA_LIBS}:$LD_LIBRARY_PATH



## For "all-qtc" (Qt Creator) builds
# executable path:
#
#   %{sourceDir}/../../../../../-build_/via-qtc/bin/cutelyst-console
#    or
#   $$PIN_ROOT_DIR/-build_/via-qtc/bin/cutelyst3-qt5
#    (write the substitution manually)
#

# command line arguments:
#   --server --app-file %{sourceDir}/../via-qtc/libChasm-app.so
#    or
#   --server --app-file $$PIN_ROOT_DIR/apps/Chasm-app/tsi/-build_/via-qtc/libChasm_app.so
#    (write the substitution manually)

# working directory:
#   $$PIN_ROOT_DIR/apps/Chasm-app/Chasm-app
#    or
#   %{sourceDir}/../../../Chasm-app

#
# add to the environment:
#   (batch script mode)
# LD_LIBRARY_PATH=/home/nlevisrael/Qt/5.15.2/gcc_64/lib:$$PIN_ROOT_DIR/-build_/via-qtc/lib:${THIS_APP_EXTRA_LIBS}:$LD_LIBRARY_PATH

######


## For projects using grantlee from a local installation -- version 5.3
   #(see FEATURE_USE_LOCAL_GRANTLEE in the main project file)

#  Qt Creator configuration, run environment batch build, add (above the LD_LIBRARY_PATH= line)
# THIS_APP_EXTRA_LIBS=$$PIN_ROOT_DIR/-build_/via-qtc/lib/cutelyst3-qt5-plugins/grantlee/5.3:$$PIN_ROOT_DIR/-build_/grantlee/install/lib

#  With a build via cmake, replace the first path with
# $$PIN_ROOT_DIR/-build_/install/lib/cutelyst3-qt5-plugins/grantlee/5.3

# note: the Qt and Grantlee version are fixed to when the current app project was generated.

