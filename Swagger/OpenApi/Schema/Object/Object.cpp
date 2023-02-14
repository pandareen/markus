#include "Object.h"
#include <QJsonDocument>

namespace Swagger
{


	struct Object::Properties : public DynamicField
	{
	public:
		Properties(SchemaList	const& properties);

		ConvertError process(QVariant& val) const;

		const QJsonValue getJson() const final;
		const QVariant getVariant() const final;

		const SchemaList& getList() const;

	private:
		const SchemaList m_properties;

	};

	Object::Properties::Properties(SchemaList const& properties) : DynamicField("properties"),
		m_properties(properties)
	{}

	Swagger::ConvertError Object::Properties::process(QVariant& val) const {
		QVariantMap map = val.toMap();
		ConvertError error;

		for (int i = 0; !error && i < m_properties.size(); i++) {
			const auto property = m_properties[i]; 
			const auto& title = property->getName();

			auto& value = map[title];
			const bool hasValue = map.contains(title);
			const bool isNull = value.isNull();

			if (isNull && property->getQtType() == QMetaType::Type::QVariantMap)
			{
				
			}
			else if (!property->isReadOnly() && hasValue) {
				error << ConvertError{ isNull, "property is null [ " + title + " ]" };
				error << property->convert(value);

				if (property->getQtType() == QMetaType::Type::QVariantMap)
					if (error.list().last().startsWith("too many properties"))
					{
						error.eraseError(error.list().size()-1);
					}
			}
			map.remove(title);
		}

		return 	error << ConvertError{ !error && !map.isEmpty(), "too many properties [ " + map.keys().join("; ") + " ]" };
	}

	const QJsonValue Object::Properties::getJson() const {

		return 	m_properties.getJson();
	}

	const QVariant Object::Properties::getVariant() const {
		return m_properties.getJson();
	}

	const SchemaList& Object::Properties::getList() const
	{
		return m_properties;
	}

	struct Object::Required : public DynamicField
	{
	public:
		Required(QStringList const& required);

		ConvertError process(QVariant& val) const;

		const QJsonValue getJson() const final;
		const QStringList& required() const;

		const QVariant getVariant() const final;

	private:
		const QStringList m_required;
		inline const static QString error = "Object has properties that are required, but missing. Required: [%1]";
	};

	Object::Required::Required(QStringList const& required) : DynamicField("required"), m_required(required)

	{}

	Swagger::ConvertError Object::Required::process(QVariant& val) const {
		const QVariantMap map = val.toMap();
		bool retn = true;

		for (int i = 0; retn && i < m_required.size(); i++)
			retn = map.contains(m_required[i]);

		return { !retn,  error.arg(m_required.join(",")) };
	}


	Object::Object(QString const& title, const Object::Properties* properties, const Object::Required* required, FieldList const& fields) :
		Schema(title, FF::TypeObject(), FieldList{ const_cast<Object::Properties*>(properties) } + FieldList{ required } + fields),
		properties(properties), required(required)
	{}

	Object::Object(QString const& title,
		SchemaList const& properties,
		QStringList const& required,
		FieldList const& fields)
		: Object(title, new Object::Properties(properties), new Object::Required(required), fields)
	{

	}


	const Swagger::SchemaList Object::getProperties() const
	{
		return properties->getList();
	}

	const QStringList Object::getRequired() const
	{
		return required->required();
	}

	QJsonValue Object::getJson() const
	{
		auto json = Schema::getJson().toObject();

		if (required->required().isEmpty())
			json.remove("required");

		return json;
	}


	Swagger::Object* Object::clone() const
	{
		auto retn = new Object(getName(), properties, required, fields);
		retn->setProperties(fields);
		return retn;
	}

	ConvertError Object::convert(QVariant& variant) const {
		ConvertError retn;

		if (variant.typeId() != QMetaType::QVariantMap) {
			if (variant.typeId() == QMetaType::QJsonValue) {
				variant = variant.toJsonValue().toObject();
			}
			else if (variant.typeId() == QMetaType::QByteArray) {
				QJsonParseError error;
				variant = QJsonDocument::fromJson(variant.toByteArray(), &error).object();
				retn << ConvertError{ error.error != QJsonParseError::NoError, "JsonParser: " + error.errorString() + "(" + QString::number(error.offset) + ")" };
			}
			else if (variant.typeId() == QMetaType::QString) {
				QJsonParseError error;
				variant = QJsonDocument::fromJson(variant.toString().toLatin1(), &error).object();
				retn << ConvertError{ error.error != QJsonParseError::NoError,  "JsonParser: " + error.errorString() + "(" + QString::number(error.offset) + ")" };
			}

			if (variant.typeId() == QMetaType::QJsonDocument) variant = variant.toJsonDocument().object();

			if (variant.typeId() == QMetaType::QJsonObject) {
				variant = variant.toJsonObject().toVariantMap();
			}
			else variant = QVariantMap();
		}

		retn << ConvertError{ variant.toMap().isEmpty(), "Couldn't convert data to json object" };

		if (!retn.occured())
			retn << Schema::convert(variant);

		return retn;
	}

	const QJsonValue Object::Required::getJson() const {
		return QJsonArray::fromStringList(m_required);
	}

	const QStringList& Object::Required::required() const {
		return m_required;
	}

	const QVariant Object::Required::getVariant() const {
		return m_required;
	}

}
