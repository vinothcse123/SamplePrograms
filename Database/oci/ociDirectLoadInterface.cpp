
//g++ $1 -std=c++11 -I $ORACLE_HOME/rdbms/public/ -L $ORACLE_HOME/lib/  -lclntsh

#include <iostream>
#include <oci.h>
#include <string>
#include <cstring>

using namespace std;


class OCIConnection
{
	public:
	string schemaNameStr = "schemaNameStr", userStr = "schemaNameStr", passwordStr = "schemaNameStr";
	string tableNameStr = "V6PlayPartition";
	string partitionNameStr = "RANGE_1_TO_100";
	OCIEnv *pOciEnv;
	OCIError *pOciErrorHandle;
	OCISvcCtx *pOciServiceContextHandle = nullptr;
	sword ociret; /* return code from OCI calls */
	OCIDirPathCtx *pOciDirectPathHandle;
	OCIDirPathFuncCtx *pFuncCtxArray;
	OCIDirPathColArray *pColumnArray;
	OCIDirPathStream *pDirectPathStream;
	ub2 id_col;
	OCIParam *colLstDesc_ctl; /* column list parameter handle */
	OCIServer *pOciServerHandle = nullptr;
	OCISession *pOciSessionHandle = nullptr;


	int connectToDb();
	int directLoad();

};

void handleError(OCIError *pOciErrorHandle)
{
	sb4 errcode = 0;
	text errorBuf[5120];
	sword errorCode = OCIErrorGet((dvoid *)pOciErrorHandle, (ub4)1, (text *)NULL, &errcode, errorBuf, (ub4)sizeof(errorBuf), OCI_HTYPE_ERROR);

	if (OCI_ERROR != errorCode)
		std::cout << " \n==============OCI ERROR: " << errcode << " : " << (const char *)errorBuf << std::endl;
	else
		std::cout << " \n==============Error in getting OCI ERROR: " << errorCode << (const char *)errorBuf << std::endl;

	exit(-1);
}

void IS_ERROR(OCIError *pOciErrorHandle, sword errorCode)
{

	if (errorCode != OCI_SUCCESS)
	{
		std::cout << " \n==============Returned error Code: " << errorCode << std::endl;
		if (errorCode == OCI_ERROR)
			handleError(pOciErrorHandle);
	}
}



int OCIConnection::connectToDb()
{
	//Create Environment

	if (OCIEnvCreate((OCIEnv **)&pOciEnv, (ub4)OCI_DEFAULT,
					 (dvoid *)0, (dvoid * (*)(dvoid *, size_t))0,
					 (dvoid * (*)(dvoid *, dvoid *, size_t))0,
					 (void (*)(dvoid *, dvoid *))0, (size_t)0, (dvoid **)0))
	{
		std::cout << " \n==============V6P: Unabled to create Environment==================" << std::endl;
		return -1;
	}

	// Set error handler

	if (OCI_SUCCESS != OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciErrorHandle, OCI_HTYPE_ERROR, (size_t)0, (dvoid **)0))
		handleError(pOciErrorHandle);

	// set server handle

	if (OCI_SUCCESS != OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciServerHandle, OCI_HTYPE_SERVER, (size_t)0, (dvoid **)0))
		handleError(pOciErrorHandle);

	//set service handle

	if (OCI_SUCCESS != OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciServiceContextHandle, OCI_HTYPE_SVCCTX, (size_t)0, (dvoid **)0))
		handleError(pOciErrorHandle);

	//Connect to server

	if (OCI_SUCCESS != OCIServerAttach(pOciServerHandle, pOciErrorHandle, (text *)schemaNameStr.c_str(), (sb4)schemaNameStr.length(), (ub4)OCI_DEFAULT))
		handleError(pOciErrorHandle);

	//set server context

	if (OCI_SUCCESS != OCIAttrSet((dvoid *)pOciServiceContextHandle, (ub4)OCI_HTYPE_SVCCTX, (dvoid *)pOciServerHandle, (ub4)0, (ub4)OCI_ATTR_SERVER, (OCIError *)pOciErrorHandle))
		handleError(pOciErrorHandle);

	//Allocate session handle
	if (OCI_SUCCESS != OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciSessionHandle, (ub4)OCI_HTYPE_SESSION, (size_t)0, (dvoid **)0))
		handleError(pOciErrorHandle);

	// Set the username
	if (OCI_SUCCESS != OCIAttrSet((dvoid *)pOciSessionHandle, (ub4)OCI_HTYPE_SESSION, (dvoid *)userStr.c_str(), (ub4)userStr.length(), (ub4)OCI_ATTR_USERNAME, pOciErrorHandle))
		handleError(pOciErrorHandle);

	// Set the password
	if (OCI_SUCCESS != OCIAttrSet((dvoid *)pOciSessionHandle, (ub4)OCI_HTYPE_SESSION, (dvoid *)passwordStr.c_str(), (ub4)passwordStr.length(), (ub4)OCI_ATTR_PASSWORD, pOciErrorHandle))
		handleError(pOciErrorHandle);

	// Set the schema attribute
	if (OCI_SUCCESS != OCIAttrSet((dvoid *)pOciSessionHandle, (ub4)OCI_HTYPE_SESSION, (dvoid *)userStr.c_str(), (ub4)userStr.length(), (ub4)OCI_ATTR_CURRENT_SCHEMA, pOciErrorHandle))
		handleError(pOciErrorHandle);

	//Begin the session
	if (OCI_SUCCESS != OCISessionBegin(pOciServiceContextHandle, pOciErrorHandle, pOciSessionHandle, OCI_CRED_RDBMS, (ub4)OCI_DEFAULT))
		handleError(pOciErrorHandle);
}


int OCIConnection::directLoad()
{
	// set session parameters for authentication
	if (OCI_SUCCESS != OCIAttrSet((dvoid *)pOciServiceContextHandle, (ub4)OCI_HTYPE_SVCCTX, (dvoid *)pOciSessionHandle, (ub4)0, (ub4)OCI_ATTR_SESSION, pOciErrorHandle))
		handleError(pOciErrorHandle);

	// setting direct path handle
	if (OCI_SUCCESS != OCIHandleAlloc((void *)pOciEnv,
									  (void **)&pOciDirectPathHandle,
									  (ub4)OCI_HTYPE_DIRPATH_CTX,
									  (size_t)0, (void **)0))
		handleError(pOciErrorHandle);
	std::cout << " \n============== V6P: Initialized Direct path context! ==================" << std::endl;

	//Set table name
	IS_ERROR(pOciErrorHandle,(OCIAttrSet((void *)pOciDirectPathHandle, (ub4)OCI_HTYPE_DIRPATH_CTX,
						   (void *)tableNameStr.c_str(),
						   (ub4)tableNameStr.length(),
						   (ub4)OCI_ATTR_NAME, pOciErrorHandle)));

	//Set partition name
	IS_ERROR(pOciErrorHandle,OCIAttrSet((void *)pOciDirectPathHandle, (ub4)OCI_HTYPE_DIRPATH_CTX,
						   (void *)partitionNameStr.c_str(),
						   (ub4)partitionNameStr.length(),
						   (ub4)OCI_ATTR_SUB_NAME, pOciErrorHandle));



	
	int numberOfCol =2;
	/* set number of columns to be loaded */
	IS_ERROR(pOciErrorHandle, OCIAttrSet((void *)pOciDirectPathHandle, (ub4)OCI_HTYPE_DIRPATH_CTX,
										 (void *)&numberOfCol,
										 (ub4)0,
										 (ub4)OCI_ATTR_NUM_COLS, pOciErrorHandle));

	/* get the column parameter list */

	IS_ERROR(pOciErrorHandle, OCIAttrGet((void *)pOciDirectPathHandle, (ub4)OCI_HTYPE_DIRPATH_CTX,
										 (void *)&colLstDesc_ctl,
										 (ub4)0,
										 (ub4)OCI_ATTR_LIST_COLUMNS, pOciErrorHandle));

	/* get parameter handle on the column */


/* set external attributes on the column */

	OCIParam *colDesc;

	IS_ERROR(pOciErrorHandle, OCIParamGet((const void *)colLstDesc_ctl,
										  (ub4)OCI_DTYPE_PARAM, pOciErrorHandle,
										  (void **)&colDesc, 1));

	

	/* column name - First column */
	IS_ERROR(pOciErrorHandle, OCIAttrSet((void *)colDesc, (ub4)OCI_DTYPE_PARAM,
										 (void *)&"MyNumber",
										 (ub4)strlen((const char *)"MyNumber"),
										 (ub4)OCI_ATTR_NAME, pOciErrorHandle));

	/* column type */
	ub2 exttyp_col = SQLT_INT;
	IS_ERROR(pOciErrorHandle, OCIAttrSet((void *)colDesc, (ub4)OCI_DTYPE_PARAM,
										 (void *)&exttyp_col,
										 (ub4)0,
										 (ub4)OCI_ATTR_DATA_TYPE, pOciErrorHandle));

	/* max data size */
	ub4 maxlen_fld = 32;
	IS_ERROR(pOciErrorHandle, OCIAttrSet((void *)colDesc, (ub4)OCI_DTYPE_PARAM,
										 (void *)&maxlen_fld,
										 (ub4)0,
										 (ub4)OCI_ATTR_DATA_SIZE, pOciErrorHandle));

	

	/* column name - [second column] */


	IS_ERROR(pOciErrorHandle, OCIParamGet((const void *)colLstDesc_ctl,
										  (ub4)OCI_DTYPE_PARAM, pOciErrorHandle,
										  (void **)&colDesc, 2)); // 2 - represents second pos


	IS_ERROR(pOciErrorHandle, OCIAttrSet((void *)colDesc, (ub4)OCI_DTYPE_PARAM,
										 (void *)&"MYVARCHAR",
										 (ub4)strlen((const char *)"MYVARCHAR"),
										 (ub4)OCI_ATTR_NAME, pOciErrorHandle));

	/* column type */
	exttyp_col = SQLT_CHR;
	IS_ERROR(pOciErrorHandle, OCIAttrSet((void *)colDesc, (ub4)OCI_DTYPE_PARAM,
										 (void *)&exttyp_col,
										 (ub4)0,
										 (ub4)OCI_ATTR_DATA_TYPE, pOciErrorHandle));

	/* max data size */
	maxlen_fld = 2000;
	IS_ERROR(pOciErrorHandle, OCIAttrSet((void *)colDesc, (ub4)OCI_DTYPE_PARAM,
										 (void *)&maxlen_fld,
										 (ub4)0,
										 (ub4)OCI_ATTR_DATA_SIZE, pOciErrorHandle));


	IS_ERROR(pOciErrorHandle, OCIDirPathPrepare(pOciDirectPathHandle, pOciServiceContextHandle, pOciErrorHandle));

	std::cout << " \n============== V6P: Initialized OCIDirPathPrepare! ==================" << std::endl;

	IS_ERROR(pOciErrorHandle, OCIHandleAlloc((void *)pOciDirectPathHandle, (void **)&pColumnArray,
											 (ub4)OCI_HTYPE_DIRPATH_COLUMN_ARRAY,
											 (size_t)0, (void **)0));

	std::cout << " \n============== V6P: Initialized Column Array! ==================" << std::endl;

	// Setting direct path stream

	if (OCI_SUCCESS != OCIHandleAlloc((void *)pOciDirectPathHandle, (void **)&pDirectPathStream,
									  (ub4)OCI_HTYPE_DIRPATH_STREAM,
									  (size_t)0, (void **)0))
		handleError(pOciErrorHandle);

	std::cout << " \n============== V6P: Finished  OCI_HTYPE_DIRPATH_STREAM ==================" << std::endl;

	// Set entries in the column array to point to the input data value for each column
	int64_t a[2];
	a[0]=20;
	a[1]=10;


	
	IS_ERROR(pOciErrorHandle, OCIDirPathColArrayEntrySet(pColumnArray, pOciErrorHandle, 0, 0, (ub1 *)&a[0], sizeof(a[0]), OCI_DIRPATH_COL_COMPLETE));
	IS_ERROR(pOciErrorHandle, OCIDirPathColArrayEntrySet(pColumnArray, pOciErrorHandle, 1, 0, (ub1 *)&a[1], sizeof(a[0]), OCI_DIRPATH_COL_COMPLETE));
	

		char stringCol[2][100];
	strcpy(stringCol[0],"HAI");
	strcpy(stringCol[1],"HELLO");


	
	IS_ERROR(pOciErrorHandle, OCIDirPathColArrayEntrySet(pColumnArray, pOciErrorHandle, 0, 1, (ub1 *)&stringCol[0], sizeof(stringCol[0]), OCI_DIRPATH_COL_COMPLETE));
	IS_ERROR(pOciErrorHandle, OCIDirPathColArrayEntrySet(pColumnArray, pOciErrorHandle, 1, 1, (ub1 *)&stringCol[1], sizeof(stringCol[1]), OCI_DIRPATH_COL_COMPLETE));


	ub4 rowcnt = 2;	  /* number of rows in column array */
	ub4 startoff = 0; /* starting row offset into column array  */

	std::cout << " \n============== V6P: Finished OCIDirPathColArrayEntrySet  ==================" << std::endl;

	//Convert a column array to a direct path stream format
	if (OCI_SUCCESS != OCIDirPathColArrayToStream(pColumnArray, pOciDirectPathHandle,
												  pDirectPathStream, pOciErrorHandle,
												  rowcnt, startoff))
		handleError(pOciErrorHandle);

	std::cout << " \n============== V6P: Finished  OCIDirPathColArrayToStream ==================" << std::endl;

	// Load the direct path stream
	if (OCI_SUCCESS != OCIDirPathLoadStream(pOciDirectPathHandle, pDirectPathStream,
											pOciErrorHandle))
		handleError(pOciErrorHandle);

	std::cout << " \n============== V6P: Finished   OCIDirPathLoadStream ==================" << std::endl;

	//Invoke the direct path finishing function
	if (OCI_SUCCESS != OCIDirPathFinish(pOciDirectPathHandle, pOciErrorHandle))
		handleError(pOciErrorHandle);

}

int main()
{
	OCIConnection ociConnection;

	if(0 != ociConnection.connectToDb())
		return -1;

	if(0 != ociConnection.directLoad())
		return -1;
}
