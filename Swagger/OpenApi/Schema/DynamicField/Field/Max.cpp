
#include "Max.h"

namespace Swagger
{

	namespace Field
	{
		Max::Max(const float value) : DynamicField("maximum"), m_maximum(value)
		{}

		ConvertError Max::process(QVariant& val) const {
			return { val.toFloat() >= m_maximum, error.arg(m_maximum) };
		}
		const QJsonValue Max::getJson() const {
			return m_maximum;
		}
		const QVariant Max::getVariant() const {
			return m_maximum;
		}
	}

}
