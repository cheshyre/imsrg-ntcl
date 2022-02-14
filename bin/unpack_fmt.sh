# Root src dir
SRC_DIR=$PWD/lib/src
# fmt source should land here
DEST_DIR=$SRC_DIR/fmt
# Clear it out if it exists
rm -rf $DEST_DIR
# Ensure that path up to src exists
mkdir -p $SRC_DIR
# Move to archive directory
cd lib/archive/fmt/
# Untar the archive
tar xf fmt.tar.gz
# Move the resulting direcjory to the destination directory
mv fmt-* $DEST_DIR
# Add empty flag file to indicate that fmt src was extracted
touch $DEST_DIR/fmt-extracted.txt
