#include "Cookie.h"

Swagger::Cookie::Cookie(QString const& name, std::shared_ptr<Schema> const& schema, QString const& description, const bool required /*= false*/, const bool deprecated /*= false*/) :
	Parameter(name, schema, description, Parameter::cookie, required, deprecated)
{

}
