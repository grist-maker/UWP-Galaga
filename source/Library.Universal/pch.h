#pragma once

// Standard
#include <memory>
#include <string>
#include <cstdint>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <map>
#include <iomanip>

// Windows
#include <wrl/client.h>

// C++/WinRT
#include "winrt/Windows.UI.Xaml.Markup.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Input.h>

// DirectX
#include <d3d11_4.h>
#include <wincodec.h>

#if defined(NTDDI_WIN10_RS2)
#include <dxgi1_6.h>
#else
#include <dxgi1_5.h>
#endif

#ifdef _DEBUG
#include <dxgidebug.h>
#endif

#include <DirectXColors.h>
#include <DirectXMath.h>
#include <DirectXTK\DDSTextureLoader.h>
#include <DirectXTK\WICTextureLoader.h>
#include <DirectXTK\SpriteBatch.h>
#include <DirectXTK\SpriteFont.h>
#include <DirectXTK\GamePad.h>
#include <DirectXTK\Keyboard.h>
#include <DirectXTK\Mouse.h>

#include "DirectXHelper.h"