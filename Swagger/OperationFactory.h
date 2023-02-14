#pragma once
#include "swagger_global.h"
#include "OpenApi/Operation.h"
#include "OpenApi/Response/ResponsesFactory.h"

namespace Swagger
{
	class SWAGGER_EXPORT OperationFactory
	{
	public:
		OperationFactory(
			std::shared_ptr<::Swagger::SchemaFactory> const& schemaFactory,
			std::shared_ptr<ResponsesFactory> const& responsesFactory) :
			schemaFactory(schemaFactory), responsesFactory(responsesFactory)
		{

		}

		std::shared_ptr<::Swagger::Operation> create(
			QString const& id,
			ParameterList const& parameters,
			std::shared_ptr<Responses> const& responses,
			QStringList const& tags = {},
			QString const& summary = "",
			QString const& description = "",
			std::shared_ptr<RequestBody> const& body = nullptr) const;

	protected:
		const std::shared_ptr<SchemaFactory> schemaFactory;
		const std::shared_ptr<ResponsesFactory> responsesFactory;
	};
}


