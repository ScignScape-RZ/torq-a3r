# shell script to launch the cutelyst console ...
#

PIN_ROOT=`pwd`/../../../../..
PIN_ROOT=$(readlink -f ${PIN_ROOT})

echo "pinned at ${PIN_ROOT}"

QT_DIR=`cat ${PIN_ROOT}/_user-qt`

echo "Qt DIR: ${QT_DIR}"


cd ../../../# shell script to launch the cutelyst console ...;
## for local grantlee add these libs
#
#  --server --app-file /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps/Chasm-app/tsi/-build_/via-qtc/libChasm-app.so/lib/%3-plugins/grantlee/%4:\
#  %5/-build_/grantlee/install/lib
