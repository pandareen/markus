#include "Enum.h"
#include <QJsonArray>

namespace Swagger
{

	namespace Field
	{
		Enum::Enum(QStringList const& types) : DynamicField("enum"), m_types(types)

		{}

		Swagger::ConvertError Enum::process(QVariant& val) const {
			return {
				!m_types.contains(val.toString()),
				error.arg( m_types.join(","))
			};
		}

		const QJsonValue Enum::getJson() const {
			return QJsonArray::fromStringList(m_types);
		}

		const QVariant Enum::getVariant() const {
			return m_types;
		}

	}

}
