#pragma once
#include "../../swagger_global.h"
#include "Parameter.h"
#include "../Schema/Factory/SchemaFactory.h"

namespace Swagger
{
	class SWAGGER_EXPORT ParameterFactory
	{
	public:
		ParameterFactory(std::shared_ptr<::Swagger::SchemaFactory> const& schemaFactory);

		std::shared_ptr<Parameter> createIdentifierPathParameter(std::shared_ptr<::Swagger::Schema> const& identifier) const;
		std::shared_ptr<Parameter> createSortByParameter(QStringList const& possibleProperties) const;
		std::shared_ptr<Parameter> createOrderByParameter() const;
		std::shared_ptr<Parameter> createFilterNameParameter() const;
		std::shared_ptr<Parameter> createFileNameParameter() const;
		std::shared_ptr<Parameter> createFileFormatParameter(QStringList const& formats) const;
		std::shared_ptr<Parameter> createPageIndexParameter() const;



		std::shared_ptr<::Swagger::Parameter> createPathParameter(
			QString const& name,
			std::shared_ptr<::Swagger::Schema> const& schema,
			QString const& description = "",
			bool required = true) const;

	private:
		std::shared_ptr<::Swagger::Parameter> createQueryParameter(
			QString const& name,
			std::shared_ptr<::Swagger::Schema> const& schema,
			QString const& description = "",
			bool required = false) const;


		const std::shared_ptr<::Swagger::SchemaFactory> schemaFactory;
	};
}