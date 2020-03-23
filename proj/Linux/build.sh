
mkdir bin
mkdir bin/release
mkdir bin/debug

mkdir object
mkdir object/release
mkdir object/release/interp
mkdir object/debug
mkdir object/debug/interp

release() {

    echo "Building INTP."

	gcc -Wall -O2 -c ../../src/log.c -o object/release/log.o    
	gcc -Wall -O2 -c ../../src/data.c -o object/release/data.o
    gcc -Wall -O2 -c ../../src/lexer.c -o object/release/lexer.o
    gcc -Wall -O2 -c ../../src/interp/expr.c -o object/release/interp/expr.o
    gcc -Wall -O2 -c ../../src/interp/interp.c -o object/release/interp/interp.o
    gcc -Wall -O2 -c ../../src/core.c -o object/release/core.o
    gcc -Wall -O2 -c ../../src/main.c -o object/release/main.o

    gcc -o bin/release/intp object/release/main.o object/release/log.o object/release/lexer.o object/release/data.o object/release/interp/expr.o object/release/interp/interp.o object/release/core.o -s -O2

    echo "Build ended."
}

debug() {
    echo "Building INTP (debug)."

	gcc -Wall -g -c ../../src/log.c -o object/debug/log.o
    gcc -Wall -g -c ../../src/lexer.c -o object/debug/lexer.o
    gcc -Wall -g -c ../../src/data.c -o object/debug/data.o
    gcc -Wall -g -c ../../src/interp/expr.c -o object/debug/interp/expr.o
    gcc -Wall -g -c ../../src/interp/interp.c -o object/debug/interp/interp.o
    gcc -Wall -g -c ../../src/core.c -o object/debug/core.o
    gcc -Wall -g -c ../../src/main.c -o object/debug/main.o

    gcc -o bin/debug/intp object/debug/main.o object/debug/log.o object/debug/lexer.o object/debug/data.o object/debug/interp/interp.o object/debug/interp/expr.o object/debug/core.o

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

