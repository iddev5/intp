echo "Building INTP (debug)."

mkdir bin
mkdir bin/debug

mkdir object
mkdir object/debug

gcc -Wall -g -c ../../src/lexer/lexer.c -o object/debug/lexer.o
gcc -Wall -g -c ../../src/parser/parser.c -o object/debug/parser.o
gcc -Wall -g -c ../../src/core.c -o object/debug/core.o
gcc -Wall -g -c ../../src/main.c -o object/debug/main.o

gcc -o bin/debug/intp object/debug/main.o object/debug/lexer.o object/debug/parser.o object/debug/core.o

echo "Build ended."