# shell script to launch the cutelyst console ...



PIN_ROOT=`pwd`/../../../../..
PIN_ROOT=$(readlink -f ${PIN_ROOT})

echo "pinned at ${PIN_ROOT}"

QT_DIR=`cat ${PIN_ROOT}/_user-qt`

echo "Qt DIR: ${QT_DIR}"

#
# additional defines/configuration (for docker, etc.)
#


cd ../../../Chasm-app;

LD_LIBRARY_PATH=${QT_DIR}/lib:\
${PIN_ROOT}/-build_/via-qtc/lib:\
$LD_LIBRARY_PATH \
\
${PIN_ROOT}/-build_/via-qtc/bin/cutelyst-console --server --app-file ${PIN_ROOT}/apps/Chasm-app/tsi/-build_/via-qtc/libChasm-app.so ;

cd --

##  for local grantlee add these libs (before $LD_LIBRARY_PATH)
#
#  ${PIN_ROOT}/-build_/via-qtc/lib/cutelyst3-qt5-plugins/grantlee/5.3:\
#  ${PIN_ROOT}/-build_/grantlee/install/lib:\
#


# (also you may need to add to CUTELYST_PLUGINS_DIR) 

