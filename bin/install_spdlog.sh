# General installation directory
DEST_DIR=$PWD/lib/build
# Move to spdlog-extracted src directory
cd lib/src/spdlog/
# Remove a build directory if it exists
rm -rf build
# Make and enter build directory
mkdir build && cd build
# Configure cmake to build spdlog here and target install directory
cmake -DCMAKE_INSTALL_PREFIX:PATH=$DEST_DIR -DCMAKE_CXX_STANDARD=17 ..
# Build and install
cmake --build . --target install --config Release
# Clean up build directory
cd .. && rm -rf build
# Create empty file to indicate that spdlog was installed
touch $DEST_DIR/spdlog-installed.txt
