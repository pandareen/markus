#pragma once
#include "../../../swagger_global.h"
#include <QString>
#include <QJsonValue>
#include <QJsonValue>
#include "../../../container/List.h"
#include "../ConvertError.h"

namespace Swagger
{
		class SWAGGER_EXPORT DynamicField
		{
		public:
			DynamicField(QString const& name);

			virtual const QJsonValue getJson() const = 0;

			const  QPair<QString, QJsonValue> getPair() const
			{
				return {getName(), getJson()};
			}
			virtual const QVariant getVariant() const = 0;

			QString const& getName() const;
			virtual ConvertError process(QVariant& val) const;

		private:
			const QString name;
		};

		class FieldList : public List<const DynamicField*>
		{
		public:
			using List<const DynamicField*>::List;

			bool hasField(QString const& title) const;
			const DynamicField* getField(QString const& title) const;

			FieldList& operator+(FieldList const& list);
			FieldList& operator<<(FieldList const& list);

			using QList<const DynamicField*>::at;
			using QList<const DynamicField*>::size;
			using QList<const DynamicField*>::operator<<;


		private:
			void removeEmptyFields();

		};


}