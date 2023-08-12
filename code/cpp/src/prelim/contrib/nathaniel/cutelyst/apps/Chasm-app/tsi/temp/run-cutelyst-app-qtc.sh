# shell script to launch the cutelyst console ...
#

PIN_ROOT=`pwd`/../../../
PIN_ROOT=$(readlink -f ${PIN_ROOT})

echo "pinned at ${PIN_ROOT}"

QT_DIR=`cat ${PIN_ROOT}/_user-qt`

echo "Qt DIR: ${QT_DIR}"


cd ../Chasm-app;

# LD_LIBRARY_PATH=/home/nlevisrael/Qt/5.15.2/gcc_64/lib:\
# /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/via-qtc/lib:\
# $LD_LIBRARY_PATH:\
# /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/via-qtc/lib/cutelyst3-qt5-plugins/grantlee/5.3:\
# /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/grantlee/install/lib \
# /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/via-qtc/bin/cutelyst-console --server --app-file /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps/Chasm-app/tsi/-build_/via-qtc/libChasm-app.so ;
# cd --

## for local grantlee add these libs
#
#  /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/via-qtc/lib/cutelyst3-qt5-plugins/grantlee/5.3:\
#  /home/nlevisrael/docker/gits/torq-wip/ar/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/grantlee/install/lib
