/*****************************************/
/* Copyright: DevelEdu 2013              */
/* Author: sha                           */
/*****************************************/

// bindanyfunction.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
#include <mutex>
#include <functional>
#include "Events.hpp"
#include "Timer.hpp"
#include <typeinfo>
#include <sstream>
#include "boost/bind.hpp"

std::mutex stdioProt;


std::string printEvent(const std::shared_ptr<Event>& event){
    std::stringstream ss;
    
    //if(dynamic_cast<EventOther*>(&(*event)) != 0){
    //ss << typeid(*event).name();
    if(typeid(*event) == typeid(EventOther)){
        ss << "EventOther: ";
    }else if(typeid(*event) == typeid(Event)){
        ss << "Event: ";
    }else{
        ss << "Unknown derivative: ";
    }
    ss << *event;
    return ss.str();
}

void freeFunction(const std::shared_ptr<Event> &event) {
    // Protecting stdio since its not thread safe
    std::lock_guard<std::mutex> lock(stdioProt);
    std::cout << "freeFunction received: " << printEvent(event);
}


void withAnExtra(const std::shared_ptr<Event> &event, const std::string text) {
    // Protecting stdio since its not thread safe
    std::lock_guard<std::mutex> lock(stdioProt);
    std::cout << "withAnExtra received: " << printEvent(event);
    std::cout << "With extra text : " << text << std::endl;
}

struct testFunctor{
    void operator()(const std::shared_ptr<Event> &event){
        std::cout << "Functor received: " << printEvent(event);
    }
};


class ReferenceObj
{
public:
    ReferenceObj() : called_(0) 
    {
    }
    
    void call( const std::shared_ptr<Event>& event )
    {
        // Protecting stdio since its not thread safe
        std::lock_guard<std::mutex> lock(stdioProt );
        std::cout << "ReferenceObj received: " << printEvent(event);
        ++called_;
    }
    
    int gotCalled()
    {
        return called_;
    }
    
private:
    int   called_;
};



int main()
{
    // Try to make several timers with different callbacks
    Timer t1( 4 );
    std::cout << "freeFunction, functor, withExtra using boost::bind" << std::endl;
    
    // freeFunction
    int free = t1.attach( freeFunction );
    
    // functor
    testFunctor tf;
    int functor = t1.attach(tf);
    
    // withAnExtra
    int withExtra = t1.attach(boost::bind(withAnExtra, _1, "extra tick-tock"));
    
    // Sleep a little so we get to see it
    std::chrono::milliseconds sleepFor(3000);
    std::this_thread::sleep_for(sleepFor);
    
    // clean up for the threads
    t1.detach(free);
    t1.detach(functor);
    t1.detach(withExtra);
    
    
    std::cout << "Adding two reference object callback." << std::endl;
    std::shared_ptr<ReferenceObj> r1 = std::make_shared<ReferenceObj>();
    std::shared_ptr<ReferenceObj> r2 = std::make_shared<ReferenceObj>();
    t1.attach(boost::bind(&ReferenceObj::call, r1, _1));
    t1.attach(boost::bind(&ReferenceObj::call, r2, _1));
    
    
    // You might wanna change the loop below such that you can extract the value of called_
    //  from your instance of ReferenceObj
    for(;;)
    {
        std::chrono::milliseconds sleepFor(1000);
        std::this_thread::sleep_for(sleepFor);
        std::cout << "r1 called " << r1->gotCalled() << " times." << std::endl;
        std::cout << "r2 called " << r2->gotCalled() << " times." << std::endl;
    }
    
    
    return EXIT_SUCCESS;
}
