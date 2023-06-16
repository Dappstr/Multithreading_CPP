#include <memory>
#include <string>
#include <thread>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <vector>

using namespace std::chrono;

void print_evens() {
    for (int i = 0; i <= 50; ++i) {
        if (i % 2 == 0) {
            std::cout << i << " sleeping for 2 seconds\n";
            std::this_thread::sleep_for(2s);
        }
    }
}
void print_odds() {
    for (int i = 0; i <= 50; ++i) {
        if (i % 2 != 0) {
            std::cout << i << " Sleeping for 5 seconds. . ." << '\n';
            std::this_thread::sleep_for(5s);
        }
    }
}

std::mutex mtx;
//std::shared_mutex s_mx;

void print(const std::string& str) {
    for (int i = 0; i < 3; ++i) {
        //std::unique_lock<std::mutex> lock(mtx);

        //std::shared_lock<std::shared_mutex> s_lock(s_mx) <- Not recommended for writing to a shared object
        //Shared locks and shared mutexes should be used for reader threads (threads only reading data)

        std::lock_guard<std::mutex> lock(mtx);
        std::cout << str << '\n';
    }
}

class Singleton
{
    public:
        Singleton() { std::cout << "Initializing Singleton\n"; }

        Singleton(const Singleton& src) = delete;
        Singleton(Singleton&& src) = delete;

        Singleton& operator=(const Singleton& src) = delete;
        Singleton& operator=(Singleton&& src) = delete;

        static Singleton& get_Singleton() {
            static Singleton single;
            return single;
        }
};

void task()
{
    Singleton& single = Singleton::get_Singleton();
    std::cout << &single << '\n';
}


class Test_class
{
    public:
        Test_class() { std::cout << __FUNCTION__ << '\n';}

        void func() {
            //...
        }
};

std::once_flag ptest_flag;
Test_class* ptest = nullptr;

//Function will only be called once even though two threads are calling it.
void process()
{
    std::call_once(ptest_flag, []() { ptest = new Test_class;});
    ptest->func();
}

int main()
{

    //std::thread t1(print_evens);
    //std::thread t2(print_odds);

    //t1.join();
    //t2.join();

    /* Data race
     * Each thread is accessing the global `cout` object causing mangled output
     */
    std::thread dr1(print, std::string("abc"));
    std::thread dr2(print, std::string("def"));
    std::thread dr3(print, std::string("xyz"));
   
    dr1.join();
    dr2.join();
    dr3.join();

    std::vector<std::thread> threads {};

    for(int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(task));
    }

    for(auto& i : threads) {
        i.join();
    }

    std::thread proct1(process);
    std::thread proct2(process);


    proct1.join();
    proct2.join();
    return 0;
}
