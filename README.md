### Hacks for "The Legend of Heroes: Trails of Cold Steel" game

### Introduction

A very long story short: while it's the common practice for games to use the button (X) for the
action and (O) for the cancel, TLoH's English game version forces to use a different setup
(O - action, X - cancel).

(Read more here: https://steamcommunity.com/app/538680/discussions/0/1471967615842855904/, http://www.xseedgames.com/forum/index.php?threads/trails-of-cold-steel-coming-to-pc-this-summer.29219/page-20)

This repository is introducing a hack allowing to swap these buttons.

### Downloads

Downloads here: https://github.com/ChronoMonochrome/DirectX_Hacks_for_TLoH/releases

### How to:

Download dinput8.zip and unpack to the game folder.
Now "X" and "O" buttons will be swapped in the game.

### Known issues:

A hardcoded joystick GUID is used.
```
DEFINE_GUID(GUID_Joystick2, 0xD8C36BF0, 0x6A94, 0x11E8, 0x80, 0x02, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
```

This repository is not tested on a different joysticks than this GUID.

### Credits
Bases on [DirectX-Wrappers](https://github.com/elishacloud/DirectX-Wrappers) repository:

### License

Copyright (C) 2019 Elisha Riedlinger

This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
authors be held liable for any damages arising from the use of this software.
Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
applications, and to alter it and redistribute it freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
      original  software. If you use this  software  in a product, an  acknowledgment in the product
      documentation would be appreciated but is not required.
   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
      being the original software.
   3. This notice may not be removed or altered from any source distribution.

Code in this project is taken from:
- [Jari Komppa's dxwrapper](https://github.com/jarikomppa/dxwrapper)
- [d3d8to9](https://github.com/crosire/d3d8to9)
- [Direct3D9 Wrapper DLL](https://gist.github.com/shaunlebron/3854bf4eec5bec297907)
- [DirectSoundControl](https://github.com/nRaecheR/DirectSoundControl)
- [XWA hooks](https://github.com/JeremyAnsel/xwa_hooks/tree/master/DInputLogger)

### Development

Development was done in C++ using Microsoft Visual Studio Community 2017.
