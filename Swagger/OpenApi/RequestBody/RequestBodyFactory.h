#pragma once
#include "RequestBody.h"
#include "../Schema/Factory/SchemaFactory.h"

namespace Swagger
{
	class RequestBodyFactory
	{
	public:
		RequestBodyFactory(std::shared_ptr<::Swagger::SchemaFactory> const& schemaFactory);

		std::shared_ptr<::Swagger::RequestBody> createJsonRequestBody(
			std::shared_ptr<Schema> const& schema, 
			QString const& description = "") const;

		std::shared_ptr<::Swagger::RequestBody> createBinaryRequestBody(QString const& description = "") const;


	private:
		std::shared_ptr<::Swagger::SchemaFactory> schemaFactory;

	};

}