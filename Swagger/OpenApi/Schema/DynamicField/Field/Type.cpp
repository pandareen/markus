
#include "Type.h"

namespace Swagger
{
	namespace Field
	{
		Type::Type(const SwaggerType type) 	: DynamicField("type"),
			type(type)

		{}

		ConvertError Type::process(QVariant& val) const {
			return { !val.convert(QMetaType(getQtType())), error.arg(val.typeName()).arg(swaggerTypes(type))};
		}

		const QJsonValue Type::getJson() const {
			return swaggerTypes(type);
		}

		const QVariant Type::getVariant() const {
			return static_cast<uchar>(type);
		}

		const QMetaType::Type Type::getQtType() const {
			return qtTypes(type);
		}

		const QString& Type::swaggerTypes(const SwaggerType type) {
			return strTypes.at(static_cast<int>(type));
		}

		QMetaType::Type const& Type::qtTypes(const SwaggerType type) {
			return types.at(static_cast<int>(type));
		}
	}

}
