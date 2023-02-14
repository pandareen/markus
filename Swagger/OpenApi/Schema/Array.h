#pragma once
#include <QJsonDocument>
#include <QJsonArray>
#include "Schema.h"

namespace Swagger
{
	class SWAGGER_EXPORT Array : public Schema
	{

	public:
		Array(QString const& title,	const std::shared_ptr<Schema>& data, FieldList const& fields);
		ConvertError convert(QVariant& variant)  const;

		std::shared_ptr<Schema> data() const;

		Schema* clone() const
		{
			return new Array(getName(), objectSchema, fields);
		}

		QJsonValue getJson() const override {
			auto json = Schema::getJson().toObject();

			json.insert("items", objectSchema->getJson());

			return json;
		}

	protected:


		const std::shared_ptr<Schema> objectSchema;

	};
}

