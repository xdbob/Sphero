#include <QApplication>
#include "core.h"

#ifdef SDL_WIN
#undef main
#endif

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationVersion(QString("Version ") +
                              "0.1 Alpha"
                              );
    Core w;
    return app.exec();
}
