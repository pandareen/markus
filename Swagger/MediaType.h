#pragma once
#include "OpenApi/Schema/Schema.h"


namespace Swagger
{
	class  SWAGGER_EXPORT MediaType
	{
	public:
		MediaType(std::shared_ptr<Schema> const& schema) : schema(schema)
		{

		}

		QJsonObject getJson()
		{
			return QJsonObject{ {"schema" , schema->getJson()} };
		}

		std::shared_ptr<Schema> const& getSchema() const
		{
			return schema;
		}



	private:
		const std::shared_ptr<Schema> schema;
		//example //example of the media type...
		//examples
		//encoding
	};
}