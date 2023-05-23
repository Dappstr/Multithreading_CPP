`std::thread` objects come from the `<thread>` library

The thread constructor takes a callable object like an entry point function

Cannot use overloaded functions, and any return value is ignored.

If the parent thread ends while the child thread is continuing, a "zombie thread" will continue to run, causing `std::terminate` to be called on the child thread causing the program to terminate.

When attempting to call a member function from a new thread, you must specify the object of the thread as well.

```cpp

struct S {
    void hello () {
        std::cout << "Hello world!\n";
    }
};

int main()
{
    S s;
    std::thread t1(&S::hello, &s);
```

Threads may start in any order, interrupted at any time, and restarted at any time.

Threads can also be given different priorities depending on importance.

Threads created through `std::thread` are guaranteed to be unique, however they can be reused. `std::this_thread::get_id()` to get the ID of the current thread, or `thr.get_id()` to get ther ID of the thread object.

Make threads sleep by calling `sleep_for`, on the current thread through `std::this_thread::sleep_for(std::chrono::seconds(3))` or `thr.sleep_for(std::chrono::seconds(2))`

Time slicing is when you have threads taking turns running for a short period of time.

The scheduler is responsible for the execution order of threads.

Disadvantages of time slicing include context switches, which means that the computer stores various "context" information about each thread, the processor also cannot execute any instructions during a context switch.

The cache is memory holding information between the cpu and main memory.

Cache fetching is when the CPU looks up certain information and if it finds it, there is a "cache hit" and then the CPU uses the copy in the cache rather than the main memory, otherwise it gets it from the cache.

Cache writing is when the CPU wants to write information to the memory, which is first written into the cache and then looked up by the main memory.

Multiple processors means having multiple levels of a cache.

Level 1 cache has private data t oeach processor core, and is as close to the processor core.

Level 2 cache is private to each core

Level 3 cache is shared information between all cores on the same socket.


