# shell script to launch cutelyst generators ...
# note: the arguments after the cutelyst invocation will pass the -h
# argument unless this script is called with one or more alternative parameters

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
<=_BUILD_VIA_QTC_FOLDER=>/bin/cutelyst-console=> ${1:-h} ${@:2:$#} ;
cd --

## for local grantlee add these libs
#
#  <=_BUILD_VIA_QTC_FOLDER=>/lib/<=cutelyst_qt_version_string=>-plugins/grantlee/<=grantlee_version_string=>:\
#  <=_ROOT_FOLDER=>/-build_/grantlee/install/lib
