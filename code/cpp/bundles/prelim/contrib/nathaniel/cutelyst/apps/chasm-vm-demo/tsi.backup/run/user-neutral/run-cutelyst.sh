# shell script to launch cutelyst generators ...
# note: the arguments after the cutelyst invocation will pass the -h
# argument unless this script is called with one or more alternative parameters



PIN_ROOT=`pwd`/../../../../..
PIN_ROOT=$(readlink -f ${PIN_ROOT})

echo "pinned at ${PIN_ROOT}"

QT_DIR=`cat ${PIN_ROOT}/_user-qt`

echo "Qt DIR: ${QT_DIR}"

#
# additional defines/configuration (for docker, etc.)
#


cd ../../../chasm-vm-demo;

LD_LIBRARY_PATH=${QT_DIR}/lib:\
${PIN_ROOT}/-build_/install/lib:\
$LD_LIBRARY_PATH \
\
${PIN_ROOT}/-build_/install/bin/cutelyst3-qt5 ${1:-h} ${@:2:$#} ;

cd --

##  for local grantlee add these libs (before $LD_LIBRARY_PATH)
#
#  ${PIN_ROOT}/-build_/install/lib/cutelyst3-qt5-plugins/grantlee/5.3:\
#  ${PIN_ROOT}/-build_/grantlee/install/lib:\
#


# (also you may need to add to CUTELYST_PLUGINS_DIR) 

