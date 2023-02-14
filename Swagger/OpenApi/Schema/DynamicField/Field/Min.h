#pragma once
#pragma once
#include "../DynamicField.h"

namespace Swagger
{
	namespace Field
	{
		struct Min : public DynamicField
		{
		public:
			Min(const float value);

			ConvertError process(QVariant& val) const final;
			const QJsonValue getJson() const final;
			const QVariant getVariant() const final;

		private:
			const float m_minimum;
			inline static const QString error{ "value is smaller than the minimum of %1" };
		};
	}
}