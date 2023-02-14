
#include "Pattern.h"

namespace Swagger
{

	namespace Field
	{
		Pattern::Pattern(QString const& qtReg) : DynamicField("pattern"), m_reg(qtReg) {
			m_reg.optimize();
		}

		ConvertError Pattern::process(QVariant& val) const {
			const auto value = val.toString();

			return {!m_reg.match(value).hasMatch(), error.arg(m_reg.pattern()) };
		}

		const QJsonValue Pattern::getJson() const {
			return m_reg.pattern();
		}
		const QVariant Pattern::getVariant() const {
			return m_reg;
		}

	}
}
