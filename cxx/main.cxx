#include"utilities/math/matrix.h"

int main(void){
   Matrix test("file.txt");
    test.print();
    test.output("output.txt");
    return 0;
}