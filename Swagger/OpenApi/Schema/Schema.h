#pragma once
#include "../../SwaggerObject.h"
#include "./Factory/FieldFactory.h"
#include "../../container/List.h"

namespace Swagger
{
	class SWAGGER_EXPORT Schema : public SwaggerObject
	{
	public:
		Schema(QString const& name, const Field::Type* type, FieldList const& fields);

		virtual ConvertError convert(QVariant& variant) const;

		static const QJsonValue toJson(QVariant const& variant);

		const bool isWriteOnly() const;
		const bool isReadOnly() const;
		const QMetaType::Type getQtType() const;
		const Field::Type* getType() const;

		virtual Schema* clone() const;
		virtual QJsonValue getJson() const;

		void setProperties(FieldList const& list);
		void addProperties(FieldList const& list);

	protected:
		static QJsonObject createJson(const Field::Type* type, FieldList const& properties);

		mutable FieldList fields;
		const Field::Type* const type;
	};

	class SchemaList : public List<Schema*>
	{
	public:
		using List<Schema*>::List;


		virtual const QJsonValue getJson() const {
			QJsonObject retn;

			for (auto item : *this)
				retn[item->getName()] = item->getJson();

			return retn;
		}
	};
}