#include "TopTracker.h"
#include <algorithm>

void TopTracker::add(const std::string& action)
{
    const auto now = Clock::now();
    std::lock_guard lock(mutex);

    // ������� ���������� ������� ����� �����������
    cleanup_implementation();

    entries.emplace_back(Entry{ action, now });

    // ������������ ����������� �� ���������� ���������
    while (entries.size() > max_entries)
    {
        entries.pop_front();
    }
}

std::vector<std::string> TopTracker::get_actions()
{
    std::lock_guard lock(mutex);
    cleanup_implementation();
    std::vector<std::string> actions;
    actions.reserve(entries.size());

    std::transform(entries.begin(), entries.end(), std::back_inserter(actions),
        [](const Entry& e) { return e.action; });

    return actions;
}

void TopTracker::cleanup()
{
    std::lock_guard lock(mutex);
    cleanup_implementation();
}

// ���������� ���������� �������
void TopTracker::cleanup_implementation()
{
    const auto now = Clock::now();
    const auto expiry_time = now - timeout;

    // ������� ������, ������� �������� �� �������
    while (!entries.empty() && entries.front().timestamp < expiry_time)
    {
        entries.pop_front();
    }
}