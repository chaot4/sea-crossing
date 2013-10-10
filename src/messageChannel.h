#ifndef MessageChannel_h
#define MessageChannel_h

#include <memory>

/* generic channel, passing <Value>s which can contain any type
 * an implementation creates a MessageReceiver and MessagedSender,
 * which are linked to one channel.
 * each sent value is received exactly once (unless the channel is
 * destroyed before the value is received).
 */
namespace MessageChannel {
	class Value {
	private:
		class BaseContent {
		public:
			virtual ~BaseContent();
		protected:
			BaseContent() { }
		private:
			/* not copyable */
			BaseContent(const BaseContent& other);
			BaseContent& operator=(const BaseContent& other);
		};
		template<typename T>
		class Content : public BaseContent {
		public:
			T data;
			Content(const T& data) : data(data) { }
			Content(T&& data) : data(std::move(data)) { }
			virtual ~Content() { }
		};

		std::shared_ptr<BaseContent> content;
	public:
		Value() { }
		Value(const Value &other) : content(other.content) { }
		Value(Value &&other) : content(std::move(other.content)) { }
		Value& operator=(const Value &other) { content = other.content; return *this; }
		Value& operator=(Value &&other) { content = std::move(other.content); return *this; }

		template<typename T>
		static Value make(const T& data) { Value v; v.reset<T>(data); return v; }
		template<typename T>
		static Value make(T&& data) { Value v; v.reset<T>(data); return v; }

		template<typename T>
		void reset(const T& data) {
			content.reset(new Content<T>(data));
		}
		template<typename T>
		void reset(T&& data) {
			content.reset(new Content<T>(std::move(data)));
		}

		template<typename T>
		T* tryGet() const {
			std::shared_ptr< Content<T> > c(std::dynamic_pointer_cast< Content<T> >(content));
			if (!c) return nullptr;
			return &c->data;
		}

		template<typename T>
		T& get() const {
			T* data = tryGet<T>();
			if (nullptr == data) throw std::bad_cast();
			return *data;
		}

		bool empty() const { return !content; }
	};

	class IMessageReceiver {
	public:
		virtual ~IMessageReceiver();
		virtual bool tryGet(Value &v) = 0;
	};

	class MessageReceiver {
	private:
		std::shared_ptr<IMessageReceiver> m_receiver;
	public:
		MessageReceiver() { }
		explicit MessageReceiver(std::shared_ptr<IMessageReceiver> receiver) : m_receiver(receiver) { }
		MessageReceiver(const MessageReceiver& other) : m_receiver(other.m_receiver) { }
		MessageReceiver(MessageReceiver&& other) : m_receiver(std::move(other.m_receiver)) { }
		MessageReceiver& operator=(const MessageReceiver& other) { m_receiver = other.m_receiver; return *this; }
		MessageReceiver& operator=(MessageReceiver&& other) { m_receiver = std::move(other.m_receiver); return *this; }

		void unlink() { m_receiver.reset(); }
		operator bool () const { return (bool) m_receiver; }

		bool tryGetValue(Value &v) const {
			if (!m_receiver) return false;
			return m_receiver->tryGet(v);
		}

		template<typename T>
		bool tryGet(T &v) const {
			Value _v;
			if (!tryGetValue(_v)) return false;
			v = _v.get<T>();
			return true;
		}
	};

	class IMessageSender {
	public:
		virtual ~IMessageSender();
		virtual void send(Value &&v) = 0;
	};
	class MessageSender {
	private:
		std::shared_ptr<IMessageSender> m_sender;
	public:
		MessageSender() { }
		explicit MessageSender(std::shared_ptr<IMessageSender> sender) : m_sender(sender) { }
		MessageSender(const MessageSender& other) : m_sender(other.m_sender) { }
		MessageSender(MessageSender&& other) : m_sender(std::move(other.m_sender)) { }
		MessageSender& operator=(const MessageSender& other) { m_sender = other.m_sender; return *this; }
		MessageSender& operator=(MessageSender&& other) { m_sender = std::move(other.m_sender); return *this; }

		void unlink() { m_sender.reset(); }
		operator bool () const { return (bool) m_sender; }

		void sendValue(Value &&v) const {
			m_sender->send(std::move(v));
		}
		void sendValue(const Value &v) const {
			Value _v(v);
			m_sender->send(std::move(_v));
		}
		template<typename T>
		void send(T &&data) const {
			Value v = Value::make<T>(data);
			sendValue(v);
		}
		template<typename T>
		void send(const T &data) const {
			Value v = Value::make<T>(data);
			sendValue(v);
		}
	};

	/* create thread-safe message queue */
	void initMessageChannel(MessageReceiver &receiver, MessageSender &sender);
}

class TwoWayChannel {
	private:
		MessageChannel::MessageSender sender;
		MessageChannel::MessageReceiver receiver;

	public:
		template <typename T>
		void send(T const& message);
		template <typename T>
		bool receive(T& message);
		MessageChannel::MessageReceiver& getReceiver();
		MessageChannel::MessageSender& getSender();

		static void connect(TwoWayChannel& one_side, TwoWayChannel& other_side);
};

template <typename T>
void TwoWayChannel::send(T const& message){
	sender.send<T>(message);
}

template <typename T>
bool TwoWayChannel::receive(T& message){
	return receiver.tryGet<T>(message);
}

#endif
