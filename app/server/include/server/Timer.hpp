#pragma once

#include <iostream>
#include <chrono>
#include <functional>
#include <thread>

namespace timer
{

class Timer
{

public:
	Timer();

	Timer(std::function<void(void)> func, const long &interval);
	Timer(Timer&& timer);

	~Timer();

	void start();

	void stop();

	void restart();

	bool isRunning();

	Timer *setFunc(std::function<void(void)> func);

	long getInterval();

	Timer *setInterval(const long &interval);

private:
	std::function<void(void)> m_func;
	long m_interval;

	std::thread m_thread;
	bool m_running = false;
};

} // namespace timer
