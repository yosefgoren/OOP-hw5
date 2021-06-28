#include "lisp.h"

int main(int argc, char** argv) {
    Eval<PLUS, Int<1>, Int<2>> v1;
    Eval<LPAR, PLUS, Int<1>, Int<2>, RPAR> v2;
    Eval<COND, Int<1>, Int<1>, Int<0>> v3; // v3::value == 1
    Eval<COND, Int<0>, Int<1>, Int<5>> v4; // v4::value == 5
    Eval<COND, LPAR, EQ, Int<5>, LPAR, PLUS, Int<3>, Int<2>, RPAR, RPAR, Int<2>, LPAR, PLUS, Int<2>, Int<0>, RPAR> v5;
}
