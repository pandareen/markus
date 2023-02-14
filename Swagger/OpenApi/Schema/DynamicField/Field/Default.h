#pragma once
#include "../DynamicField.h"


namespace Swagger
{
	namespace Field
	{
		class  Default : public DynamicField {

		public:
			Default(QString const& value);

			const QJsonValue getJson() const final;
			const QVariant getVariant() const final;
		
		private:
			const QString m_default;
		};
	}
}