#include "MaxLength.h"

namespace Swagger
{
	namespace Field
	{
		MaxLength::MaxLength(const uint value) :
			DynamicField("maxLength"),
			maxLength(value)
		{}

		ConvertError MaxLength::process(QVariant& val) const {
			return {
				val.toString().size() > maxLength,
				error.arg(maxLength)
			};
		}
		const QJsonValue MaxLength::getJson() const {
			return (qint64)maxLength;
		}

		const QVariant MaxLength::getVariant() const {
			return maxLength;
		}
	}
}
