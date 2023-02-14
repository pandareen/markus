#pragma once
#include "../../swagger_global.h"
#include "License.h"
#include "Contact.h"

namespace Swagger
{
	struct SWAGGER_EXPORT Info : public QJsonObject
	{
		Info(QString const& title, // The title of the application.
			QString const& description, // CommonMark ...
			QUrl const& termsOfService,
			Contact const& contact,
			License const& license,
			QString const& version
		);
	};
}