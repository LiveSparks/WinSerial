#include "winStats.h"
#include <pdh.h>
#include <pdhmsg.h>
#include <stdio.h>

static HQUERY query;

static HCOUNTER cpuCounter;
static HCOUNTER memCounter;
static HCOUNTER dskCounter;

static PDH_STATUS Status;

void pdhinit(){
    Status = PdhOpenQuery(NULL, NULL, &query);
    if(Status != ERROR_SUCCESS){
        wprintf(L"\nPdhOpenQuery failed with status 0x%x.", Status);
    }
    
    Status = PdhAddCounter(query, TEXT("\\Processor(_Total)\\% Processor Time"), NULL, &cpuCounter);
    if(Status != ERROR_SUCCESS){
        wprintf(L"\nPdhAddCounter CPU failed with status 0x%x.", Status);
    }

    Status = PdhAddCounter(query, TEXT("\\PhysicalDisk(1 C:)\\% Idle Time"), NULL, &dskCounter);
    if(Status != ERROR_SUCCESS){
        wprintf(L"\nPdhAddCounter Disk failed with status 0x%x.", Status);
    }

    Status = PdhAddCounter(query, TEXT("\\Memory\\Available MBytes"), NULL, &memCounter);
    if(Status != ERROR_SUCCESS){
        wprintf(L"\nPdhAddCounter Memory failed with status 0x%x.", Status);
    }
    
    Status = PdhCollectQueryData(query);
    if(Status != ERROR_SUCCESS){
        wprintf(L"\nPdhCollectQueryData failed with status 0x%x.", Status);
    }
}
 
void getCpuUsage(double &cpuVal, long &memVal, double &dskVal)
{
    PDH_FMT_COUNTERVALUE counterVal;

    Status = PdhCollectQueryData(query);
    if(Status != ERROR_SUCCESS){
        wprintf(L"\nPdhCollectQueryData failed with status 0x%x.", Status);
    }

    Status = PdhGetFormattedCounterValue(cpuCounter, PDH_FMT_DOUBLE, NULL, &counterVal);
    if(Status != ERROR_SUCCESS){
        wprintf(L"\nPdhGetFormatedCounterValue failed with status 0x%x.", Status);
    }
    cpuVal = counterVal.doubleValue;

    Status = PdhGetFormattedCounterValue(dskCounter, PDH_FMT_DOUBLE, NULL, &counterVal);
    if(Status != ERROR_SUCCESS){
        wprintf(L"\nPdhGetFormatedCounterValue failed with status 0x%x.", Status);
    }
    dskVal = counterVal.doubleValue;

    Status = PdhGetFormattedCounterValue(memCounter, PDH_FMT_LONG, NULL, &counterVal);
    if(Status != ERROR_SUCCESS){
        wprintf(L"\nPdhGetFormatedCounterValue failed with status 0x%x.", Status);
    }
    memVal = counterVal.longValue;

    // wprintf(L"%.20g",counterVal.doubleValue);

    // return counterVal.doubleValue;
}