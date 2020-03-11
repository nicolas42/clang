# Make system in bash
# run cake to make, clean to clean
# puts object files in obj dir

cake(){
    for f in `find . -name "*.c"` ; do 
        cc -c -g -std=c99 -Wall -Werror $f -o obj/${f%.c}.o ; 
    done 

    find . -name "*.o" -exec  \
        cc -o main {} + ;
    
    ./main ;

}

clean(){
    for f in `find . -name "*.o"` ; do 
        rm $f ;
    done 
    rm main
}

# find -exec
# https://unix.stackexchange.com/questions/389705/understanding-the-exec-option-of-find/389706


# find . -type f -name "*.c" -exec sh -c \
#    'cc -c -g -std=c99 -Wall -Werror $1 -o obj/${1%.c}.o' \
#    sh {} ';'
