#pragma once
#include "../DynamicField.h"


namespace Swagger
{
	namespace Field
	{
		struct MinLength : public DynamicField
		{
		public:

			MinLength(const uint value);

			ConvertError process(QVariant& val) const final;
			const QJsonValue getJson() const final;
			const QVariant getVariant() const final;

		private:
			const uint m_minLength;
			inline static QString error{ "the string size is smaller than the minimum of %1" };
		};
	}
}