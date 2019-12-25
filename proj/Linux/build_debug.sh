echo "Building INTP (debug)."

mkdir bin
mkdir bin/debug

mkdir object
mkdir object/debug
mkdir object/debug/sds

gcc -Wall -g -c ../../src/sds/sds.c -o object/debug/sds/sds.o
gcc -Wall -g -c ../../src/lexer.c -o object/debug/lexer.o
gcc -Wall -g -c ../../src/parser.c -o object/debug/parser.o
gcc -Wall -g -c ../../src/core.c -o object/debug/core.o
gcc -Wall -g -c ../../src/main.c -o object/debug/main.o

gcc -o bin/debug/intp object/debug/main.o object/debug/lexer.o object/debug/parser.o object/debug/core.o object/debug/sds/sds.o

echo "Build ended."