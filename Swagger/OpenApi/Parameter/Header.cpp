#include "Header.h"

Swagger::Header::Header(QString const& name, std::shared_ptr<Schema> const& schema, QString const& description, const bool required /*= false*/, const bool deprecated /*= false*/) :
	Parameter(name, schema, description, Parameter::header, required, deprecated)
{

}

const QJsonValue Swagger::Header::getJson() const
{
	auto parameterRetn = Parameter::getJson().toObject();

	parameterRetn.remove("in");
	parameterRetn.remove("name");

	return parameterRetn;
}
