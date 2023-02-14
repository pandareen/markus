#include "pch.h"

#include <Swagger/OpenApi/Schema/Factory/SchemaFactory.h>
#include <QJsonObject>
#include <QDebug>
#include <QVariant>



QT_BEGIN_NAMESPACE
inline void PrintTo(const QString& qString, ::std::ostream* os)
{
	*os << qUtf8Printable(qString);
}
QT_END_NAMESPACE


QT_BEGIN_NAMESPACE
inline void PrintTo(const QVariant& variant, ::std::ostream* os)
{
	*os << qUtf8Printable(variant.toString());
}
QT_END_NAMESPACE



struct SchemaConvertCase {

	struct Values
	{
		QVariant value;
		bool expectedError;
		QVariant expectedValue;
	};

	SchemaConvertCase(Swagger::Schema* schema, Values const& values): schema(schema), values(values)
	{}

	Values values;
	Swagger::Schema* schema;
};



class SchemaConvertTest :public ::testing::TestWithParam<SchemaConvertCase> {

public:
	static std::vector<SchemaConvertCase> data() {
		return {
			{factory->Bool("test"), { true            , false, true   }},
			{factory->Bool("test"), { false          , false, false   }},
			{factory->Bool("test"), { "true"         , false, true    }},
			{factory->Bool("test"), { "false"        , false, false   }},
			{factory->Bool("test"), { "asdfasdf"     , false, true    }},
			{factory->Bool("test"), { "fa234lse"     , false, true    }},
			{factory->Bool("test"), { 1              , false, true    }},
			{factory->Bool("test"), { 0              , false, false   }},
			{factory->Bool("test"), { 1.3            , false, true    }},
			{factory->Bool("test"), { 0.3            , false, false   }},
			{factory->Bool("test"), { QVariant{}     ,  true, false   }},
			{factory->Bool("test"), { QJsonObject{}  ,  true, false   }},
			{factory->Bool("test"), { QJsonDocument{},  true, false   }},
			{factory->Bool("test"), { QUrl{}         ,  true, false   }},
			{factory->Bool("test"), { QDateTime{}    ,  true, false   }},
			{factory->Bool("test"), { QStringList{}  ,  true, false   }},
			{factory->Bool("test"), { QJsonArray{}   ,  true, false   }},
		};
	}

private:
	static const inline std::shared_ptr<Swagger::SchemaFactory> factory = std::make_shared<Swagger::SchemaFactory>();
};

TEST_P(SchemaConvertTest, check_if_convert_is_working_correctly) {
	//Arrange
	auto testCase = GetParam();
	auto testValues = testCase.values;
	auto sut = testCase.schema;
	auto value = testValues.value;

	//Act
	auto error = sut->convert(value);

	qDebug() << "Error occured: " << error.occured() << error.message() << "Converted Value: " << value;

	//Assert
	ASSERT_EQ(testValues.expectedError, error);
	ASSERT_EQ(testValues.expectedValue, value);
}

INSTANTIATE_TEST_SUITE_P(BulkTest, SchemaConvertTest, ::testing::ValuesIn(SchemaConvertTest::data()));


