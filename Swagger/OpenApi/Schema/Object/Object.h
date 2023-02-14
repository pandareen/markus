#pragma once
#include "../Schema.h"
#include <QString>

namespace Swagger
{

	class Object : public Schema
	{
	public:
		struct Required;
		struct Properties;

		Object(QString const& title,
			SchemaList const& properties,
			QStringList const& required,
			FieldList const& fields = {});

		ConvertError convert(QVariant& variant) const;

		const SchemaList  getProperties() const;
		const QStringList  getRequired() const;

		virtual QJsonValue getJson() const;

		Object* clone() const override;

	protected:
		const Properties* properties;
		const Required* required;

	private:
		Object(QString const& title,
			const Properties* properties,
			const Required* required,
			FieldList const& fields = {});

	};

}
