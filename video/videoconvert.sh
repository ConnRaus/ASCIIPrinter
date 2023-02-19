#!/bin/bash

#this script converts all files in the frames folder to .asc with ./convert <filename>
#remove extension and folder name from filename

if [ -z "$1" ]
then
    echo "Usage: ./videoconvert.sh <foldername> [-deletebmps]"
    echo "Example: ./videoconvert.sh gigachad -deletebmps"
    echo "Folder must be inside frames folder"
    exit 1
fi

path="frames/$1/"

#if .bmp files are in the folder, delete all .asc files
if [ -n "$(find $path -name "*.bmp" -print -quit)" ]
then
    find $path -name "*.asc" -print0 | xargs -0 rm
    echo "Removed all .asc files in $path"
else
    echo "Conversion failed. No .bmp files found in folder ASCIIPrinter/video/frames/$1!"
    exit 1
fi


convert() {
    filename=$(basename "$1")
    extension="${filename###*.}"
    filename="${filename%.*}"
    filename="$2/$filename"

    #make sure ./convertvideoframes runs successfully
    #./program; echo $? will print 0 if successful, 1 if not
    if [ $(./convertvideoframes $filename; echo $?) -eq 0 ]
    then
        echo "Successfully converted $filename.bmp to $filename.asc"
    else
        echo "Failed to convert $filename"
        exit 1
    fi
}


# multi-threaded conversion
# Use convert function as convert(filename<no extension>, foldername)
# Output files as 000001.asc, 000002.asc, etc.
export -f convert
find $path -name "*.bmp" -print0 | xargs -0 -n1 -P8 -I{} bash -c 'convert "{}" "$1"' _ "$1"
# -print0 separates files with null character
# -0 means null character is separator
# -n1: one file per command
# -P8: 8 processes
# -I{}: replace {} with file name
# convert "{}" "$1": run convert function with file name and folder name
# _ "$1": replace _ with folder name





#find all files in frames folder
#rename all .asc files in folder to ######.asc
i=0
for file in $path*.asc
do
    # checks each filename number and puts it in correct format. lt=less than.
    i=$((i+1))
    if [ $i -lt 10 ]
    then
        mv $file $path/00000$i.asc
    elif [ $i -lt 100 ]
    then
        mv $file $path/0000$i.asc
    elif [ $i -lt 1000 ]
    then
        mv $file $path/000$i.asc
    elif [ $i -lt 10000 ]
    then
        mv $file $path/00$i.asc
    elif [ $i -lt 100000 ]
    then
        mv $file $path/0$i.asc
    else
        mv $file $path/$i.asc
    fi
    echo "Renamed $file to $path/$i.asc"
done

if [ "$2" = "-deletebmps" ]
then
    #make sure there are .asc files already compiled
    #if there are .asc files, remove all .bmp files in folder
    #if there are no .asc files, exit
    if [ -z "$(ls -A $path*.asc)" ]
    then
        echo "No .asc files in folder! Conversion failed!"
        exit 1
    else
        find . -name "*.bmp" -print0 | xargs -0 rm
        echo "Removed all .bmp files in $path"
    fi
fi
