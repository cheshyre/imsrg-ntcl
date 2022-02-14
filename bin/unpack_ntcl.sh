# Root src dir
SRC_DIR=$PWD/lib/src
# ntcl source should land here
DEST_DIR=$SRC_DIR/ntcl
# Clear it out if it exists
rm -rf $DEST_DIR
# Ensure that path up to src exists
mkdir -p $SRC_DIR
# Move to archive directory
cd lib/archive/ntcl/
# Untar the archive
tar xf ntcl.tar.gz
# Move the resulting direcjory to the destination directory
mv ntcl-* $DEST_DIR
# Add empty flag file to indicate that ntcl src was extracted
touch $DEST_DIR/ntcl-extracted.txt
