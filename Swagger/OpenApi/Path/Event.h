#pragma once
#include <QJsonObject>
#include "../../IJson.h"

namespace Swagger
{
	class SWAGGER_EXPORT Event : public IJson
	{
	public:
		Event(QString const& name, QJsonObject const& paths );

		const QJsonValue getJson() const;

	private:
		const QJsonObject paths;
	};

}