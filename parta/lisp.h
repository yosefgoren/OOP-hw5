#ifndef LISP_H
#define LISP_H
    
struct LPAR {};
struct RPAR {};
struct PLUS {};
struct MINUS {};
struct MUL {};
struct DIV {};
struct EQ {};
struct NOT {};
struct COND {};

struct FACT {};

template <int v>
struct Int {
    static constexpr int value = v;
};

// Eval (initial) =============================================================================================================

static const int UNDEFINED = -3;

template<typename ...List>
struct Eval{
    static constexpr int value = UNDEFINED;
    static constexpr int drop_amount = UNDEFINED;
};

// LPAR =============================================================================================================
template<typename ...List>
struct Eval<LPAR, List...>{
    static constexpr int value = Eval<List...>::value;
    static constexpr int drop_amount = 1+Eval<List...>::drop_amount;
};

// RPAR - CountClosingPar =============================================================================================================
template<typename ...List>
struct CountClosingPar{
    static constexpr int num_closing_par = 0;
};

template<typename ...List>
struct CountClosingPar<RPAR, List...>{
    static constexpr int num_closing_par = 1 + CountClosingPar<List...>::num_closing_par;
};

// Int =============================================================================================================
template<int n, typename ...ToDiscard>
struct Eval<Int<n>, ToDiscard...>{
    static constexpr int value = n;
    static constexpr int drop_amount = 1 + CountClosingPar<ToDiscard...>::num_closing_par;
};

// EvalAfter =============================================================================================================
template<unsigned int InHowLong, typename Head, typename ...Tail>
struct EvalAfter{
    static constexpr int value = EvalAfter<InHowLong-1, Tail...>::value;
    static constexpr int drop_amount = EvalAfter<InHowLong-1, Tail...>::drop_amount;
};

template<typename Head, typename ...Tail>
struct EvalAfter<0, Head, Tail...>{
    static constexpr int value = Eval<Head, Tail...>::value;
    static constexpr int drop_amount = Eval<Head, Tail...>::drop_amount;
};

// FACT =============================================================================================================
template<typename ...List>
struct Eval<FACT, List...>{
    static constexpr int value = Eval<FACT, Int<Eval<List...>::value>>::value;
    static constexpr int drop_amount = 1 + Eval<List...>::drop_amount;
};

template<int n, typename ...ToDiscard>
struct Eval<FACT, Int<n>, ToDiscard...>{
    static constexpr int value = n*Eval<FACT, Int<n-1>>::value;
    static constexpr int drop_amount = Eval<FACT, Int<n-1>, ToDiscard...>::drop_amount;
};

template<typename ...ToDiscard>
struct Eval<FACT, Int<0>, ToDiscard...>{
    static constexpr int value = 1;
    static constexpr int drop_amount = 2 + CountClosingPar<ToDiscard...>::num_closing_par;
};

// NOT =============================================================================================================
template<typename ...List>
struct Eval<NOT, List...>{
    static constexpr int value = (Eval<List...>::value == 0);
    static constexpr int drop_amount = 1 + Eval<List...>::drop_amount;
};

// PLUS =============================================================================================================
template<typename ...List>
struct Eval<PLUS, List...>{
    static constexpr int value = Eval<List...>::value + EvalAfter<Eval<List...>::drop_amount, List...>::value;
    static constexpr int drop_amount = 
        1 + Eval<List...>::drop_amount + EvalAfter<Eval<List...>::drop_amount, List...>::drop_amount;
};

// MINUS =============================================================================================================
template<typename ...List>
struct Eval<MINUS, List...>{
    static constexpr int value = Eval<List...>::value - EvalAfter<Eval<List...>::drop_amount, List...>::value;
    static constexpr int drop_amount = 
        1 + Eval<List...>::drop_amount + EvalAfter<Eval<List...>::drop_amount, List...>::drop_amount;
};

// MUL =============================================================================================================
template<typename ...List>
struct Eval<MUL, List...>{
    static constexpr int value = Eval<List...>::value * EvalAfter<Eval<List...>::drop_amount, List...>::value;
    static constexpr int drop_amount = 
        1 + Eval<List...>::drop_amount + EvalAfter<Eval<List...>::drop_amount, List...>::drop_amount;
};

// DIV =============================================================================================================
template<typename ...List>
struct Eval<DIV, List...>{
    static constexpr int value = Eval<List...>::value / EvalAfter<Eval<List...>::drop_amount, List...>::value;
    static constexpr int drop_amount = 
        1 + Eval<List...>::drop_amount + EvalAfter<Eval<List...>::drop_amount, List...>::drop_amount;
};

// EQ =============================================================================================================
template<typename ...List>
struct Eval<EQ, List...>{
    static constexpr int value = Eval<List...>::value == EvalAfter<Eval<List...>::drop_amount, List...>::value;
    static constexpr int drop_amount = 
        1 + Eval<List...>::drop_amount + EvalAfter<Eval<List...>::drop_amount, List...>::drop_amount;
};

// COND =============================================================================================================
template<typename ...List>
struct Eval<COND, List...>{
    static constexpr int first_param_len = Eval<List...>::drop_amount;
    static constexpr int value_first_param = Eval<List...>::value;

    static constexpr int second_param_len = EvalAfter<first_param_len, List...>::drop_amount;
    static constexpr int value_second_param = EvalAfter<first_param_len, List...>::value;
    
    static constexpr int third_param_len = EvalAfter<first_param_len + second_param_len, List...>::drop_amount;
    static constexpr int value_third_param = EvalAfter<first_param_len + second_param_len, List...>::value;

    static constexpr int value = (value_first_param ? value_second_param : value_third_param);    
    static constexpr int drop_amount = 1 + first_param_len + second_param_len + third_param_len;
};

#endif /* LISP_H */
