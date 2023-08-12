# shell script to launch the cutelyst console ...
#

PIN_ROOT=`pwd`/../../../../..
PIN_ROOT=$(readlink -f ${PIN_ROOT})

echo "pinned at ${PIN_ROOT}"

QT_DIR=`cat ${PIN_ROOT}/_user-qt`

echo "Qt DIR: ${QT_DIR}"


cd ../../../# shell script to launch cutelyst generators ...
# note: the arguments after the cutelyst invocation will pass the -h
# argument unless this script is called with one or more alternative parameters;
## for local grantlee add these libs
#
#  ${1:-h} ${@:2:$#}/lib/%3-plugins/grantlee/%4:\
#  %5/-build_/grantlee/install/lib
