#pragma once
#include "../../swagger_global.h"
#include <QUrl>
#include <QJsonObject>

namespace Swagger
{
	struct SWAGGER_EXPORT Contact : public QJsonObject
	{
		Contact(QString const& name, QString const& email,QUrl const& url);
	};
}