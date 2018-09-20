// std::iterator example
#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag

// REF: http://www.cplusplus.com/reference/iterator/iterator/

template<typename T>
class MyIterator : public std::iterator<std::input_iterator_tag, T>
{
private:
  T* p;
  
public:
  MyIterator() :p(nullptr) {}
  MyIterator(T* x) :p(x) {}
  MyIterator(const MyIterator& mit) : p(mit.p) {}
  
  MyIterator& operator++() {
      ++p;
      return *this;
  }
  MyIterator& operator--() {
      --p;
      return *this;
  }
  
  MyIterator operator++(int) {
      MyIterator tmp(*this); 
      operator++(); 
      return tmp;
  }
  MyIterator operator--(int) {
      MyIterator tmp(*this); 
      operator--(); 
      return tmp;
  }
  
  MyIterator operator+(int i) {
      p += i;
      return *this;
  }
  MyIterator operator-(int i) {
      p -= i;
      return *this;
  }
  int operator-(const MyIterator<T>& it) {return p - it.p;}


  bool operator==(const MyIterator& rhs) const {return p==rhs.p;}
  bool operator!=(const MyIterator& rhs) const {return p!=rhs.p;}
  bool operator<(const MyIterator& rhs) {return p<rhs.p;}
  bool operator<=(const MyIterator& rhs) {return p<=rhs.p;}
  bool operator>(const MyIterator& rhs) {return p>rhs.p;}
  bool operator>=(const MyIterator& rhs) {return p>=rhs.p;}
  
  T& operator*() {return *p;}
  T& operator->() {return *p;}
  T& operator[](int index) {return *(p+index);}
};
