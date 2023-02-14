#include "AllOf.h"

namespace Swagger
{

	AllOf::AllOf(QString const& title, QList<Swagger::Object*> const& objects, FieldList const& fields) :

		Object(title,  mergeProperties(objects) ,  mergeRequired(objects) , fields),
		m_arr(mergeJson(objects)), objects(objects)
	{

	}

	SchemaList AllOf::mergeProperties(QVector<Object*> const& objects) {
		SchemaList retn;

		for (auto const& item : objects) {
			retn.append(item->getProperties());
		}
		return retn;
	}

	QStringList AllOf::mergeRequired(QVector<Object*> const& objects) {
		QStringList retn;

		for (auto const& item : objects) {
			retn.append(item->getRequired());
		}
		return retn;
	}

	QJsonArray AllOf::mergeJson(QVector<Object*> const& objects) {
		QJsonArray retn;

		for (auto item : objects) {
			retn.append(item->getJson());
		}
		return retn;
	}

	QJsonValue AllOf::getJson() const {
		return QJsonObject{ { "allOf", m_arr } };
	}
}