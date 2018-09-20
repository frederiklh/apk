#include <iostream>
#include <vector>
#include "MyIterator.h"
#include <iterator>
#include <numeric>

template <typename T>
MyIterator<T>& operator+(int i, MyIterator<T>& it) {return it+i;}

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
        MyIterator<T> j = p.begin();
        for(MyIterator<T> i = begin(); i!=end(); i++, j++){
            *i = *j;
        }
        return *this;
    }
    // Assignment operator for two of different types
    template<typename U>
    MyArray<T, N> & operator =(const MyArray<U, N> & p) {
        std::cout << "assignment operator called" << std::endl;
        MyIterator<U> j = p.begin();
        for(MyIterator<T> i = begin(); i!=end(); i++, j++){
            *i = *j;
        }
        return *this;
    }
    // Copy constructor
    template<typename U>
    MyArray(const MyArray<U, N> & p) {
        std::cout << "copy constructor called" << std::endl;
        _elements = new T[N];
        MyIterator<U> j = p.begin();
        for(MyIterator<T> i = begin(); i!=end(); i++, j++){
            *i = *j;
        }
    }
    // Destructor
    ~MyArray() {
        std::cout << "destructor called" << std::endl;
        delete [] _elements;
    }
    void fill(const T& t) {
        for(MyIterator<T> i = begin(); i!=end(); i++){
            *i = t;
        }
    }
    MyIterator<T> begin() const{
        return MyIterator<T>(_elements);
    }
    MyIterator<T> end() const{
        return MyIterator<T>(_elements + _maxsize);
    }
    MyIterator<const T> cbegin() const{
        return MyIterator<const T>(_elements);
    }
    MyIterator<const T> cend() const{
        return MyIterator<const T>(_elements + _maxsize);
    }
    
    T& operator [](int const index){
        return *(_elements+index);
    }
    std::size_t size() const{
        return _maxsize;
    }
    void print() const{
        for(MyIterator<T> i = begin(); i!=end(); i++){
            std::cout << "Value=" << *i << std::endl;
        }
    }
private:
    T* _elements;
    std::size_t _maxsize;
};


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
        
        // assignment and copy testing for different types
        MyArray<double, 10> myDouble;
        myDouble.fill(3);
        myDouble.print();
        MyArray<int, 10> myIntArray(myDouble);
        myDouble = myIntArray;
        myDouble.print(); 
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
    
    // Algo testing
    {
        std::cout << "\n======MyArray iterator testing======" << std::endl;
        MyArray<double, 10> myArray;
        myArray.fill(3);
        std::cout << "Test of std::copy operator. Should output a line with 10 3s" << std::endl;
        std::copy(myArray.cbegin(), myArray.cend(), std::ostream_iterator<double>(std::cout, " "));
        
        std::cout << std::endl << "Test of std::accumulate. Should print out 30." << std::endl;
        std::cout << std::accumulate(myArray.begin(), myArray.end(), 0) << std::endl;
    }
}
