//GH_MISC_2

#include <arrow/api.h>
#include <memory>
#include <arrow/io/api.h>
#include <parquet/arrow/reader.h>
#include <parquet/exception.h>
#include <iostream>
#include <string>
#include <arrow/type_fwd.h>

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
        //std::cout << "FieldName " << arrowSchemaPtr->field(i)->name() << std::endl;
        //std::cout << "Type: " << arrowSchemaPtr->field(i)->type()->id() << std::endl;

        //arrow::Type::type myType=arrow::Type::INT64;
    }

    std::shared_ptr<parquet::arrow::RowGroupReader> rgReader = pFileReader->RowGroup(0);
    std::shared_ptr<parquet::arrow::ColumnChunkReader> colReaderVec;
    for (int32_t dwColIdx = 0; dwColIdx < arrowSchemaPtr->num_fields(); dwColIdx++)
    {
        colReaderVec = rgReader->Column(dwColIdx);

        std::shared_ptr<arrow::ChunkedArray> ChunkedArray;
        colReaderVec->Read(&ChunkedArray);
       

        std::shared_ptr<::arrow::Array> arrowArray;
        
        

        arrow::Type::type colType = arrowSchemaPtr->field(dwColIdx)->type()->id();
        const string &strColName = arrowSchemaPtr->field(dwColIdx)->name();
        const uint32_t dwNumberOfRows = ChunkedArray->length();
        int32_t dwElementSize = 100;

        arrowArray= std::move(ChunkedArray->chunk(0));//V6P-Handle multiple chunks.


         //std::cout << " \n Number of rows read " << ChunkedArray->length() << std::endl;
          //std::cout << " \n ColType " << colType << std::endl;

          std::cout << strColName << " : ";

        for (int i = 0; i < arrowArray->length(); i++)
        {
            switch(colType)
            {
                case arrow::Type::INT64:
                    std::cout   << (arrowArray->data()->GetMutableValues<int64_t>(1)[i]) <<",";
                break;

                case arrow::Type::DOUBLE:
                    std::cout  << (arrowArray->data()->GetMutableValues<double>(1)[i]) <<"," ;
                break;

                case arrow::Type::STRING:
                    //1st Pos - Size of string
                    //2nd in array - Value of string 
                    
                    //V6P - optimize reading part

                    uint8_t* valuePtr=arrowArray->data()->GetMutableValues<uint8_t>(2) + arrowArray->data()->GetValues<int32_t>(1)[i];
                    std::cout  << string( (const char*)valuePtr  , arrowArray->data()->GetValues<int32_t>(1)[i+1] - arrowArray->data()->GetValues<int32_t>(1)[i] ) <<"," ;
                break;
            }
        }


        std::cout << '\n';
    }
}
