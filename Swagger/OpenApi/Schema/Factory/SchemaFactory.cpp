#include "SchemaFactory.h"

#include "../DynamicField/Field/Enum.h"
#include "../Object/AnyOf.h"

namespace Swagger
{
	Schema* SchemaFactory::objectIntoStorage(QString const& title, SchemaList const& list, QStringList const& required, FieldList const& fields) const {

		return  createIntoStorage<Object>(title, list, required, fields);
	}

	Object* SchemaFactory::object(QString const& title, SchemaList const& list) const {
		return  create<Object>(title, list, QStringList{});
	}

	Object* SchemaFactory::object(QString const& title, SchemaList const& list, QStringList const& required, FieldList const& fields) const {

		return  create<Object>(title, list, required, fields);
	}

	Array* SchemaFactory::array(QString const& title, std::shared_ptr<Schema> const& data, FieldList const& properties) const {
		return  create<Array>(title, data, properties);
	}

	Schema* SchemaFactory::binaryString(QString const& title, FieldList const& properties /*= {}*/) const
	{
		static auto format = FF::Format("binary",
			[&](QVariant& value) {
				return value.convert(QMetaType::Type::QByteArray);
			});

		return  string(title, format, properties);
	}


	Object* SchemaFactory::object(QString const& title, SchemaList const& list, SchemaList const& required, FieldList const& fields) const {

		QStringList strList;

		for (auto const& item : required) {
			strList << item->getName();
		}

		return  create<Object>(title, list, strList, fields);
	}

	Schema* SchemaFactory::AllOf(QString const& title, QList<Swagger::Object*>  const& objects, FieldList const& fields) const
	{
		return createIntoStorage<Swagger::AllOf>(title, objects, fields);
	}

	Schema* SchemaFactory::OneOf(QString const& title, SchemaList const& objects, FieldList const& fields /*= {}*/) const
	{
		return new Swagger::OneOf(title, objects);
	}

	Schema* SchemaFactory::AnyOf(QString const& title, SchemaList const& objects, FieldList const& fields /*= {}*/) const
	{
		return new Swagger::AnyOf(title, objects);
	}

	Schema* SchemaFactory::TinyInt(QString const& title, FieldList const& properties) const {
		static const auto format = FF::Format(
			"int8",
			[&](QVariant& value) {
				return !(value.toInt() <= 255);
			}
		);

		return  integer(title, format, properties);
	}

	Schema* SchemaFactory::SmallInt(QString const& title, FieldList const& properties) const {
		static const auto format = FF::Format(
			"int16",
			[&](QVariant& value) {
				return !(value.toInt() <= 32767 && value.toInt() >= -32767);
			}
		);

		return  integer(title, format, properties);
	}

	Schema* SchemaFactory::UInt(QString const& title, FieldList const& properties)const {
		static const auto format = FF::Format(
			"uint",
			[&](QVariant& value) {
				bool isUInt = false;
				value.toUInt(&isUInt);
				return !isUInt;
			}
		);

		return  integer(title, format, properties);
	}

	Schema* SchemaFactory::BigInt(QString const& title, FieldList const& properties) const {
		static const auto format = FF::Format(
			"int32",
			[&](QVariant& value) {
				bool isBigInt = false;
				value.toLongLong(&isBigInt);
				return !isBigInt;
			}
		);

		return  integer(title, format, properties);
	}

	Schema* SchemaFactory::Enum(QString const& title, QStringList const& types, FieldList const& properties) const {
		return string(title, FieldList{ new Field::Enum{types} } + properties);
	}

	Schema* SchemaFactory::DateTime(QString const& title, FieldList const& properties)const {
		auto format = FF::Format(
			"date-time",
			[title](QVariant& value) {

				const auto timeString = value.toString();
				auto dateTime = QDateTime::fromString(timeString);

				if (!dateTime.isValid())
					dateTime = QDateTime::fromString(timeString, Qt::DateFormat::ISODate);

				if (!dateTime.isValid())
					dateTime = QDateTime::fromString(timeString, Qt::DateFormat::ISODateWithMs);
				
				const auto dateTimeValid = dateTime.isValid();
				const auto isCreatedDataType = (title == "created" && timeString.isEmpty());
				const auto canConvert = isCreatedDataType || ( dateTimeValid );

				return !canConvert;
			});

		return  string(title, format, properties);
	}

	Schema* SchemaFactory::Date(QString const& title, FieldList const& properties) const {
		static auto format = FF::Format(
			"date",
			[&](QVariant& value) {
				return !value.convert(QMetaType::Type::QDate);
			});

		return  string(title, format, properties);
	}

	Schema* SchemaFactory::Binary(QString const& title, FieldList const& properties) const {
		static auto format = FF::Format("binary",
			[&](QVariant& value) {
				return !value.convert(QMetaType::Type::QByteArray);
			});

		return  string(title, format, properties);
	}

	Schema* SchemaFactory::Url(QString const& title, FieldList const& properties)const {
		static auto format = FF::Format("url",
			[&](QVariant& value) {
				const QUrl url(value.toString());
				return !(url.isValid() && value.convert(QMetaType::Type::QString));
			});

		return string(title, format, properties);
	}

	Schema* SchemaFactory::Hash256(QString const& title, FieldList const& properties)const {
		static auto* format = FF::Format("hash",
			[&](QVariant& value) {
				bool retn = value.convert(QMetaType::Type::QString);
				const QString& hash = value.toString();
				retn = retn && hash.length() == 64;

				for (int i = 0; retn && i < hash.size();i++) {
					retn = (hash[i].isDigit()) || (hash[i].isLetter());
				}
				return !retn;
			});
		static auto pattern = FieldList{ FF::Pattern("^[A-Fa-f0-9]{64}$") };

		return string(title, format, FieldList{ properties } + pattern);

	}

	Schema* SchemaFactory::Time(QString const& title, FieldList const& properties) const {
		static auto format = FF::Format("time",
			[&](QVariant& value) {

				const auto timeString = value.toString();
				auto time = QTime::fromString(timeString);

				if (!time.isValid())
					time = QTime::fromString(timeString, Qt::DateFormat::ISODate);

				if (!time.isValid())
					time = QTime::fromString(timeString, Qt::DateFormat::ISODateWithMs);
				
				const auto timeValid = time.isValid();

				return !timeValid;
			});

		return  string(title, format, properties);
	}

	Schema* SchemaFactory::Float(QString const& title, FieldList const& properties) const {
		static auto format = FF::Format("float",
			[&](QVariant& value) {
				bool isFloat = false;
				value.toFloat(&isFloat);
				return !isFloat;
			});

		return  number(title, format, properties);
	}

	Schema* SchemaFactory::number(QString const& title, const DynamicField* const format, FieldList const& properties) const {
		return create<Schema>(title, FF::TypeNumber(), FieldList{ format } + properties);
	}
	Schema* SchemaFactory::integer(QString const& title, const DynamicField* const format, FieldList const& properties)const {
		return create<Schema>(title, FF::TypeInteger(), FieldList{ format } + properties);
	}

	Schema* SchemaFactory::string(QString const& title, FieldList const& properties)const {
		return  create<Schema>(title, FF::TypeString(),  properties);
	}

	Schema* SchemaFactory::UniqueName(QString const& title) const {

		constexpr uchar maxLength = 60;

		static auto pattern = FieldList{
			FF::Pattern(
				"^[a-zA-Z0-9_.-]*$"
			),
			FF::MinLength(1),
			FF::MaxLength(maxLength) 
		};

		static auto* format = FF::Format("uniqueName",
			[maxLength](QVariant& value) {
// 				const static QList<QChar> allowedCharacters{ '.', '_',  '-' , '~' };
// 
// 				bool canConvert = value.convert(QVariant::Type::String);
// 				const auto name = value.toString();
// 				canConvert = canConvert && name.length() <= maxLength && name.length() >= 1;
// 
// 				for (int i = 0; canConvert && i < name.size(); i++)
// 					canConvert = (name[i].isDigit()) || (name[i].isLetter() || allowedCharacters.contains(name[i]));
// 
// 				return !canConvert;
				return false;
			});

		return string(title, format, pattern);
	}

	Schema* SchemaFactory::integer(QString const& title,  FieldList const& properties)const {
		return create<Schema>(title, FF::TypeInteger(),  properties);
	}
					
	Schema* SchemaFactory::string(QString const& title, const DynamicField* const format, FieldList const& properties)const {
		return  create<Schema>(title, FF::TypeString(), FieldList{ format } + properties);
	}

	Schema* SchemaFactory::Bool(QString const& title, FieldList const& properties) const {
		return create<Schema>(title, FF::TypeBoolean(), properties);
	}

	Schema* SchemaFactory::identifier(QString const& title)const {

		constexpr uchar identifierLength = 30;

		static auto pattern = FieldList{ FF::Pattern(
			"^[A-Fa-f0-9]{30}$|^(?![\s\S])$"
		), FF::ReadOnly() };

		static auto* format = FF::Format("identifier",
			[&](QVariant& value) {
				bool canConvert = value.convert(QMetaType::Type::QString);
				const auto hash = value.toString();

				canConvert = canConvert && (hash.length() == 30 || hash.isEmpty());

				for (int i = 0; canConvert && i < hash.size(); i++) 
					canConvert = (hash[i].isDigit()) || (hash[i].isLetter());
				
				return !canConvert;
			});


		return string(title, format, pattern);
	}

	QString SchemaFactory::path() const
	{
		return refPath;
	}

	QJsonObject SchemaFactory::getJson() const
	{

		return components;
	}

	std::shared_ptr<Swagger::Schema> SchemaFactory::getSchemaFromStorage(QString const& name)
	{
		return schemaMap[name];
	}

}