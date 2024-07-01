#include <thread>
#include <iostream>

/*
    Using functors instead of functions provides maintain state between calls.
    This is also possible with functions but, functors encapsulate data better.
*/
struct Hello{
    int& i;
    Hello(int& i_):i(i_){}
    void operator()(){
        for (std::size_t t = 0; t < 500; t++)
        {
            std::cout << "Hello " << i << std::endl;
        }
        
    }
};

/*
    Ensure that threads are joining.
    Also delete = operator that makes code unsafe.
*/
class ThreadGuard{

    private:
        std::thread& t;

    public:
        explicit ThreadGuard(std::thread& thread_):t(thread_){}
        ~ThreadGuard(){
            if (t.joinable())
            {
                t.join();
            }
        }
        ThreadGuard(ThreadGuard const&) = delete;
        ThreadGuard operator= (ThreadGuard const&) = delete;
};

void f(){
    int i = 0, j = 1;
    Hello hello1(i);
    Hello hello2(j);
    std::thread thread1(hello1);
    std::thread thread2(hello2);
    ThreadGuard tg1(thread1);
    ThreadGuard tg2(thread2);
    
    std::cout << "f is destroyed." << std::endl;
}

int main(){
    f();
    return 0;
}