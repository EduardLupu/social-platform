#include "SocialPlatform.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo{ "users.txt", "topics.txt", "posts.txt" };
    Service service{ repo };
    for (auto user : service.get_users())
    {
        auto GUI = new SocialPlatform(service, user);
        GUI->show();
    }
    return a.exec();
}
