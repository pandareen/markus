#include "OneOf.h"



namespace Swagger
{

	OneOf::OneOf(QString const& name, SchemaList const& objects) :
		Schema(name, FF::TypeObject(), {}),
		m_arr(mergeJson(objects)), objects(objects)
	{

	}

	ConvertError OneOf::convert(QVariant& value) const {
		ConvertError error = false;

		for (auto const& item : objects) 
			if (error = item->convert(value); error.occured() == false) {
				const auto name = item->getName();
				const auto json = value.toJsonObject();
				const auto classType = json["classType"].toString();

				error << ConvertError{name != classType, QString("classtype is not correct for this object [should be %1 and is %2]").arg(name).arg(classType)};
				break;
			}
		
		return error;
	}

	QJsonArray OneOf::mergeJson(SchemaList const& objects) {
		QJsonArray retn;

		for (auto item : objects) {
			retn.append(item->getJson());
		}
		return retn;
	}

	QJsonValue OneOf::getJson() const {
		return QJsonObject{ 
			
			{ "oneOf", m_arr } , 
			{ "discriminator", QJsonObject{{"propertyName", "classType"}}	}
		};
	}

	Swagger::OneOf* OneOf::clone() const
	{
		return new OneOf(getName(), objects);
	}

}