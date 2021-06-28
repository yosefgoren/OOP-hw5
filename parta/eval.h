#ifndef EVAL
#define EVAL

#include "lisp.h"

template<typename ...T>
struct Eval{
    static constexpr int value;
    static constexpr int drop_amount;
};

// FACT =============================================================================================================


template<typename FACT, typename ...T>
struct Eval{
    static constexpr int value = 
    Eval<typename ...T>::drop_amout
};

template<>
struct Eval<typename FACT, typename Int<0>>{
    static constexpr int value = 1;
    static constexpr int drop_amount = 2;
};

template<int n>
struct Eval<typename FACT, typename Int<n>>{
    static constexpr int value = n*Eval<FACT, Int<n-1>>::value;
    static constexpr int drop_amount = 2;
};


// INT =============================================================================================================

template<int n>
struct Eval<typename Int<n>>{
    static constexpr int value = n;
    static constexpr int drop_amount = 1;
};


#endif