#pragma once

#include "Parameter.h"

namespace Swagger
{
	class Header : public Parameter
	{
	public:
		Header(QString const& name, std::shared_ptr<Schema> const& schema, QString const& description, const bool required = false, const bool deprecated = false);

		virtual const QJsonValue getJson() const;
	};
}