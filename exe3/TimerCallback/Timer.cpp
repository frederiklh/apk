#include <iostream>
#include "Events.hpp"
#include "Timer.hpp"


Timer::Timer( int timer) :
	eventTimer_( timer ), terminator_(false)
{
	thread_     = new std::thread( std::bind( &Timer::timerThreadFunction, this ) );
}

Timer::~Timer()
{
	terminator_ = true;
	thread_->join();
	delete thread_;
}

int Timer::timerThreadFunction()
{
  int counter = 0;
  while( !terminator_ )
  {
    std::chrono::milliseconds sleepFor( 1000 );
    std::this_thread::sleep_for( sleepFor );

    notifyAll( std::make_shared<Event>() );
    if( ++counter >= eventTimer_ )
    {	
      counter = 0;
      std::cout << "EventOther created..." << std::endl;
      
      notifyAll( std::make_shared<EventOther>() );
    }
  }
  return 0;
}

int Timer::attach(std::function<void(const std::shared_ptr<Event>&)> cb){
    std::lock_guard<std::mutex> lock(mapProt_);
    callbacks_[idIndexCounter_] = cb;
    return idIndexCounter_++;
}

void Timer::detach(int cbId){
    std::lock_guard<std::mutex> lock(mapProt_);
    callbacks_.erase(cbId);
}

void Timer::notifyAll(const std::shared_ptr<Event>& any){
    std::lock_guard<std::mutex> lock(mapProt_);
    for(auto &it :callbacks_)
        it.second(any);
}
