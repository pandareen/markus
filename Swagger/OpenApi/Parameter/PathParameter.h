#pragma once
#include "Parameter.h"

namespace Swagger
{
	class PathParameter : public Parameter {
	public:
		PathParameter(QString const& name, std::shared_ptr<Schema> const& schema, QString const& description, const bool deprecated = false) :
			Parameter(name, schema, description, Parameter::path, true, deprecated)
		{

		}
	};
}