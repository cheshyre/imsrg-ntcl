# General installation directory
DEST_DIR=$PWD/lib/build
# Make build directory if need be
mkdir -p $DEST_DIR
mkdir -p $DEST_DIR/include
mkdir -p $DEST_DIR/lib
# Move to GSL-extracted src directory
cd lib/src/wigxjpf/
# Clean directory if necessary
make clean
# Make library locally
make
# Copy libs to destination
cp -r lib/* $DEST_DIR/lib/
# Copy headers to destination
cp -r inc/* $DEST_DIR/include/
# Clean up build directory
make clean
# Create empty file to indicate that abseil was installed
touch $DEST_DIR/wigxjpf-installed.txt
