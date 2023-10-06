
GAMBIT_INSTALL_DIR=`cat ../../../../../../../../../../../../preferred/gambit-install`

echo $GAMBIT_INSTALL_DIR

$GAMBIT_INSTALL_DIR/bin/gsc -c chasm-slib.scm
$GAMBIT_INSTALL_DIR/bin/gsc -link chasm-slib.c




