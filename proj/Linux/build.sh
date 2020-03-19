
mkdir bin
mkdir bin/release
mkdir bin/debug

mkdir object
mkdir object/release
mkdir object/debug

release() {

    echo "Building INTP."

    gcc -Wall -O2 -c ../../src/lexer.c -o object/release/lexer.o
    gcc -Wall -O2 -c ../../src/parser.c -o object/release/parser.o
    gcc -Wall -O2 -c ../../src/core.c -o object/release/core.o
    gcc -Wall -O2 -c ../../src/main.c -o object/release/main.o

    gcc -o bin/release/intp object/release/main.o object/release/lexer.o object/release/parser.o object/release/core.o -s -O3

    echo "Build ended."
}

debug() {
    echo "Building INTP (debug)."

    gcc -Wall -g -c ../../src/lexer.c -o object/debug/lexer.o
    gcc -Wall -g -c ../../src/parser.c -o object/debug/parser.o
    gcc -Wall -g -c ../../src/core.c -o object/debug/core.o
    gcc -Wall -g -c ../../src/main.c -o object/debug/main.o

    gcc -o bin/debug/intp object/debug/main.o object/debug/lexer.o object/debug/parser.o object/debug/core.o

    echo "Build ended."
}

run() {
    debug
    ./bin/debug/intp bin/debug/test.intp
}

if [ "$1" = "release" ]
then release 

elif [ "$1" = "run" ]
then run

else debug
fi

