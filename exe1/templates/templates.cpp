#include <iostream>
#include <vector>

// MyArray
template<typename T, std::size_t N>
class MyArray{
public:
    typedef T value_type; // <-- For accumulation only
    
    // Constructor
    MyArray(): _maxsize(N) {
        std::cout << "constructor called" << std::endl;
        _elements = new T[_maxsize];
    }
    // Assignment operator for two of the same type
    MyArray<T, N> & operator =(const MyArray<T, N> & p) {
        std::cout << "assignment operator called" << std::endl;
        T * j = p.begin();
        for(T* i = begin(); i!=end(); i++, j++){
            *i = *j;
        }
        return *this;
    }
    // Assignment operator for two of different types
    template<typename U>
    MyArray<T, N> & operator =(const MyArray<U, N> & p) {
        std::cout << "assignment operator called" << std::endl;
        U * j = p.begin();
        for(T* i = begin(); i!=end(); i++, j++){
            *i = *j;
        }
        return *this;
    }
    // Copy constructor
    template<typename U>
    MyArray(const MyArray<U, N> & p) {
        std::cout << "copy constructor called" << std::endl;
        _elements = new T[N];
        U * j = p.begin();
        for(T* i = begin(); i!=end(); i++, j++){
            *i = *j;
        }
    }
    // Destructor
    ~MyArray() {
        std::cout << "destructor called" << std::endl;
        delete [] _elements;
    }
    void fill(const T& t) {
        for(T* i = begin(); i!=end(); i++){
            *i = t;
        }
    }
    T* begin() const{
        return _elements;
    }
    T* end() const{
        return _elements + _maxsize;
    }
    T& operator [](int const index){
        return *(_elements+index);
    }
    std::size_t size() const{
        return _maxsize;
    }
    void print() const{
        for(T* i = begin(); i!=end(); i++){
            std::cout << "Value=" << *i << " Adress=" << i << std::endl;
        }
    }
private:
    T* _elements;
    std::size_t _maxsize;
};
template<typename T, typename U>
T* myfind(T* first, T* last, const U& v){
    for( ; first!=last; first++){
        if(*first == v){
            std::cout << "myfind found value=" << v << " at adress=" << first << std::endl;
            return first;
        }
    }
    std::cout << "myfind did not find " << v << std::endl;
    return last;
}


// MyArray Partial specialisation
template<typename T, std::size_t N>
class MyArray<T*, N>{  // <-- Partial specialisation
public:
    // Constructor
    MyArray(): _maxsize(N) {
        std::cout << "Partial constructor called" << std::endl;
        _elements = new T*[_maxsize];
        for(T** i = begin(); i!=end(); i++){
            *i = nullptr;
        }
    }
    // Assignment operator for two of different types
    template<typename U>
    MyArray<T*, N> & operator =(const MyArray<U, N> & p) {
        std::cout << "Partial assignment operator called" << std::endl;
        U * j = p.begin();
        for(T** i = begin(); i!=end(); i++){
            *i = *j;
            j++;
        }
        return *this;
    }
    // Copy constructor
    template<typename U>
    MyArray(const MyArray<U, N> & p) {
        std::cout << "Partial copy constructor called" << std::endl;
        _elements = new T*[N];
        U * j = p.begin();
        for(T** i = begin(); i!=end(); i++){
            *i = *j;
            j++;
        }
    }
    // Destructor
    ~MyArray() {
        std::cout << "Partial destructor called" << std::endl;
        for(T** i = begin(); i!=end(); i++){
            delete *i;
        }
        delete [] _elements;
    }
    T** begin() const{
        return _elements;
    }
    T** end() const{
        return _elements + _maxsize;
    }
    T*& operator [](int const index){
        return *(_elements+index);
    }
    std::size_t size() const{
        return _maxsize;
    }
    void print() const{
        T** i = begin();
        for(T** j=i; j!=i+_maxsize; j++){
            std::cout << "Value=" << **j << " Adress=" << j << std::endl;
        }
    }
private:
    T** _elements;
    std::size_t _maxsize;
};
template<typename T, typename U>
T** myfind(T** first, T** last, const U& v){
    for( ; first!=last; first++){
        if(*first && **first == v){
            std::cout << "myfind found value=" << v << " at adress=" << first << std::endl;
            return first;
        }
    }
    std::cout << "myfind did not find " << v << std::endl;
    return last;
}


// Accumulation
template<typename U>
typename U::value_type myAccumulation (const U& u) {
    typename U::value_type m = typename U::value_type();
    for (auto first = u.begin(); first != u.end(); ++first) {
        m += *first;
    }
    return m;
}


int main() {
    // MyArray class testing
    {
        std::cout << "======MyArray class testing======" << std::endl;
        MyArray<int, 3> myArray;
        myArray[0] = 1;
        myArray[1] = 2;
        myArray.print();
        
        // size test
        std::cout << "size() = " << myArray.size() << std::endl;
        
        // assignment and destructor      
        {
            MyArray<int, 3> myArray2;
            myArray2 = myArray;
            myArray2.print();
        }
        
        // fill test
        myArray.fill(4);
        myArray.print();
        
        // myfind test
        MyArray<int, 5> mu;
        mu[3] = 3; 
        mu.print();
        myfind(mu.begin(), mu.end(), 8);
        myfind(mu.begin(), mu.end(), 3);
        myfind(mu.begin(), mu.end(), (double)3);
        myfind(mu.begin(), mu.end(), (float)3);
        
        // assignment and copy testing for different types
        MyArray<double, 10> myDouble;
        myDouble.fill(3);
        MyArray<int, 10> myIntArray(myDouble);
        myDouble = myIntArray;
    }
    
    // MyArray Partial specialisation testing
    {
        std::cout << "\n======Partial testing======" << std::endl;
        std::size_t const count = 10;
        MyArray<std::string *, count> my;
        for(int i = 0; i<count; i++){
            my[i] = new std::string("Hello" + std::to_string(i));
        }
        my.print();
        myfind(my.begin(),my.end(), std::string("Hello3")) != my.end();
    }
    
    // Accumulation testing
    {
        std::cout << "\n======Accumulation testing======" << std::endl;
        std::vector<std::string> myVector1 = {"Hello ", "world"};
        std::vector<int> myVector2 = {1, 2, 3, 4, 5};
        MyArray<int, 5> myArray;
        myArray.fill(1);
        std::cout << "myAccumulation (should be 'Hello world'): " << myAccumulation(myVector1) << std::endl;
        std::cout << "myAccumulation (should be '15'): " << myAccumulation(myVector2) << std::endl;
        std::cout << "myAccumulation (should be '5'): " << myAccumulation(myArray) << std::endl;
    }
}
