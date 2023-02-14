#include "Info.h"

Swagger::Info::Info(QString const& title, /* The title of the application. */ QString const& description, /* CommonMark ... */ QUrl const& termsOfService, Contact const& contact, License const& license, QString const& version) : QJsonObject{
				   {"title", title},
				   {"description", description},
				   {"termsOfService", termsOfService.toString() },
				   {"contact", contact},
				   {"license", license},
				   {"version", version}
}
{

}
