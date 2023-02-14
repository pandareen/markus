#include "Schema.h"


namespace Swagger
{
	Schema::Schema(QString const& title, const Field::Type* type, FieldList const& fields) :
		SwaggerObject(title), fields(fields),	type(type)
	{
	}

	ConvertError Schema::convert(QVariant& variant) const {
			ConvertError retn;
			const auto list = FieldList{ const_cast<Field::Type*>(type) } + fields;

			for (int i = 0; !retn && i < list.size(); i++)
				retn << list.at(i)->process(variant);

			return retn;
		}

		const QJsonValue Schema::toJson(QVariant const& variant) {
			return QJsonValue::fromVariant(variant);
		}

		const bool Schema::isWriteOnly() const {
			return fields.hasField("readOnly");
		}

		const bool Schema::isReadOnly() const {
			return fields.hasField("writeOnly");
		}

		const QMetaType::Type Schema::getQtType() const {
			return type->getQtType();
		}

		const Swagger::Field::Type* Schema::getType() const
		{
			return type;
		}

		Schema* Schema::clone() const
		{
		
			return new Schema(getName(), type, fields);
		}

		QJsonValue Schema::getJson() const
		{
			return createJson(type, fields);
		}

		void Schema::setProperties(FieldList const& list)
		{
			fields = list;
		}

		void Schema::addProperties(FieldList const& list)
		{
			fields.append(list);
		}

		QJsonObject Schema::createJson(const Field::Type* type, FieldList const& properties)
		{
			const auto list = FieldList { const_cast<Field::Type*>(type) } + properties;
			QJsonObject retn;

			for (auto const& item : list) {
		
				const auto name = item->getName();
				const auto json = item->getJson();


				if (!name.isEmpty())
					retn[name] = json;
			}

			return retn;
		}
}