#pragma once
#include "../DynamicField.h"

namespace Swagger
{
	
	namespace Field
	{
		class WriteOnly : public DynamicField {
		public:
			WriteOnly();

			const QJsonValue getJson() const final;
			const QVariant getVariant() const final;

		};
	}
}