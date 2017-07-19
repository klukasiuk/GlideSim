#pragma once

#include "simple_window.h"
#include "logger.h"

#include "config_loader.h"
#include "asset_manager.h"
#include "renderer.h"

namespace core
{
	ConfigLoader configLoader;

	AssetManager assetManager;

	Renderer renderer;
}