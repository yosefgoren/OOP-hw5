#ifndef FREE
#define FREE

// template<typename ...T>
// struct Tuple{
//     static constexpr int size = sizeof ...(T);
// };

template<typename ...TT>
struct Tuple{
    static constexpr int size = (sizeof ...(TT));
};

#endif