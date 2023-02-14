#include "AnyOf.h"

namespace Swagger
{
	AnyOf::AnyOf(QString const& name, SchemaList const& objects) :
		Schema(name, FF::TypeObject(), {}),
		m_arr(mergeJson(objects)), objects(objects)
	{

	}

	ConvertError AnyOf::convert(QVariant& value) const {
		ConvertError retn = false;

		for (auto const& item : objects) {
			if (retn = item->convert(value)) {
				break;
			}
		}

		return retn;
	}

	QJsonArray AnyOf::mergeJson(SchemaList const& objects) {
		QJsonArray retn;

		for (auto item : objects) retn.append(item->getJson());
		
		return retn;
	}

	QJsonValue AnyOf::getJson() const {
		return QJsonObject{
			{ "anyOf", m_arr } , 
			{ "discriminator", QJsonObject{{"propertyName", "classType"}}	}
		};
	}

	Swagger::AnyOf* AnyOf::clone() const
	{
		return new AnyOf(getName(), objects);
	}
}