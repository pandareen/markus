
#include "WriteOnly.h"

namespace Swagger
{

	namespace Field
	{
		WriteOnly::WriteOnly() : DynamicField("writeOnly") {}

		const QJsonValue WriteOnly::getJson() const {
			return true;
		}
		const QVariant WriteOnly::getVariant() const {
			return true;
		}

	}
}
