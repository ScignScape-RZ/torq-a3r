

## auto-generated defines:
# INSTALL_ROOT_FOLDER: /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install (build via cmake)
#  or /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/via-qtc (build via Qt Creator)
# APPS_ROOT_FOLDER: /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps
# FRAMEWORK_ROOT_FOLDER: /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/framework

# Other Notes
#  Qt libraries: /home/nlevisrael/Qt/5.15.2/gcc_64/lib

PIN_ROOT_DIR = /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst
APPS_ROOT_DIR = /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps
FRAMEWORK_ROOT_DIR = /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/framework


defined(FEATURE_ALL_VIA_QTC ,var) {

INSTALL_ROOT_DIR = /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/via-qtc

} else {

INSTALL_ROOT_DIR=/home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install

}


###  Paste this into the custom executable to run the server from Qt Creator ...

## For cmake-based builds
# executable path:
#
#   %{sourceDir}/../../../../../-build_/install/bin/cutelyst3-qt5
#    or
#   /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install/bin/cutelyst3-qt5

# command line arguments:
#   --server --app-file %{sourceDir}/../lib/libChasm_app.so
#    or
#   --server --app-file /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps/Chasm-app/tsi/-build_/lib/libChasm_app.so


# working directory:
#   %{sourceDir}/../../../Chasm-app
#    or
#   /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps/Chasm-app/Chasm-app

#
# add to the environment:
#   (batch script mode)
# LD_LIBRARY_PATH=/home/nlevisrael/Qt/5.15.2/gcc_64/lib:/home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install/lib:${THIS_APP_EXTRA_LIBS}:$LD_LIBRARY_PATH



## For "all-qtc" (Qt Creator) builds

# executable path:
#
#   %{sourceDir}/../../../../../-build_/via-qtc/bin/cutelyst-console
#    or
#   /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/via-qtc/bin/cutelyst-console
#

# command line arguments:
#   --server --app-file %{sourceDir}/../lib/libChasm-app.so
#    or
#   --server --app-file /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps/Chasm-app/tsi/-build_/via-qtc/libChasm-app.so

# working directory:
#   %{sourceDir}/../../../Chasm-app
#    or
#   /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps/Chasm-app/Chasm-app

#
# add to the environment:
#   (batch script mode)
# LD_LIBRARY_PATH=/home/nlevisrael/Qt/5.15.2/gcc_64/lib:/home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/via-qtc/lib:${THIS_APP_EXTRA_LIBS}:$LD_LIBRARY_PATH

######


## For projects using grantlee from a local installation -- version 5.3
   # (see FEATURE_USE_LOCAL_GRANTLEE in the main project file)

#  Qt Creator configuration, run environment batch build, add
   # (above the LD_LIBRARY_PATH= line)
# THIS_APP_EXTRA_LIBS=/home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/via-qtc/lib/cutelyst3-qt5-plugins/grantlee/5.3:/home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/grantlee/install/lib

#  With a build via cmake, replace the first path with
# /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install/lib/cutelyst3-qt5-plugins/grantlee/5.3

# note: the Qt and Grantlee version are fixed to when the current app project was generated.

