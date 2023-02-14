#pragma once
#include <QString>
#include <QJsonObject>
#include "../OpenApi/Schema/Schema.h"
#include "../OpenApi/Schema/Object/Object.h"


namespace Swagger
{
	template<typename T>
	class Reference : public T
	{

	public:
		Reference(QString const& path, std::shared_ptr<T> const& schema) :
			T(*schema->clone()), path(path), schema(schema), data(schema->getJson())
		{

		}

		QJsonValue getJson() const
		{
			return QJsonObject{ getPair() };
		}

		QJsonValue getSchemaJson() const
		{
			return data;
		}

		const QPair<QString, QJsonValue> getPair() const {
			return { "$ref", path + SwaggerObject::getName() };
		}

		T* clone() const
		{
			return new Reference<T>(path, schema);
		}


		operator std::shared_ptr<T>() const
		{
			return schema;
		}


	private:
		QJsonValue data;
		const QString path;
		const std::shared_ptr<T> schema;

	};

}