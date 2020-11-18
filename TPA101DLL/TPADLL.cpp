#include<iostream>
#include<stdio.h>
#include"pch.h"
#include"framework.h"
#include"TPADLL.h"
#include"Thorlabs.MotionControl.TCube.Quad.h"
using namespace std;

//get device list num
int GetDeviceListNum() {
	short num = TLI_GetDeviceListSize();
	return (int)num;
}

//get  the number of index's deviceInfo
TLI_DeviceInfo GetDeviceInfo(int index) {
	
	// get BBD serial numbers
	char serialNos[100];
	TLI_GetDeviceListByTypeExt(serialNos, 100, 89);
	char *searchContext = nullptr;
	char *p = strtok_s(serialNos, ",", &searchContext);
	TLI_DeviceInfo deviceInfo;
	while (p != nullptr && index > 0) {
		
		// get device info from device
		TLI_GetDeviceInfo(p, &deviceInfo);
		index -= 1;
		if (index == 0) {
			break;
		}
		p = strtok_s(nullptr, ",", &searchContext);
	}
	return deviceInfo;
}
//get divice description infomation
char* GetDeviceDescriptionInfo(TLI_DeviceInfo deviceInfo) {
	char desc[65];
	strncpy(desc, deviceInfo.description, 64);
	desc[64] = '\0';
	return desc;
}

//get device serial number
char* GetDeviceSerialNumber(TLI_DeviceInfo deviceInfo) {
	char serialNo[9];
	strncpy(serialNo, deviceInfo.serialNo, 8);
	serialNo[8] = '\0';
	return serialNo;
}

//get device PID
DWORD GetDevicePID(TLI_DeviceInfo deviceInfo) {
	DWORD pid;
	pid = deviceInfo.PID;
	return pid;
}

//get device typeID
DWORD GetDeviceTypeID(TLI_DeviceInfo deviceInfo) {
	DWORD typeID;
	typeID = deviceInfo.typeID;
	return typeID;
}

// if the device is a piezo device
bool isPizeoDevice(TLI_DeviceInfo deviceInfo) {
	return deviceInfo.isPiezoDevice;
}

//if the device is a laser
bool isLaser(TLI_DeviceInfo deviceInfo) {
	return deviceInfo.isLaser;
}

//if the device is a custom type
bool isCustomType(TLI_DeviceInfo deviceInfo) {
	return deviceInfo.isCustomType;
}

//if the device is a rack
bool isRack(TLI_DeviceInfo deviceInfo) {
	return deviceInfo.isRack;
}

//open device
bool openDevice(const char* serialNo) {
	//char testSerialNo[16];
	//sprintf_s(testSerialNo, "%d", serialNo);
	if (QD_Open(serialNo) == 0) {
		return true;
	}
	return false;
}

//start the device polling at  milliseconds intervals
//Starts the internal polling loop which continuously requests position and status.
//只有在轮询状态下，才能一直获取探测器的坐标和状态
bool StartPolling(const char* serialNo, int milliseconds) {
	//char testSerialNo[16];
	//sprintf_s(testSerialNo, "%d", serialNo);
	if (QD_Open(serialNo) == 0) {
		if (QD_StartPolling(serialNo, milliseconds)) {
			Sleep(1000);
			return true;
		}
	}
	return false;
}

//stop polling
void stopPolling(const char* serialNo) {
	//char testSerialNo[16];
	//sprintf_s(testSerialNo, "%d", serialNo);
	QD_StopPolling(serialNo);
}

//set operation mode {"openLoop","closeLoop","monitor"}

bool setOperationMode(const char* serialNo,const char* mode) {
	//char testSerialNo[16];
	//sprintf_s(testSerialNo, "%d", serialNo);
	if (mode == "openLoop") {
		if (QD_SetOperatingMode(serialNo, QD_OperatingMode::QD_OpenLoop)==0) {
			Sleep(100);
			return true;
		}
		else {
			return false;
		}
	}
	else if(mode=="closeLoop"){
		if (QD_SetOperatingMode(serialNo, QD_OperatingMode::QD_ClosedLoop)==0) {
			Sleep(100);
			return true;
		}
		else {
			return false;
		}
	}
	else if (mode == "monitor") {
		if (QD_SetOperatingMode(serialNo, QD_OperatingMode::QD_Monitor)==0) {
			Sleep(100);
			return true;
		}
		else {
			return false;
		}
	}else {
		QD_SetOperatingMode(serialNo, QD_OperatingMode::QD_ModeUndefined);
		Sleep(100);
		return false;
	}
}