#include "ParameterFactory.h"

namespace Swagger
{
	ParameterFactory::ParameterFactory(std::shared_ptr<SchemaFactory> const& schemaFactory) : schemaFactory(schemaFactory)
	{

	}

	std::shared_ptr<Parameter> ParameterFactory::createIdentifierPathParameter(std::shared_ptr<::Swagger::Schema> const& identifier) const
	{
		return createPathParameter("id", identifier, "The identifier of a resource");
	}

	std::shared_ptr<Parameter> ParameterFactory::createFilterNameParameter() const
	{
		return createQueryParameter("filterName", std::shared_ptr<Schema>(schemaFactory->UniqueName("filterName")), "the name of a Filter resource");
	}

	std::shared_ptr<Parameter> ParameterFactory::createSortByParameter(QStringList const& possibleProperties) const
	{
		return createQueryParameter("sortBy", std::shared_ptr<Schema>(schemaFactory->Enum("sortBy", possibleProperties)));
	}

	std::shared_ptr<Parameter> ParameterFactory::createOrderByParameter() const
	{
		return createQueryParameter("orderBy", std::shared_ptr<Schema>(schemaFactory->Enum("orderBy", { "ASC", "DESC" })));
	}

	std::shared_ptr<Parameter> ParameterFactory::createFileNameParameter() const
	{
		return createQueryParameter("filename", std::shared_ptr<Schema>(schemaFactory->string("filename")) );
	}

	std::shared_ptr<Parameter> ParameterFactory::createFileFormatParameter(QStringList const& formats) const
	{
		return createQueryParameter("format", std::shared_ptr<Schema>(schemaFactory->Enum("format", formats)));
	}

	std::shared_ptr<Parameter> ParameterFactory::createPageIndexParameter() const
	{
		return createQueryParameter("pageIndex", std::shared_ptr<Schema>(schemaFactory->UInt("pageIndex")) );
	}

	std::shared_ptr<Parameter> ParameterFactory::createPathParameter(QString const& name, std::shared_ptr<Schema> const& schema , QString const& description, bool required) const
	{
		return std::make_shared<Parameter>(name, schema,description, Parameter::Type::path, required);
	}

	std::shared_ptr<Parameter> ParameterFactory::createQueryParameter(QString const& name, std::shared_ptr<Schema> const& schema, QString const& description, bool required) const
	{
		return std::make_shared<Parameter>(name, schema, description, Parameter::Type::query, required);
	}
}