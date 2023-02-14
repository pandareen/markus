#pragma once
#include "../../swagger_global.h"
#include "Event.h"

namespace Swagger
{
	class SWAGGER_EXPORT Callbacks : public IJson
	{
	public:
		Callbacks(QList<std::shared_ptr<Event>> const& events);

		const QJsonValue getJson() const;

	private:
		QList<std::shared_ptr<Event>> events;
	};
}