#pragma once

#include <deque>
#include <chrono>
#include <string>
#include <mutex>
#include <vector>
#include <type_traits>

class TopTracker final
{
public:
    using Clock = std::chrono::system_clock;
    using TimePoint = Clock::time_point;

    template <typename Rep, typename Period>
    explicit TopTracker(
        size_t max_entries = 100,
        std::chrono::duration<Rep, Period> timeout = std::chrono::seconds(100)
    ) : max_entries(max_entries),
        timeout(std::chrono::duration_cast<std::chrono::milliseconds>(timeout))
    {}

    void add(const std::string& action);
    std::vector<std::string> get_actions();
    void cleanup();

private:
    struct Entry
    {
        std::string action;
        TimePoint timestamp;
    };

    std::deque<Entry> entries;
    std::mutex mutex;
    size_t max_entries;

    // Очистка реализация
    void cleanup_implementation();
    
    std::chrono::milliseconds timeout;
}; 

#pragma once
