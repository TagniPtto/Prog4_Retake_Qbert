#pragma once

#include <functional>
#include <queue>

namespace dae 
{
	template<typename Event>
	class EventDispatcher 
	{
	public:
		using CallbackFn = std::function<void(const Event&)>;
	private:
		std::vector<CallbackFn> m_listeners;
		std::queue<Event> m_eventQueue;
	public:

		void BroadCast(const Event& event) 
		{
			for (auto& listener : m_listeners)
			{
				listener(event);
			}
		}
		void AddListener(CallbackFn listener)
		{
			m_listeners.push_back(listener);
		}

		void EnqueueEvent(const Event& event) {
			m_eventQueue.push(event);
		}
		void ProcessEventQueue()
		{
			while (!m_eventQueue.empty()) 
			{
				BroadCast(m_eventQueue.front);
				m_eventQueue.pop();
			}
		}
	};
}