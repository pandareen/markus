#pragma once
#include "../../IJson.h"
#include "../../MediaType.h"

#include "../../container/Map.h"
#include "../Schema/Schema.h"

namespace Swagger
{
	class SWAGGER_EXPORT RequestBody : public IJson
	{
	public:
		 	RequestBody(
				std::shared_ptr<Schema> const& schema,
				QString const& contentType,
				QString const& description, 
				const bool isRequired = true);
		 	 

			virtual const QJsonValue getJson() const;
		 
		 
		 	virtual ConvertError convert(QVariant& body) const;
		 

			operator const std::shared_ptr<Schema>() const;

		 private:
			const std::shared_ptr<Schema> schema;
		 	const Map<MediaType> content;
		 	const bool isRequierd;
		 	const QString description;

	};
}
