// create date : 2019-01-01
// author      : wmy
// email       : zhlhwmy@163.com
//
#include "nt00.h"
//
#pragma   INICODE
extern "C" NTSTATUS DriverEntry(
	IN PDRIVER_OBJECT	pdrv_obj,
	IN PUNICODE_STRING	rgt_path
	) 
{
	//
	NTSTATUS status = mCreateDevice(pdrv_obj);
	DbgPrint("step into DriverEntry... ");
	pdrv_obj->DriverUnload = nt00Unload;
	
	DbgPrint("register-path . buffer is %s",rgt_path->Buffer);
	return STATUS_SUCCESS;
}
//
// 创建设备自定义函数
// -----------------------------------------------
#pragma INICODE
NTSTATUS mCreateDevice(IN	 PDRIVER_OBJECT pdrv_obj) 
{
	//
	PDEVICE_OBJECT pdev_obj;
	UNICODE_STRING dev_name;
	//
	// 初始化设备名字
	RtlInitUnicodeString(&dev_name, DEVICE_NAME);	
	// 创建设备
	NTSTATUS status_create_dev = IoCreateDevice(
		pdrv_obj,0,&dev_name,FILE_DEVICE_UNKNOWN,0,true,&pdev_obj);
	//
	if (!NT_SUCCESS(status_create_dev))
	{
		DbgPrint("create device fail!!!");
		return status_create_dev;
	}
	// 
	pdev_obj->Flags |= DO_BUFFERED_IO;
	// 创建符号链接
	UNICODE_STRING sym_link_name = RTL_CONSTANT_STRING(SYM_LINK_NAME);
	NTSTATUS status_create_symlink = IoCreateSymbolicLink(
		&sym_link_name,
		&dev_name
		);
	//
	if (!NT_SUCCESS(status_create_symlink)) {
		DbgPrint("link fail");
		IoDeleteDevice(pdev_obj);
		return status_create_symlink;
		}
	return STATUS_SUCCESS;
}
//
// 自定义卸载例程
// ---------------------------------------------
#pragma   PCODE
VOID nt00Unload(IN PDRIVER_OBJECT pdrv_obj) {
	//PDEVICE_OBJECT nx_dev;
	DbgPrint("step into Unload ...");
	//
//	nx_dev = pdrv_obj->DeviceObject;
	//
}
