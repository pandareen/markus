#pragma once
#include "../DynamicField.h"


namespace Swagger
{
	namespace Field
	{
		class Description : public DynamicField
		{

		public:
			Description(QString const& description);
			const QVariant getVariant() const final;
			const QJsonValue getJson() const final;

		private:
			const QString m_description;
		};
	}
}