#include "messageGeneric.h"

#include <mutex>
#include <queue>

namespace MessageChannel {
	Value::BaseContent::~BaseContent() { }
	IMessageReceiver::~IMessageReceiver() { }
	IMessageSender::~IMessageSender() { }

	namespace {
		class Queue {
		public:
			class Receiver : public IMessageReceiver {
			private:
				Queue *m_queue;
			public:
				Receiver(Queue *queue) : m_queue(queue) { }
				virtual ~Receiver() { }
				virtual bool tryGet(Value &v);
			};
			class Sender : public IMessageSender {
			private:
				Queue *m_queue;
			public:
				Sender(Queue *queue) : m_queue(queue) { }
				virtual ~Sender() { }
				virtual void send(Value &&v);
			};
		private:
			std::mutex m_mutex;
			std::queue<Value> m_queue;
			Receiver m_receiver;
			Sender m_sender;

			// non copyable
			Queue(const Queue &other);
			Queue& operator=(const Queue &other);

			friend class Receiver;
			friend class Sender;
			bool tryGet(Value &v) {
				std::lock_guard<std::mutex> lock(m_mutex);
				if (m_queue.empty()) return false;
				v = m_queue.front();
				m_queue.pop();
				return true;
			}
			void send(Value &&v) {
				std::lock_guard<std::mutex> lock(m_mutex);
				m_queue.push(std::move(v));
			}
		public:
			Queue() :m_receiver(this), m_sender(this) { }
			static MessageReceiver receiver(const std::shared_ptr<Queue> &queue) {
				return MessageReceiver(std::shared_ptr<IMessageReceiver>(queue, dynamic_cast<IMessageReceiver*>(&queue->m_receiver)));
			}
			static MessageSender sender(const std::shared_ptr<Queue> &queue) {
				return MessageSender(std::shared_ptr<IMessageSender>(queue, dynamic_cast<IMessageSender*>(&queue->m_sender)));
			}
		};

		bool Queue::Receiver::tryGet(Value &v) {
			return m_queue->tryGet(v);
		}
		void Queue::Sender::send(Value &&v) {
			m_queue->send(std::move(v));
		}

	}

	void initMessageChannel(MessageReceiver &receiver, MessageSender &sender) {
		std::shared_ptr<Queue> queue(new Queue());
		receiver = Queue::receiver(queue);
		sender = Queue::sender(queue);
	}
}
