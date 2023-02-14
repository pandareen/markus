#include "FieldFactory.h"

#include "../DynamicField/Field/ReadOnly.h"
#include "../DynamicField/Field/WriteOnly.h"
#include "../DynamicField/Field/Default.h"
#include "../DynamicField/Field/Min.h"
#include "../DynamicField/Field/Max.h"
#include "../DynamicField/Field/MinLength.h"
#include "../DynamicField/Field/MaxLength.h"
#include "../DynamicField/Field/Format.h"
#include "../DynamicField/Field/Summary.h"
#include "../DynamicField/Field/Description.h"
#include "../DynamicField/Field/Pattern.h"



namespace Swagger
{

	const DynamicField* FieldFactory::ReadOnly() {
		const static auto retn = new Field::ReadOnly;
		return retn;
	}

	const DynamicField* FieldFactory::WriteOnly() {
		const static auto retn = new Field::WriteOnly;
		return retn;
	}

	const DynamicField* FieldFactory::Default(QString const& value) {
		const static auto retn = new Field::Default{ value };
		return retn;
	}

	const DynamicField* FieldFactory::Min(const float min) {
		return new Field::Min{ min };
	}

	const DynamicField* FieldFactory::Max(const float max) {
		return new Field::Max{ max };
	}

	const DynamicField* FieldFactory::MinLength(const uint min) {
		return new Field::MinLength{ min };
	}

	const DynamicField* FieldFactory::MaxLength(const uint max) {
		return new Field::MaxLength{ max };
	}

	template<int len>
	const DynamicField* FieldFactory::Min() {
		const auto static retn = new Field::Min{ len };
		return retn;
	}

	template<int len>
	const DynamicField* FieldFactory::Max() {
		const auto static retn = new Field::Max{ len };
		return retn;
	}

	template<int len>
	const DynamicField* FieldFactory::MinLength() {
		const auto static retn = new Field::MinLength{ len };
		return retn;
	}

	template<int len>
	const DynamicField* FieldFactory::MaxLength() {
		const auto static retn = new Field::MinLength{ len };
		return retn;
	}

	template<Field::Type::SwaggerType type>
	const Field::Type* FieldFactory::Type() {
		const auto static retn = new Field::Type{ type };
		return retn;
	}

	const Field::Type* FieldFactory::TypeObject()
	{
		return Type<Field::Type::SwaggerType::object>();
	}

	const Field::Type* FieldFactory::TypeInteger()
	{
		return Type<Field::Type::SwaggerType::integer>();
	}

	const Field::Type* FieldFactory::TypeArray()
	{
		return Type<Field::Type::SwaggerType::array>();
	}

	const Field::Type* FieldFactory::TypeString()
	{
		return Type<Field::Type::SwaggerType::string>();
	}

	const Field::Type* FieldFactory::TypeNumber()
	{
		return Type<Field::Type::SwaggerType::number>();
	}

	const Field::Type* FieldFactory::TypeBoolean()
	{
		return Type<Field::Type::SwaggerType::boolean>();
	}

	const DynamicField* FieldFactory::Format(QString const& format, std::function<bool(QVariant&)> const& func) {
		auto retn = new Field::Format{ format, func };
		return retn;
	}

	const DynamicField* FieldFactory::Summary(QString const& summary) {
		return new Field::Summary{ summary };
	}

	const DynamicField* FieldFactory::Description(QString const& description) {
		return  new Field::Description{ description };
	}

	const DynamicField* FieldFactory::Pattern(QString const& regEx) {
		return new Field::Pattern{ regEx };
	}

	//const DynamicField* FieldFactory::QtPattern(QString const& qtReg) {
	//	return new Field::QtPattern(qtReg);
	//}
}