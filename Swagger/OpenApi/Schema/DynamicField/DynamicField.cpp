
#include "DynamicField.h"

namespace Swagger
{
		DynamicField::DynamicField(QString const& name) : name(name)
		{

		}

		QString const& DynamicField::getName() const
		{
			return name;
		}

		Swagger::ConvertError DynamicField::process(QVariant& val) const
		{
			return { false , ""};
		}


		bool FieldList::hasField(QString const& title) const {
			return getField(title);
		}

		void FieldList::removeEmptyFields() {
			this->removeAll(nullptr);
		}

		const DynamicField* FieldList::getField(QString const& title) const {

			for (auto const& item : *this)
				if (item->getName() == title)
					return item;

			return nullptr;
		}

		FieldList& FieldList::operator+(FieldList const& list) {
			this->append(list);
			removeEmptyFields();
			return *this;
		}

		FieldList& FieldList::operator<<(FieldList const& list) {
			return FieldList::operator+(list);
		}
	
}