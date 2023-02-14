#pragma once
#include "ResponseFactory.h"
#include <memory>
#include "Responses.h"
#include "../Parameter/Header.h"

namespace Swagger
{

class SWAGGER_EXPORT ResponsesFactory
{
public:
	ResponsesFactory(std::shared_ptr<ResponseFactory> const& factory);

	std::shared_ptr<Responses> returnStaticString() const;
	std::shared_ptr<Responses> returnNumber() const;
	std::shared_ptr<Responses> returnFilteredEntities(std::shared_ptr<Schema> const& schema) const;
	std::shared_ptr<Responses> returnEntityById(std::shared_ptr<Schema> const& schema) const;
	std::shared_ptr<Responses> returnTextFile() const;
	std::shared_ptr<Responses> returnImageFile() const;
	std::shared_ptr<Responses> returnAudioFile() const;
	std::shared_ptr<Responses> updateEntity() const;
	std::shared_ptr<Responses> insertEntity() const;
	std::shared_ptr<Responses> deleteEntity() const;
	std::shared_ptr<Responses> callbackResponses() const;

private:
	std::shared_ptr<ResponseFactory> factory;
};
}