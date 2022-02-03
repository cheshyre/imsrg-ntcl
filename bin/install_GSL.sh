# General installation directory
DEST_DIR=$PWD/lib/build
# Move to GSL-extracted src directory
cd lib/src/GSL/
# Remove a build directory if it exists
rm -rf build
# Make and enter build directory
mkdir build && cd build
# Configure cmake to build GSL here and target install directory
cmake -DCMAKE_INSTALL_PREFIX:PATH=$DEST_DIR -DGSL_TEST=OFF ..
# Build and install
cmake --build . --target install --config Release
# Clean up build directory
cd .. && rm -rf build
# Create empty file to indicate that abseil was installed
touch $DEST_DIR/GSL-installed.txt
