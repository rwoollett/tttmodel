#include <nlohmann/json.hpp>
#include "tttmodel/model.h"
#include "tttmodel/timestamp.h"
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

using json = nlohmann::json;
using namespace TTTModel;
using namespace Timestamp;

void worker(int id, int iterations)
{
    for (int i = 0; i < iterations; ++i)
    {
        auto now = timeNow();
        std::string s = formatDate(now);

        auto parsed = parseDate(s);
        if (!parsed)
        {
            std::cerr << "Thread " << id << ": parse returned null for " << s << "\n";
            continue;
        }

        // Compare milliseconds difference
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(
                        *parsed - now).count();

        if (std::abs(diff) > 5)  // allow small rounding differences
        {
            std::cerr << "Thread " << id << ": mismatch "
                      << diff << " ms for " << s << "\n";
        }
    }
}

int main()
{
    const int threadCount = 8;
    const int iterations = 10000;

    std::vector<std::thread> threads;
    threads.reserve(threadCount);

    for (int i = 0; i < threadCount; ++i)
        threads.emplace_back(worker, i, iterations);

    for (auto &t : threads)
        t.join();

    std::cout << "Done\n";
    return 0;
}
