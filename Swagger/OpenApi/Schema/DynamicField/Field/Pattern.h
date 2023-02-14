#pragma once
#pragma once
#include "../DynamicField.h"

namespace Swagger
{

	namespace Field
	{

		struct Pattern : public DynamicField
		{
		public:
			Pattern(QString const& qtReg);

			ConvertError process(QVariant& val) const;
			const QJsonValue getJson() const;
			const QVariant getVariant() const final;

		private:
			const QRegularExpression m_reg;
			inline const static QString error = "string does not match regex pattern: %1";
		};

	
	}
	


}