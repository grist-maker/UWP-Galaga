#pragma once

// Use the C++ standard templated min/max
#define NOMINMAX

// Windows
#include <wrl/client.h>

// Standard
#include <memory>
#include <string>
#include <cstdint>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <future>
#include <iomanip>

// C++/WinRT
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.ApplicationModel.h"
#include "winrt/Windows.ApplicationModel.Core.h"
#include "winrt/Windows.ApplicationModel.Activation.h"
#include "winrt/Windows.Foundation.h"
#include "winrt/Windows.Graphics.Display.h"
#include "winrt/Windows.System.h"
#include "winrt/Windows.UI.Core.h"
#include "winrt/Windows.UI.Input.h"
#include "winrt/Windows.UI.ViewManagement.h"

// DirectX
#include <d3d11_4.h>
#include <wincodec.h>

#if defined(NTDDI_WIN10_RS2)
#include <dxgi1_6.h>
#else
#include <dxgi1_5.h>
#endif

#include <pix.h>

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