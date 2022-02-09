# General installation directory
DEST_DIR=$PWD/lib/build
# Move to abseil-extracted src directory
cd lib/src/abseil-cpp/
# Remove a build directory if it exists
rm -rf build
# Make and enter build directory
mkdir build && cd build
# Configure cmake to build abseil here and target install directory
cmake -DCMAKE_INSTALL_PREFIX:PATH=$DEST_DIR -DCMAKE_CXX_STANDARD=17 ..
# Build and install
cmake --build . --target install --config Release
# Clean up build directory
cd .. && rm -rf build
# Create merged abseil library
# (bad practice, but because we don't use CMake this is the most convenient approach)
cd $DEST_DIR/lib
echo "create libabsl.a" > libabsl.mri
for f in libabsl*.a; do echo "addlib $f" >> libabsl.mri; done
echo "save" >> libabsl.mri
echo "end" >> libabsl.mri
ar -M <libabsl.mri
# Create empty file to indicate that abseil was installed
touch $DEST_DIR/abseil-cpp-installed.txt
