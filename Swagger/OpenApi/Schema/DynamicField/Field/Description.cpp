
#include "Description.h"

namespace Swagger
{

	namespace Field
	{
		Description::Description(QString const& description) : DynamicField("description"),
			m_description(description)
		{

		}
		const QVariant Description::getVariant() const {
			return m_description;
		}
		const QJsonValue Description::getJson() const {
			return m_description;
		}
	}

}
