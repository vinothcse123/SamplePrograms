#include <iostream>
#include <string>

#include <arrow/io/api.h>
#include <parquet/exception.h>
#include "parquet/api/reader.h"
#include <parquet/arrow/reader.h>
#include "arrow/status.h"
#include "arrow/buffer.h"
#include "arrow/filesystem/hdfs.h"
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
#include "arrow/util/uri.h"
#include <parquet/arrow/writer.h>
#include <parquet/file_writer.h>

#define DEBUG 1

using std::endl;
using std::string;
using namespace arrow::internal;
int64_t g_qBufferferSize = 500000;

/*
update below by taking access key from portal.azure.com
/mnt/c/Users/hadoop-3.2.1/etc/hadoop/core-site.xml
With name as "fs.azure.account.auth.type.vinoth.dfs.core.windows.net"

*/

void writeFileInGen2UsingFileWriter(const string &strInputPath, const string &outputDirectory,const string &strOutputPath, std::shared_ptr<arrow::fs::HadoopFileSystem> &hadoopFileSysObj)
{
	try
	{
		using namespace arrow::io;
		using namespace arrow;



		const std::string outputPath = outputDirectory + "/" + strOutputPath;

		std::cout << outputPath << std::endl;

		std::shared_ptr<parquet::schema::GroupNode> m_parquetSchema;
		std::shared_ptr<parquet::WriterProperties> m_Props;
		parquet::WriterProperties::Builder m_Builder;
		parquet::schema::NodeVector m_Fields;
		parquet::Repetition::type repetition =  parquet::Repetition::REQUIRED;
		m_Fields.push_back(parquet::schema::PrimitiveNode::Make("MY_INT_COLUMN", repetition, parquet::Type::INT64, parquet::ConvertedType::NONE));
		std::unique_ptr<parquet::arrow::FileWriter> m_pParquetWriter;

		m_Builder.compression(parquet::Compression::SNAPPY)->created_by("VINOTH");

		m_parquetSchema = std::static_pointer_cast<parquet::schema::GroupNode>(parquet::schema::GroupNode::Make(std::string("data_schema"), parquet::Repetition::REQUIRED, m_Fields));
		m_Props = m_Builder.build();

		parquet::SchemaDescriptor descriptor;
        descriptor.Init(m_parquetSchema);
        std::shared_ptr<arrow::Schema> arrow_schema;
        parquet::ArrowReaderProperties props;

        parquet::arrow::FromParquetSchema(&descriptor, props, &arrow_schema);

		//auto outStream = ::arrow::io::FileOutputStream::Open(outputPath, false);
		
		//V6P Throw exception
		auto outStream = hadoopFileSysObj->OpenOutputStream(outputPath);

        auto pWriter = parquet::ParquetFileWriter::Open(outStream.ValueOrDie(), m_parquetSchema, m_Props);

		
		// V6P: This is coded with customized api which is wrote on top of hdfs Arrow integration. This need to be migrated to standard api in hdfs fs namespace
		// 		std::shared_ptr<HdfsOutputStream> outStream;
		// PARQUET_THROW_NOT_OK(hadoopFileSysObj->OpenWritable(outputPath, false, &outStream));

		
		PARQUET_THROW_NOT_OK(parquet::arrow::FileWriter::Make(arrow::default_memory_pool(), std::move(pWriter), arrow_schema,
                                         parquet::default_arrow_writer_properties(), &m_pParquetWriter));

		m_pParquetWriter->NewRowGroup(100);

		 std::shared_ptr<arrow::Array> pArray;//V6P
		//m_pParquetWriter->WriteColumnChunk(*pArray);

		m_pParquetWriter->Close();

	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}
}


void writeFileInLocalUsingFileWriter(const string &strInputPath, const string &outputDirectory,const string &strOutputPath, std::shared_ptr<arrow::fs::HadoopFileSystem> &hadoopFileSysObj)
{
	try
	{
		using namespace arrow::io;
		using namespace arrow;

		//Read and write to different path

		std::shared_ptr<HdfsReadableFile> file;
		// V6P: This is coded with customized api which is wrote on top of hdfs Arrow integration. This need to be migrated to standard api in hdfs fs namespace
		//PARQUET_THROW_NOT_OK((*(hadoopFileSysObj)).OpenReadable(strInputPath, &file));

		int64_t file_size = file->GetSize().ValueOrDie();

		


		const std::string outputPath = outputDirectory + "/" + strOutputPath;

		std::cout << outputPath << std::endl;

		std::shared_ptr<parquet::schema::GroupNode> m_parquetSchema;
		std::shared_ptr<parquet::WriterProperties> m_Props;
		parquet::WriterProperties::Builder m_Builder;
		parquet::schema::NodeVector m_Fields;
		parquet::Repetition::type repetition =  parquet::Repetition::REQUIRED;
		m_Fields.push_back(parquet::schema::PrimitiveNode::Make("MY_INT_COLUMN", repetition, parquet::Type::INT64, parquet::ConvertedType::NONE));
		std::unique_ptr<parquet::arrow::FileWriter> m_pParquetWriter;

		m_Builder.compression(parquet::Compression::SNAPPY)->created_by("VINOTH");

		m_parquetSchema = std::static_pointer_cast<parquet::schema::GroupNode>(parquet::schema::GroupNode::Make(std::string("data_schema"), parquet::Repetition::REQUIRED, m_Fields));
		m_Props = m_Builder.build();

		parquet::SchemaDescriptor descriptor;
        descriptor.Init(m_parquetSchema);
        std::shared_ptr<arrow::Schema> arrow_schema;
        parquet::ArrowReaderProperties props;

        parquet::arrow::FromParquetSchema(&descriptor, props, &arrow_schema);

		auto outStream = ::arrow::io::FileOutputStream::Open(outputPath, false);
        auto pWriter = parquet::ParquetFileWriter::Open(outStream.ValueOrDie(), m_parquetSchema, m_Props);
		
		PARQUET_THROW_NOT_OK(parquet::arrow::FileWriter::Make(arrow::default_memory_pool(), std::move(pWriter), arrow_schema,
                                         parquet::default_arrow_writer_properties(), &m_pParquetWriter));

		m_pParquetWriter->NewRowGroup(100);

		 std::shared_ptr<arrow::Array> pArray;//V6P
		//m_pParquetWriter->WriteColumnChunk(*pArray);

		m_pParquetWriter->Close();

	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}
}

void writeFileInAdlsG2UsingOpenWriteable(const string &strInputPath, const string &outputDirectory,const string& outputFileName, std::shared_ptr<arrow::fs::HadoopFileSystem> &hadoopFileSysObj)
{
	try
	{
		using namespace arrow::io;
		using namespace arrow;

		//Read and write to different path

		std::shared_ptr<ReadableFile> file;
		file = ReadableFile::Open(strInputPath).ValueOrDie();




		int64_t file_size = file->GetSize().ValueOrDie();
		

		//Check Directory exists or not
		//if (!hadoopFileSysObj->Exists(outputDirectory))
		{
			// V6P: This is coded with customized api which is wrote on top of hdfs Arrow integration. This need to be migrated to standard api in hdfs fs namespace
			//if (!hadoopFileSysObj->MakeDirectory(outputDirectory).ok())
			{
				std::cout << "Unable to create Directory " << std::endl;
				exit(1);
			}
		}

		
		const std::string outputPath = outputDirectory + "/" + outputFileName;

		std::cout << outputPath << std::endl;

		std::shared_ptr<HdfsOutputStream> outStream;
		//PARQUET_THROW_NOT_OK(hadoopFileSysObj->OpenWritable(outputPath, false, &outStream));

		int64_t dw_readBytes = 0, dw_curWriteBytes = -1;
		Result<int64_t> dw_curReadBytesRes;
		int64_t dw_curReadBytes = -1;
		char strBuffer[g_qBufferferSize];
		while (dw_readBytes < file_size && dw_curReadBytes != 0)
		{
			PARQUET_THROW_NOT_OK(dw_curReadBytesRes = (*file).Read(g_qBufferferSize, (void *)strBuffer));

			if (dw_curReadBytesRes.ok())
			{
				dw_curReadBytes = dw_curReadBytesRes.ValueOrDie();
			}
			else
			{
				std::cout << "dw_curReadBytesRes error " << endl;
				exit(1);
			}

#if DEBUG
			std::cout << "Current Read Bytes: " << dw_curReadBytes << endl;
#endif

			dw_curWriteBytes = 0;
			uint64_t dw_bytesToWrite = 0, dw_startPos = 0;

			while (dw_curWriteBytes < dw_curReadBytes)
			{
				dw_bytesToWrite = dw_curReadBytes - dw_curWriteBytes;
				int64_t dw_bytesWrittenNow = -1;
				PARQUET_THROW_NOT_OK((*outStream).Write(strBuffer + dw_startPos, dw_bytesToWrite, &dw_bytesWrittenNow));

				dw_curWriteBytes += dw_bytesWrittenNow;
				dw_startPos = dw_curWriteBytes;
			}
			dw_readBytes += dw_curReadBytes;
		}
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}
}

void listFileInDirectory(const string &directoryPath, std::shared_ptr<arrow::fs::HadoopFileSystem> &hadoopFileSysObj)
{

	try
	{
		using namespace arrow::io;
		using namespace arrow;

		std::vector<io::HdfsPathInfo> children;
		// V6P: This is coded with customized api which is wrote on top of hdfs Arrow integration. This need to be migrated to standard api in hdfs fs namespace
		//Status st = hadoopFileSysObj->ListDirectory(directoryPath, &children);

		arrow::fs::FileSelector fileSelector;
		fileSelector.base_dir=directoryPath;
		fileSelector.recursive=true;
		fileSelector.max_recursion=1;

		std::vector<arrow::fs::FileInfo> fileInfoVec = hadoopFileSysObj->GetFileInfo(fileSelector).ValueOrDie();

		for(auto fileInfo : fileInfoVec)
		{	
			std::cout << "File/Directory Name: " << fileInfo.base_name() <<'\n';
			std::cout << "Directory: " << fileInfo.dir_name() <<'\n';
		}
		
		return;

		//V6P Clear downward code
		
		std::vector<std::string> fileList;
		//PARQUET_THROW_NOT_OK(hadoopFileSysObj->GetChildren(directoryPath, &fileList));

		std::string wd, wd2;
		//PARQUET_THROW_NOT_OK(hadoopFileSysObj->GetWorkingDirectory(&wd));

		Uri wd_uri;
		wd_uri.Parse(wd);
		wd2 = wd_uri.path();

		// std::cout << "Dir Path: " << directoryPath <<'\n';
		// std::cout << "fileList size: " << fileList.size() <<'\n';
		// std::cout << "ListDirectory size: " << children.size() <<'\n';
		// std::cout << "working directory: " << wd <<'\n';
		// std::cout << "working directory after parse: " << wd2 <<'\n';

		for (const auto &child_path_info : children)
		{
			// HDFS returns an absolute URI here, need to extract path relative to wd
			Uri uri;
			uri.Parse(child_path_info.name);
			std::string child_path = uri.path();
			//std::cout << "child_path " << child_path << '\n';
			//std::cout << "file/directory " << child_path_info.kind << '\n';
		}

		for (const auto &file : fileList)
		{
			Uri uri;
			uri.Parse(file);
			std::string child_path = uri.path();
			//std::cout << "File List:  " << file << '\n';
			//std::cout << "Parsed File List:  " << child_path << '\n';
		}
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}
}

void readusingChunkedArray(const string &strInputPath, std::shared_ptr<arrow::fs::HadoopFileSystem> &hadoopFileSysObj)
{
	try
	{
		using namespace arrow::io;
		using namespace arrow;

		const int64_t strBufferferSize = 10000;
		char strBuffer[strBufferferSize];

		//Read and write to different path

		std::shared_ptr<HdfsReadableFile> infile;
		// V6P: This is coded with customized api which is wrote on top of hdfs Arrow integration. This need to be migrated to standard api in hdfs fs namespace
		//PARQUET_THROW_NOT_OK((*(hadoopFileSysObj)).OpenReadable(strInputPath, &infile));

		int64_t file_size = infile->GetSize().ValueOrDie();

		parquet::arrow::FileReaderBuilder builder;
		parquet::ReaderProperties properties = parquet::default_reader_properties();
		parquet::ArrowReaderProperties arrowprops(true);
		arrowprops.set_batch_size(10000);
		arrowprops.set_pre_buffer(true);
		PARQUET_THROW_NOT_OK(builder.Open(infile, properties));
		std::unique_ptr<parquet::arrow::FileReader> pFileReader;
		PARQUET_THROW_NOT_OK(builder.properties(arrowprops)->Build(&pFileReader));

		std::shared_ptr<parquet::FileMetaData> pFileMetaData;
		pFileMetaData = pFileReader->parquet_reader()->metadata();

		std::cout << " \nNumber of rows " << pFileMetaData->RowGroup(0)->num_rows() << std::endl;

		std::shared_ptr<arrow::Schema> arrowSchemaPtr;
		pFileReader->GetSchema(&arrowSchemaPtr);
		for (auto i = 0; i < arrowSchemaPtr->num_fields(); i++)
		{
			std::cout << "FieldName " << arrowSchemaPtr->field(i)->name() << std::endl;
		}

		std::shared_ptr<parquet::arrow::RowGroupReader> rgReader = pFileReader->RowGroup(0);
		std::shared_ptr<parquet::arrow::ColumnChunkReader> colReaderVec;
		colReaderVec = rgReader->Column(0);

		std::shared_ptr<arrow::ChunkedArray> ChunkedArray;
		colReaderVec->Read(&ChunkedArray);
		std::cout << " \n Number of rows read " << ChunkedArray->length() << std::endl;

		std::shared_ptr<::arrow::Array> arrowArray = ChunkedArray->chunk(0);

		std::cout << "value " << (arrowArray->data()->GetMutableValues<int64_t>(1)[0]) << std::endl;
		std::cout << "value " << (arrowArray->data()->GetMutableValues<int64_t>(1)[1]) << std::endl;
		std::cout << "value " << (arrowArray->data()->GetMutableValues<int64_t>(1)[2]) << std::endl;
		std::cout << "value " << (arrowArray->data()->GetMutableValues<int64_t>(1)[3]) << std::endl;
		std::cout << "value " << (arrowArray->data()->GetMutableValues<int64_t>(1)[4]) << std::endl;
		std::cout << "value " << (arrowArray->data()->GetMutableValues<int64_t>(1)[5]) << std::endl;
		std::cout << "value " << (arrowArray->data()->GetMutableValues<int64_t>(1)[7]) << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}
}

void readFileInAdlsG2(const string &strInputPath, std::shared_ptr<arrow::fs::HadoopFileSystem> &hadoopFileSysObj)
{
	try
	{
		using namespace arrow::io;
		using namespace arrow;

		const int64_t strBufferferSize = 10000;
		char strBuffer[strBufferferSize];

		//Read and write to different path

		std::shared_ptr<io::RandomAccessFile> file;
		// V6P: This is coded with customized api which is wrote on top of hdfs Arrow integration. This need to be migrated to standard api in hdfs fs namespace
		//PARQUET_THROW_NOT_OK((*(hadoopFileSysObj)).OpenReadable(strInputPath, &file));

		file = hadoopFileSysObj->OpenInputFile(strInputPath).ValueOrDie();

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

			std::cout << " \n==============V6P: val1 " << val1 << "==================" << std::endl;
			std::cout << " \n==============V6P: val2 " << val2 << "==================" << std::endl;
		}

		std::cout << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}
}

void initAdlsConnection(std::shared_ptr<arrow::fs::HadoopFileSystem> &hadoopFileSysObj)
{
	arrow::fs::HdfsOptions hdfsOptionsObj;
	//V6P
	//hdfsOptionsObj.connection_config.host = "abfs://vinothUser@vinothStorageAccount.dfs.core.windows.net";
	

	hdfsOptionsObj.connection_config.user = ""; //User name is not required since we passed in host
	hdfsOptionsObj.connection_config.port = 0;
	//V6P hdfsConConfig.driver = arrow::io::HdfsDriver::LIBHDFS; // JNI Driver

	//Connecting to ADLS
	hadoopFileSysObj = arrow::fs::HadoopFileSystem::Make(hdfsOptionsObj).ValueOrDie();

}

int main()
{
	std::shared_ptr<arrow::fs::HadoopFileSystem> hadoopFileSysObj;
	initAdlsConnection(hadoopFileSysObj);

	//V6P
	//	string path = "/path/without/prefix/MyParquet.parquet";
	// string outputFileName="test_parquet_file3.parquet";
	// string outputPath="/path/";
	// string localParquetFilePath="parquetfiles/unitTestData_01.parquet";
	// string strLocalPath="/vinoth/dir/";




	//readFileInAdlsG2(path, hadoopFileSysObj);
	//readusingChunkedArray(path, hadoopFileSysObj);
	listFileInDirectory("/v6Test/", hadoopFileSysObj);

	// V6P: This is coded with customized api which is wrote on top of hdfs Arrow integration. This need to be migrated to standard api in hdfs fs namespace
	//writeFileInAdlsG2UsingOpenWriteable(localParquetFilePath, outputPath,outputFileName, hadoopFileSysObj);

	//V6PWIP	
	//writeFileInLocalUsingFileWriter(path, strLocalPath,outputFileName, hadoopFileSysObj);
	//V6PWIP
	//writeFileInGen2UsingFileWriter(path, outputPath,outputFileName, hadoopFileSysObj);
}
