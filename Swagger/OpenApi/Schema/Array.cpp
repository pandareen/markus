#include "Array.h"


namespace Swagger
{

		Array::Array(QString const& title, const std::shared_ptr<Schema>& data, FieldList const& fields)
			: Schema(title, FF::TypeArray(), fields), objectSchema(data)
		{

		}

		ConvertError Array::convert(QVariant& variant)  const {

			if (variant.metaType().id() == QMetaType::QJsonDocument) {
				variant = variant.toJsonDocument().array();
			}
			else if (variant.metaType().id() == QMetaType::QJsonValue) {
				variant = variant.toJsonValue().toArray();
			}
			else if (variant.metaType().id() == QMetaType::QByteArray) {
				variant = QJsonDocument::fromJson(variant.toByteArray()).array();
			}
			else if (variant.metaType().id() == QMetaType::QString) {
				variant = QJsonDocument::fromJson(variant.toString().toLatin1()).array();
			}
			else if (variant.metaType().id() == QMetaType::QStringList) {
				variant = QJsonArray::fromStringList(variant.toStringList());
			}

			if (variant.metaType().id() == QMetaType::QJsonArray) {
				variant = variant.toJsonArray().toVariantList();
			}
			else
			{

			}

			return Schema::convert(variant);
		}




		std::shared_ptr<Schema> Array::data() const {
			return objectSchema;
		}






}

