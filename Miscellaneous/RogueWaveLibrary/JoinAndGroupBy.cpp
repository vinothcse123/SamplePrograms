// .
//

#include "stdafx.h"
#include <rw/db/db.h>

void connect(RWDBConnection &l_database_conn,RWDBDatabase &l_database);
int main()
{
	RWDBConnection l_database_conn;
	RWDBDatabase l_database;
	connect(l_database_conn,l_database);
	RWDBSelector l_selector = l_database.selector();

	int a=10;
	RWDBTable V6TAB_MasterTab = l_database.table("VINOTHDB.DBO.V6TAB__MASTER");
	RWDBTable underlyingV6TAB_Tab = l_database.table("VINOTHDB.DBO._V6TAB_");

	RWDBColumn V6TAB_MasterCol = V6TAB_MasterTab["V6TAB___ID"];
	RWDBColumn underlyingV6TAB_Col = underlyingV6TAB_Tab["V6TAB___ID"];


	a=25;


	/*RWDBJoinExpr l_pdcProcessSumJoin=rwdbRightOuter(V6TAB_MasterTab,underlyingV6TAB_Tab);
	RWDBSelector l_joinSelector = l_database.selector();
	*/


	RWDBCriterion l_criteria;


	/* WORK AREA */



	RWDBTable primary = l_database.table("VINOTHDB.DBO.V6TAB__MASTER");
	RWDBTable backup = l_database.table("VINOTHDB.DBO.UNDERLYING_V6TAB_");

	RWDBSelector avg = l_database.selector();
	l_selector << primary["V6TAB___ID"];
	avg.fromExtern(primary);
	avg << rwdbMax(backup["V6TAB___ID"]);
	RWDBCriterion l_local(backup["V6TAB___ID"] == primary["V6TAB___ID"] || backup["V6TAB___ID"] == primary["V6TAB___ID"]);
	avg.where(((backup["V6TAB___ID"] == primary["V6TAB___ID"])) && backup["V6TAB___ID"] == primary["V6TAB___ID"] || backup["V6TAB___ID"] == primary["V6TAB___ID"]);
	avg.fromClear();
	avg.from(backup);

	
	//1

	l_selector.where(primary["V6TAB___ID"] >= avg);










	RWDBReader rdr = l_selector.reader(l_database_conn);

	std::cout << rdr.status().vendorMessage2()  << std::endl;
	std::cout<<"\n ======= SQL=========" <<std::endl;
	std::cout << l_selector.asString()  << std::endl;
	std::cout<<"\n ======= RESULT=========" <<std::endl;
	std::string l_dbName;
	rdr();
	rdr >> l_dbName ;
	std::cout<<l_dbName <<std::endl;  
	return 0;
}

void connect(RWDBConnection &l_database_conn,RWDBDatabase &l_database)
{

	l_database = RWDBManager::database(
		"rwodbc64.dll", // access module name              //1
		"V6_SERVER",     // server name                     //2
		"V6PASS",              // user name                       //3
		"V6PASS",               // password                        //4
		""            // database name                   //5
		);

	if (l_database.isValid()) {
		std::cout << "Connection esatablished with database!" << std::endl; 
	}
	else {
		std::cout << l_database.status().vendorMessage2() << std::endl;
	}
	l_database_conn= l_database.connection();
}
