# shell script to launch cutelyst generators ...
# note: the arguments after the cutelyst invocation will pass the -h
# argument unless this script is called with one or more alternative parameters
#

#/home/nlevisrael/gits/dcr-wip/ar

docker_app_root=/app

echo "docker_app_root=$docker_app_root"

app_lib_root=/app/lib/docker-only

cd ../demo-tutorial;
LD_LIBRARY_PATH=$docker_app_root/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install/lib:\
/home/nlevisrael/Qt/5.15.2/gcc_64/lib:$LD_LIBRARY_PATH \
$docker_app_root/code/cpp/src/prelim/contrib/nathaniel/cutelyst/-build_/install/bin/cutelyst3-qt5 --server --app-file $docker_app_root/code/cpp/src/prelim/contrib/nathaniel/cutelyst/apps/demo-tutorial/tsi/-build_/lib/libdemo_tutorial.so ;
cd --

