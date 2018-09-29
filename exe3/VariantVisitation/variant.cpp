#include <iostream>
#include <vector>
#include "boost/variant.hpp"

class Writer{
public:
    Writer(int i)
    {
        writer_ = writerList_[i];
    }
    
    std::string print() const{
        return writer_;
    };
    
    
private:
    std::vector<std::string> writerList_ = {"Hello", "Hallo", "Yellow"};
    std::string writer_;
};

std::ostream& operator<<(std::ostream& os, const Writer& writer){
    os << writer.print();
    return os;
}

class Visitor : public boost::static_visitor<std::string>
{
public:
    std::string operator()(int & i) const
    {
        return std::string("the integer ") + std::to_string(i) + std::string(" has been accessed");
    }
    
    std::string operator()(Writer & w) const
    {
        return std::string("the writer ") + w.print() + std::string(" has been accessed");
    }
    
    std::string operator()(double & d) const
    {
        return std:: string("the double ") + std::to_string(d) + std::string(" has been accessed");
    }
    
};



int main(){
    // Double testing
    boost::variant<int, Writer, double> u = 20.2;
    std::cout << boost::apply_visitor( Visitor(), u) << std::endl;
    std::cout << u << std::endl;                 
    
    // Integer testing
    u = 1;
    std::cout << boost::apply_visitor( Visitor(), u) << std::endl;
    std::cout << u << std::endl;     
    
    // Writer testing
    for(int i =0; i < 3; i++){
        u = Writer(i);
        std::cout << boost::apply_visitor( Visitor(), u) << std::endl;
        std::cout << u << std::endl;     
    }
}
