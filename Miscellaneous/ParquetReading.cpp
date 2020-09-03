
/*
COMPILATION:
g++ lowLevelParquetReading.cpp -I ./libs/parquet/include/ -L ./libs/parquet/lib/ -larrow -lparquet -std=c++11
*/


#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/resource.h>
#include <string>
#include <memory>
#include <parquet/api/reader.h>
#include <parquet/api/writer.h>
#include <parquet/metadata.h>


//#define VERBOSE 0

///@brief Computation of elapsed time of program
class ElapsedTime
{
private:
    ///@brief Message for elapsed time
    std::string m_startMsg;

public:

    ///@brief time point which holds the start and end time
    std::chrono::time_point<std::chrono::steady_clock> begin, end;

    ///@brief elapsed time
    unsigned long int m_elapsedTime;

    ///@brief    start capturing elapsed time
    ///@return   None
    void start()
    {
        m_elapsedTime = 0;
        begin = std::chrono::steady_clock::now();
    }

    ///@brief    start capturing elapsed time and accumulated with previous metrics
    ///@param ArgName : ArgDesc
    ///@return   None
    void startAccumulate(const std::string &s)
    {
        m_startMsg = s;
        begin = std::chrono::steady_clock::now();
    }

    ///@brief    start capturing elapsed time
    ///@param string : message to display at end
    ///@return   None
    void start(const std::string &s)
    {
        m_startMsg = s;
        start();
    }

    ///@brief    constructor
    ElapsedTime()
    {
        start();
        m_elapsedTime = 0;
    }

    ///@brief    print the elapsed time
    ///@return   None
    void printTime()
    {
        std::cout << "Elapsed time[" << m_startMsg << "](milliseconds): " << m_elapsedTime << '\n';
    }

    ///@brief    stop capturing elapsed time and print values
    ///@return   None
    void stop()
    {
        end = std::chrono::steady_clock::now();
        m_elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        std::cout << "Elapsed time[" << m_startMsg << "](milliseconds): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << '\n';
    }

    ///@brief    stopAccumulate the elapsed time and print values
    ///@return   None
    void stopAccumulate()
    {
        end = std::chrono::steady_clock::now();
        m_elapsedTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    }

    ///@brief    destructor
    ~ElapsedTime()
    {
    }
};

///@brief Calculation of CPU related metrics of the program
class CppCpuMetrics
{
private:
    ///@brief resource usage 
    struct rusage cpuResUsage;

    ///@brief start and end time of cpu
    clock_t m_startCpuTime, m_endCpuTime;

    ///@brief total cpu time
    unsigned long long m_totalCpuTime;

    ///@brief message to display
    std::string m_descriptionStr;

    const int numberOfMicroSecInSec=1000000;

public:
    ///@brief    constructor
    ///@return   None
    CppCpuMetrics()
    {
        m_startCpuTime = 0;
        m_endCpuTime = 0;
        m_totalCpuTime = 0;
    }

    ///@brief    Returns user cpu time from beginning of program to this point
    ///@return   double
    double getUserCpuTimeInSeconds()
    {
        getrusage(RUSAGE_SELF, &cpuResUsage);
        //tv_usec is milliseconds, so dividing by 1000000
        return (cpuResUsage.ru_utime.tv_sec + (cpuResUsage.ru_utime.tv_usec / static_cast<double>(numberOfMicroSecInSec)));
    }

    ///@brief    print the user cpu time
    ///@return   None
    void printUserCpuTimeInSeconds()
    {
        std::cout << "User CPU time(Seconds): " << getUserCpuTimeInSeconds() << '\n';
    }

    ///@brief    Returns system cpu time from beginning of program to this point
    ///@return   double
    double getSystemCpuTimeInSeconds()
    {
        getrusage(RUSAGE_SELF, &cpuResUsage);
        //tv_usec is milliseconds, so dividing by 1000000
        return (cpuResUsage.ru_stime.tv_sec + (cpuResUsage.ru_stime.tv_usec / static_cast<double>(numberOfMicroSecInSec)));
    }

    ///@brief    printSystemCpuTimeInSeconds
    ///@return   None
    void printSystemCpuTimeInSeconds()
    {
        std::cout << "System CPU time(Seconds): " << getSystemCpuTimeInSeconds() << '\n';
    }

    ///@brief    Starts the cpu time when this function is called
    ///@return   None
    void start()
    {
        m_startCpuTime = clock();
    }

    ///@brief    Starts the cpu time when this function is called
    ///@param descriptionStr : descriptionStr
    ///@return   None
    void start(const std::string &descriptionStr)
    {
        m_descriptionStr = descriptionStr;
        m_startCpuTime = clock();
    }

    ///@brief    stops the cpu time calculation when this function is called
    ///@return   None
    void stop()
    {
        m_endCpuTime = clock();
        m_totalCpuTime = (m_endCpuTime - m_startCpuTime) / CLOCKS_PER_SEC;
        std::cout << "CPU Time [ " << m_descriptionStr << " ] : " << m_totalCpuTime << " seconds" << '\n';
    }
};


using namespace std;
int main()
{
    ElapsedTime elapsedTimeObj;
    CppCpuMetrics cpuTimeObj;
    elapsedTimeObj.start("Total");
    cpuTimeObj.start("Total");

    const int columnSize = 5;
    uint64_t qwRowsToRead=0;
    uint64_t qwCurrentChunkToRead=40000;
    uint64_t qwOffset = 0;
    int16_t deflevel[qwCurrentChunkToRead];
    int64_t *pInt64Buffer=nullptr;
    double *pDoubleBuffer=nullptr;
    int64_t qwNNValues = 0;           


    std::cout << "Reading " << std::endl;

    std::unique_ptr<parquet::ParquetFileReader> pParquetReader = parquet::ParquetFileReader::OpenFile("123.parquet", false);

    std::shared_ptr<parquet::FileMetaData> pFileMetaData = pParquetReader->metadata();

    std::vector<std::vector<std::shared_ptr<parquet::ColumnReader>>> colReaderVec;

    colReaderVec.resize(pFileMetaData->num_row_groups());
    for (uint16_t rgIdx = 0; rgIdx < pFileMetaData->num_row_groups(); ++rgIdx)
        colReaderVec[rgIdx].resize(columnSize);

    for (int rowGroupIdx = 0; rowGroupIdx < pFileMetaData->num_row_groups(); rowGroupIdx++)
    {
        std::shared_ptr<parquet::RowGroupReader> rgReader = pParquetReader->RowGroup(rowGroupIdx);

        qwRowsToRead = rgReader->metadata()->num_rows();

        for (int colIdx = 0; colIdx < columnSize; colIdx++)
        {
            colReaderVec[rowGroupIdx][colIdx] = rgReader->Column(colIdx);

            switch (colReaderVec[rowGroupIdx][colIdx]->type())
			{
                        case parquet::Type::INT64:
						{
                            int64_t qwRowsRead=0;
                            pInt64Buffer = new int64_t[qwRowsToRead];

                            while(qwRowsRead < qwRowsToRead)
                            {
                                qwRowsRead = static_cast<parquet::Int64Reader *>(colReaderVec[rowGroupIdx][colIdx].get())->ReadBatch(qwRowsToRead, &deflevel[qwOffset], nullptr, &((int64_t *)pInt64Buffer)[qwOffset], &qwNNValues);

                                #ifdef VERBOSE
                            for (uint64_t qwRowIdx = 0; qwRowIdx < 5; ++qwRowIdx)
							{
                                std::cout << colIdx << " : "<< pInt64Buffer[qwRowIdx] << "\n";
							}
                                #endif
                            }                            
						}
                        break;

                        case parquet::Type::BYTE_ARRAY:
						{
                            int64_t qwRowsRead=0;
                            parquet::ByteArray *byteArrayBuf = (parquet::ByteArray*)new char[sizeof(parquet::ByteArray) * qwRowsToRead];

                            while(qwRowsRead < qwRowsToRead)
                            {
                                qwRowsRead = static_cast<parquet::ByteArrayReader *>(colReaderVec[rowGroupIdx][colIdx].get())->ReadBatch(qwRowsToRead, &deflevel[qwOffset], nullptr, byteArrayBuf, &qwNNValues);

                                #ifdef VERBOSE
                                for (uint64_t qwRowIdx = 0; qwRowIdx < 1; ++qwRowIdx)
                                {
                                    char arr[100];
                                strncpy(arr,(const char*)byteArrayBuf[qwRowIdx].ptr,byteArrayBuf[qwRowIdx].len);

                                std::cout << colIdx << " : " <<  arr << "\n";
                                }
                                #endif
                            }                            
						}
                        break;

						case parquet::Type::DOUBLE:
						{
                            int64_t qwRowsRead=0;
                            pDoubleBuffer=new double[qwCurrentChunkToRead];

                            while(qwRowsRead < qwRowsToRead)
                            {
                                qwRowsRead += static_cast<parquet::DoubleReader *>(colReaderVec[rowGroupIdx][colIdx].get())->ReadBatch(qwCurrentChunkToRead, &deflevel[qwOffset], nullptr, &((double *)pDoubleBuffer)[qwOffset], &qwNNValues);

                                #ifdef VERBOSE
                                for (uint64_t qwRowIdx = 0; qwRowIdx < 1; ++qwRowIdx)
                                {
                                    std::cout << colIdx << " : "<< pDoubleBuffer[qwRowIdx] << "\n";
                                }
                                #endif
                            }                            
						}
                        break;
            }
        }     
    }

    std::cout << pFileMetaData->num_row_groups() << std::endl;

    elapsedTimeObj.stop();
    cpuTimeObj.stop();
}
