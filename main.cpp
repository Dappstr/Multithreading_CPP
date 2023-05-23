#include <thread>
#include <iostream>

using namespace std::chrono;

void print_evens() {
    for(int i = 0; i <= 50; ++i) {
        if (i % 2 == 0) {
            std::cout << i << " sleeping for 2 seconds\n";
            std::this_thread::sleep_for(2s);
        }
    }
}
void print_odds() {
    for(int i = 0; i <= 50; ++i) {
        if (i % 2 != 0) {
            std::cout << i << " Sleeping for 5 seconds. . ." << '\n';
            std::this_thread::sleep_for(5s);
        }
    }
}

int main()
{

    std::thread t1(print_evens);
    std::thread t2(print_odds);

    t1.join();
    t2.join();
    
    return 0;
}
