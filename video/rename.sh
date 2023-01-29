

path="frames/$1/"

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
        echo "No .asc files in folder! Conversion must have failed!"
        exit 1
    else
        #allow for mass file deletion
        find . -name "*.bmp" -print0 | xargs -0 rm
        echo "Removed all .bmp files in $path"
    fi
fi