# shell script to launch cutelyst generators ...
# note: the arguments after the cutelyst invocation will pass the -h
# argument unless this script is called with one or more alternative parameters
#

#/home/nlevisrael/gits/dcr-wip/ar
#/home/nlevisrael/Qt/5.15.2/gcc_64/lib

docker_app_root=/app/cutelyst
echo "docker_app_root=$docker_app_root"

app_lib_root=/app/cutelyst/docker/lib/docker-only
echo "app_lib_root=$app_lib_root"

cd ../Chasm-app;
LD_LIBRARY_PATH=$docker_app_root/-build_/via-qtc/lib:\
$docker_app_root/-build_/grantlee/install/lib:\
$app_lib_root/qt:$app_lib_root/system:$LD_LIBRARY_PATH \
CUTELYST_PLUGINS_DIR="$docker_app_root/-build_/via-qtc/lib/cutelyst3-qt5-plugins;$docker_app_root/-build_/grantlee/install/lib" \
$docker_app_root/-build_/via-qtc/bin/cutelyst-console --server --app-file $docker_app_root/apps/Chasm-app/tsi/-build_/via-qtc/libChasm-app.so ;
cd --

