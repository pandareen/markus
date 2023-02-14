#include "Object.h"

namespace Swagger
{
	class AllOf : public Object
	{
	public:
		AllOf(QString const& title, QList<Swagger::Object*> const& objects, FieldList const& fields);


		static SchemaList mergeProperties(QVector<Object*> const& objects);
		static QStringList mergeRequired(QVector<Object*> const& objects);
		static QJsonArray mergeJson(QVector<Object*> const& objects);

		virtual QJsonValue getJson() const;

		AllOf* clone() const
		{
			auto retn = new AllOf(getName(), objects, fields);
			retn->setProperties(fields);
			return retn;
		}
	private:
		const QJsonArray m_arr;
		const QList<Object*> objects;

	};
}