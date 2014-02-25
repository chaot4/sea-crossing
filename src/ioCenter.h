#ifndef ioCenter_h
#define ioCenter_h

#ifdef _WIN32
	/*Fix call to windows macros instead of std::max*/
	#define NOMINMAX
	#include <windows.h>
	#define sleep(x) Sleep(x)
#elif __linux__
#include <unistd.h>
#define sleep(x) usleep(x)
#else
#define sleep(x)
#endif

#include "messageChannel.h"
#include "messages.h"
#include "engine/renderHub.h"

#include <thread>

class IoCenter
{
private:
	bool m_run;
	bool m_input_requested;
	unsigned int m_sleep_time;

	TwoWayChannel m_hub_channel;

	TwoWayChannel m_controls_channel;
	TwoWayChannel m_engine_channel;

	RenderHub m_renderHub;
	std::thread m_engine_thread;

	void processMessage(TwoWayChannel& channel);
	
public:
	IoCenter();

	void start();

	TwoWayChannel& getHubChannel();
};

#endif