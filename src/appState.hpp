#ifndef __APP_STATE_HPP__
#define __APP_STATE_HPP__
#include <atomic>

// Global atomic boolean to track whether the app is running
extern std::atomic<bool> g_app_running;

#endif