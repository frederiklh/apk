
// Exercise 3.1 Write your own TL
template <typename L, typename R>
struct TypeList
{
    typedef L First;
    typedef R Rest;
};

struct NullType {};

#define TYPELIST1(arg1) TypeList<arg1, NullType>
#define TYPELIST2(arg1, arg2) TypeList<arg1, TYPELIST1(arg2)>
#define TYPELIST3(arg1, arg2, arg3) TypeList<arg1, TYPELIST2(arg2, arg3)>
#define TYPELIST4(arg1, arg2, arg3, arg4) TypeList<arg1, TYPELIST3(arg2, arg3, arg4)>

typedef TYPELIST1(int) IntTL;
typedef TYPELIST4(int, char, long, short) MixTL;


// Exercise 3.2.1 struct IsSame<>
template<typename T, typename U>
struct IsSame
{
    // Default case: T and U are not the same type
    static const bool value = false;  
};

template<typename T>
struct IsSame<T,T>
{
    // Specialization: both template arguments are of the same type
    static const bool value = true;  
};


// Exercise 3.2.2 struct Contains<>
template<typename TypeList, typename T>
struct Contains
{
    static const bool value = IsSame<typename TypeList::First, T>::value // Base case
    || Contains<typename TypeList::Rest, T>::value; // Recursive case
};

template<typename T>
struct Contains<NullType, T>
{
    static const bool value = false;
};


// Exercise 3.2.3 struct AtIndex<>
//Declare the AtIndex struct
template<class T, unsigned int i> 
struct AtIndex;

// Get the i'th index of a typelist: Base case, i = 0.
template<>
template<class T, class U>
struct AtIndex<TypeList<T, U>, 0> 
{
    typedef T type;
};

// Get the (i-1)'th index of the typelist U
template<>
template<class T, class U, unsigned int i>
struct AtIndex<TypeList<T, U>, i> 
{
    typedef typename AtIndex<U, i-1>::type type;
};


// Exercise 3.2.4 struct PrintIT<>
template<class T, unsigned int i> 
struct PrintIT;

template<>
template<class T, class U>
struct PrintIT<TypeList<T, U>, 0> 
{
    typedef T type;
};

template<>
template<class T, class U, unsigned int i>
struct PrintIT<TypeList<T, U>, i> 
{
    typedef typename PrintIT<U, i-1>::type type;
};


#include <iostream>
int main(){
    
    // IsSame test
    std::cout << "IsSame <int, int>::value= " << IsSame<int, int>::value << std::endl;
    std::cout << "IsSame <int, char>::value= " << IsSame<int, char>::value << std::endl;
    
    // Contains test
    typedef TYPELIST3(int, char, long) TL;
    std::cout << "Contains<TL, int>::value= " << Contains<TL, int>::value << std::endl;
    std::cout << "Contains<TL, std::string>::value= " << Contains <TL, std::string>::value << std::endl;
    
    // AtIndex test
    std::cout << "IsSame<typename AtIndex<TL, 0>::type, int>::value= " << IsSame<typename AtIndex<TL, 0>::type, int>::value << std::endl;
    std::cout << "IsSame<typename AtIndex<TL, 2>::type, int>::value= " << IsSame<typename AtIndex<TL, 2>::type, int>::value << std::endl;
    
    
    return 0;
}
