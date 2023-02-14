#include "${class_name}.h"

namespace Domain
{
	Q_INVOKABLE ${class_name}(QObject* parent = nullptr) : ${class_name_base}(parent)
	{
		classType = ClassTypes::${class_name};
	}
}