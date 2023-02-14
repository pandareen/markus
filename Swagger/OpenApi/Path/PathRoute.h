#pragma once
#include "../../swagger_global.h"
#include "../Schema/ConvertError.h"
#include "../Parameter/PathParameter.h"
#include "PathFragment.h"

namespace Swagger
{
	class SWAGGER_EXPORT PathRoute
	{

	public:
		PathRoute(FragmentList const& list);

		operator QString() const;

		ConvertError compare(QStringList const& path) const;

	private:
		FragmentList parameterList;
	};
}

