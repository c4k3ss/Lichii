// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "common/settings.h"

namespace Settings {

inline constexpr u64 MarioKartWorldProgramId = 0x0400C3F00006E000ULL;

inline void SetMarioKartWorldRecommendedSettings(Values& settings, bool global) {
    const auto session = [global](auto& setting, auto value) {
        setting.SetGlobal(global);
        setting.SetValue(value);
    };
    session(settings.renderer_backend, RendererBackend::Vulkan);
    session(settings.resolution_setup, ResolutionSetup::Res1X);
    session(settings.gpu_accuracy, GpuAccuracy::Low);
    session(settings.use_asynchronous_shaders, true);
    session(settings.astc_recompression, AstcRecompression::Bc3);
    session(settings.vram_usage_mode, VramUsageMode::Conservative);
    session(settings.use_reactive_flushing, false);
    session(settings.vsync_mode, VSyncMode::FifoRelaxed);
    session(settings.use_docked_mode, ConsoleMode::Handheld);
    session(settings.scaling_filter, ScalingFilter::ScaleForce);
    session(settings.anti_aliasing, AntiAliasing::Fxaa);
}

inline bool ApplyMarioKartWorldPreset(Values& settings, u64 program_id, bool accepted) {
    if (!accepted || program_id != MarioKartWorldProgramId) {
        return false;
    }
    SetMarioKartWorldRecommendedSettings(settings, false);
    return true;
}

// The Duskbloods network test (0400D1D02399A000) needs these whatever the saved settings say:
// the LLE error applet crashes the emulator on the game's first error dialog, handheld mode
// changes its memory layout and render targets, and GPU Fast with asynchronous shaders is the
// difference between 60 fps and 30. They apply to the session only; nothing is written back.
inline constexpr u64 DuskbloodsNetworkTestProgramId = 0x0400D1D02399A000ULL;

inline void SetDuskbloodsRequiredSettings(Values& settings) {
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
}

inline bool ApplyDuskbloodsPreset(Values& settings, u64 program_id) {
    if (program_id != DuskbloodsNetworkTestProgramId) {
        return false;
    }
    SetDuskbloodsRequiredSettings(settings);
    return true;
}

} // namespace Settings
