#include "free.h"
#include <iostream>
#include "lisp.h"
#include "eval.h"

using namespace std;

// #define Check(exp,num) cout << \
//     (exp::value == num ?\
//     "PASSED\n" :\
//     "FAIL in expression: \n" + #exp + "\n expected to be " + atoi(num) + "\n"); 

bool passed_all = true;
unsigned checks_done = 0;

void printBool(bool b){
    cout << (b ? "TRUE" : "FALSE");
}

void check(int x, int y){
    cout << (x == y ? "PASS" : "FAIL") << ",    check number: " << checks_done << endl;
    cout << "       result: " << x << ", expected: " << y << endl;
    passed_all = passed_all&&(x == y);

    ++checks_done;
}

int main(){
    //check number 0:
    check(Eval<COND, Int<1>, Int<2>, Int<3>>::value, 2);
    check(Eval<COND, Int<0>, Int<2>, Int<3>>::value, 3);
    check(Eval<COND, EQ, Int<39>, Int<17>, PLUS, Int<10>, Int<30>, MINUS, Int<9>, Int<3>>::value, 6);
    
    check(Eval<Int<24>>::value, 24);
    check(Eval<COND, Int<1>, Int<24>, PLUS, Int<1>, Int<3>>::value, 24);
    check(Eval<COND, Int<1>, COND, Int<1>, Int<24>, Int<2>, PLUS, Int<1>, Int<3>>::value, 24);
    //check number 6:
    check(Eval<COND, Int<1>, COND, Int<1>, FACT, Int<4>, Int<2>, PLUS, Int<1>, Int<3>>::value, 24);
    check(Eval<COND, Int<1>, COND, Int<1>, LPAR, LPAR, FACT, Int<4>, RPAR, RPAR, LPAR, Int<2>, RPAR, PLUS, Int<1>, Int<3>>::value, 24);    
    check(Eval<COND, COND, Int<0>, Int<9>, LPAR, Int<1>, RPAR, COND, Int<1>, LPAR, LPAR, FACT, Int<4>, RPAR, RPAR, LPAR, Int<2>, RPAR, PLUS, Int<1>, Int<3>>::value, 24);    
    //check number 9:
    check(Eval<COND, COND, Int<0>, Int<9>, LPAR, Int<1>, RPAR, Int<2>, Int<3>>::value, 2);
    check(Eval<COND, COND, Int<0>, Int<9>, Int<1>, Int<2>, Int<3>>::value, 2);
    check(Eval<
        PLUS, 
            LPAR, COND,
                COND,
                    Int<0>,
                    Int<9>,
                    LPAR, Int<1>, RPAR,
                COND,
                    Int<1>,
                    LPAR, LPAR, FACT, Int<4>, RPAR, RPAR,
                    LPAR, Int<2>, RPAR,
                PLUS, Int<1>, Int<3>,
            RPAR,
            Int<1>
        >::value, 25);    
    
    //check number 12:
    check(Eval<FACT, LPAR, MINUS, LPAR, Int<5>, RPAR, LPAR, Int<2>, RPAR, RPAR>::value, 6);

    cout << "passed all = ";
    printBool(passed_all);
    cout << endl;
}
