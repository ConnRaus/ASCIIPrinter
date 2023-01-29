#!/bin/bash
#takes in a folder inside the frames folder and prints all the .asc frames in that folder using ./viewasciivideo <filepath> 5

#if no folder or scale is specified, print usage and exit
if [ -z "$1" ] || [ -z "$2" ]
then
    echo "Usage: ./playvideo.sh <foldername> <scale> [framerate]"
    echo "Default framerate is 30"
    echo "Example: ./playvideo.sh gigachad 5"
    echo "Increased scale decreases video size"
    echo "Folder must be inside frames folder"
    exit 1
fi

#if third argument is not specified, set framerate to 30
if [ -z "$3" ]
then
    framerate=30
else
    framerate=$3
fi

#take in argument as folder name
folder=frames/$1
i=0
#count number of .asc files in folder
for file in $folder/*.asc
do
    i=$((i+1))
done

#total expected runtime = number of frames * 1/framerate
expectedtime=$((i/framerate))

#start time to the nanosecond
start=$(date +%s%N)

#loop through all files and print them, make sure to stay at 30fps.
#to do this, keep track of the current time and calculate the percentage of the video that has been played using current time/expected time
#then calculate the frame that should be printed using the percentage of the video that has been played * total number of frames
#then print the frame that should be printed
#frame names are in the format ######.asc
#do this for how long the video is, so current-start < expectedtime. use 8 decimal places for accuracy
clear
while [ $(echo "scale=7; $(($(date +%s%N)-$start))/1000000000 < $expectedtime" | bc) -eq 1 ]
do
    echo -ne "\033[0;0H"

    #calculate percentage of video that has been played
    percentage=$(echo "scale=7; ($(($(date +%s%N)-$start))/1000000000)/$expectedtime" | bc)
    #calculate frame that should be printed
    frame=$(echo "scale=0; $percentage*$i" | bc)
    #round frame to nearest integer
    frame=${frame%.*}
    #find filename of frame that should be printed
    filename=$(printf "%06d" $frame)
    #print frame
    ./viewasciivideo $folder/$filename.asc $2

    # #sleep
    sleep 0.001
done
clear