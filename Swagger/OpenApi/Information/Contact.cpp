#include "Contact.h"

Swagger::Contact::Contact(QString const& name, QString const& email, QUrl const& url) : QJsonObject
{
	{"name", name},
	{"url", url.isValid() ? url.toString() : "no url available" },
	{"email", email}
}
{

}
