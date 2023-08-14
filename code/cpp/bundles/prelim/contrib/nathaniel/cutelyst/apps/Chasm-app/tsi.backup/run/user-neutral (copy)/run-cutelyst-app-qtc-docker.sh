# shell script to launch the cutelyst console ...

#


PIN_ROOT=`pwd`/../../../../..
PIN_ROOT=$(readlink -f ${PIN_ROOT})

echo "pinned at ${PIN_ROOT}"

QT_DIR=`cat ${PIN_ROOT}/_user-qt`

echo "Qt DIR: ${QT_DIR}"

docker_app_lib=/app/cutelyst/docker/lib/docker-only
echo "docker_app_lib = $docker_app_lib"

#

cd ../../../<=filename=>;
LD_LIBRARY_PATH=<=QT_LIBS_FOLDER=>:\
<=_INSTALL_ROOT_FOLDER=>/lib:\
$LD_LIBRARY_PATH \
\
CUTELYST_PLUGINS_DIR="${PIN_ROOT}/-build_/via-qtc/lib/cutelyst3-qt5-plugins;\
${PIN_ROOT}/-build_/grantlee/install/lib" \
\
<=_INSTALL_ROOT_FOLDER=>/bin/<=cutelyst_qt_version_string=> --server --app-file /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/bundles/prelim/contrib/nathaniel/cutelyst/apps/Chasm-app/tsi/-build_/via-qtc/libChasm-app.so ;
cd --

## for local grantlee add these libs
#
#  <=_INSTALL_ROOT_FOLDER=>/lib/<=cutelyst_qt_version_string=>-plugins/grantlee/<=grantlee_version_string=>:\
#  <=_ROOT_FOLDER=>/-build_/grantlee/install/lib
