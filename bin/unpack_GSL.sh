# Root src dir
SRC_DIR=$PWD/lib/src
# GSL source should land here
DEST_DIR=$SRC_DIR/GSL
# Clear it out if it exists
rm -rf $DEST_DIR
# Ensure that path up to src exists
mkdir -p $SRC_DIR
# Move to archive directory
cd lib/archive/GSL/
# Untar the archive
tar xf GSL.tar.gz
# Move the resulting direcjory to the destination directory
mv GSL-* $DEST_DIR
# Add empty flag file to indicate that GSL src was extracted
touch $DEST_DIR/GSL-extracted.txt
