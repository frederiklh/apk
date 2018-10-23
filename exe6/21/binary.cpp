#include <cstddef>
#include <iostream>

template <size_t N>
struct Binary
{
    static const size_t value = Binary<N/10>::value << 1 | Binary<N%10>::value; 
    // Binary<N%10>::value <= kalder sig selv med Binary<TALLET>
    
    // static const size_t value = Binary<N/10>::value << 1 | N%10; // Sørens
};

template <>
struct Binary <0>
{
    static const size_t value = 0;
};

template <>
struct Binary <1>
{
    static const size_t value = 1;
};

template <>
struct Binary <2>
{};

template <>
struct Binary <3>
{};

template <>
struct Binary <4>
{};

template <>
struct Binary <5>
{};

template <>
struct Binary <6>
{};

template <>
struct Binary <7>
{};

template <>
struct Binary <8>
{};

template <>
struct Binary <9>
{};


int main(){
    std::cout << "Binary <1021 >:: value = " << Binary<1021>::value << std::endl; /* Should generate a compiler error , but does not! */
    std::cout << "Binary <1011 >:: value = " << Binary<1011>::value << std::endl;
    return 0;
}   
