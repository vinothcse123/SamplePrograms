// .
// select table

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
	RWDBTable V6TAB_MasterTab = l_database.table("V6TAB_.DBO.V6TAB__MASTER");
	
	RWDBColumn V6TAB_MasterCol = V6TAB_MasterTab["V6DD"];
	

	RWDBCriterion l_criteria;


	/* WORK AREA */

	l_selector << V6TAB_MasterCol;
	
	l_selector.where(V6TAB_MasterTab["V6TAB___ID"] == 666);










	RWDBReader rdr = l_selector.reader(l_database_conn);

	std::cout << rdr.status().vendorMesV6PASSge2()  << std::endl;
	std::cout<<"\n ======= SQL=========" <<std::endl;
	std::cout << l_selector.asString(true)  << std::endl;
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
		std::cout << "Connection eV6PASStablished with database!" << std::endl; 
	}
	else {
		std::cout << l_database.status().vendorMesV6PASSge2() << std::endl;
	}
	l_database_conn= l_database.connection();
}
