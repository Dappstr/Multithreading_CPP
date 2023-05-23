#include <string>
#include <thread>
#include <iostream>

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

void print(std::string str) {
    for (int i = 0; i < 3; ++i) {
        std::cout << str << '\n';
    }
}

int main() {

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
    return 0;
}
