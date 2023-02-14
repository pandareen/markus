#pragma once
#include "Parameter.h"

namespace Swagger
{
	class Query : public Parameter {
	public:
		Query(QString const& name, std::shared_ptr<Schema> const& schema, QString const& description, const bool required = false, const bool deprecated = false);
	};
}