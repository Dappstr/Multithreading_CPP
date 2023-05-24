# Concurrency

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
    //std::jthread for C++20 or later
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


# Cache levels

Level 1 cache has private data t oeach processor core, and is as close to the processor core.

Level 2 cache is private to each core

Level 3 cache is shared information between all cores on the same socket.

Thread exceptions must be caught in the function in which the thread is executing otherwise `std::terminate` will be thrown, causing every thread to halt causing the program to end.

If the child thread detaches from the parent thread, each thread will run independently. Deatching is performed through the "detach" member function.

Unless `join` is called after an exception is thrown, then the terminate function is called, stopping the program's execution.


# Data races

Data races occur when multiple threads attempt to access the same memory location, as well as at least one thread modifies it, along with potentially conflicting accesses to the same memory location.

The way to fix this is to ensure thread synchronization.


# Mutexes

Mutex stands for "MUTual EXclusion object"

Mutexes have two states: locked and unlocked.

If more than one thread are going to be accessing a function at the same time, a global mutex should be chosen over a local mutex. However, otherewise a loal mutex should be chosen.

Disadvantage of using mutex is that if an exception is thrown before a `mtx.unlock` then them mutex will remain locked.


# Internal Synchronization

Multiple threads accessing the same memory location.

 
# std::lock_guard

 `std::lock_guard` is a replacement for `std::mutex` which also utilizes RAII to automatically unlock the mutex in its destructor which is a private member.

It takes a mutex as an argument.


# std::unique_lock

Same basic features as std::lock_guard but is a bit slower and requires slightly more storage.

Takes an optional second argument, which can be:
    `std::try_lock` which will call the mutex's `try_lock` member function, as well as the `owns_lock` member function will check if the mutex is locked
    
    `std::defer_lock` which does not lock the mutex. You can lock it later by calling the `lock` member function, or by passing `std::unique_lock` to object `std::lock`

    `std::adopt_lock` which takes an already locked mutex, and avoids locking the mutex twice.


# std::shared_mutex

Defined in `<shared_mutex>`

It can be locked two different ways; through an **exclusive lock** or a **shared lock**. With an **exclusive lock**, no other thread may acquire a lock, and no other thread can run the critical code. However, a **shared lock** allows other threads to acquire a shared lock and threads can execute code concurrently. Exclusive locking should be preferred when writing to object such as `cout`, and shared locking should be preferred when reading to allow for concurrency.

