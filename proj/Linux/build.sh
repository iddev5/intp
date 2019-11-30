echo "Building INTP."

mkdir bin
mkdir bin/release

mkdir object
mkdir object/release
mkdir object/release/sds

gcc -Wall -O2 -c ../../src/sds/sds.c -o object/release/sds/sds.o
gcc -Wall -O2 -c ../../src/lexer.c -o object/release/lexer.o
gcc -Wall -O2 -c ../../src/parser.c -o object/release/parser.o
gcc -Wall -O2 -c ../../src/intp.c -o object/release/intp.o
gcc -Wall -O2 -c ../../src/main.c -o object/release/main.o

gcc -o bin/release/intp object/release/main.o object/release/lexer.o object/release/parser.o object/release/intp.o object/release/sds/sds.o -s

echo "Build ended."