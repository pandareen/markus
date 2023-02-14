
#include "Summary.h"

namespace Swagger
{
	namespace Field
	{
		
		Summary::Summary(QString const& summary) : DynamicField("summary"), m_summary(summary)
		{

		}

		const QJsonValue Summary::getJson() const {
			return m_summary;
		}
		const QVariant Summary::getVariant() const {
			return m_summary;
		}
	}
}
