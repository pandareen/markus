
#include "Default.h"

namespace Swagger
{
	namespace Field
	{
		Default::Default(QString const& value ) : DynamicField("default"), m_default(value) {


		}
		const QJsonValue Default::getJson() const {
			return m_default;
		}

		const QVariant Default::getVariant() const {
			return m_default;
		}
	}
}
