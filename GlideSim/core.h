#pragma once

#include "simple_window.h"
#include "logger.h"

#include "config_loader.h"
#include "asset_manager.h"
#include "renderer.h"
#include "input_handler.h"


namespace core
{
	extern SimpleWindow simpleWindow;

	extern InputHandler inputHandler;

	extern ConfigLoader configLoader;

	extern AssetManager assetManager;

	extern Renderer renderer;
}