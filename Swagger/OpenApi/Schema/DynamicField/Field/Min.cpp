#include "Min.h"

namespace Swagger
{
	namespace Field
	{
		Min::Min(const float value) : DynamicField("minimum"), m_minimum(value)

		{}

		ConvertError Min::process(QVariant& val) const {
			return {
				val.toFloat() <= m_minimum,
				error.arg(m_minimum)
			};
		}

		const QJsonValue Min::getJson() const {
			return m_minimum;
		}

		const QVariant Min::getVariant() const {
			return m_minimum;
		}

	}
}
