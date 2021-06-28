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

#endif /* LISP_H */
