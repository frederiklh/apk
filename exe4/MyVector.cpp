template <typename T>
class MyVector
{
public:
    explicit MyVector(int capacity = 10){
        data_= new T[capacity];
    }
    
    MyVector(const MyVector& other){
        MyVector temp(other);
        swap(*this, temp);
        
        return *this;
    }
    
    MyVector& operator=(const MyVector& other){
        MyVector temp(other);
        swap(*this, temp);
        
        return *this;
    }
    
    ~MyVector(){
        delete[] data_;
    }
    
    int size() const{
        
    }
    
    T& back(){
        
    }
    
    void push_back( const T& t ){
        
    }
    
    void pop_back(){
        
    }
    
    void insert(const T& t, size_t n){
        
    }
    
    T* begin(){
        return data_;
    }
    
    T* end(){
        return data_ + 
    }
    
    T& operator[]( size_t i ){
        return data_[i];
    }
private:
    T* data_; /* Contains the actual elements - data on the heap */
};
