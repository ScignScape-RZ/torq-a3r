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
LD_LIBRARY_PATH=<=QT_LIBS_FOLDER=>:\
<=_BUILD_VIA_QTC_FOLDER=>/lib:\
$LD_LIBRARY_PATH \
\
<=_BUILD_VIA_QTC_FOLDER=>/bin/cutelyst-console=> --server --app-file /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/bundles/prelim/contrib/nathaniel/cutelyst/apps/Chasm-app/tsi/-build_/lib/libChasm_app.so ;
cd --

## for local grantlee add these libs
#
#  <=_BUILD_VIA_QTC_FOLDER=>/lib/<=cutelyst_qt_version_string=>-plugins/grantlee/<=grantlee_version_string=>:\
#  <=_ROOT_FOLDER=>/-build_/grantlee/install/lib
