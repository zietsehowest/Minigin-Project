#pragma once
namespace dae
{
	enum EventType
	{
		EVENT_PLAYER_DEATH,
		EVENT_PLAYER_SCORE_CHANGED
	};
	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() {};
		virtual void onNotify(std::weak_ptr<GameObject>& entity, EventType eventType) = 0;
	};
}

