#include "Components.h"
namespace Swagger
{
	Components::Components() : IJson("components")
	{

	}

	std::shared_ptr<Swagger::SchemaFactory> const& Components::schema() const
	{
		return schemaFactory;
	}

	std::shared_ptr<Swagger::OperationFactory> const& Components::operation() const
	{
		return operationFactory;
	}

	std::shared_ptr<Swagger::ResponseFactory> const& Components::response() const
	{
		return responseFactory;
	}

	std::shared_ptr<Swagger::ResponsesFactory> const& Components::responses() const
	{
		return responsesFactory;
	}

	std::shared_ptr<Swagger::ParameterFactory> const& Components::parameter() const
	{
		return parameterFactory;
	}

	std::shared_ptr<Swagger::RequestBodyFactory> const& Components::requestBody() const
	{
		return requestBodyFactory;
	}

	std::shared_ptr<Swagger::PathFactory> const& Components::path() const
	{
		return pathFactory;
	}
}