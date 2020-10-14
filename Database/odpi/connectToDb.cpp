
#include <iostream>
#include <dpi.h>
#include <cstring>
#include <string>

#define MAJOR_VERSION 4
#define MINOR_VERSION 1

using std::string;

dpiContext *pContext = NULL;
dpiConn *conn;

void connectToDb()
{
    string userName = "userName", password = "userName", dbName = "userName";
    dpiErrorInfo errorInfo;

    if (dpiContext_createWithParams(MAJOR_VERSION, MINOR_VERSION,
                                    NULL, &pContext, &errorInfo) < 0)
    {
        fprintf(stderr, "ERROR: %.*s (%s : %s)\n", errorInfo.messageLength,
                errorInfo.message, errorInfo.fnName, errorInfo.action);
    }

    if (dpiConn_create(pContext, userName.c_str(),
                       userName.length(), password.c_str(),
                       password.length(), dbName.c_str(),
                       dbName.length(), NULL, NULL, &conn) < 0)
    {
        dpiErrorInfo info;
        dpiContext_getError(pContext, &info);
        fprintf(stderr, "ERROR: %.*s (%s: %s), offset: %u\n", info.messageLength,
                info.message, info.fnName, info.action, info.offset);
    }
}

int main()
{
    connectToDb();
    return 0;
}
