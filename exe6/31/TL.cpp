struct NullType {};

template <typename L, typename R>
struct TypeList
{
    typedef L First;
    typedef R Rest;
};

int main(){
    
    typedef TypeList<int, NullType> TYPELIST1(int) IntTL;
    
    //typedef TypeList<char, TypeList<int, TypeList<long, TypeList<short, NullType>>>> TYPELIST4 MixTL;
    
    //typedef TYPELIST1(int) IntTL;

    //typedef TYPELIST4(char , int , long , short) MixTL;
    
    return 0;
}
