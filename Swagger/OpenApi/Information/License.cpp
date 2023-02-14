#include "License.h"

Swagger::License::License(QString const& name, QUrl const& url) :
	QJsonObject
{
	{"name", name},
	{"url", url.isValid() ? url.toString() : "no url available" }
}
{

}

