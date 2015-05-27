#include <QtGui/QApplication>
#include "mainwindow.h"

extern "C"
{
#  include <debug_util/debug.h>
}

int main(int argc, char *argv[])
{
    debug_util_set_level(static_cast<const debug_util_LEVELS>(DEBUG_UTIL_LEVEL_TRACE + 1)
                         );
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
