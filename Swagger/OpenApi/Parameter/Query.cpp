#include "Query.h"

Swagger::Query::Query(QString const& name, std::shared_ptr<Schema> const& schema, QString const& description, const bool required /*= false*/, const bool deprecated /*= false*/) :
	Parameter(name, schema, description, Parameter::query, required, deprecated)
{

}
