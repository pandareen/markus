#include "RequestBodyFactory.h"



namespace Swagger
{

	RequestBodyFactory::RequestBodyFactory(std::shared_ptr<::Swagger::SchemaFactory> const& schemaFactory) : schemaFactory(schemaFactory)
	{

	}

	std::shared_ptr<::Swagger::RequestBody> RequestBodyFactory::createJsonRequestBody(std::shared_ptr<Schema> const& schema, QString const& description) const
	{
		return std::make_shared<::Swagger::RequestBody>(schema, "application/json", description);
	}

	std::shared_ptr<::Swagger::RequestBody> RequestBodyFactory::createBinaryRequestBody( QString const& description ) const
	{
		const static std::shared_ptr<::Swagger::Schema> binary(schemaFactory->binaryString(""));

		return std::make_shared<::Swagger::RequestBody>(binary, "application/octet-stream", description);
	}
}