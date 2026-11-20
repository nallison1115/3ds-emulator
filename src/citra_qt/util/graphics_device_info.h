// Copyright 2023 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the misc/licenses/gplv2.txt file included.

#pragma once

#include <vector>
#include <QString>
#include "common/common_types.h"

#ifdef ENABLE_OPENGL
/// Returns the name of the OpenGL renderer.
QString GetOpenGLRenderer();
#endif

#ifdef ENABLE_VULKAN
/// Returns a list of all available vulkan GPUs.
std::vector<QString> GetVulkanPhysicalDevices();

/// Returns the requested GPU index, or the best hardware GPU if the requested one is a
/// software (CPU) renderer or doesn't exist.
u32 GetPreferredVulkanPhysicalDevice(u32 requested);
#endif
