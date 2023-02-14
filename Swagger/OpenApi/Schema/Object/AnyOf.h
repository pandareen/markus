#pragma once
#include "../Schema.h"

namespace Swagger
{
	class AnyOf : public Schema
	{
	public:
		AnyOf(QString const& name, SchemaList const& objects);

		virtual ConvertError convert(QVariant& value) const;
		virtual QJsonValue getJson() const;
		virtual AnyOf* clone() const;

	private:
		static QJsonArray mergeJson(SchemaList const& objects);

		const QJsonArray m_arr;
		const SchemaList objects;
	};
}
