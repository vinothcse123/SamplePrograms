#include <arrow/api.h>
#include <memory>
#include <arrow/io/api.h>
#include <parquet/arrow/reader.h>
#include <parquet/arrow/writer.h>
#include <parquet/exception.h>
#include <iostream>
#include <string>
using namespace std;
int main()
{
    std::cout << "Reading first column of parquet-arrow-example.parquet" << std::endl;
    std::shared_ptr<arrow::io::ReadableFile> infile;
    PARQUET_ASSIGN_OR_THROW(
        infile,
        arrow::io::ReadableFile::Open("vinoth-00000-dasdfsd-81ad-57a7-88c8-ddd36e51952f.parquet",
                                      arrow::default_memory_pool()));

    std::unique_ptr<parquet::arrow::FileReader> reader;
    PARQUET_THROW_NOT_OK(
        parquet::arrow::OpenFile(infile, arrow::default_memory_pool(), &reader));
    std::shared_ptr<arrow::ChunkedArray> array;
    PARQUET_THROW_NOT_OK(reader->ReadColumn(2, &array));
    //PARQUET_THROW_NOT_OK(arrow::PrettyPrint(*array, 4, &std::cout));
    std::shared_ptr<arrow::Table> table;
    PARQUET_THROW_NOT_OK(reader->ReadTable(&table));

    std::cout << "Number of columns : " << table->num_columns() << std::endl;
    std::cout << "Number of Rows : " << table->num_rows() << std::endl;
    std::cout << "Name of column : " << table->schema()->field(0)->name() << std::endl;
    std::cout << "Name of column : " << table->schema()->field(1)->name() << std::endl;
    std::cout << "Name of column : " << table->schema()->field(2)->name() << std::endl;
    std::cout << "Name of column : " << table->schema()->field(3)->name() << std::endl;

    //std::vector<std::shared_ptr<Field>> myFields=table->schema()->fields();
    //     std::cout << "Name of 2nd columns : " <<  << std::endl;
    auto col1 =
        std::static_pointer_cast<arrow::StringArray>(table->column(0)->chunk(0));
    auto col2 =
        std::static_pointer_cast<arrow::Int64Array>(table->column(2)->chunk(0));

    for (int64_t i = 0; i < table->num_rows(); i++)
    {
        std::string val1 = col1->GetString(i);
        int64_t val2 = col2->Value(i);

    }

    std::cout << std::endl;
}
