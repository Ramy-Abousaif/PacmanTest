#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <vector>

template<class Event>
class EventDispatcher
{
public:
	class Listener
	{
	public:
		virtual ~Listener() = default;
		virtual void OnEvent(const Event& event, const EventDispatcher& sender) = 0;
	};

private:
	std::vector<Listener*> listeners;

public:
	void Invoke(const Event& events)
	{
		for (unsigned int i = 0; i < listeners.size(); ++i)
			listeners[i]->OnEvent(events, *this);
	}

	void Assign(Listener* listener)
	{
		for (unsigned int i = 0; i < listeners.size(); ++i)
			if (listeners[i] == listener)
				return;

		listeners.push_back(listener);
	}

	void Unassign(Listener* listener)
	{
		for (unsigned int i = 0; i < listeners.size(); ++i)
		{
			if (listeners[i] == listener)
			{
				listeners.erase(listeners.begin() + i);
				return;
			}
		}
	}
};
#endif