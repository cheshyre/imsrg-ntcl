# Root src dir
SRC_DIR=$PWD/lib/src
# Abseil source should land here
DEST_DIR=$SRC_DIR/abseil-cpp
# Clear it out if it exists
rm -rf $DEST_DIR
# Ensure that path up to src exists
mkdir -p $SRC_DIR
# Move to archive directory
cd lib/archive/abseil-cpp/
# Untar the archive
tar xf abseil-cpp.tar.gz
# Move the resulting direcjory to the destination directory
mv abseil-cpp-* $DEST_DIR
# Add empty flag file to indicate that abseil src was extracted
touch $DEST_DIR/abseil-cpp-extracted.txt
