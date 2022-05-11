#include "error.h"

Error::Error(string f)
{
    str_error=QObject::tr("/home/debian/PROG_C++/mon_serveur/public_html/error/")+QObject::tr(f.c_str());
    file_err = new QFile(str_error);
}

void Error::error_function()
{
    if (!file_err->open(QIODevice::ReadOnly))
    {
        delete file_err;
        return;
    }
}
