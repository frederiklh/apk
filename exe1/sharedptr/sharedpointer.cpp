#include <iostream>
// SharedPtr implementation
/*
template<typename T, typename D>
class SharedPtr
{
public:
    explicit SharedPtr<T>(T* t) : p_(t), counter_(new size_t(1)) {
        std::cout << "Constructor called\n";
        this->count();
    }
    // Copy constructor overloading
    SharedPtr<T>(const SharedPtr<T>& p) : p_(p.p_), counter_(p.counter_) {
        ++*counter_;
        std::cout << "Copy constructor called\n";
        this->count();
    }
    // Assignment operator overloading
    SharedPtr<T> & operator=(const SharedPtr<T> & p){
        // self assignment
        if(this == &p){
            std::cout << "Assignment operator called (self assignment)\n";
            this->count();
            return *this;
        }
        if(--*counter_ <= 0){
            std::cout << "Destroying old pointer, because of new assignment\n";
            delete p_;
            delete counter_;
        }
        p_ = p.p_;
        counter_ = p.counter_;
        ++*counter_;
        std::cout << "Assignment operator called\n";
        this->count();
        return *this;
    }
    
    ~SharedPtr<T>(){
        if(--*counter_ <= 0){
            std::cout << "Left scope and decremented counter\n";
            this->count();
            delete p_;
            delete counter_;
            std::cout << "Destructor called\n";
        }
        else{
            std::cout << "Left scope and decremented counter\n";
            this->count();
        }
    }
    
    // Exercise 2.2.2 - Overloading bool operator, to get the nullptr comparison
    explicit operator bool() const{ 
        return p_; 
    }
    
    // Smart pointer idiom
    T& operator*() const{
        return *p_;
    }
    T* operator->() const{
        return p_;
    }
    std::size_t count() const{
        std::cout << "count=" << *counter_ << std::endl;
        return *counter_;
    }
private:
    T* p_;
    std::size_t * counter_;
};*/


// SharedPtr helper implementation
namespace details {
        template<typename T>
        struct Helper {
            virtual void operator()(T *t) = 0;
            virtual ~Helper() {}
        };

        template<typename T, typename D>
        struct HelperImpl : public Helper<T> {
            HelperImpl(D d) : d_(d) {};

            void operator()(T *t) {
                d_(t);
            }

            D d_;
        };
    }
template<typename T>
class SharedPtr
{
public:
    explicit SharedPtr(T* t) : p_(t), counter_(new size_t(1)) {
        std::cout << "Explicit constructor called\n";
        this->count();
    }
    template<typename D>
    SharedPtr(T* const t, D const d) : SharedPtr(t) {
        std::cout << "Constructor called\n";
        h_ = new details::HelperImpl<T,D>(d);
    }
    // Copy constructor overloading
    SharedPtr(const SharedPtr& p) : p_(p.p_), counter_(p.counter_), h_(p.h_) {
        ++*counter_;
        std::cout << "Copy constructor called\n";
        this->count();
    }
    // Assignment operator overloading
    SharedPtr & operator=(const SharedPtr & p){
        // self assignment
        if(this == &p){
            std::cout << "Assignment operator called (self assignment)\n";
            this->count();
            return *this;
        }
        if(--*counter_ <= 0){
            if(h_){
                (*h_)(p_);
            } 
            else {
                delete p_;
            }
            std::cout << "Destroying old pointer, because of new assignment\n";
            delete h_;
            delete counter_;
        }
        p_ = p.p_;
        counter_ = p.counter_;
        ++*counter_;
        h_ = p.h_;
        std::cout << "Assignment operator called\n";
        this->count();
        return *this;
    }
    
    ~SharedPtr(){
        if(--*counter_ <= 0){
            if(h_){
                (*h_)(p_);
            } 
            else {
                delete p_;
            }
            std::cout << "Left scope and decremented counter\n";
            this->count();
            delete h_;
            delete counter_;
            std::cout << "Destructor called\n";
        }
        else{
            std::cout << "Left scope and decremented counter\n";
            this->count();
        }
    }
    
    // Exercise 2.2.2 - Overloading bool operator, to get the nullptr comparison
    explicit operator bool() const{ 
        return p_; 
    }
    
    // Smart pointer idiom
    T& operator*() const{
        return *p_;
    }
    T* operator->() const{
        return p_;
    }
    std::size_t count() const{
        std::cout << "count=" << *counter_ << std::endl;
        return *counter_;
    }
private:
    T* p_;
    std::size_t * counter_;
    details::Helper<T> *h_ = nullptr;
};


// Exercise 2.2.3 - Overloading the equality operator
template<typename T, typename U>
bool operator==(const SharedPtr<T>& left, const SharedPtr<U>& right) 
{
    std::cout << &left << " == " << &right << std::endl;
    return &left == &right;
};
template<typename T, typename U>
bool operator!=(const SharedPtr<T>& left, const SharedPtr<U>& right) 
{
    return &left != &right;
};


struct CustomDestruct{
    void operator()(int* i){
        std::cout << "super custom" << *i << std::endl;
    }
};

typedef struct TestStruct{
    std::string a = "hello";
    std::string b = "world";
} TestStruct;


int main(){
    // SharedPtr testing
    {
    SharedPtr<int> p1 = SharedPtr<int>(new int(42));
    SharedPtr<int> p3 = SharedPtr<int>(new int(24));
    {
        SharedPtr<int> p2(p1);
        {
            p1 = p1;
            {
                p3 = p1;
            }
        }
    }
    
    //2.1: Conversion to bool - THIS WORKS
    SharedPtr<std::string> sp(new std::string("Hello world"));
    if(sp)
        std::cout << "SP Contains: " << *sp << std::endl;
    
    //2.2: Conversion to bool - THIS DOESN'T
    //SharedPtr <std::string > sp(new std:: string("Hello"));
    //SharedPtr <std::string > sp2(new std:: string("world"));
    //if(sp == sp2) // No comparison function implemented , thus should fail
    //    std::cout << "Do Stuff" << std::endl;
    //
    //int x = test << 1; // bool is not an int and should not be treated as one.
    
    // 2.2.3 Test of equality operator overload
    if(p1 == p1)
        std::cout << "They are equal" << std::endl;
    if(p1 != p3)
        std::cout << "They are not equal" << std::endl;
    }
    
    // SharedPtr helper testing
    {
        SharedPtr<TestStruct> mySharedPtr = SharedPtr<TestStruct>(new TestStruct);
        
        std::cout << "(*mySharedPtr).a << (*mySharedPtr).b returned: " << (*mySharedPtr).a << " " << (*mySharedPtr).b << std::endl;
        
        std::cout << "mySharedPtr->a << mySharedPtr->b returned: " << mySharedPtr->a << " " << mySharedPtr->b << std::endl;

        std::cout << "testing custom destructor:";
        SharedPtr<int>* cDestrShPtr = new SharedPtr<int>(new int(5), CustomDestruct());
        delete(cDestrShPtr);
    }
    
    return 0;
}
