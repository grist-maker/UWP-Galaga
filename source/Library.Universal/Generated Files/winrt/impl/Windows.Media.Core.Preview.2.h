// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.220608.4

#pragma once
#ifndef WINRT_Windows_Media_Core_Preview_2_H
#define WINRT_Windows_Media_Core_Preview_2_H
#include "winrt/impl/Windows.Foundation.1.h"
#include "winrt/impl/Windows.Media.Core.Preview.1.h"
WINRT_EXPORT namespace winrt::Windows::Media::Core::Preview
{
    struct SoundLevelBroker
    {
        SoundLevelBroker() = delete;
        [[nodiscard]] static auto SoundLevel();
        static auto SoundLevelChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable> const& handler);
        using SoundLevelChanged_revoker = impl::factory_event_revoker<winrt::Windows::Media::Core::Preview::ISoundLevelBrokerStatics, &impl::abi_t<winrt::Windows::Media::Core::Preview::ISoundLevelBrokerStatics>::remove_SoundLevelChanged>;
        [[nodiscard]] static auto SoundLevelChanged(auto_revoke_t, winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable> const& handler);
        static auto SoundLevelChanged(winrt::event_token const& token);
    };
}
#endif
