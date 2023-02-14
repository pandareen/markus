#include "Parameter.h"

namespace Swagger
{
	const QStringList Parameter::s_type = { "query", "header", "path", "cookie" };

	Parameter::Parameter(QString const& name, std::shared_ptr<Schema> const& schema, QString const& description, const Type in, const bool required, const bool deprecated) :
		IJson(name), m_description(description), m_required(required), m_deprecated(deprecated), m_schema(schema), m_in(in)
	{

	}

	const QJsonValue Parameter::getJson() const {
		return QJsonObject{
			{ "name", m_name }, //m_schema.getname() ?! #todo
			{ "in", s_type[static_cast<int>(m_in)] },
			{ "description", m_description},
			{ "required", m_required},
			{ "schema" , m_schema->getJson() },
		};
	}

	const QPair<QString, QJsonValue> Parameter::getPair() const {
		return QPair<QString, QJsonValue>();
	}

	Parameter::operator const Schema& () const {
		return *m_schema;
	}

	const bool Parameter::operator==(const Type type) const {
		return m_in == type;
	}

	Parameter::operator const Type() {
		return m_in;
	}

	const bool Parameter::isRequired() const {
		return m_required;
	}

	std::shared_ptr<Schema> Parameter::scheme() const {
		return m_schema;
	}

	bool Parameter::convert(QVariant& value) const
	{
		if ( !(value.isValid() && scheme()->convert(value)) ) {
			value = QVariant();
			return true;
		}

		return false;
	}
}

