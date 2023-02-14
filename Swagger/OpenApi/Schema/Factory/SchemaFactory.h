#pragma once
#include "../../../swagger_global.h"
#include "../Object/Object.h"
#include "../Schema.h"
#include "../Array.h"
#include "../DynamicField/DynamicField.h"
#include "../../../container/Reference.h"
#include "../Object/AllOf.h"
#include "../Object/OneOf.h"
#include "../../../container/Map.h"

namespace Swagger
{
		class SWAGGER_EXPORT SchemaFactory
		{
		public:
			Object* object(QString const& title, SchemaList const& list) const;
			Object* object(QString const& title, SchemaList const& list, QStringList const& required, FieldList const& fields = {}) const;
			Object* object(QString const& title, SchemaList const& list, SchemaList const& required, FieldList const& fields = {}) const;

			Schema* objectIntoStorage(QString const& title, SchemaList const& list, QStringList const& required, FieldList const& fields = {}) const;

			Schema* AllOf(QString const& title, QList<Swagger::Object*>  const& objects, FieldList const& fields = {})const;
			Schema* OneOf(QString const& title, SchemaList const& objects, FieldList const& fields = {}) const;
			Schema* AnyOf(QString const& title, SchemaList const& objects, FieldList const& fields = {}) const;

			Array* array(QString const& title, std::shared_ptr<Schema> const& data, FieldList const& properties = {})const;
			
			Schema* binaryString(QString const& title, FieldList const& properties = {}) const;
			Schema* string(QString const& title, FieldList const& properties = {})const;
			Schema* UniqueName(QString const& title) const;
			Schema* integer(QString const& title, FieldList const& properties = {}) const;

			Schema* TinyInt(QString const& title, FieldList const& properties = {})const;
			Schema* SmallInt(QString const& title, FieldList const& properties = {})const;
			Schema* UInt(QString const& title, FieldList const& properties = {} ) const;
			Schema* BigInt(QString const& title, FieldList const& properties = {} ) const;
			Schema* Enum(QString const& title, QStringList const& types, FieldList const& properties = {}) const;

			Schema* Time(QString const& title, FieldList const& properties = {}) const;
			Schema* Float(QString const& title, FieldList const& properties = {}) const;
			Schema* Date(QString const& title, FieldList const& properties = {}) const;
			Schema* DateTime(QString const& title, FieldList const& properties = {}) const;

			Schema* Binary(QString const& title, FieldList const& properties = {}) const;
			Schema* Url(QString const& title, FieldList const& properties = {}) const;
			Schema* Hash256(QString const& title, FieldList const& properties = {})const;
			Schema* Bool(QString const& title, FieldList const& properties = {})const;

			Schema* identifier(QString const& title)const;
			QString path()const;
			QJsonObject getJson() const;


			static std::shared_ptr<Schema> getSchemaFromStorage(QString const& name);

		private:
			Schema* integer(QString const& title, const DynamicField* const format, FieldList const& properties = {}) const;
			Schema* number(QString const& title, const DynamicField* const format, FieldList const& properties) const;
			Schema* string(QString const& title, const DynamicField* const format, FieldList const& properties = {})const ;


			template <typename T, typename ... Args>
			static T* create(QString const& title, Args&& ... args) {

				return new T(title, std::forward<Args>(args)...);
			}

			template <typename T, typename ... Args>
			static Schema* createIntoStorage(QString const& title, Args&& ... args) {

				if (!schemaMap.contains(title)) {
					auto ptr = std::make_shared<T>(title, std::forward<Args>(args)...);
					schemaMap[title] = std::make_shared<Reference<T>>(refPath, ptr);
					components[title] = ptr->getJson();
				}


				return schemaMap[title]->clone();
			}

			//#todo make that dynamic, doesnt work don'T know..,.
			static inline QMap<QString, std::shared_ptr<Schema>> schemaMap;
			static inline QJsonObject components;

			static const inline QString refPath = "#/components/schemas/";
		};

		using SF = SchemaFactory;
}