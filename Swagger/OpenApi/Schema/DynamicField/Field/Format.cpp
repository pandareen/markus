
#include "Format.h"

namespace Swagger
{
	namespace Field
	{
		Format::Format(QString const& format, std::function<bool(QVariant&)> const& func) :
			DynamicField("format"),
			m_format(format),
			m_processFunc(func)

		{}

		ConvertError Format::process(QVariant& val) const {
			return {
				m_processFunc(val),
				error.arg(m_format)
			};
		}

		const QJsonValue Format::getJson() const {
			return m_format;
		}

		const QVariant Format::getVariant() const {
			return m_format;
		}
	}
}
