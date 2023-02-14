#include "Callbacks.h"

namespace Swagger
{
	Callbacks::Callbacks(QList<std::shared_ptr<Event>> const& events) : IJson("callbacks") , events(events)
	{

	}

	const QJsonValue Callbacks::getJson() const
	{
		QJsonObject retn;

		for (const auto& event : events)
			retn.insert(event->getName(), event->getJson());

		return retn;
	}
}