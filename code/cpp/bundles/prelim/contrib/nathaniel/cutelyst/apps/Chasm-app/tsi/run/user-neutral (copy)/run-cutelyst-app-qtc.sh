# shell script to launch the cutelyst console ...

#


PIN_ROOT=`pwd`/../../../../..
PIN_ROOT=$(readlink -f ${PIN_ROOT})

echo "pinned at ${PIN_ROOT}"

QT_DIR=`cat ${PIN_ROOT}/_user-qt`

echo "Qt DIR: ${QT_DIR}"

#
# (docker-specific configuration if needed)
#

#

cd ../../../<=filename=>;

LD_LIBRARY_PATH=<=QT_LIBS_FOLDER=>:\   QT_LIBS_FOLDER= ${QT_DIR}/lib
<=_INSTALL_ROOT_FOLDER=>/lib:\         _INSTALL_ROOT_FOLDER= ${PIN_ROOT}/-build_/via-qtc/lib 
   (add $LD_LIBRARY_PATH:${docker_app_lib}/qt:\
    $LD_LIBRARY_PATH:${docker_app_lib}/system:\)

$LD_LIBRARY_PATH \
\
<=_INSTALL_ROOT_FOLDER=>/bin/<=cutelyst_qt_version_string=> --server --app-file /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/bundles/prelim/contrib/nathaniel/cutelyst/apps/Chasm-app/tsi/-build_/via-qtc/libChasm-app.so ;
cd --


_INSTALL_ROOT_FOLDER= ${PIN_ROOT}/-build_/via-qtc/bin/cutelyst-console


## for local grantlee add these libs
#
#  <=_INSTALL_ROOT_FOLDER=>/lib/<=cutelyst_qt_version_string=>-plugins/grantlee/<=grantlee_version_string=>:\
#  <=_ROOT_FOLDER=>/-build_/grantlee/install/lib
