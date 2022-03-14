# General installation directory
DEST_DIR=$PWD/lib/build
# Make build directory if need be
mkdir -p $DEST_DIR
mkdir -p $DEST_DIR/include
mkdir -p $DEST_DIR/lib
# Move to wigxjpf-extracted src directory
cd lib/src/wigxjpf/
# Clean directory if necessary
make clean
# Make library locally
make HAVE_QUADMATH=0
# Copy libs to destination
cp -r lib/libwigxjpf.* $DEST_DIR/lib/
# Copy only relevant header to destination
cp -r inc/wigxjpf.h $DEST_DIR/include/
# Clean up build directory
make clean
# Create empty file to indicate that wigxjpf was installed
touch $DEST_DIR/wigxjpf-installed.txt
