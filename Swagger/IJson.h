#pragma once
#include "swagger_global.h"

#include <QString>
#include <QJsonValue>

namespace Swagger
{
	class SWAGGER_EXPORT IJson
	{
	public:
		IJson(QString const& name = "");

		using JsonPair = QPair<QString, QJsonValue>;

		virtual const QJsonValue getJson() const = 0;
		virtual const JsonPair getPair() const;

		QString const& getName() const;

		operator const JsonPair() const;
		operator QString const& () const;

	protected:
		const QString m_name;
	};

}
