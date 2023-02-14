#pragma once
#pragma once
#include "../DynamicField.h"

namespace Swagger
{
	namespace Field
	{
		class Summary : public DynamicField
		{

		public:
			Summary(QString const& summary);

			const QJsonValue getJson() const final;
			const QVariant getVariant() const final;

		private:
			const QString m_summary;
		};

	}
}