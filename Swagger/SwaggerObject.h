#pragma once
#include "swagger_global.h"
#include <QJsonObject>

namespace Swagger
{
	class SWAGGER_EXPORT SwaggerObject
	{

	public:
		SwaggerObject(QString const& name);

		virtual QJsonValue getJson() const = 0;

		QString const& getName() const;


	protected:
		const QString m_name;

	};
}
