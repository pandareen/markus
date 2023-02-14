#pragma once
#include "../DynamicField.h"

namespace Swagger
{
	namespace Field
	{
		struct Enum : public DynamicField
		{
		public:
			Enum(QStringList const& types);

			ConvertError process(QVariant& val) const;

			const QJsonValue getJson() const;
			const QVariant getVariant() const final;

		private:
			const QStringList m_types;
			inline static const QString error{ "Value does not match enum! Value should be one of these: %1" };
		};
	}
}