#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <random>

void work(int id, int iterations)
{
    std::mt19937 rng(id);
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double sum = 0.0;
    for (int i = 0; i < iterations; i++)
    {
        sum += std::sqrt(std::pow(dist(rng), 2) + std::pow(dist(rng), 2));
    }
    std::cout << "Thread " << id << " finished with sum = " << sum << std::endl;
}

int main()
{
    const int num_threads = 24;
    const int iterations_per_thread = 100000000;

    std::vector<std::thread> threads;
    auto start_time = std::chrono::high_resolution_clock::now();
    auto end_time = start_time + std::chrono::minutes(20);
    while (std::chrono::high_resolution_clock::now() < end_time)
    {
        for (int i = 0; i < num_threads; i++)
        {
            threads.emplace_back(work, i, iterations_per_thread);
        }
        for (auto &t : threads)
        {
            t.join();
        }
        threads.clear();
    }
    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << "ms" << std::endl;
    return 0;
}
