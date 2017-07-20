#pragma once

#include "simple_window.h"
#include "logger.h"

#include "config_loader.h"
#include "asset_manager.h"
#include "renderer.h"


namespace core
{
	extern SimpleWindow simpleWindow;

	extern ConfigLoader configLoader;

	extern AssetManager assetManager;

	extern Renderer renderer;
}