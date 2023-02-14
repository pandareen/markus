#pragma once
#include "../DynamicField.h"
#include <QStringView>

namespace Swagger
{
	namespace Field
	{
		struct MaxLength : public DynamicField
		{
		public:
			MaxLength(const uint value);

			ConvertError process(QVariant& val) const final;
			const QJsonValue getJson() const final;
			const QVariant getVariant() const final;

		private:
			const uint maxLength;
			inline static const QString error{ "the string size is bigger than the maximum of %1" };
		};
	}
}