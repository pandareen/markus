#pragma once
#include "../DynamicField.h"
#include <QMetaType>

namespace Swagger
{
	namespace Field
	{
		class SWAGGER_EXPORT Type : public DynamicField
		{
		public:
			enum class SwaggerType : uchar { string, number, integer, boolean, array, object };

			Type(const SwaggerType type);

			ConvertError process(QVariant& val) const;
			const QJsonValue getJson() const final;
			const QVariant getVariant() const final;
			const QMetaType::Type getQtType() const;

		private:
			static QString const& swaggerTypes(const SwaggerType type);
			static QMetaType::Type const& qtTypes(const SwaggerType type);

		private:
			const SwaggerType type;
			inline static const QString error = "Value has not the correct type! [can't convert %1 to %2 type]";


			inline static const QStringList strTypes { "string", "number",	"integer",	"boolean", "array",	"object" };

			inline static const QList<QMetaType::Type> types {
				QMetaType::QByteArray,
				QMetaType::Double,
				QMetaType::Int,
				QMetaType::Bool,
				QMetaType::QVariantList,
				QMetaType::QVariantMap, };
		};
	}
}