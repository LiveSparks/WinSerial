#include "winStats.h"
#include <pdh.h>
#include <pdhmsg.h>
#include <stdio.h>

static HQUERY cpuQuery;
static HCOUNTER cpuTotal;
static PDH_STATUS Status;

__int64 Filetime2Int64(const FILETIME &ftime)
{
    LARGE_INTEGER li;
    li.LowPart = ftime.dwLowDateTime;
    li.HighPart = ftime.dwHighDateTime;
    return li.QuadPart;
}
 
__int64 CompareFileTime2(const FILETIME &preTime, const FILETIME &nowTime)
{
    return Filetime2Int64(nowTime) - Filetime2Int64(preTime);
}

void pdhinit(){
    Status = PdhOpenQuery(NULL, NULL, &cpuQuery);
    if(Status != ERROR_SUCCESS){
        wprintf(L"\nPdhOpenQuery failed with status 0x%x.", Status);
    }
    
    Status = PdhAddCounter(cpuQuery, TEXT("\\Processor(_Total)\\% Processor Time"), NULL, &cpuTotal);
    if(Status != ERROR_SUCCESS){
        wprintf(L"\nPdhAddCounter failed with status 0x%x.", Status);
    }
    
    Status = PdhCollectQueryData(cpuQuery);
    if(Status != ERROR_SUCCESS){
        wprintf(L"\nPdhCollectQueryData failed with status 0x%x.", Status);
    }
}
 
double getCpuUsage()
{
    Sleep(500);
    PDH_FMT_COUNTERVALUE counterVal;

    Status = PdhCollectQueryData(cpuQuery);
    if(Status != ERROR_SUCCESS){
        wprintf(L"\nPdhCollectQueryData failed with status 0x%x.", Status);
    }

    Status = PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
    if(Status != ERROR_SUCCESS){
        wprintf(L"\nPdhGetFormatedCounterValue failed with status 0x%x.", Status);
    }

    // wprintf(L"%.20g",counterVal.doubleValue);

    return counterVal.doubleValue;
}