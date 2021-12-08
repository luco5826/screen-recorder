
#pragma comment(lib, "Strmiids.lib")

#include "ListAVDevices.h"

#ifdef _WINDOWS

HRESULT DS_GetAudioVideoInputDevices(std::vector<std::string>& vectorDevices, const std::string deviceType)
{
	GUID guidValue;
	if (deviceType == "v") {
		guidValue = CLSID_VideoInputDeviceCategory;
	}
	else if (deviceType == "a") {
		guidValue = CLSID_AudioInputDeviceCategory;
	}
	else {
		throw std::invalid_argument("param deviceType must be 'a' or 'v'.");
	}

	char FriendlyName[MAX_FRIENDLY_NAME_LENGTH];
	HRESULT hr;

	vectorDevices.clear();

	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (FAILED(hr))
	{
		return hr;
	}

	ICreateDevEnum* pSysDevEnum = NULL;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void**)&pSysDevEnum);
	if (FAILED(hr))
	{
		CoUninitialize();
		return hr;
	}
	
	IEnumMoniker* pEnumCat = NULL;
	hr = pSysDevEnum->CreateClassEnumerator(guidValue, &pEnumCat, 0);
	if (hr == S_OK)
	{
		IMoniker* pMoniker = NULL;
		ULONG cFetched;
		while (pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
		{
			IPropertyBag* pPropBag;
			hr = pMoniker->BindToStorage(NULL, NULL, IID_IPropertyBag, (void**)&pPropBag);
			if (SUCCEEDED(hr))
			{
				// 获取设备友好名
				VARIANT varName;
				VariantInit(&varName);

				hr = pPropBag->Read(L"FriendlyName", &varName, NULL);
				if (SUCCEEDED(hr))
				{
					// Inefficient but it's the only working way I've found
					std::ostringstream o;
					for (size_t i = 0; i < SysStringLen(varName.bstrVal); i++)
					{
						o << (char)varName.bstrVal[i];
					}
					//StringCchCopy(FriendlyName, MAX_FRIENDLY_NAME_LENGTH, varName.bstrVal);
					vectorDevices.push_back(o.str());
				}

				VariantClear(&varName);
				pPropBag->Release();
			}

			pMoniker->Release();
		} 

		pEnumCat->Release();
	}

	pSysDevEnum->Release();
	CoUninitialize();

	return hr;
}

std::string DS_GetDefaultAudioDevice() {
	std::vector<std::string> v;
	int ret = DS_GetAudioVideoInputDevices(v, "a");
	if (ret >= 0 && !v.empty()) {
		return v[0];
	}
	else {
		return "";
	}
}
#endif