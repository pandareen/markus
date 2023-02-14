#pragma once
#include "../../swagger_global.h"
#include <QString>
#include "../Schema/Schema.h"
#include "../../IJson.h"

namespace Swagger
{
	class SWAGGER_EXPORT Parameter : public IJson
	{
	public:
		enum Type : uchar { query, header, path, cookie };
		static const QStringList s_type;

		Parameter(QString const& name,  std::shared_ptr<Schema> const& schema, QString const& description, const Type in, const bool required = false, const bool deprecated = false);

		virtual const QJsonValue getJson() const;
		virtual const QPair<QString, QJsonValue> getPair() const;

		operator const Schema& () const;
		const bool operator==(const Type type) const;

		operator const Type();

		const bool isRequired() const;

		std::shared_ptr<Schema> scheme() const;

		bool convert(QVariant& value) const;

	private:
		const QString m_description;
		const Type m_in;
		const bool m_required;
		const bool m_deprecated;
		const std::shared_ptr<Schema> m_schema;
	};

	using ParameterList = QList<std::shared_ptr<Parameter>>;
}