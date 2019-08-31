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
#ifdef DEBUG
	Log() << __func__ << ": riid=";
#endif
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
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->AddRef();
}

ULONG m_IDirectInputDevice8A::Release()
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

HRESULT m_IDirectInputDevice8A::GetCapabilities(LPDIDEVCAPS lpDIDevCaps)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->GetCapabilities(lpDIDevCaps);
}

HRESULT m_IDirectInputDevice8A::EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->EnumObjects(lpCallback, pvRef, dwFlags);
}

HRESULT m_IDirectInputDevice8A::GetProperty(REFGUID rguidProp, LPDIPROPHEADER pdiph)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->GetProperty(rguidProp, pdiph);
}

HRESULT m_IDirectInputDevice8A::SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph)
{
#ifdef DEBUG
	Log() << __func__;
#endif

	HRESULT res = ProxyInterface->SetProperty(rguidProp, pdiph);

	return res;
}

HRESULT m_IDirectInputDevice8A::Acquire()
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->Acquire();
}

HRESULT m_IDirectInputDevice8A::Unacquire()
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->Unacquire();
}

#define BUTTON_TRIANGLE	48
#define BUTTON_CIRCLE	49
#define BUTTON_CROSS	50
#define BUTTON_SQUARE	51

/*
 *  Below is the most common data received from the joystick.
 *  For debugging purposes, this sequence of bytes can be used
 *  to override the actual data received, in order to reverse-
 *  engineer meaning of each individual byte.
 *  Uncomment for debugging.
 */

#ifdef VERBOSE_DEBUG
#define DONT_OVERRIDE -9999

int my_buf[] = {
	-2, // 0
	-1, // 1
	-1, // 2
	-1, // 3
	0, // 4
	0, // 5
	0, // 6
	0, // 7
	-2, // 8
	-1, // 9
	-1, // 10
	-1, // 11
	0, // 12
	0, // 13
	0, // 14
	0, // 15
	0, // 16
	0, // 17
	0, // 18
	0, // 19
	0, // 20
	0, // 21
	0, // 22
	0, // 23
	0, // 24
	0, // 25
	0, // 26
	0, // 27
	0, // 28
	0, // 29
	0, // 30
	0, // 31
	-1, // 32
	-1, // 33
	-1, // 34
	-1, // 35
	-1, // 36
	-1, // 37
	-1, // 38
	-1, // 39
	-1, // 40
	-1, // 41
	-1, // 42
	-1, // 43
	-1, // 44
	-1, // 45
	-1, // 46
	-1, // 47
	DONT_OVERRIDE, // 48 - triangle button
	DONT_OVERRIDE, // 49 - action (2) button
	DONT_OVERRIDE, // 50 - cancel (3) button
	DONT_OVERRIDE, // 51 - square button
	0, // 52
	0, // 53
	0, // 54
	0, // 55
	0, // 56
	DONT_OVERRIDE, // 57 - start button
	0, // 58
	0, // 59
	0, // 60
	0, // 61
	0, // 62
	0, // 63
	0, // 64
	0, // 65
	0, // 66
	0, // 67
	0, // 68
	0, // 69
	0, // 70
	0, // 71
	0, // 72
	0, // 73
	0, // 74
	0, // 75
	0, // 76
	0, // 77
	0, // 78
	0, // 79
	0, // 80
	0, // 81
	0, // 82
	0, // 83
	0, // 84
	0, // 85
	0, // 86
	0, // 87
	0, // 88
	0, // 89
	0, // 90
	0, // 91
	0, // 92
	0, // 93
	0, // 94
	0, // 95
	0, // 96
	0, // 97
	0, // 98
	0, // 99
	0, // 100
	0, // 101
	0, // 102
	0, // 103
	0, // 104
	0, // 105
	0, // 106
	0, // 107
	0, // 108
	0, // 109
	0, // 110
	0, // 111
	0, // 112
	0, // 113
	0, // 114
	0, // 115
	0, // 116
	0, // 117
	0, // 118
	0, // 119
	0, // 120
	0, // 121
	0, // 122
	0, // 123
	0, // 124
	0, // 125
	0, // 126
	0, // 127
	0, // 128
	0, // 129
	0, // 130
	0, // 131
	0, // 132
	0, // 133
	0, // 134
	0, // 135
	0, // 136
	0, // 137
	0, // 138
	0, // 139
	0, // 140
	0, // 141
	0, // 142
	0, // 143
	0, // 144
	0, // 145
	0, // 146
	0, // 147
	0, // 148
	0, // 149
	0, // 150
	0, // 151
	0, // 152
	0, // 153
	0, // 154
	0, // 155
	0, // 156
	0, // 157
	0, // 158
	0, // 159
	0, // 160
	0, // 161
	0, // 162
	0, // 163
	0, // 164
	0, // 165
	0, // 166
	0, // 167
	0, // 168
	0, // 169
	0, // 170
	0, // 171
	0, // 172
	0, // 173
	0, // 174
	0, // 175
	0, // 176
	0, // 177
	0, // 178
	0, // 179
	0, // 180
	0, // 181
	0, // 182
	0, // 183
	0, // 184
	0, // 185
	0, // 186
	0, // 187
	0, // 188
	0, // 189
	0, // 190
	0, // 191
	0, // 192
	0, // 193
	0, // 194
	0, // 195
	0, // 196
	0, // 197
	0, // 198
	0, // 199
	0, // 200
	0, // 201
	0, // 202
	0, // 203
	0, // 204
	0, // 205
	0, // 206
	0, // 207
	0, // 208
	0, // 209
	0, // 210
	0, // 211
	0, // 212
	0, // 213
	0, // 214
	0, // 215
	0, // 216
	0, // 217
	0, // 218
	0, // 219
	0, // 220
	0, // 221
	0, // 222
	0, // 223
	0, // 224
	0, // 225
	0, // 226
	0, // 227
	0, // 228
	0, // 229
	0, // 230
	0, // 231
	0, // 232
	0, // 233
	0, // 234
	0, // 235
	0, // 236
	0, // 237
	0, // 238
	0, // 239
	0, // 240
	0, // 241
	0, // 242
	0, // 243
	0, // 244
	0, // 245
	0, // 246
	0, // 247
	0, // 248
	0, // 249
	0, // 250
	0, // 251
	0, // 252
	0, // 253
	0, // 254
	0, // 255
	0, // 256
	0, // 257
	0, // 258
	0, // 259
	0, // 260
	0, // 261
	0, // 262
	0, // 263
	0, // 264
	0, // 265
	0, // 266
	0, // 267
	0, // 268
	0, // 269
	0, // 270
	0 // 271
};
#endif

HRESULT m_IDirectInputDevice8A::GetDeviceState(DWORD cbData, LPVOID lpvData)
{
	char *buf = reinterpret_cast<char*>(lpvData);

#ifdef DEBUG
	Log() << __func__ << ": received " << cbData << " bytes";
#endif

	/*for (char c: buf) {
		Log() << format("%02x", c);
	}*/

	HRESULT res = ProxyInterface->GetDeviceState(cbData, lpvData);

	// swap action and cancel buttons
	char tmp = buf[BUTTON_CIRCLE];
	buf[BUTTON_CIRCLE] = buf[BUTTON_CROSS];
	buf[BUTTON_CROSS] = tmp;

	// swap mismatched triangle and square buttons
	tmp = buf[BUTTON_TRIANGLE];
	buf[BUTTON_TRIANGLE] = buf[BUTTON_SQUARE];
	buf[BUTTON_SQUARE] = tmp;

	// uncomment to debug data received from joystick
#ifdef VERBOSE_DEBUG
	for (int i = 0; i < cbData; i++) {
		if (my_buf[i] != DONT_OVERRIDE) {
			buf[i] = my_buf[i];
		}
	}
#endif

	return res;
}

HRESULT m_IDirectInputDevice8A::GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags)
{
#ifdef DEBUG
	Log() << __func__;
#endif
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
#ifdef DEBUG
	std::string fmt = getDataFormat(lpdf);

	Log() << __func__ << ": format = " << fmt;
#endif

	return ProxyInterface->SetDataFormat(lpdf);
}

HRESULT m_IDirectInputDevice8A::SetEventNotification(HANDLE hEvent)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->SetEventNotification(hEvent);
}

HRESULT m_IDirectInputDevice8A::SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->SetCooperativeLevel(hwnd, dwFlags);
}

HRESULT m_IDirectInputDevice8A::GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA pdidoi, DWORD dwObj, DWORD dwHow)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->GetObjectInfo(pdidoi, dwObj, dwHow);
}

HRESULT m_IDirectInputDevice8A::GetDeviceInfo(LPDIDEVICEINSTANCEA pdidi)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->GetDeviceInfo(pdidi);
}

HRESULT m_IDirectInputDevice8A::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT m_IDirectInputDevice8A::Initialize(HINSTANCE hinst, DWORD dwVersion, REFGUID rguid)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->Initialize(hinst, dwVersion, rguid);
}

HRESULT m_IDirectInputDevice8A::CreateEffect(REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT * ppdeff, LPUNKNOWN punkOuter)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	HRESULT hr = ProxyInterface->CreateEffect(rguid, lpeff, ppdeff, punkOuter);

	if (SUCCEEDED(hr) && ppdeff)
	{
		*ppdeff = ProxyAddressLookupTable.FindAddress<m_IDirectInputEffect>(*ppdeff);
	}

	return hr;
}

HRESULT m_IDirectInputDevice8A::EnumEffects(LPDIENUMEFFECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwEffType)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->EnumEffects(lpCallback, pvRef, dwEffType);
}

HRESULT m_IDirectInputDevice8A::GetEffectInfo(LPDIEFFECTINFOA pdei, REFGUID rguid)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->GetEffectInfo(pdei, rguid);
}

HRESULT m_IDirectInputDevice8A::GetForceFeedbackState(LPDWORD pdwOut)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->GetForceFeedbackState(pdwOut);
}

HRESULT m_IDirectInputDevice8A::SendForceFeedbackCommand(DWORD dwFlags)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->SendForceFeedbackCommand(dwFlags);
}

HRESULT m_IDirectInputDevice8A::EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl)
{
#ifdef DEBUG
	Log() << __func__;
#endif
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
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->Escape(pesc);
}

HRESULT m_IDirectInputDevice8A::Poll()
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->Poll();
}

HRESULT m_IDirectInputDevice8A::SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->SendDeviceData(cbObjectData, rgdod, pdwInOut, fl);
}

HRESULT m_IDirectInputDevice8A::EnumEffectsInFile(LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->EnumEffectsInFile(lpszFileName, pec, pvRef, dwFlags);
}

HRESULT m_IDirectInputDevice8A::WriteEffectToFile(LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->WriteEffectToFile(lpszFileName, dwEntries, rgDiFileEft, dwFlags);
}

HRESULT m_IDirectInputDevice8A::BuildActionMap(LPDIACTIONFORMATA lpdiaf, LPCSTR lpszUserName, DWORD dwFlags)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->BuildActionMap(lpdiaf, lpszUserName, dwFlags);
}

HRESULT m_IDirectInputDevice8A::SetActionMap(LPDIACTIONFORMATA lpdiActionFormat, LPCSTR lptszUserName, DWORD dwFlags)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->SetActionMap(lpdiActionFormat, lptszUserName, dwFlags);
}

HRESULT m_IDirectInputDevice8A::GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA lpdiDevImageInfoHeader)
{
#ifdef DEBUG
	Log() << __func__;
#endif
	return ProxyInterface->GetImageInfo(lpdiDevImageInfoHeader);
}
