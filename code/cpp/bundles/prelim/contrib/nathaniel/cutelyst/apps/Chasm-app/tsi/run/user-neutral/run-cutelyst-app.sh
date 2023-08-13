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
${PIN_ROOT}/-build_/install/lib:\
\
$LD_LIBRARY_PATH \
\
${PIN_ROOT}/-build_/install/bin/cutelyst3-qt5 --server --app-file ${PIN_ROOT}/apps/Chasm-app/tsi/-build_/lib/libChasm_app.so ;

cd --

##  for local grantlee add these libs (before $LD_LIBRARY_PATH)
#
#  ${PIN_ROOT}/-build_/install/lib/cutelyst3-qt5-plugins/grantlee/5.3:\
#  ${PIN_ROOT}/-build_/grantlee/install/lib:\
#


# (also you may need to add to CUTELYST_PLUGINS_DIR) 

