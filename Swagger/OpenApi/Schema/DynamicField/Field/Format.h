#pragma once
#include "../DynamicField.h"


namespace Swagger
{
	namespace Field
	{
		struct Format : public DynamicField
		{
		public:
			Format(QString const& format, std::function<bool(QVariant&)> const& func);

			ConvertError process(QVariant& val) const final;
			const QJsonValue getJson() const final;
			const QVariant getVariant() const final;

		private:
			const QString m_format;
			const std::function<bool(QVariant&)> m_processFunc;
			static inline const QString error{ "Value has not the correct format! [%1]" };
		};
	}
}