#!/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )


TEST_DIR="$SCRIPT_DIR/test"
TEST_FILES=$(find $TEST_DIR/*.c -type f -printf '%f\n' | sort)

CMAKELIST="$TEST_DIR/cmakelists.txt"
touch $CMAKELIST

{
    echo "# CLOX TESTS"
    echo $'# ==========\n\n'
} > $CMAKELIST
#echo "//Generated Code" > "$CMAKELIST"

for testFile in ${TEST_FILES} 
do

    fileNameNoExt=$(cut -d'.' -f1 <<< $testFile)
    #read -a fileName <<< $(echo $testFile) &> /dev/null
    {
        echo "# ${fileNameNoExt} Tests"
        echo "# ----------------------------------------"
        echo ""
        echo "add_executable($fileNameNoExt $testFile)"
        echo ""
        echo "target_link_libraries($fileNameNoExt LINK_PUBLIC cloxlib unitytest)"
        echo ""
        echo "#Adding test this way because the main cmakelist overrides some of the output directory variables,"
        echo "#which interferes with add_test unless we specify it this way."
        echo "add_test(NAME ${fileNameNoExt}_suite "
        echo "         COMMAND $<TARGET_FILE:${fileNameNoExt}>)"
        echo ""
        echo ""
    } >> $CMAKELIST

done