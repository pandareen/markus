#pragma once
#pragma once
#include "../DynamicField.h"

namespace Swagger
{
	namespace Field
	{
		struct MultipleOf : public DynamicField
		{
		public:
			MultipleOf(const uint value);

			ConvertError process(QVariant& val) const final;

			const QJsonValue getJson() const final;
			const QVariant getVariant() const final;

		private:
			const uint multipleOf;
			inline static const QString error{ "value is no multiple of %1" };
		};

	}
}