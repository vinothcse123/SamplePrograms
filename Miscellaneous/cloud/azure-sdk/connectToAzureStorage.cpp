

/*
AZURE_BASE_PATH=/path/
source scl_source enable devtoolset-9
g++  $1 -std=c++17 -pthread -larrow -lparquet  -Ilibs/parquet/include/ -Lparquet/lib -I azure-sdk/include -Lazure-sdk/lib/ -lazure-storage-blobs \
    -DBUILD_CURL_HTTP_TRANSPORT_ADAPTER \
    -lazure-storage-files-datalake \
    -lazure-storage-files-shares \
    -lazure-storage-blobs \
    -lazure-storage-common \
     -lazure-identity \
     -lazure-core \
     -lazure-template\
     -I${AZURE_BASE_PATH}/libs/azure-sdk/include/sdk/core/azure-core/inc/ \
    -I${AZURE_BASE_PATH}/libs/azure-sdk/include/sdk/core/performance-stress/inc/ \
    -I${AZURE_BASE_PATH}/libs/azure-sdk/include/sdk/identity/azure-identity/inc/ \
    -I${AZURE_BASE_PATH}/libs/azure-sdk/include/sdk/storage/azure-storage-blobs/inc/ \
    -I${AZURE_BASE_PATH}/libs/azure-sdk/include/sdk/storage/azure-storage-common/inc/ \
    -I${AZURE_BASE_PATH}/libs/azure-sdk/include/sdk/storage/azure-storage-files-datalake/inc/ \
    -I${AZURE_BASE_PATH}/libs/azure-sdk/include/sdk/storage/azure-storage-files-shares/inc/ \
    -I${AZURE_BASE_PATH}/libs/azure-sdk/include/sdk/template/azure-template/inc/ \
    -I${AZURE_BASE_PATH}/libs/curl/include/ \
    -L${AZURE_BASE_PATH}/libs/curl/lib/x86/Linux/ -lcurl \
    -lcrypto \
    -lxml2 \


*/

#include <iostream>
#include <string>
using std::string;

#include "azure/storage/files/datalake/datalake_directory_client.hpp"
#include "azure/storage/files/datalake/datalake_file_client.hpp"


//V6P
string g_strConnectionString = "DefaultEndpointsProtocol=https;AccountName=vinothStorageAccount;AccountKey=myAccountKey==;EndpointSuffix=core.windows.net";
string g_strFileSystemName = "vinothFileSystemOrContainerName";
const string g_parquetFilePath = "v6Test/path/to/unitTestData_01.parquet";

int main()
{
    using namespace std;

    std::shared_ptr<Azure::Storage::Files::DataLake::FileSystemClient> fileSystemClient;

    fileSystemClient = std::make_shared<Azure::Storage::Files::DataLake::FileSystemClient>(
        Azure::Storage::Files::DataLake::FileSystemClient::CreateFromConnectionString(g_strConnectionString, g_strFileSystemName));

    std::shared_ptr<Azure::Storage::Files::DataLake::FileClient> fileClient =
        std::make_shared<Azure::Storage::Files::DataLake::FileClient>(fileSystemClient->GetFileClient(g_parquetFilePath));

    uint64_t bytesRead = 0;
    Azure::Storage::Files::DataLake::ReadFileOptions options;
    options.Offset = 0;
    options.Length = 100000;
    auto result = fileClient->Read(options);
    Azure::Core::Context context;
    std::vector<uint8_t> downloaded = Azure::Core::Http::BodyStream::ReadToEnd(context, *(result->Body));
    bytesRead = downloaded.size();

    std::cout << bytesRead << std::endl;

    return 0;
}
