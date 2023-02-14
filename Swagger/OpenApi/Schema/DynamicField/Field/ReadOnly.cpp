
#include "ReadOnly.h"

namespace Swagger
{
	namespace Field
	{
		ReadOnly::ReadOnly() : DynamicField("readOnly") {}

		const QJsonValue ReadOnly::getJson() const {
			return true;
		}
		const QVariant ReadOnly::getVariant() const {
			return true;
		}
	}

}
