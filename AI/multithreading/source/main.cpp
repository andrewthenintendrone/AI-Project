#include <iostream>
#include <thread>

static const int numberOfThreads = 10;

void myThread(const int message)
{
    std::cout << "This is thread " << message << std::endl;
}

int main()
{
    std::thread threads[numberOfThreads];
    for (int i = 0; i < numberOfThreads; i++)
    {
        threads[i] = std::thread(myThread, i);
    }

    for (int i = 0; i < numberOfThreads; i++)
    {
        threads[i].join();
    }

    std::cout << "threads all completed successfully\n";

    system("pause");
    return 0;
}