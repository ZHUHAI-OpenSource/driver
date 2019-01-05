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

	pdrv_obj->DriverUnload = nt00Unload;
	
	return STATUS_SUCCESS;
}
// 自定义卸载例程
// ---------------------------------------------
#pragma   PCODE
VOID nt00Unload(IN PDRIVER_OBJECT pdrv_obj) {
    //
}
