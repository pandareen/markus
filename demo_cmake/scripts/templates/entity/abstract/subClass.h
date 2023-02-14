#pragma once
#include "${class_name_base}.h"

namespace Domain
{
	class ${project_name}_EXPORT ${class_name} : public ${class_name_base}
	{
		Q_OBJECT
		Q_CLASSINFO("polymorphic", "true")
		${class_info}
		${value_object_properties}

	public:
		Q_INVOKABLE ${class_name}(QObject* parent = nullptr);

		${value_objects}
	};
}
Q_DECLARE_METATYPE(Domain::${class_name}*)