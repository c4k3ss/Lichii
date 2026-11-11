// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "common/common_types.h"

namespace Settings {

inline constexpr u64 MarioKartWorldProgramId = 0x0400C3F00006E000ULL;

// The Duskbloods network test (0400D1D02399A000) needs these whatever the saved settings say:
// the LLE error applet crashes the emulator on the game's first error dialog, handheld mode
// changes its memory layout and render targets, and GPU Fast with asynchronous shaders is the
// difference between 60 fps and 30. They apply to the session only; nothing is written back.
inline constexpr u64 DuskbloodsNetworkTestProgramId = 0x0400D1D02399A000ULL;

inline bool ApplyDuskbloodsPreset(Values& settings, u64 program_id) {
    if (program_id != DuskbloodsNetworkTestProgramId) {
        return false;
    }
    const auto session = [](auto& setting, auto value) {
        setting.SetGlobal(false);
        setting.SetValue(value);
    };
    session(settings.renderer_backend, RendererBackend::Vulkan);
    session(settings.error_applet_mode, AppletMode::HLE);
    session(settings.use_docked_mode, ConsoleMode::Docked);
    session(settings.gpu_accuracy, GpuAccuracy::Low);
    session(settings.use_asynchronous_shaders, true);
    session(settings.async_presentation, false);
    session(settings.vsync_mode, VSyncMode::Mailbox);
    return true;
}

} // namespace Settings
