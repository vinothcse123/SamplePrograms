#include <arrow/api.h>
#include <memory>
#include <arrow/io/api.h>
#include <parquet/arrow/reader.h>
#include <parquet/exception.h>
#include <iostream>
#include <string>
using namespace std;
int main()
{
    std::shared_ptr<arrow::io::ReadableFile> infile;
    //V6P
    //string source = "vinoth.parquet";

    PARQUET_ASSIGN_OR_THROW(infile, arrow::io::ReadableFile::Open(source,
                                                                  arrow::default_memory_pool()));
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
    colReaderVec = rgReader->Column(1);

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
