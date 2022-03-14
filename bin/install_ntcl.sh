# General installation directory
DEST_DIR=$PWD/lib/build
# Make build directory if need be
mkdir -p $DEST_DIR
mkdir -p $DEST_DIR/include
mkdir -p $DEST_DIR/lib
# Move to ntcl-extracted src directory
cd lib/src/ntcl/
# Make library locally
make
# Copy libs to destination
cp -r lib/lib*.* $DEST_DIR/lib/
# Copy only relevant header to destination
cp -r include/* $DEST_DIR/include/
# Create empty file to indicate that ntcl was installed
touch $DEST_DIR/ntcl-installed.txt
