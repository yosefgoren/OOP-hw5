#ifndef FREE
#define FREE

template<typename ...T>
struct Tuple{
    static constexpr int size = sizeof ...(T);
};

#endif