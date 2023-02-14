#pragma once
#include "../../../swagger_global.h"
#include "../DynamicField/Field/Type.h"

namespace Swagger
{

	class SWAGGER_EXPORT FieldFactory
	{
	public:
		static const DynamicField* ReadOnly();
		static const DynamicField* WriteOnly();

		static const DynamicField* Default(QString const& value);

		static const DynamicField* MinLength(const uint min);
		static const DynamicField* MaxLength(const uint max);

		template<int len>
		static const DynamicField* Min();

		template<int len>
		static const DynamicField* Max();

		template<int len>
		static const DynamicField* MinLength();

		template<int len>
		static const DynamicField* MaxLength();


		static const Field::Type* TypeObject();
		static const Field::Type* TypeArray();
		static const Field::Type* TypeString();
		static const Field::Type* TypeNumber();
		static const Field::Type* TypeBoolean();
		static const Field::Type* TypeInteger();

		static const DynamicField* Format(QString const& format, std::function<bool(QVariant&)> const& func);

		static const DynamicField* Summary(QString const& summary);
		static const DynamicField* Description(QString const& description);

		static const DynamicField* Pattern(QString const& regEx);
		static const DynamicField* QtPattern(QString const& qtReg);

	protected:
		static const DynamicField* Min(const float min);
		static const DynamicField* Max(const float max);

		template<Field::Type::SwaggerType type>
		static const Field::Type* Type();



	};

	using FF = FieldFactory;
}