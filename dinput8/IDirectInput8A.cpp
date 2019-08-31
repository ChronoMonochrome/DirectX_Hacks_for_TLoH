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


HRESULT m_IDirectInput8A::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	//Log() << "m_IDirectInput8A::QueryInterface, riid passed = " << GetNameOfRefIID(riid);
	if ((riid == IID_IDirectInput8A || riid == IID_IUnknown) && ppvObj)
	{
		AddRef();

		*ppvObj = this;

		return S_OK;
	}

	HRESULT hr = ProxyInterface->QueryInterface(riid, ppvObj);

	if (SUCCEEDED(hr))
	{
		genericQueryInterface(riid, ppvObj);
	}

	return hr;
}

ULONG m_IDirectInput8A::AddRef()
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->AddRef();
}

ULONG m_IDirectInput8A::Release()
{
#ifdef DEBUG
	Log() << __func__;
#endif
	ULONG ref = ProxyInterface->Release();

	if (ref == 0)
	{
		delete this;
	}

	return ref;
}

HRESULT m_IDirectInput8A::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8A *lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
{
	this->iid = GetNameOfRefIID(rguid);
	Log() << __func__ << " rguid=" << this->iid;

	HRESULT hr = ProxyInterface->CreateDevice(rguid, lplpDirectInputDevice, pUnkOuter);

	if (rguid == GUID_Joystick2) {
		if (SUCCEEDED(hr) && lplpDirectInputDevice)
		{
			*lplpDirectInputDevice = ProxyAddressLookupTable.FindAddress<m_IDirectInputDevice8A>(*lplpDirectInputDevice);
		}
	}

	return hr;
}

HRESULT m_IDirectInput8A::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
}

HRESULT m_IDirectInput8A::GetDeviceStatus(REFGUID rguidInstance)
{
#ifdef DEBUG
	Log() << __func__ << " rguidInstance = " << GetNameOfRefIID(rguidInstance);
#endif
	return ProxyInterface->GetDeviceStatus(rguidInstance);
}

HRESULT m_IDirectInput8A::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT m_IDirectInput8A::Initialize(HINSTANCE hinst, DWORD dwVersion)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->Initialize(hinst, dwVersion);
}

HRESULT m_IDirectInput8A::FindDevice(REFGUID rguidClass, LPCSTR ptszName, LPGUID pguidInstance)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->FindDevice(rguidClass, ptszName, pguidInstance);
}

HRESULT m_IDirectInput8A::EnumDevicesBySemantics(LPCSTR ptszUserName, LPDIACTIONFORMATA lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCBA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	if (!lpCallback)
	{
		return E_INVALIDARG;
	}

	ENUMDEVICEA CallbackContext;
	CallbackContext.pvRef = pvRef;
	CallbackContext.lpCallback = lpCallback;

	return ProxyInterface->EnumDevicesBySemantics(ptszUserName, lpdiActionFormat, m_IDirectInputEnumDevice::EnumDeviceCallbackA, &CallbackContext, dwFlags);
}

HRESULT m_IDirectInput8A::ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMSA lpdiCDParams, DWORD dwFlags, LPVOID pvRefData)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->ConfigureDevices(lpdiCallback, lpdiCDParams, dwFlags, pvRefData);
}
