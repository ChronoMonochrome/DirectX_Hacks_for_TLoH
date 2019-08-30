/**
* Copyright (C) 2019 Elisha Riedlinger
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*/

#include "dinput8.h"
#include <Windows.h>
#include <winnt.h>
#include <NTSecAPI.h>
#include <string>


HRESULT m_IDirectInputDevice8A::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	Log() << __func__ << ": riid=";
	if ((riid == IID_IDirectInputDevice8A || riid == IID_IUnknown) && ppvObj)
	{
		AddRef();

		*ppvObj = this;

		return S_OK;
	}

	Log() << "m_IDirectInputDevice8A::QueryInterface";

	HRESULT hr = ProxyInterface->QueryInterface(riid, ppvObj);

	if (SUCCEEDED(hr))
	{
		genericQueryInterface(riid, ppvObj);
	}

	return hr;
}

ULONG m_IDirectInputDevice8A::AddRef()
{
	Log() << __func__;
	return ProxyInterface->AddRef();
}

ULONG m_IDirectInputDevice8A::Release()
{
	Log() << __func__;
	ULONG ref = ProxyInterface->Release();

	if (ref == 0)
	{
		delete this;
	}

	return ref;
}

HRESULT m_IDirectInputDevice8A::GetCapabilities(LPDIDEVCAPS lpDIDevCaps)
{
	Log() << __func__;
	return ProxyInterface->GetCapabilities(lpDIDevCaps);
}

HRESULT m_IDirectInputDevice8A::EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	Log() << __func__;
	return ProxyInterface->EnumObjects(lpCallback, pvRef, dwFlags);
}

int count = 0;

std::string ToString1(const GUID& guid)
{
	// could use StringFromIID() - but that requires managing an OLE string
	std::string str;
	str = format("%08X",
		guid.Data1);
}

HRESULT m_IDirectInputDevice8A::GetProperty(REFGUID rguidProp, LPDIPROPHEADER pdiph)
{
	Log() << __func__;
	return ProxyInterface->GetProperty(rguidProp, pdiph);
}
//Log() << GetNameOfRefIID(## x);
#define LOG_REFGUID(rguid, x) \
		if (rguid == ## x) { \
			Log() << "bump"; \
		}

HRESULT m_IDirectInputDevice8A::SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph)
{
	Log() << __func__;

	HRESULT res = ProxyInterface->SetProperty(rguidProp, pdiph);

	return res;
}

HRESULT m_IDirectInputDevice8A::Acquire()
{
	Log() << __func__;
	return ProxyInterface->Acquire();
}

HRESULT m_IDirectInputDevice8A::Unacquire()
{
	Log() << __func__;
	return ProxyInterface->Unacquire();
}

HRESULT m_IDirectInputDevice8A::GetDeviceState(DWORD cbData, LPVOID lpvData)
{
	char *buf = reinterpret_cast<char*>(lpvData);

	//buf = (char*)malloc(cbData);
	//memcpy(buf, lpvData, cbData);


	Log() << __func__ << ": received " << cbData << " bytes";

	/*for (char c: buf) {
		Log() << format("%02x", c);
	}*/

	//return S_OK;
	HRESULT res = ProxyInterface->GetDeviceState(cbData, lpvData);

	/*for (int i = 0; i < cbData; i++) {
		Log() << i << ": " << int(buf[i]);
	}*/

	return res;
}

HRESULT m_IDirectInputDevice8A::GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags)
{
	Log() << __func__;
	return ProxyInterface->GetDeviceData(cbObjectData, rgdod, pdwInOut, dwFlags);
}

std::string getDataFormat(LPCDIDATAFORMAT lpdf) {
	LPCDIDATAFORMAT kbd = &c_dfDIKeyboard,
		mouse = &c_dfDIMouse,
		mouse2 = &c_dfDIMouse2,
		joy1 = &c_dfDIJoystick,
		joy2 = &c_dfDIJoystick2;

	if (lpdf == kbd)
		return std::string("c_dfDIKeyboard");
	else if (lpdf == mouse)
		return std::string("c_dfDIMouse");
	else if (lpdf == mouse2)
		return std::string("c_dfDIMouse2");
    else if (lpdf == GetdfDIJoystick())
		return std::string("c_dfDIJoystick");
	else if (lpdf == joy2)
		return std::string("c_dfDIJoystick2");

	return std::string("custom format");
}

HRESULT m_IDirectInputDevice8A::SetDataFormat(LPCDIDATAFORMAT lpdf)
{
	std::string fmt = getDataFormat(lpdf);

	Log() << __func__ << ": format = " << fmt;

	return ProxyInterface->SetDataFormat(lpdf);
}

HRESULT m_IDirectInputDevice8A::SetEventNotification(HANDLE hEvent)
{
	Log() << __func__;
	return ProxyInterface->SetEventNotification(hEvent);
}

HRESULT m_IDirectInputDevice8A::SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
{
	Log() << __func__;
	return ProxyInterface->SetCooperativeLevel(hwnd, dwFlags);
}

HRESULT m_IDirectInputDevice8A::GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA pdidoi, DWORD dwObj, DWORD dwHow)
{
	Log() << __func__;
	return ProxyInterface->GetObjectInfo(pdidoi, dwObj, dwHow);
}

HRESULT m_IDirectInputDevice8A::GetDeviceInfo(LPDIDEVICEINSTANCEA pdidi)
{
	Log() << __func__;
	return ProxyInterface->GetDeviceInfo(pdidi);
}

HRESULT m_IDirectInputDevice8A::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	Log() << __func__;
	return ProxyInterface->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT m_IDirectInputDevice8A::Initialize(HINSTANCE hinst, DWORD dwVersion, REFGUID rguid)
{
	Log() << __func__;
	return ProxyInterface->Initialize(hinst, dwVersion, rguid);
}

HRESULT m_IDirectInputDevice8A::CreateEffect(REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT * ppdeff, LPUNKNOWN punkOuter)
{
	Log() << __func__;
	HRESULT hr = ProxyInterface->CreateEffect(rguid, lpeff, ppdeff, punkOuter);

	if (SUCCEEDED(hr) && ppdeff)
	{
		*ppdeff = ProxyAddressLookupTable.FindAddress<m_IDirectInputEffect>(*ppdeff);
	}

	return hr;
}

HRESULT m_IDirectInputDevice8A::EnumEffects(LPDIENUMEFFECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwEffType)
{
	Log() << __func__;
	return ProxyInterface->EnumEffects(lpCallback, pvRef, dwEffType);
}

HRESULT m_IDirectInputDevice8A::GetEffectInfo(LPDIEFFECTINFOA pdei, REFGUID rguid)
{
	Log() << __func__;
	return ProxyInterface->GetEffectInfo(pdei, rguid);
}

HRESULT m_IDirectInputDevice8A::GetForceFeedbackState(LPDWORD pdwOut)
{
	Log() << __func__;
	return ProxyInterface->GetForceFeedbackState(pdwOut);
}

HRESULT m_IDirectInputDevice8A::SendForceFeedbackCommand(DWORD dwFlags)
{
	Log() << __func__;
	return ProxyInterface->SendForceFeedbackCommand(dwFlags);
}

HRESULT m_IDirectInputDevice8A::EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl)
{
	Log() << __func__;
	if (!lpCallback)
	{
		return E_INVALIDARG;
	}

	ENUMEFFECT CallbackContext;
	CallbackContext.pvRef = pvRef;
	CallbackContext.lpCallback = lpCallback;

	return ProxyInterface->EnumCreatedEffectObjects(m_IDirectInputEnumEffect::EnumEffectCallback, &CallbackContext, fl);
}

HRESULT m_IDirectInputDevice8A::Escape(LPDIEFFESCAPE pesc)
{
	Log() << __func__;
	return ProxyInterface->Escape(pesc);
}

HRESULT m_IDirectInputDevice8A::Poll()
{
	Log() << __func__;
	return ProxyInterface->Poll();
}

HRESULT m_IDirectInputDevice8A::SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl)
{
	Log() << __func__;
	return ProxyInterface->SendDeviceData(cbObjectData, rgdod, pdwInOut, fl);
}

HRESULT m_IDirectInputDevice8A::EnumEffectsInFile(LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags)
{
	Log() << __func__;
	return ProxyInterface->EnumEffectsInFile(lpszFileName, pec, pvRef, dwFlags);
}

HRESULT m_IDirectInputDevice8A::WriteEffectToFile(LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags)
{
	Log() << __func__;
	return ProxyInterface->WriteEffectToFile(lpszFileName, dwEntries, rgDiFileEft, dwFlags);
}

HRESULT m_IDirectInputDevice8A::BuildActionMap(LPDIACTIONFORMATA lpdiaf, LPCSTR lpszUserName, DWORD dwFlags)
{
	Log() << __func__;
	return ProxyInterface->BuildActionMap(lpdiaf, lpszUserName, dwFlags);
}

HRESULT m_IDirectInputDevice8A::SetActionMap(LPDIACTIONFORMATA lpdiActionFormat, LPCSTR lptszUserName, DWORD dwFlags)
{
	Log() << __func__;
	return ProxyInterface->SetActionMap(lpdiActionFormat, lptszUserName, dwFlags);
}

HRESULT m_IDirectInputDevice8A::GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA lpdiDevImageInfoHeader)
{
	Log() << __func__;
	return ProxyInterface->GetImageInfo(lpdiDevImageInfoHeader);
}
