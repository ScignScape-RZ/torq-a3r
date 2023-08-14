# shell script to launch the cutelyst console ...
#

PIN_ROOT=`pwd`/../../../../..
PIN_ROOT=$(readlink -f ${PIN_ROOT})

echo "pinned at ${PIN_ROOT}"

QT_DIR=`cat ${PIN_ROOT}/_user-qt`

echo "Qt DIR: ${QT_DIR}"

docker_app_lib=/app/cutelyst/docker/lib/docker-only
echo "docker_app_lib = $docker_app_lib"


cd ../../../Chasm-app

LD_LIBRARY_PATH=${QT_DIR}/lib:\
${PIN_ROOT}/-build_/via-qtc/lib:\
$LD_LIBRARY_PATH:${docker_app_lib}/qt:\
$LD_LIBRARY_PATH:${docker_app_lib}/system:\
${PIN_ROOT}/-build_/via-qtc/lib/cutelyst3-qt5-plugins/grantlee/5.3:\
${PIN_ROOT}/-build_/grantlee/install/lib \
\
CUTELYST_PLUGINS_DIR="${PIN_ROOT}/-build_/via-qtc/lib/cutelyst3-qt5-plugins;${PIN_ROOT}/-build_/grantlee/install/lib" \
\
${PIN_ROOT}/-build_/via-qtc/bin/cutelyst-console --server --app-file ${PIN_ROOT}/apps/Chasm-app/tsi/-build_/via-qtc/libChasm-app.so ;
cd --

## for local grantlee add these libs
#
#  ${PIN_ROOT}/-build_/via-qtc/lib/cutelyst3-qt5-plugins/grantlee/5.3:\
#  ${PIN_ROOT}/-build_/grantlee/install/lib
# shell script to launch the cutelyst console ...;
## for local grantlee add these libs
#
#  --server --app-file ${PIN_ROOT}/apps/Chasm-app/tsi/-build_/via-qtc/libChasm-app.so/lib/%3-plugins/grantlee/%4:\
#  %5/-build_/grantlee/install/lib
