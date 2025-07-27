DIRNAME=$(basename "$PWD")

DEBUG_FLAG=""
if [ "$1" == "-debug" ]; then
    DEBUG_FLAG="-DDEBUG"
fi

if [ -f ./a.out ]; then
    rm a.out
fi

gcc -O3 -fopenmp -march=native -ffast-math -funroll-loops -std=c17 -Wall \
    -o a.out $(find . -type f \( -name "*.c" \)) $DEBUG_FLAG

if [ -f ./a.out ]; then
    find . -type f -regex '.*\.\(c\|cxx\|h\)' -exec clang-format -i {} +
    ./a.out
    rm a.out
    cd ..

    if [ -f "./$DIRNAME.zip" ]; then
        rm "./$DIRNAME.zip"
    fi

    zip -rq "$DIRNAME.zip" "$DIRNAME"
fi
