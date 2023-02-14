#include "RequestBody.h"

namespace Swagger
{
	RequestBody::RequestBody(std::shared_ptr<Schema> const& schema, QString const& contentType, QString const& description, const bool isRequired /*= true*/) :

		IJson("requestBody"),
		schema(schema),
		content{ { contentType,  std::make_shared<MediaType>(schema) } },

		isRequierd(isRequired), description(description)
	{

	}

	const QJsonValue RequestBody::getJson() const
	{
		const QJsonObject retn{
			 { "content", content.getJson() } ,
			 {"description", description}
		};

		return retn;
	}

	Swagger::ConvertError RequestBody::convert(QVariant& body) const
	{
		return schema->convert(body);
	}

	Swagger::RequestBody::operator const std::shared_ptr<Schema>() const
	{
		return schema;
	}
}