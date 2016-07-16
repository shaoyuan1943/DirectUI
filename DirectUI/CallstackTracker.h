#pragma once

namespace DirectUI
{
	class UILIB_API CallstackTracker
	{
	public:
		CallstackTracker(void);
		~CallstackTracker(void);
		CallstackTracker & operator=(CallstackTracker const &);
		int CaptureCallstackFrames(void);
		int EnumCallstackFrames(void(__stdcall*)(char const *, char const *, unsigned long, unsigned long));
		static void __stdcall Uninit(void);
		static int __stdcall Init(void);

	private:
		static int __stdcall InitFailed(void);
		static int __stdcall InitializeDllInfo(void);
		static int __stdcall InitializeSymbols(void);
		static int __stdcall IsCorrectImageHlpVersion(void);
		static int const STACKDEPTH;
		static struct IMGHLPFN_LOAD * s_ImageHlpFuncList;
		static int s_fInitFailed;
		static void * s_hProcess;
		static struct HINSTANCE__ * s_hinstImageHlp;
		static struct HINSTANCE__ * s_hinstNtDll;
		static struct API_VERSION * (__stdcall* s_pfnImagehlpApiVersionEx)(struct API_VERSION *);
		static unsigned short(__stdcall* s_pfnRtlCaptureStackBackTrace)(unsigned long, unsigned long, void * *, unsigned long *);
		static int(__stdcall* s_pfnSymFromAddr)(void *, unsigned __int64, unsigned __int64 *, struct _SYMBOL_INFO *);
		static int(__stdcall* s_pfnSymGetModuleInfo64)(void *, unsigned __int64, struct _IMAGEHLP_MODULE64 *);
		static int(__stdcall* s_pfnSymInitialize)(void *, char const *, int);
		static unsigned __int64(__stdcall* s_pfnSymLoadModule64)(void *, void *, char const *, char const *, unsigned __int64, unsigned long);
		static unsigned long(__stdcall* s_pfnSymSetOptions)(unsigned long);
		static int __stdcall DllsLoaded(void);
		void FillSymbolInfo(struct STACK_SYMBOL_INFO *, unsigned __int64);
		unsigned __int64 GetModuleBase(void *, unsigned __int64);
		static int const INITIALSTACKSKIP;
	};
}