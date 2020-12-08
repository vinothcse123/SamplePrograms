
//g++ $1 -std=c++11 -I $ORACLE_HOME/rdbms/public/ -L $ORACLE_HOME/lib/  -lclntsh

#include <iostream>
#include <oci.h>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

class OCIConnection
{
public:
	//V6P
	//string schemaNameStr = "VINOTH", userStr = "VINOTH", passwordStr = "VINOTH";

	string tableNameStr = "V6PlayPartition";
	string partitionNameStr = "RANGE_1_TO_100K";
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

	IS_ERROR(pOciErrorHandle, OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciErrorHandle, OCI_HTYPE_ERROR, (size_t)0, (dvoid **)0));

	// set server handle

	IS_ERROR(pOciErrorHandle, OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciServerHandle, OCI_HTYPE_SERVER, (size_t)0, (dvoid **)0));

	//set service handle

	IS_ERROR(pOciErrorHandle, OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciServiceContextHandle, OCI_HTYPE_SVCCTX, (size_t)0, (dvoid **)0));

	//Connect to server

	IS_ERROR(pOciErrorHandle, OCIServerAttach(pOciServerHandle, pOciErrorHandle, (text *)schemaNameStr.c_str(), (sb4)schemaNameStr.length(), (ub4)OCI_DEFAULT));

	

	//set server context

	IS_ERROR(pOciErrorHandle, OCIAttrSet((dvoid *)pOciServiceContextHandle, (ub4)OCI_HTYPE_SVCCTX, (dvoid *)pOciServerHandle, (ub4)0, (ub4)OCI_ATTR_SERVER, (OCIError *)pOciErrorHandle));

	//Allocate session handle
	IS_ERROR(pOciErrorHandle, OCIHandleAlloc((dvoid *)pOciEnv, (dvoid **)&pOciSessionHandle, (ub4)OCI_HTYPE_SESSION, (size_t)0, (dvoid **)0));

	// Set the username
	IS_ERROR(pOciErrorHandle, OCIAttrSet((dvoid *)pOciSessionHandle, (ub4)OCI_HTYPE_SESSION, (dvoid *)userStr.c_str(), (ub4)userStr.length(), (ub4)OCI_ATTR_USERNAME, pOciErrorHandle));

	// Set the password
	IS_ERROR(pOciErrorHandle, OCIAttrSet((dvoid *)pOciSessionHandle, (ub4)OCI_HTYPE_SESSION, (dvoid *)passwordStr.c_str(), (ub4)passwordStr.length(), (ub4)OCI_ATTR_PASSWORD, pOciErrorHandle));

	// Set the schema attribute
	IS_ERROR(pOciErrorHandle, OCIAttrSet((dvoid *)pOciSessionHandle, (ub4)OCI_HTYPE_SESSION, (dvoid *)userStr.c_str(), (ub4)userStr.length(), (ub4)OCI_ATTR_CURRENT_SCHEMA, pOciErrorHandle));

	//Begin the session
	IS_ERROR(pOciErrorHandle, OCISessionBegin(pOciServiceContextHandle, pOciErrorHandle, pOciSessionHandle, OCI_CRED_RDBMS, (ub4)OCI_DEFAULT));

	// set session parameters for authentication
	IS_ERROR(pOciErrorHandle, OCIAttrSet((dvoid *)pOciServiceContextHandle, (ub4)OCI_HTYPE_SVCCTX, (dvoid *)pOciSessionHandle, (ub4)0, (ub4)OCI_ATTR_SESSION, pOciErrorHandle));

	return 0;
}

int OCIConnection::directLoad()
{

	// setting direct path handle
	IS_ERROR(pOciErrorHandle, OCIHandleAlloc((void *)pOciEnv,
											 (void **)&pOciDirectPathHandle,
											 (ub4)OCI_HTYPE_DIRPATH_CTX,
											 (size_t)0, (void **)0));
	std::cout << " \n============== V6P: Initialized Direct path context! ==================" << std::endl;

	//Set table name
	IS_ERROR(pOciErrorHandle, (OCIAttrSet((void *)pOciDirectPathHandle, (ub4)OCI_HTYPE_DIRPATH_CTX,
										  (void *)tableNameStr.c_str(),
										  (ub4)tableNameStr.length(),
										  (ub4)OCI_ATTR_NAME, pOciErrorHandle)));

	//Set partition name
	IS_ERROR(pOciErrorHandle, OCIAttrSet((void *)pOciDirectPathHandle, (ub4)OCI_HTYPE_DIRPATH_CTX,
										 (void *)partitionNameStr.c_str(),
										 (ub4)partitionNameStr.length(),
										 (ub4)OCI_ATTR_SUB_NAME, pOciErrorHandle));

bool isParallel = TRUE;
	// Setting parallel load option
	IS_ERROR(pOciErrorHandle, OCIAttrSet((void *)pOciDirectPathHandle, (ub4)OCI_HTYPE_DIRPATH_CTX,
										 (void *)&isParallel,
										 (ub1)0,
										 (ub1)OCI_ATTR_DIRPATH_PARALLEL, pOciErrorHandle));

	ub1 skipFlag = OCI_DIRPATH_INDEX_MAINT_SKIP_ALL;

	IS_ERROR(pOciErrorHandle, OCIAttrSet((void *)pOciDirectPathHandle, (ub4)OCI_HTYPE_DIRPATH_CTX,
										 (void *)&skipFlag,
										 (ub1)0,
										 (ub1)OCI_ATTR_DIRPATH_SKIPINDEX_METHOD, pOciErrorHandle));

	int numberOfCol = 2;
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

	// Number of records to be loaded in one
	unsigned long long int bufSize=10000;
	IS_ERROR(pOciErrorHandle, OCIAttrSet((void *)pOciDirectPathHandle, (ub4)OCI_HTYPE_DIRPATH_CTX,
										 (void *)&bufSize,
										 (ub4)0,
										 (ub4)OCI_ATTR_BUF_SIZE, pOciErrorHandle));



	IS_ERROR(pOciErrorHandle, OCIDirPathPrepare(pOciDirectPathHandle, pOciServiceContextHandle, pOciErrorHandle));

	std::cout << " \n============== V6P: Initialized OCIDirPathPrepare! ==================" << std::endl;

	IS_ERROR(pOciErrorHandle, OCIHandleAlloc((void *)pOciDirectPathHandle, (void **)&pColumnArray,
											 (ub4)OCI_HTYPE_DIRPATH_COLUMN_ARRAY,
											 (size_t)0, (void **)0));

	std::cout << " \n============== V6P: Initialized Column Array! ==================" << std::endl;

	// Setting direct path stream

	IS_ERROR(pOciErrorHandle, OCIHandleAlloc((void *)pOciDirectPathHandle, (void **)&pDirectPathStream,
											 (ub4)OCI_HTYPE_DIRPATH_STREAM,
											 (size_t)0, (void **)0));

	std::cout << " \n============== V6P: Finished  OCI_HTYPE_DIRPATH_STREAM ==================" << std::endl;

	// Set entries in the column array to point to the input data value for each column
	int rowIndex=0;
	int dataSize=10;
	int intValue=0;
	vector<int64_t> intVec(dataSize,intValue);
	vector<string> stringVec(dataSize,string("STRING_VALUE_")+to_string(intValue));

	for_each(intVec.begin(),intVec.end(),[&](int64_t &i){ i=intValue++; });
	intValue=0;
	for_each(stringVec.begin(),stringVec.end(),[&](string &str){ str=string("STRING_VALUE_")+to_string(intValue++); });



	for(int i=0; i<dataSize; i++)
	{
		IS_ERROR(pOciErrorHandle, OCIDirPathColArrayEntrySet(pColumnArray, pOciErrorHandle, rowIndex,0,  (ub1 *)&intVec[i], sizeof(intVec[i]), OCI_DIRPATH_COL_COMPLETE));
		IS_ERROR(pOciErrorHandle, OCIDirPathColArrayEntrySet(pColumnArray, pOciErrorHandle, rowIndex, 1, (ub1 *)stringVec[i].c_str(), stringVec[i].length(), OCI_DIRPATH_COL_COMPLETE));


		rowIndex++;

		if (rowIndex == 2)
		{
		
			ub4 rowcnt = rowIndex; /* number of rows in column array */
			ub4 startoff = 0;	   /* starting row offset into column array  */

			//Convert a column array to a direct path stream format
			IS_ERROR(pOciErrorHandle, OCIDirPathColArrayToStream(pColumnArray, pOciDirectPathHandle,
																 pDirectPathStream, pOciErrorHandle,
																 rowcnt, startoff));
			// Load the direct path stream
			IS_ERROR(pOciErrorHandle, OCIDirPathLoadStream(pOciDirectPathHandle, pDirectPathStream,
												   pOciErrorHandle));

			OCIDirPathColArrayReset(pColumnArray,pOciErrorHandle);
			OCIDirPathStreamReset(pDirectPathStream,pOciErrorHandle);
			rowIndex = 0;
		}
	}


	//Invoke the direct path finishing function
	IS_ERROR(pOciErrorHandle, OCIDirPathFinish(pOciDirectPathHandle, pOciErrorHandle));

	return 0;
}

int main()
{
	OCIConnection ociConnection;

	if (0 != ociConnection.connectToDb())
		return -1;

	if (0 != ociConnection.directLoad())
		return -1;
}
