#include <chrono>
#include <future>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>


class Algo
{
public:
  Algo(std::vector<int> v)
    : data_(std::move(v))
  {}
    
  void doAlgo()
  {
    std::chrono::time_point<std::chrono::high_resolution_clock> commence = std::chrono::high_resolution_clock::now();
    std::sort(data_.begin(), data_.end());
    std::chrono::time_point<std::chrono::high_resolution_clock> complete = std::chrono::high_resolution_clock::now();
    duration_ = std::chrono::nanoseconds(complete - commence);
  }
    
  std::chrono::duration<long double> processingTime()
  {
    return duration_;
  }
    
    
  void print()
  {
    std::copy(data_.begin(), data_.end(), std::ostream_iterator<int>(std::cout, " "));
  }
private:
  Algo(const Algo&) = delete; // No copy construction is allowed
    
  Algo& operator=(const Algo&) = delete; // No copy assignment is allowed

  std::vector<int>                    data_;
  std::chrono::nanoseconds            duration_;
};


typedef Algo SmartAlgo;
typedef Algo CoolAlgo;
typedef Algo FantasticAlgo;


int main(int argc, char* argv[])
{
    int i = 0;
    int n = 10000000; // Change at your leasure
    
    std::vector<int> data;
    data.reserve(n);
    generate_n( back_inserter( data ), n, [&i](){return i++;}  );
    random_shuffle( data.begin (), data.end () );
    
    
    
    /* Insert code here ... */
    
    
    /* future from a packaged_task */
    
    std::packaged_task<std::shared_ptr<Algo()>> task1([=](){ return std::make_shared<SmartAlgo>(data); }); /* wrap the function */
    //std::packaged_task<Algo()> task2([=]{ return std::make_shared<CoolAlgo>(data); }); /* wrap the function */
    //std::packaged_task<Algo()> task3([=]{ return std::make_shared<FantasticAlgo>(data); }); /* wrap the function */
    
    //auto f1 = task1.get_future(); /* get a future */
    //auto f2 = task2.get_future(); /* get a future */
    //auto f3 = task3.get_future(); /* get a future */
    //
    //std::thread(std::move(task1)).detach(); /* launch on a thread */
    //std::thread(std::move(task2)).detach(); /* launch on a thread */
    //std::thread(std::move(task3)).detach(); /* launch on a thread */
    //
    //std::cout << "Waiting..." << std::flush;
    //f1.wait();
    //f2.wait();
    //f3.wait();
    //std::cout << "Done!\nResults are: " << "\n";
    //f1.get().print();
    //f2.get().print();
    //f3.get().print();
    //std::cout << '\n';
    
    
    return 0;
}
