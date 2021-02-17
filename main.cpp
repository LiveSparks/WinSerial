#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <string.h>

using namespace std;

void exitSerial();
string readSerial(int len);
void sendKey(uint8_t key, int state);

//Serial Port Handle
HANDLE hComm;

int main()
{
    printf("Hello World\n");

    //Open Serial Port
    hComm = CreateFile(
        "\\\\.\\COM5",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (hComm == INVALID_HANDLE_VALUE){
        printf("\nPort can't be opened");
        system("pause");
        return 0;
    }

    //Configuring Serial Parameters
    DCB serialParams = {0};
    serialParams.DCBlength = sizeof(serialParams);
    if(GetCommState(hComm, &serialParams) == FALSE){
        printf("\nFailed to get COM State");
        exitSerial();
    }
    serialParams.BaudRate = CBR_115200;
    serialParams.ByteSize = 8;
    serialParams.StopBits = ONESTOPBIT;
    serialParams.Parity = NOPARITY;
    if(SetCommState(hComm, &serialParams) == FALSE){
        printf("\nFailed to set COM Parameters.");
        exitSerial();
    }

    //Configure Timeouts
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (SetCommTimeouts(hComm, &timeouts) == FALSE)
    {
        printf("\nError to Setting Time outs");
        exitSerial();
    }

    while(1){
        string rtn = readSerial(5);
        if(rtn!="NULL"){
            if(rtn[0] == 'F'){
                int key = stoi(rtn.substr(1,2));
                uint8_t hex_code = key + 111;

                printf("KeyEvent : F%d HEX:%X\t",key,hex_code);
                if(rtn.substr(3,2) == "DW"){
                    printf("PRESSED\n");
                    sendKey(hex_code,1);
                }
                else{
                    printf("RELEASED\n");
                    sendKey(hex_code,0);
                }
            }
        }
    }
}

/**
 * Reads a specific number of serial bytes
 * @param   len:    number of bytes to read
 * @retval  returns a string of the read bytes
 */
string readSerial(int len){
    char ch[len] = {0};
    DWORD dwByteRead = 0;
    if(!ReadFile(hComm, ch, len, &dwByteRead, NULL)){
        printf("Read Failed\n");
        exitSerial();
    }
    if(dwByteRead > 0){
        string s = ch;
        return s;
    }
    else{
        string str = "NULL";
        return str;
    }
}

/**
 * send the keypress to the system
 * @param   key:    Virtual Key Code that needs to be sent
 * @param   state:  State of key
 *                  1: Press
 *                  0: Release
 * @retval NULL
 */
void sendKey(uint8_t key, int state){
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = key;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    if(state)
        ip.ki.dwFlags = 0;
    
    SendInput(1, &ip, sizeof(INPUT));
}

/**
 * Exits the program after closing the serial port
 */ 
void exitSerial(){
    CloseHandle(hComm);
    exit(0);
}