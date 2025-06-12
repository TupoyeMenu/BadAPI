#include "gta/datBitBuffer.hpp"

extern "C" __declspec(dllexport) uint32_t bitbuffer_GetPosition(rage::datBitBuffer* buf)
{
	return buf->GetPosition();
}
extern "C" __declspec(dllexport) void bitbuffer_ReadBitsSingle(uint8_t* data, uint32_t* out, int size, int offset)
{
	return rage::datBitBuffer::ReadBitsSingle(data, out, size, offset);
}
extern "C" __declspec(dllexport) void bitbuffer_WriteBitsSingle(uint8_t* data, int value, int size, int offset)
{
	return rage::datBitBuffer::WriteBitsSingle(data, value, size, offset);
}
extern "C" __declspec(dllexport) bool bitbuffer_CopyBits(rage::datBitBuffer* buf, const void* dest, const void* source, int length, int destBitOffset, int sourceBitOffset)
{
	return buf->CopyBits(dest, source, length, destBitOffset, sourceBitOffset);
}
extern "C" __declspec(dllexport) bool bitbuffer_IsReadBuffer(rage::datBitBuffer* buf)
{
	return buf->IsReadBuffer();
}
extern "C" __declspec(dllexport) bool bitbuffer_IsSizeCalculator(rage::datBitBuffer* buf)
{
	return buf->IsSizeCalculator();
}
extern "C" __declspec(dllexport) void bitbuffer_Seek(rage::datBitBuffer* buf, int bits)
{
	return buf->Seek(bits);
}

extern "C" __declspec(dllexport) bool bitbuffer_ReadDword(rage::datBitBuffer* buf, uint32_t* out, int size)
{
	return buf->ReadDword(out, size);
}
extern "C" __declspec(dllexport) bool bitbuffer_WriteDword(rage::datBitBuffer* buf, int val, int size)
{
	return buf->WriteDword(val, size);
}
extern "C" __declspec(dllexport) bool bitbuffer_ReadQword(rage::datBitBuffer* buf, uint64_t* out, int size)
{
	return buf->ReadQword(out, size);
}
extern "C" __declspec(dllexport) bool bitbuffer_WriteQword(rage::datBitBuffer* buf, uint64_t val, int size)
{
	return buf->WriteQword(val, size);
}
extern "C" __declspec(dllexport) bool bitbuffer_ReadInt64(rage::datBitBuffer* buf, int64_t* out, int size)
{
	return buf->ReadInt64(out, size);
}
extern "C" __declspec(dllexport) bool bitbuffer_WriteInt64(rage::datBitBuffer* buf, int64_t val, int size)
{
	return buf->WriteInt64(val, size);
}

extern "C" __declspec(dllexport) void bitbuffer_WriteArray(rage::datBitBuffer* buf, const void* array, int bits)
{
	return buf->WriteArray(array, bits);
}
extern "C" __declspec(dllexport) void bitbuffer_WriteArrayBytes(rage::datBitBuffer* buf, const void* array, int bytes)
{
	return buf->WriteArrayBytes(array, bytes);
}
extern "C" __declspec(dllexport) void bitbuffer_ReadArray(rage::datBitBuffer* buf, void* array, int bits)
{
	return buf->ReadArray(array, bits);
}
extern "C" __declspec(dllexport) void bitbuffer_ReadArrayBytes(rage::datBitBuffer* buf, void* array, int bytes)
{
	return buf->ReadArrayBytes(array, bytes);
}

extern "C" __declspec(dllexport) void bitbuffer_WriteString(rage::datBitBuffer* buf, const char* string, int max_len)
{
	return buf->WriteString(string, max_len);
}
extern "C" __declspec(dllexport) void bitbuffer_ReadString(rage::datBitBuffer* buf, char* string, int max_len)
{
	return buf->ReadString(string, max_len);
}
extern "C" __declspec(dllexport) int bitbuffer_GetDataLength(rage::datBitBuffer* buf)
{
	return buf->GetDataLength();
}
extern "C" __declspec(dllexport) bool bitbuffer_ReadRockstarId(rage::datBitBuffer* buf, int64_t* rockstar_id)
{
	return buf->ReadRockstarId(rockstar_id);
}

extern "C" __declspec(dllexport) float bitbuffer_ReadFloat(rage::datBitBuffer* buf, int size, float divisor)
{
	return buf->ReadFloat(size, divisor);
}
extern "C" __declspec(dllexport) void bitbuffer_WriteFloat(rage::datBitBuffer* buf, int size, float divisor, float value)
{
	return buf->WriteFloat(size, divisor, value);
}
extern "C" __declspec(dllexport) float bitbuffer_ReadSignedFloat(rage::datBitBuffer* buf, int size, float divisor)
{
	return buf->ReadSignedFloat(size, divisor);
}
extern "C" __declspec(dllexport) void bitbuffer_WriteSignedFloat(rage::datBitBuffer* buf, int size, float divisor, float value)
{
	return buf->WriteSignedFloat(size, divisor, value);
}

extern "C" __declspec(dllexport) void bitbuffer_ReadPosition(rage::datBitBuffer* buf, int size, rage::fvector3* pos)
{
	*pos = buf->ReadPosition(size);
}
extern "C" __declspec(dllexport) void bitbuffer_WritePosition(rage::datBitBuffer* buf, int size, rage::fvector3* pos)
{
	return buf->WritePosition(size, *pos);
}

extern "C" __declspec(dllexport) void bitbuffer_ReadVector3(rage::datBitBuffer* buf, int size, float divisor, rage::fvector3* vec)
{
	*vec = buf->ReadVector3(size, divisor);
}
extern "C" __declspec(dllexport) void bitbuffer_WriteVector3(rage::datBitBuffer* buf, int size, float divisor, rage::fvector3* vec)
{
	return buf->WriteVector3(size, divisor, *vec);
}

extern "C" __declspec(dllexport) void bitbuffer_AlignToByteBoundary(rage::datBitBuffer* buf)
{
	return buf->AlignToByteBoundary();
}

