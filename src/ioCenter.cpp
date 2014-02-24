#include "ioCenter.h"

IoCenter::IoCenter() : m_run(true), m_sleep_time(5)
{
}

void IoCenter::processMessage(TwoWayChannel& channel)
{
	std::shared_ptr<Message> msg;
        if (!channel.receive(msg)) {
                return;
        }

	switch (msg->type) {
		case CTRL_ENG_REQUEST_OBJECT_ID:
		{
			m_engine_channel.send(msg);
			break;
		}
		case ENG_COMM_SEND_OBJ_ID:
		{
			m_hub_channel.send(msg);
			break;
		}
		case ENGINE_CREATE:
		{
			m_engine_channel.send(msg);
			break;
		}
		case ENGINE_DELETE:
		{
			m_engine_channel.send(msg);
			break;
		}
		case ENGINE_UPDATE_ENTITY:
		{
			m_engine_channel.send(msg);
			break;
		}
		case ENGINE_CREATE_FEEDBACK:
		{
			break;
		}
		case ENGINE_QUIT:
		{
			m_engine_channel.send(msg);
			break;
		}
		case ENGINE_USER_INPUT:
		{
			break;
		}
		case QUIT:
//			quit();
			break;
		default:
			std::cerr << "ERROR: Unexpected message type: " << toString(msg->type) << std::endl;
	}
}

void IoCenter::start()
{
	TwoWayChannel::connect(Controls::getCommunicationChannel(), m_controls_channel);
	TwoWayChannel::connect(m_renderHub.getChannelAccesPoint(), m_engine_channel);

	m_engine_thread = std::thread(&RenderHub::init, &m_renderHub);

	while(m_run)
	{
		processMessage(m_hub_channel);
		sleep(m_sleep_time);

		processMessage(m_controls_channel);
		sleep(m_sleep_time);

		processMessage(m_engine_channel);
		sleep(m_sleep_time);
	}
}

TwoWayChannel& IoCenter::getHubChannel()
{
	return m_hub_channel;
}
