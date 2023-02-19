# ASCIIPrinter

ASCIIPrinter is a high-speed ASCII converter that converts photos to ASCII right in the console! The program is written in C, and it also happens to be fast enough to be capable of playing full-speed videos in ASCII format. The project doesn't rely on any external libraries other than the C stdlib.  

ASCIIPrinter features a custom file format for storing and retrieving ASCII photo/video data and when playing videos is optimized for a consistent framerate even with potential console print lag. There are two versions of ASCIIPrinter, one for photos and one for videos. They are both included.

If any of the `.sh` files give a permission error, you may need to elevate them! Do this by typing `chmod +x <file>`. They should then be executable.

## ASCIIPrinter Photo

### Photo convert

To start use `./compile.sh` to compile both ASCIIPrinter Photo and Video.

To convert your photos to .asc, simply place your .bmp files into the "images" folder, and run `./convert <input filename, no extension>`. 

For example, to convert the blackbuck.bmp image included, I would run `./convert blackbuck`. 

### Photo print

Once your .bmp photo has been converted to a .asc file, you can run `./print <input name, no extension> <scaleFactor>`. 

The scale factor is how small you want your image to be. scaleFactor 1 is the full original resolution, 2 is 1/2 resolution, 3 is 1/3, etc.

For example, to print the blackbuck image at 1/10 size, I would run `./print blackbuck 10`.

Once you run the print command you should see your ascii image print in the terminal! If it looks weird, then try decreasing the scaleFactor or zooming out in your terminal.



## ASCIIPrinter Video

While the AsciiPrinter program wasn't initally intended to play videos, when I saw how fast it ran at a reasonable size I just had to get it to play video.

If you haven't used `./compile.sh` in the root directory yet, please do it now to compile ASCIIPrinter Video.

Everything for ASCIIPrinter Video is located in the video folder. to get there, type `cd video`.

### Video convert

To convert videos, you will first have to have the frames separated into .bmp files. These image files(and the .asc that my program generates) are uncompressed, so videos at a relatively low resolution and that are under a minute are recommended to save hard drive space. That being said, if you are fine with using more space, higher resolution and/or longer videos will work fine. 

Once you have your folder of frames in .bmp format, drag the whole folder into the `frames` folder. This allows you to have multiple videos at once, as whatever the name of your folder is, is what you will use to run the commands. 

To convert your folder of videos, run `./videoconvert.sh <foldername> [-deletebmps]`. 

`-deletebmps` is an optional flag that will delete your original .bmp files after you convert them to .asc files. 

For example, if my folder in `frames` is called "myVideo" and I wanted to delete the original .bmps after conversion, I would then type `./videoconvert.sh myVideo -deletebmps`.

You'll see your files getting converted in the terminal once you run the command.

### Video play

Once your video is converted, you can play it by using `./playvideo.sh <foldername> <scale> [framerate]`.

The scaling works the same as in ASCIIPrinter Photo, and framerate is an optional argument. It defaults to 30fps if not specified.

For example, if you wanted to play "myVideo" at 1/5 scale and it was a 60fps video, you would type `./playvideo.sh myVideo 5 60`.

If you set the framerate to a different value than the original video was, the timing will be off! Make sure to set the correct framerate if it is different than 30.
