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
if [ -f "$path*.bmp" ]
then
    rm "$path*.asc"
fi

#converts files
for file in $path*.bmp
do
    filename=$(basename "$file")
    extension="${filename###*.}"
    filename="${filename%.*}"
    filename="$1/$filename"

    #make sure ./convertvideoframes runs successfully
    #./program; echo $? will print 0 if successful, 1 if not
    if [ $(./convertvideoframes $filename; echo $?) -eq 0 ]
    then
        echo "Successfully converted $filename.bmp to $filename.asc"
    else
        echo "Failed to convert $filename"
        exit 1
    fi
done

#find all files in frames folder
#rename all .asc files in folder to ######.asc
i=0
for file in $path*.asc
do
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
        #allow for mass file deletion
        find . -name "*.bmp" -print0 | xargs -0 rm
        echo "Removed all .bmp files in $path"
    fi
fi