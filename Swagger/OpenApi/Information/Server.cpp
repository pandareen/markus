#include "Server.h"

namespace Swagger
{
	Server::Server(QUrl const& url,	QString const& description) :
		QJsonObject
		{
			{"url", url.isValid() ? url.toString() : "no url available" },
			{"description", description}
		}
	{

	}
}
