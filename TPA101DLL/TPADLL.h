#pragma once
#ifndef _TPADLL_H_
#define _TPADLL_H_

#ifdef  __cplusplus
extern "C" {
#endif //  __cplusplus
	__declspec(dllexport)int GetDeviceListNum();
	//get  the number of index's deviceInfo
	__declspec(dllexport)TLI_DeviceInfo GetDeviceInfo(int index);
	//get divice description infomation
	__declspec(dllexport) char* GetDeviceDescriptionInfo(TLI_DeviceInfo deviceInfo);
	//get device serial number
	__declspec(dllexport)char* GetDeviceSerialNumber(TLI_DeviceInfo deviceInfo);
	//get device PID
	__declspec(dllexport)DWORD GetDevicePID(TLI_DeviceInfo deviceInfo);
	//get device typeID
	__declspec(dllexport)DWORD GetDeviceTypeID(TLI_DeviceInfo deviceInfo);
	// if the device is a piezo device
	__declspec(dllexport)bool isPizeoDevice(TLI_DeviceInfo deviceInfo);
	//if the device is a laser
	__declspec(dllexport)bool isLaser(TLI_DeviceInfo deviceInfo);
	//if the device is a custom type
	__declspec(dllexport)bool isCustomType(TLI_DeviceInfo deviceInfo);
	//if the device is a rack
	__declspec(dllexport)bool isRack(TLI_DeviceInfo deviceInfo);
	//open device
	__declspec(dllexport)bool openDevice(const char* serialNo);
	//start the device polling at  milliseconds intervals
    //Starts the internal polling loop which continuously requests position and status.
   //只有在轮询状态下，才能一直获取探测器的坐标和状态
	__declspec(dllexport)bool StartPolling(const char* serialNo, int milliseconds);
	//stop polling
	__declspec(dllexport)void stopPolling(const char* serialNo);
	//set operation mode {"openLoop","closeLoop","monitor"}
	__declspec(dllexport)bool setOperationMode(const char* serialNo, const char* mode);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !_TPADLL_H_

