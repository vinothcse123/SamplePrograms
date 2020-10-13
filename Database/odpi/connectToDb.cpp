
#include<iostream>
#include <dpi.h>
#include <cstring>

int main()
{
    dpiContext *gContext = NULL;
    dpiErrorInfo errorInfo;
    dpiConn *conn;

    if (dpiContext_createWithParams(4, 1,
                NULL, &gContext, &errorInfo) < 0) {
            fprintf(stderr, "ERROR: %.*s (%s : %s)\n", errorInfo.messageLength,
                    errorInfo.message, errorInfo.fnName, errorInfo.action);
        }

    if (dpiConn_create(gContext, "string",
            strlen("string"),"string",
            strlen("string"), "string",
            strlen("string"), NULL, NULL, &conn) < 0) {
                dpiErrorInfo info;
        dpiContext_getError(gContext, &info);
         fprintf(stderr, "ERROR: %.*s (%s: %s), offset: %u\n", info.messageLength,
            info.message, info.fnName, info.action, info.offset);
    }

    return 0;

}
