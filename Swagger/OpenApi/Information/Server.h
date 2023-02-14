#pragma once
#include "../../swagger_global.h"
#include <QJsonObject>
#include <QString>
#include <QUrl>

namespace Swagger
{
	class SWAGGER_EXPORT Server : public QJsonObject
	{
	public:
		Server(	QUrl const& url, QString const& description	);

	};
}

