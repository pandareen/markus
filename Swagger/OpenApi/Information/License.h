#pragma once
#include "../../swagger_global.h"
#include <QUrl>
#include <QJsonObject>

namespace Swagger
{
	class SWAGGER_EXPORT License : public QJsonObject
	{
	public:
		License(QString const& name, QUrl const& url );
	};
}

