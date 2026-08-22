#include <chrono>
#include <thread>
#include <sleep.h>

#if defined(__x86_64__) || defined(_M_X64) || defined(i386) || defined(_M_IX86)
#if defined(_MSC_VER)
#include <intrin.h>
#define cpu_pause() _mm_pause()
#else
#define cpu_pause() __builtin_ia32_pause()
#endif
#elif defined(__aarch64__) || defined(__arm__)
#if defined(_MSC_VER)
#include <intrin.h>
#define cpu_pause() __yield()
#else
#define cpu_pause() asm volatile("yield" ::: "memory")
#endif
#else
#define cpu_pause() ((void)0)
#endif

void sleepPrecise(std::chrono::nanoseconds duration) {
    using namespace std::chrono;

    auto start = steady_clock::now();
    auto target = start + duration;

    constexpr auto margin = milliseconds(2);
    while (steady_clock::now() + margin < target) {
        std::this_thread::sleep_for(milliseconds(1));
    }

    while (steady_clock::now() < target) {
        cpu_pause();
    }
}