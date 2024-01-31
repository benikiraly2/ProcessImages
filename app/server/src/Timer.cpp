#include "server/Timer.hpp"

namespace timer
{

Timer::Timer(){}

Timer::Timer(std::function<void(void)> func, const long &interval)
{
    m_func = func;
    m_interval = interval;
}

Timer::Timer(Timer&& timer)
{
    m_func = timer.m_func;
    m_interval = timer.m_interval;
}

Timer::~Timer()
{
    stop();
}

void Timer::start()
{
    m_running = true;
    m_thread = std::thread([&]() {
        while (m_running) {
            auto delta = std::chrono::steady_clock::now() + std::chrono::milliseconds(m_interval);
            m_func();
            std::this_thread::sleep_until(delta);
        }
    });
    m_thread.detach();
}

void Timer::stop()
{
    m_running = false;
    m_thread.~thread();
}

void Timer::restart()
{
    stop();
    start();
}

bool Timer::isRunning()
{ 
    return m_running; 
}

Timer *Timer::setFunc(std::function<void(void)> func)
{
    m_func = func;
    return this;
}

long Timer::getInterval()
{ 
    return m_interval; 
}

Timer *Timer::setInterval(const long &interval)
{
    m_interval = interval;
    return this;
}

} // namespace timer