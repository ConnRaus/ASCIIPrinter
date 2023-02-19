# compiles video/bmp2ascvideo.c as convertvideoframes
gcc video/bmp2ascvideo.c -o convertvideoframes -O3

if [ $? -eq 0 ]
then
    echo "Successfully compiled bmp2ascvideo.c"
else
    echo "Failed to compile bmp2ascvideo.c"
    exit 1
fi

# compiles video/asciiprintervideo.c as viewasciivideo
gcc video/asciiprintervideo.c -o viewasciivideo -O3

if [ $? -eq 0 ]
then
    echo "Successfully compiled asciiprintervideo.c"
else
    echo "Failed to compile asciiprintervideo.c"
    exit 1
fi

# compiles bmp2asc.c -o convert
gcc bmp2asc.c -o convert -O3

if [ $? -eq 0 ]
then
    echo "Successfully compiled bmp2asc.c"
else
    echo "Failed to compile bmp2asc.c"
    exit 1
fi

# compiles asciiprinter.c -o print
gcc asciiprinter.c -o print -O3

if [ $? -eq 0 ]
then
    echo "Successfully compiled asciiprinter.c"
else
    echo "Failed to compile asciiprinter.c"
    exit 1
fi