#pragma once
#include "../Schema.h"

namespace Swagger
{
	class OneOf : public Schema
	{
	public:
		OneOf(QString const& name, SchemaList const& objects);

		virtual ConvertError convert(QVariant& value) const;
		virtual QJsonValue getJson() const;
		virtual OneOf* clone() const;

	private:
		static QJsonArray mergeJson(SchemaList const& objects);

		const QJsonArray m_arr;
		const SchemaList objects;
	};
}
