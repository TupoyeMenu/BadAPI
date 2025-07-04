/**
 * @file fidevice.cpp
 * @attention If you want to include this file you will need to add the following pointers: 
 * @code {.cpp}
 * functions::fidevice_get_device m_fidevice_get_device;
 * functions::fipackfile_ctor m_fipackfile_ctor;
 * functions::fipackfile_dtor m_fipackfile_dtor;
 * rage::fiPackfile** m_fipackfile_instances;
 * functions::fipackfile_open_archive m_fipackfile_open_archive;
 * functions::fipackfile_mount m_fipackfile_mount;
 * functions::fipackfile_unmount m_fipackfile_unmount;
 * functions::fipackfile_close_archive m_fipackfile_close_archive;
 * @endcode
 * Look at YimMenu source if you need them.
 * https://github.com/YimMenu/YimMenu/blob/16e8e571f04b6d9d94f9be8c0d1823dc1088ae31/src/pointers.cpp#L510-L549
 * Then remove `#if 0` and `endif` from the file
 * 
 * @copyright GNU General Public License Version 2.
 * This file is part of YimMenu.
 * YimMenu is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.
 * YimMenu is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with YimMenu. If not, see <https://www.gnu.org/licenses/>.
 */

#if 0
#include "fidevice.hpp"

#include "hooking/hooking.hpp"
#include "gta/pointers.hpp"

namespace rage
{
#define PURECALL()                                         \
	LOG(FATAL) << "pure fiDevice call (" << __FUNCTION__ << ")"; \
	return 0

	fiDeviceImplemented::fiDeviceImplemented()
	{
	}

	void fiDeviceImplemented::Destroy()
	{
		LOG(FATAL) << "pure fiDevice call (" << __FUNCTION__ << ")";
	}

	uint64_t fiDeviceImplemented::Open(const char* fileName, bool)
	{
		PURECALL();
	}

	uint64_t fiDeviceImplemented::OpenBulk(const char* fileName, uint64_t* ptr)
	{
		PURECALL();
	}

	uint64_t fiDeviceImplemented::OpenBulkWrap(const char* fileName, uint64_t* ptr, void* a3)
	{
		PURECALL();
	}

	uint64_t fiDeviceImplemented::CreateLocal(const char* fileName)
	{
		PURECALL();
	}

	uint64_t fiDeviceImplemented::Create(const char*)
	{
		PURECALL();
	}

	uint32_t fiDeviceImplemented::Read(uint64_t handle, void* buffer, uint32_t toRead)
	{
		PURECALL();
	}

	uint32_t fiDeviceImplemented::ReadBulk(uint64_t handle, uint64_t ptr, void* buffer, uint32_t toRead)
	{
		PURECALL();
	}

	uint32_t fiDeviceImplemented::WriteBulk(uint64_t, int, int, int, int)
	{
		PURECALL();
	}

	uint32_t fiDeviceImplemented::Write(uint64_t, void*, int)
	{
		PURECALL();
	}

	uint32_t fiDeviceImplemented::Seek(uint64_t handle, int32_t distance, uint32_t method)
	{
		PURECALL();
	}

	uint64_t fiDeviceImplemented::SeekLong(uint64_t handle, int64_t distance, uint32_t method)
	{
		PURECALL();
	}

	int32_t fiDeviceImplemented::Close(uint64_t handle)
	{
		PURECALL();
	}

	int32_t fiDeviceImplemented::CloseBulk(uint64_t handle)
	{
		PURECALL();
	}

	int fiDeviceImplemented::GetFileLength(uint64_t handle)
	{
		PURECALL();
	}

	int fiDeviceImplemented::m_40(int)
	{
		PURECALL();
	}

	bool fiDeviceImplemented::RemoveFile(const char* file)
	{
		PURECALL();
	}

	int fiDeviceImplemented::RenameFile(const char* from, const char* to)
	{
		PURECALL();
	}

	int fiDeviceImplemented::CreateDirectory(const char* dir)
	{
		PURECALL();
	}

	int fiDeviceImplemented::RemoveDirectory(const char* dir)
	{
		PURECALL();
	}

	uint64_t fiDeviceImplemented::GetFileLengthUInt64(uint64_t file)
	{
		PURECALL();
	}

	uint64_t fiDeviceImplemented::GetFileLengthLong(const char* fileName)
	{
		PURECALL();
	}

	uint64_t fiDeviceImplemented::GetFileTime(const char* file)
	{
		PURECALL();
	}

	bool fiDeviceImplemented::SetFileTime(const char* file, FILETIME fileTime)
	{
		PURECALL();
	}

	uint64_t fiDeviceImplemented::FindFirst(const char* path, fiFindData* findData)
	{
		PURECALL();
	}

	bool fiDeviceImplemented::FindNext(uint64_t handle, fiFindData* findData)
	{
		PURECALL();
	}

	int fiDeviceImplemented::FindClose(uint64_t handle)
	{
		PURECALL();
	}

	rage::fiDevice* fiDeviceImplemented::GetUnkDevice()
	{
		PURECALL();
	}

	void* fiDeviceImplemented::m_xy(void* a1, int a2, void* a3)
	{
		PURECALL();
	}

	bool fiDeviceImplemented::Truncate(uint64_t handle)
	{
		PURECALL();
	}

	uint32_t fiDeviceImplemented::GetFileAttributes(const char* path)
	{
		PURECALL();
	}

	bool fiDeviceImplemented::m_xz()
	{
		PURECALL();
	}

	bool fiDeviceImplemented::SetFileAttributes(const char* file, uint32_t FileAttributes)
	{
		PURECALL();
	}

	void fiDeviceImplemented::m_xx()
	{
		return;
	}

	bool fiDeviceImplemented::ReadFull(uint64_t handle, void* buffer, uint32_t length)
	{
		PURECALL();
	}

	bool fiDeviceImplemented::WriteFull(uint64_t handle, void* buffer, uint32_t length)
	{
		PURECALL();
	}

	int32_t fiDeviceImplemented::GetResourceVersion(const char* fileName, ResourceFlags* flags)
	{
		PURECALL();
	}

	int fiDeviceImplemented::m_yx()
	{
		PURECALL();
	}

	int fiDeviceImplemented::m_yy()
	{
		PURECALL();
	}

	int fiDeviceImplemented::m_yz(void*)
	{
		PURECALL();
	}

	int fiDeviceImplemented::m_zx(void*)
	{
		PURECALL();
	}

	bool fiDeviceImplemented::IsCollection()
	{
		PURECALL();
	}

	bool fiDeviceImplemented::m_addedIn1290()
	{
		PURECALL();
	}

	fiDevice* fiDeviceImplemented::GetCollection()
	{
		PURECALL();
	}

	bool fiDeviceImplemented::m_ax()
	{
		PURECALL();
	}

	int fiDeviceImplemented::GetCollectionId()
	{
		PURECALL();
	}

	const char* fiDeviceImplemented::GetName()
	{
		PURECALL();
	}

	fiPackfile::fiPackfile()
	{
		big::g_pointers->m_fipackfile_ctor(this);
	}

	fiPackfile::~fiPackfile()
	{
		big::g_pointers->m_fipackfile_dtor(this);
	}

	bool fiPackfile::OpenPackfile(const char* archive, bool b_true, int type, intptr_t very_false)
	{
		return big::g_pointers->m_fipackfile_open_archive(this, archive, b_true, type, very_false);
	}

	bool fiPackfile::Mount(const char* mount_point)
	{
		return big::g_pointers->m_fipackfile_mount(this, mount_point);
	}

	void fiPackfile::ClosePackfile()
	{
		big::g_pointers->m_fipackfile_close_archive(this);
	}

	void fiDevice::Unmount(const char* rootPath)
	{
		big::g_pointers->m_fipackfile_unmount(rootPath);
	}
}
#endif