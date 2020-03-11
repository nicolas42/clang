cat $0
gcc  -c $1 src/*.c   -Isrc -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC -g -fsanitize=address
gcc  *.o             -Isrc -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC -g -fsanitize=address
rm *.o
./a.out $@
