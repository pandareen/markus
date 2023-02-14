#include "ResponsesFactory.h"


namespace Swagger
{


	ResponsesFactory::ResponsesFactory(std::shared_ptr<ResponseFactory> const& factory) : factory(factory)
	{

	}

	std::shared_ptr<Swagger::Responses> ResponsesFactory::returnStaticString() const
	{
		return 	std::make_shared<Responses>(
			Map<Response>{ {"200", factory->returnStaticString()} }
		);
	}

	std::shared_ptr<Swagger::Responses> ResponsesFactory::returnNumber() const
	{
		return 	std::make_shared<Responses>(
			Map<Response>{ {"200", factory->returnNumber()} }
		);
	}

	std::shared_ptr<Swagger::Responses> ResponsesFactory::returnFilteredEntities(std::shared_ptr<Schema> const& schema) const
	{
		return 	std::make_shared<Responses>(
			Map<Response>{
				{"200", factory->returnFilteredEntities(schema)},
				{ "404", std::make_shared<Response>("Could not find entity") }

		}
		);
	}

	std::shared_ptr<Swagger::Responses> ResponsesFactory::returnEntityById(std::shared_ptr<Schema> const& schema) const
	{
		return 	std::make_shared<Responses>(
			Map<Response>{

				{"200", factory->returnEntity(schema)},
				{ "404", std::make_shared<Response>("Could not find entity") }

		}
		);
	}

	std::shared_ptr<Swagger::Responses> ResponsesFactory::returnTextFile() const
	{
		return 	std::make_shared<Responses>(
			Map<Response>{

				{"200", factory->returnTextFile()},
				{ "404", std::make_shared<Response>("Could not find text file") }

		}
		);
	}

	std::shared_ptr<Swagger::Responses> ResponsesFactory::returnImageFile() const
	{
		return 	std::make_shared<Responses>(
			Map<Response>{

				{"200", factory->returnImageFile()},
				{ "404", std::make_shared<Response>("Could not find image file") }

		}
		);
	}

	std::shared_ptr<Swagger::Responses> ResponsesFactory::returnAudioFile() const
	{
		return 	std::make_shared<Responses>(
			Map<Response>{

				{"200", factory->returnAudioFile()},
				{ "404", std::make_shared<Response>("Could not find image file") }

		}
		);
	}

	std::shared_ptr<Swagger::Responses> ResponsesFactory::updateEntity() const
	{
		return 	std::make_shared<Responses>(
			Map<Response>{
				{"204", std::make_shared<Response>("Entity updated")},
				{ "404", std::make_shared<Response>("Could not update entity") }
		}
		);
	}

	std::shared_ptr<Swagger::Responses> ResponsesFactory::insertEntity() const
	{
		return 	std::make_shared<Responses>(
			Map<Response>{
				{"201", factory->entityWasCreated()},
				{ "404", std::make_shared<Response>("Could not insert entity") }

		}
		);
	}

	std::shared_ptr<Swagger::Responses> ResponsesFactory::deleteEntity() const
	{
		return 	std::make_shared<Responses>(
			Map<Response>{
				{"200", std::make_shared<Response>("Entity deleted successfully")},
				{ "404", std::make_shared<Response>("Could not find entity") }
		}
		);
	}

	std::shared_ptr<Swagger::Responses> ResponsesFactory::callbackResponses() const
	{
		return 	std::make_shared<Responses>(
			Map<Response>{
				{"200", factory->callbackResponse()}
			}
		);
	}

}