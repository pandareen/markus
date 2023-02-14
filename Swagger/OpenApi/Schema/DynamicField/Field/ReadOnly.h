#pragma once
#pragma once
#include "../DynamicField.h"

namespace Swagger
{
	namespace Field
	{
		class ReadOnly : public DynamicField {

		public:
			ReadOnly();

			const QJsonValue getJson() const final;
			const QVariant getVariant() const final;
		};
	}
}