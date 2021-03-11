#include <iostream>
#include <string>
#include <thread>

#include "ThreadPool.h"
using namespace std;

void thread_task(int n)
{
	this_thread::sleep_for(chrono::seconds(n));
	cout << "hello thread "
		<< this_thread::get_id()
		<< " paused" << n << " seconds" << endl;
}

void f1(int n)
{
	for (auto i = 0; i != 5; ++i)
	{
		cout << "Thread " << n << " executing\n";
		this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void f2(int& n)
{
	for (auto i = 0; i != 5; ++i)
	{
		cout << "Thread 2 executing\n";
		++n;
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}

int main()
{
	ThreadPool pool(4);

	vector<future<size_t>> resultVec;
	size_t total = 0;
	for (auto i = 0; i < 1000; ++i)
	{
		resultVec.push_back(pool.enqueue([](int count) {
			size_t s = 0;
			for (auto i = 0; i <= count; ++i)
			{
				s += i;
			}
			return s;
			}, 10000));
	}

	for (auto& f : resultVec)
	{
		total += f.get();
	}

	cout << "total sum is " << total << endl;
	string str;
	getline(cin, str);
	return EXIT_SUCCESS;
}