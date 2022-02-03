# Root src dir
SRC_DIR=$PWD/lib/src
# wigxjpf source should land here
DEST_DIR=$SRC_DIR/wigxjpf
# Clear it out if it exists
rm -rf $DEST_DIR
# Ensure that path up to src exists
mkdir -p $SRC_DIR
# Move to archive directory
cd lib/archive/wigxjpf/
# Untar the archive
tar xf wigxjpf.tar.gz
# Move the resulting direcjory to the destination directory
mv wigxjpf-* $DEST_DIR
# Add empty flag file to indicate that wigxjpf src was extracted
touch $DEST_DIR/wigxjpf-extracted.txt
