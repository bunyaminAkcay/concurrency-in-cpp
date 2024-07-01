#include <thread>
#include <iostream>

/*
    automatically join in the destructor
    very similar to std::jthread in C++20
*/
class JoiningThread{
    private:
        std::thread t;
    
    public:
        explicit JoiningThread() {};
        
        template<typename Callable, typename ... Args> 
        explicit JoiningThread(Callable&& func,Args&& ... args):
            t(std::forward<Callable>(func),std::forward<Args>(args)...)
        {}

        explicit JoiningThread(std::thread t_) noexcept:
            t(std::move(t_))
        {}

        JoiningThread(JoiningThread&& other) noexcept:
            t(std::move(other.t))
        {}

        JoiningThread& operator= (JoiningThread&& other) noexcept
        {
            if (joinable())
            {
                t.join();
            }
            t = std::move(other.t);
            return *this;
        }

        JoiningThread& operator= (std::thread&& otherThread) noexcept
        {
            if (joinable())
            {
                t.join();
            }
            t = std::move(otherThread);
            return *this;
        }

        ~JoiningThread() noexcept
        {
            if (joinable())
            {
                t.join();
            }
        }

        void swap(JoiningThread& other) noexcept
        {
            t.swap(other.t);
        }

        std::thread::id getId() const noexcept
        {
            return t.get_id();
        }

        bool joinable() const noexcept
        {
            return t.joinable();
        }

        void join() {
            t.join();
        }

        void detach(){
            t.detach();
        }
};

struct Hello{
    int& i;
    Hello(int& i_):i(i_){}
    void operator()(){
        for (std::size_t t = 0; t < 5; t++)
        {
            std::cout << "Hello " << i << std::endl;
        }
        
    }
};

int main(){

    int  i = 1, j = 2;
    Hello hello1(i);
    Hello hello2(j);
    JoiningThread jt1(hello1);
    
    std::thread t2(hello2);
    JoiningThread jt2(std::move(t2));
    
    std::cout << "id =>" << jt2.getId() << std::endl;
    jt1.swap(jt2);
    std::cout << "id =>" << jt2.getId() << std::endl;

    JoiningThread jt3 = std::move(jt2);
}