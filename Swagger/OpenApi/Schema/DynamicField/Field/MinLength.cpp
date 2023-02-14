
#include "MinLength.h"

namespace Swagger
{
	namespace Field
	{
	
		MinLength::MinLength(const uint value) : DynamicField("minLength"),
			m_minLength(value)
		{}

		ConvertError MinLength::process(QVariant& val) const {

				return {
					val.toString().size() < m_minLength,
					error.arg(m_minLength)
				};
		}

		const QJsonValue MinLength::getJson() const {
			return (qint64)m_minLength;
		}
		const QVariant MinLength::getVariant() const {
			return m_minLength;
		}

	}
}
