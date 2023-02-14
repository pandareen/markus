#include "MultipleOf.h"

namespace Swagger
{
	namespace Field
	{
		MultipleOf::MultipleOf(const uint value) :
			DynamicField("multipleOf"),
			multipleOf(value) {
		}

		ConvertError MultipleOf::process(QVariant& val) const {
			return { static_cast<bool>(val.toUInt() % multipleOf), error.arg(multipleOf) };
		}

		const QJsonValue MultipleOf::getJson() const {
			return static_cast<int>(multipleOf);
		}

		const QVariant MultipleOf::getVariant() const {
			return static_cast<int>(multipleOf);
		}
	}
}
