cat $0

a="-Isrc -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC -g -fsanitize=address"

for f in $(src/*.c)
do
    echo "gcc  -c src/*.c $a"
done

gcc  -c $1 src/*.c   -Isrc -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC -g -fsanitize=address


gcc  *.o             -Isrc -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC -g -fsanitize=address
rm *.o
./a.out $@
