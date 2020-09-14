
//g++ $1 -std=c++11 -I $ORACLE_HOME/rdbms/public/ -L $ORACLE_HOME/lib/  -lclntsh

#include<iostream>
#include <oci.h>
#include <string>

void handleError(OCIError* pOciErrorHandle)
{
	sb4 errcode = 0;
		text errorBuf[512];	
		OCIErrorGet((dvoid *)pOciErrorHandle, (ub4)1, (text *)NULL, &errcode, errorBuf, (ub4) sizeof(errorBuf), OCI_HTYPE_ERROR);
		std::cout << " \n==============OCI ERROR: " <<  (const char*)errorBuf << std::endl;
}

int main()
{
	using namespace std;
	string schemaNameStr="MYSCHEMANAME",userStr="USER_NAME",passwordStr="PASSWORD";

    OCIEnv* pOciEnv=nullptr;
	OCIServer* pOciServerHandle=nullptr;	
	OCISvcCtx* pOciServiceContextHandle=nullptr;
	OCISession* pOciSessionHandle=nullptr;
	OCIError* pOciErrorHandle=nullptr;

    //Create Environment

    if (OCIEnvCreate((OCIEnv **)&pOciEnv, (ub4)OCI_DEFAULT,
		(dvoid *)0, (dvoid * (*)(dvoid *, size_t)) 0,
		(dvoid * (*)(dvoid *, dvoid *, size_t)) 0,
		(void(*)(dvoid *, dvoid *)) 0, (size_t)0, (dvoid **)0))
	{
        std::cout << " \n==============V6P: Unabled to create Environment==================" << std::endl;
		return -1;
	}

	// Set error handler

	if(OCI_SUCCESS != OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciErrorHandle, OCI_HTYPE_ERROR, (size_t)0, (dvoid **)0))
		handleError(pOciErrorHandle);

	// set server handle

	if(OCI_SUCCESS != OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciServerHandle, OCI_HTYPE_SERVER, (size_t)0, (dvoid **)0))
		handleError(pOciErrorHandle);

	//set service handle

	if(OCI_SUCCESS != OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciServiceContextHandle, OCI_HTYPE_SVCCTX, (size_t)0, (dvoid **)0))
		handleError(pOciErrorHandle);

	//Connect to server

	if(OCI_SUCCESS != OCIServerAttach(pOciServerHandle, pOciErrorHandle, (text *)schemaNameStr.c_str(), (sb4)schemaNameStr.length(), (ub4)OCI_DEFAULT))
		handleError(pOciErrorHandle);

	//set server context

	if(OCI_SUCCESS != OCIAttrSet((dvoid *)pOciServiceContextHandle, (ub4)OCI_HTYPE_SVCCTX, (dvoid *)pOciServerHandle, (ub4)0, (ub4)OCI_ATTR_SERVER, (OCIError *)pOciErrorHandle))
		handleError(pOciErrorHandle);

	//Allocate session handle

	if(OCI_SUCCESS != OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciSessionHandle, (ub4)OCI_HTYPE_SESSION, (size_t)0, (dvoid **)0))
		handleError(pOciErrorHandle);

	// Set the username
	if(OCI_SUCCESS != OCIAttrSet((dvoid *)pOciSessionHandle, (ub4)OCI_HTYPE_SESSION, (dvoid *)userStr.c_str(), (ub4)userStr.length(), (ub4)OCI_ATTR_USERNAME, pOciErrorHandle))
		handleError(pOciErrorHandle);

	// Set the password
	if(OCI_SUCCESS != OCIAttrSet((dvoid *)pOciSessionHandle, (ub4)OCI_HTYPE_SESSION, (dvoid *)passwordStr.c_str(), (ub4)passwordStr.length(), (ub4)OCI_ATTR_PASSWORD, pOciErrorHandle))
		handleError(pOciErrorHandle);

	// Set the schema attribute
	if(OCI_SUCCESS != OCIAttrSet((dvoid *)pOciSessionHandle, (ub4)OCI_HTYPE_SESSION, (dvoid *)userStr.c_str(), (ub4)userStr.length(), (ub4)OCI_ATTR_CURRENT_SCHEMA, pOciErrorHandle))
		handleError(pOciErrorHandle);


	//Begin the session
	if(OCI_SUCCESS != OCISessionBegin(pOciServiceContextHandle, pOciErrorHandle, pOciSessionHandle, OCI_CRED_RDBMS, (ub4)OCI_DEFAULT))
		handleError(pOciErrorHandle);

	// set session parameters for authentication
	if(OCI_SUCCESS != OCIAttrSet((dvoid *)pOciServiceContextHandle, (ub4)OCI_HTYPE_SVCCTX, (dvoid *)pOciSessionHandle, (ub4)0, (ub4)OCI_ATTR_SESSION, pOciErrorHandle))
		handleError(pOciErrorHandle);

}
