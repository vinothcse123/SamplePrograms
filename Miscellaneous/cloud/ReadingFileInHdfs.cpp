#include <iostream>
#include <string>

#include <arrow/io/api.h>
#include <parquet/exception.h>
#include "parquet/api/reader.h"
#include <parquet/arrow/reader.h>
#include "arrow/status.h"
#include "arrow/buffer.h"
#include "arrow/io/hdfs.h"
#include <arrow/api.h>
#include <arrow/io/api.h>
#include "parquet/api/reader.h"
#include <parquet/arrow/reader.h>
#include <parquet/arrow/writer.h>
#include <parquet/exception.h>
#include "arrow/io/interfaces.h"
#include "parquet/arrow/schema.h"
#include "arrow/status.h"
#include "arrow/testing/util.h"
#include "parquet/properties.h"
#include "parquet/file_reader.h"
#include "parquet/platform.h"
#include "parquet/arrow/schema.h"
#include <arrow/ipc/api.h>
#include <arrow/api.h>
#include <parquet/arrow/reader.h>
#include <parquet/arrow/writer.h>

#define DEBUG 1

using std::endl;
using std::string;

/*
update below by taking access key from portal.azure.com
/mnt/c/Users/hadoop-3.2.1/etc/hadoop/core-site.xml
With name as "fs.azure.account.auth.type.vinoth.dfs.core.windows.net"

*/

void readAndWriteFileInAdlsG2(const string &strInputPath, std::shared_ptr<arrow::io::HadoopFileSystem> &hadoopFileSysObj)
{
	try
	{
		using namespace arrow::io;
		using namespace arrow;

		const int64_t strBufferferSize = 10000;
		char strBuffer[strBufferferSize];

		//Read and write to different path

		std::shared_ptr<HdfsReadableFile> file;
		PARQUET_THROW_NOT_OK((*(hadoopFileSysObj)).OpenReadable(strInputPath, &file));

		int64_t file_size = file->GetSize().ValueOrDie();


		
    std::unique_ptr<parquet::arrow::FileReader> reader;
    PARQUET_THROW_NOT_OK(
        parquet::arrow::OpenFile(file, arrow::default_memory_pool(), &reader));
    std::shared_ptr<arrow::ChunkedArray> array;
    PARQUET_THROW_NOT_OK(reader->ReadColumn(0, &array));
    //PARQUET_THROW_NOT_OK(arrow::PrettyPrint(*array, 4, &std::cout));
    std::shared_ptr<arrow::Table> table;
    PARQUET_THROW_NOT_OK(reader->ReadTable(&table));

    std::cout << "Number of columns : " << table->num_columns() << std::endl;
    std::cout << "Number of Rows : " << table->num_rows() << std::endl;
    std::cout << "Name of column : " << table->schema()->field(0)->name() << std::endl;
    std::cout << "Name of column : " << table->schema()->field(1)->name() << std::endl;
    std::cout << "Name of column : " << table->schema()->field(2)->name() << std::endl;
    std::cout << "Name of column : " << table->schema()->field(3)->name() << std::endl;

    auto col1 =
        std::static_pointer_cast<arrow::StringArray>(table->column(1)->chunk(0));
    auto col2 =
        std::static_pointer_cast<arrow::Int64Array>(table->column(0)->chunk(0));

    for (int64_t i = 0; i < 10; i++)
    {
        std::string val1 = col1->GetString(i);
        int64_t val2 = col2->Value(i);

		std::cout << " \n==============V6P: val1 "<<  val1  << "==================" << std::endl;
		std::cout << " \n==============V6P: val2 "<<  val2  << "==================" << std::endl;
    }


    std::cout << std::endl;

	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}
}

void initAdlsConnection(std::shared_ptr<arrow::io::HadoopFileSystem> &hadoopFileSysObj)
{
	arrow::io::HdfsConnectionConfig hdfsConConfig;
	//V6P
	//hdfsConConfig.host = "abfs://vinothUser@vinothStorageAccount.dfs.core.windows.net";
	hdfsConConfig.user = ""; //User name is not required since we passed in host
	hdfsConConfig.port = 0;
	//V6P hdfsConConfig.driver = arrow::io::HdfsDriver::LIBHDFS; // JNI Driver

	//Connecting to ADLS
	PARQUET_THROW_NOT_OK(arrow::io::HadoopFileSystem::Connect(&hdfsConConfig, &hadoopFileSysObj));
}

int main()
{
	std::shared_ptr<arrow::io::HadoopFileSystem> hadoopFileSysObj;
	initAdlsConnection(hadoopFileSysObj);
	//V6P
	//string path = "/path/without/prefix/MyParquet.parquet";

	readAndWriteFileInAdlsG2(path, hadoopFileSysObj);
}
