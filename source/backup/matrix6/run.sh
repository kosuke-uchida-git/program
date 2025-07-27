DIRNAME=$(basename "$PWD")

DEBUG_FLAG=""
if [ "$1" == "-debug" ]; then
    DEBUG_FLAG="-DDEBUG"
fi

if [ -f ./a.out ]; then
    rm a.out
fi

gcc $DEBUG_FLAG -Wall -pedantic -O3 -march=native -ffast-math -funroll-loops -flto -fopenmp \
-o a.out $(find . -type f \( -name "*.c" \)) -lm

if [ -f ./a.out ]; then
    find . -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -i {} +
    ./a.out
    rm a.out
    cd ..

    if [ -f "./$DIRNAME.zip" ]; then
        rm "./$DIRNAME.zip"
    fi

    zip -rq "$DIRNAME.zip" "$DIRNAME"
fi
