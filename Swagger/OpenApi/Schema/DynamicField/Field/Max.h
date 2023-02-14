#pragma once
#pragma once
#include "../DynamicField.h"

namespace Swagger
{
	namespace Field
	{
	
		struct Max : public DynamicField
		{
		public:
			Max(const float value);

			ConvertError process(QVariant& val) const final;
			const QJsonValue getJson() const final;
			const QVariant getVariant() const final;

		private:
			const float m_maximum;
			inline static const QString error{ "value is bigger than the maximum of %1" };
		};


	}
	


}