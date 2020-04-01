
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

	tcc -Wall -c ../../src/log.c -o object/release/log.o    
	tcc -Wall -c ../../src/data.c -o object/release/data.o
    tcc -Wall -c ../../src/lexer.c -o object/release/lexer.o
    tcc -Wall -c ../../src/interp/expr.c -o object/release/interp/expr.o
    tcc -Wall -c ../../src/interp/interp.c -o object/release/interp/interp.o
    tcc -Wall -c ../../src/core.c -o object/release/core.o
    tcc -Wall -c ../../intpcli.c -o object/release/intpcli.o

    tcc -o bin/release/intp object/release/intpcli.o object/release/log.o object/release/lexer.o object/release/data.o object/release/interp/expr.o object/release/interp/interp.o object/release/core.o

    echo "Build ended."
}

debug() {
    echo "Building INTP (debug)."

	tcc -Wall -g -c ../../src/log.c -o object/debug/log.o
    tcc -Wall -g -c ../../src/lexer.c -o object/debug/lexer.o
    tcc -Wall -g -c ../../src/data.c -o object/debug/data.o
    tcc -Wall -g -c ../../src/interp/expr.c -o object/debug/interp/expr.o
    tcc -Wall -g -c ../../src/interp/interp.c -o object/debug/interp/interp.o
    tcc -Wall -g -c ../../src/core.c -o object/debug/core.o
    tcc -Wall -g -c ../../intpcli.c -o object/debug/intpcli.o

    tcc -o bin/debug/intp object/debug/intpcli.o object/debug/log.o object/debug/lexer.o object/debug/data.o object/debug/interp/interp.o object/debug/interp/expr.o object/debug/core.o 

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

