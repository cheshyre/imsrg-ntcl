# Root src dir
SRC_DIR=$PWD/lib/src
# GoogleTest source should land here
DEST_DIR=$SRC_DIR/googletest
# Clear it out if it exists
rm -rf $DEST_DIR
# Ensure that path up to src exists
mkdir -p $SRC_DIR
# Move to archive directory
cd lib/archive/googletest/
# Untar the archive
tar xf googletest.tar.gz
# Move the resulting direcjory to the destination directory
mv googletest-* $DEST_DIR
# Add empty flag file to indicate that GoogleTest src was extracted
touch $DEST_DIR/googletest-extracted.txt
