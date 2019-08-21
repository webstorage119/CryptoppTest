# CryptoppTest
使用MSVC 2015编译c++ dll运行库时，注意官方测试示例中在引入dll.h的类中添加的条件编译语句：

#ifdef CRYPTOPP_IMPORTS

static CryptoPP::PNew s_pNew = NULLPTR;
static CryptoPP::PDelete s_pDelete = NULLPTR;

extern "C" __declspec(dllexport) void __cdecl SetNewAndDeleteFromCryptoPP(CryptoPP::PNew pNew, CryptoPP::PDelete pDelete, CryptoPP::PSetNewHandler pSetNewHandler)
{
	(void)(pSetNewHandler);
	s_pNew = pNew;
	s_pDelete = pDelete;
}

void * __cdecl operator new (size_t size)
{
	return s_pNew(size);
}

void __cdecl operator delete (void * p)
{
	s_pDelete(p);
}

#endif

未加该语句时函数块调用时，退出作用域会发生“CryptoPP HEAP[XXX.exe]: Invalid address specified to RtlValidateHeap”错误。
