#include "Event.h"

namespace Swagger
{
	Event::Event(QString const& name, QJsonObject const& paths) : IJson(name), paths(paths)
	{

	}

	const QJsonValue Event::getJson() const
	{
		return paths;
	}
}