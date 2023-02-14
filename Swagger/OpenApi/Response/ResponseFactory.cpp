#include "ResponseFactory.h"
namespace Swagger
{

	Swagger::ResponseFactory::ResponseFactory(std::shared_ptr<SchemaFactory> const& factory) : factory(factory)
	{

	}

	std::shared_ptr<Swagger::Response> Swagger::ResponseFactory::returnStaticString() const
	{
		Map<MediaType> type{
				{
					"text/plain",
					std::make_shared<MediaType>(std::shared_ptr<Schema>(factory->string("")))
				}
		};

		return std::make_shared<Response>(
			QString("test"),
			type
			);
	}






	std::shared_ptr<Swagger::Response> ResponseFactory::returnNumber() const
	{
		Map<MediaType> type{
				{
					"application/json",
					std::make_shared<MediaType>(std::shared_ptr<Schema>(factory->integer("")))
				}
		};

		return std::make_shared<Response>(QString("number"),type);
	}

	std::shared_ptr<Swagger::Response> ResponseFactory::returnEntity(std::shared_ptr<Schema> const& schema) const
	{
		Map<MediaType> type{
				{
					"application/json",
					std::make_shared<MediaType>(schema)
				}
		};

		return std::make_shared<Response>(QString("schema"),type);
	}

	std::shared_ptr<Swagger::Response> ResponseFactory::returnTextFile() const
	{
		const static std::shared_ptr<Schema> stringSchema(factory->string(""));
		const static auto mediatype = std::make_shared<MediaType>(stringSchema);
		const static Map<MediaType> type{
				{
					"text/plain",
					mediatype
				},
				{
					"text/css",
					mediatype
				},
				{
					"text/csv",
					mediatype
				},
				{
					"text/html",
					 mediatype
				},
				{
					"text/md",
					 mediatype
				},
		};

		return std::make_shared<Response>(QString("text file"), type);
	}

	std::shared_ptr<Swagger::Response> ResponseFactory::returnImageFile() const
	{
		const static std::shared_ptr<Schema> stringSchema(factory->string(""));
		const static auto mediatype = std::make_shared<MediaType>(stringSchema);
		const static Map<MediaType> type{
				{
					"image/jpg",
					mediatype
				}
		};

		return std::make_shared<Response>(QString("image file"), type);
	}

	std::shared_ptr<Swagger::Response> ResponseFactory::returnAudioFile() const
	{
		const static std::shared_ptr<Schema> stringSchema(factory->string(""));
		const static auto mediatype = std::make_shared<MediaType>(stringSchema);
		const static Map<MediaType> type{
				{
					"audio/ogg",
					mediatype
				},
				{
					"audio/wav",
					mediatype
				},
				{
					"audio/mpeg",
					mediatype
				},
		};

		return std::make_shared<Response>(QString("audio file"), type);
	}

	std::shared_ptr<Swagger::Response> ResponseFactory::returnFilteredEntities(std::shared_ptr<Schema> const& schema) const
	{
		Map<MediaType> type{
				{
					"application/json",
					std::make_shared<MediaType>(std::make_shared<Swagger::Array>("", schema, FieldList{}))
				}
		};

		return std::make_shared<Response>(QString("schema"), type);
	}

	std::shared_ptr<Swagger::Response> ResponseFactory::entityWasCreated() const
	{
		static const std::shared_ptr<Schema> locationSchema(factory->Url(""));
		static const auto location = std::make_shared<Header>("Location", locationSchema, "the location of the newly created resource");

		return std::make_shared<Response>("schema", Map<Parameter>{	{"Location", location }	}	);
	}

	std::shared_ptr<Swagger::Response> ResponseFactory::callbackResponse() const
	{
		return std::make_shared<Response>("Your server should return this code if it accepts the callback");

	}

}
