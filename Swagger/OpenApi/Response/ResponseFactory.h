#pragma once
#include "../../swagger_global.h"
#include <memory>
#include "Response.h"
#include "../Schema/Factory/SchemaFactory.h"
#include "../Parameter/Header.h"

namespace Swagger
{

	class SWAGGER_EXPORT ResponseFactory
	{
	public:
		ResponseFactory(std::shared_ptr<SchemaFactory> const& factory);

		std::shared_ptr<Response> returnStaticString() const;
		std::shared_ptr<Response> returnNumber() const;
		std::shared_ptr<Response> returnEntity(std::shared_ptr<Schema> const& schema) const;
		std::shared_ptr<Response> returnTextFile() const;
		std::shared_ptr<Response> returnImageFile() const;
		std::shared_ptr<Response> returnAudioFile() const;
		std::shared_ptr<Response> returnFilteredEntities(std::shared_ptr<Schema> const& schema) const;
		std::shared_ptr<Response> entityWasCreated() const;
		std::shared_ptr<Response> callbackResponse() const;

	private:
		std::shared_ptr<SchemaFactory> factory;
	};
}