# compiles bmp2ascvideo.c as convertvideoframes
gcc -o convertvideoframes bmp2ascvideo.c

if [ $? -eq 0 ]
then
    echo "Successfully compiled bmp2ascvideo.c"
else
    echo "Failed to compile bmp2ascvideo.c"
    exit 1
fi

# compiles asciiprintervideo.c as viewasciivideo
gcc -o viewasciivideo asciiprintervideo.c

if [ $? -eq 0 ]
then
    echo "Successfully compiled asciiprintervideo.c"
else
    echo "Failed to compile asciiprintervideo.c"
    exit 1
fi