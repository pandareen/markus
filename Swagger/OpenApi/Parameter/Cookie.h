#pragma once
#include "Parameter.h"

namespace Swagger
{
	class Cookie : public Parameter {
	public:
		Cookie(QString const& name, std::shared_ptr<Schema> const& schema, QString const& description, const bool required = false, const bool deprecated = false);
	};
}
