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

void genericQueryInterface(REFIID riid, LPVOID * ppvObj)
{
	if (!ppvObj || !*ppvObj)
	{
		return;
	}

	Log() << "genericQueryInterface, riid = " << GetNameOfRefIID(riid) <<
		" IID_IDirectInput8A = " << GetNameOfRefIID(IID_IDirectInput8A);

#define QUERYINTERFACE(x) \
	if (riid == IID_ ## x) \
		{ \
			*ppvObj = ProxyAddressLookupTable.FindAddress<m_ ## x>(*ppvObj); \
			Log() << "riid matched " << GetNameOfRefIID(IID_## x); \
		} else { Log() << "riid didn't match " << GetNameOfRefIID(IID_## x); }

#define CREATEINTERFACE(x) \
	if (riid == IID_ ## x) \
		{ \
			*ppvObj = new m_ ## x((x*)*ppvObj); \
		}

	QUERYINTERFACE(IDirectInput8W);
	QUERYINTERFACE(IDirectInput8A);
	QUERYINTERFACE(IDirectInputDevice8A);
	QUERYINTERFACE(IDirectInputDevice8W);
	QUERYINTERFACE(IDirectInputEffect);

	CREATEINTERFACE(IClassFactory);
}
