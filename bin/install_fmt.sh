# General installation directory
DEST_DIR=$PWD/lib/build
# Move to fmt-extracted src directory
cd lib/src/fmt/
# Remove a build directory if it exists
rm -rf build
# Make and enter build directory
mkdir build && cd build
# Configure cmake to build fmt here and target install directory
cmake -DCMAKE_INSTALL_PREFIX:PATH=$DEST_DIR -DFMT_TEST=OFF ..
# Build and install
cmake --build . --target install --config Release
# Clean up build directory
cd .. && rm -rf build
# Create empty file to indicate that fmt was installed
touch $DEST_DIR/fmt-installed.txt
