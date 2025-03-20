// Copyright 2024-2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

// If nothing has been configured, default to enabling all effects and palettes.
#if !( \
    __has_include("palettefx_user.inc") \
    || defined(PALETTEFX_ENABLE_ALL_EFFECTS) \
    || defined(PALETTEFX_ENABLE_ALL_PALETTES) \
    || defined(PALETTEFX_GRADIENT_ENABLE) \
    || defined(PALETTEFX_FLOW_ENABLE) \
    || defined(PALETTEFX_RIPPLE_ENABLE) \
    || defined(PALETTEFX_SPARKLE_ENABLE) \
    || defined(PALETTEFX_VORTEX_ENABLE) \
    || defined(PALETTEFX_REACTIVE_ENABLE) \
    || defined(PALETTEFX_AFTERBURN_ENABLE) \
    || defined(PALETTEFX_AMBER_ENABLE) \
    || defined(PALETTEFX_BADWOLF_ENABLE) \
    || defined(PALETTEFX_CARNIVAL_ENABLE) \
    || defined(PALETTEFX_CLASSIC_ENABLE) \
    || defined(PALETTEFX_DRACULA_ENABLE) \
    || defined(PALETTEFX_GROOVY_ENABLE) \
    || defined(PALETTEFX_NOTPINK_ENABLE) \
    || defined(PALETTEFX_PHOSPHOR_ENABLE) \
    || defined(PALETTEFX_POLARIZED_ENABLE) \
    || defined(PALETTEFX_ROSEGOLD_ENABLE) \
    || defined(PALETTEFX_SPORT_ENABLE) \
    || defined(PALETTEFX_SYNTHWAVE_ENABLE) \
    || defined(PALETTEFX_THERMAL_ENABLE) \
    || defined(PALETTEFX_VIRIDIS_ENABLE) \
    || defined(PALETTEFX_WATERMELON_ENABLE) \
)
#define PALETTEFX_ENABLE_ALL_EFFECTS
#define PALETTEFX_ENABLE_ALL_PALETTES
#endif

