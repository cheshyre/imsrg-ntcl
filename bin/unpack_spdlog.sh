# Root src dir
SRC_DIR=$PWD/lib/src
# spdlog source should land here
DEST_DIR=$SRC_DIR/spdlog
# Clear it out if it exists
rm -rf $DEST_DIR
# Ensure that path up to src exists
mkdir -p $SRC_DIR
# Move to archive directory
cd lib/archive/spdlog/
# Untar the archive
tar xf spdlog.tar.gz
# Move the resulting direcjory to the destination directory
mv spdlog-* $DEST_DIR
# Add empty flag file to indicate that spdlog src was extracted
touch $DEST_DIR/spdlog-extracted.txt
