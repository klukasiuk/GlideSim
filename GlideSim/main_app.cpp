#include "main_app.h"

#include "core.h"


MainApplication::MainApplication()
{
	run = true;
}


void MainApplication::start()							// Start method is also main loop
{
	init();

	while (run)
	{
		input();

		update();

		render();

		timer();
	}

	release();
}

void MainApplication::stop()
{
	run = false;
}


void MainApplication::init()
{
	string app_build = app_name + "_" + version;

	logger::init(app_build);
	logger::msg("Initialization start");

	srand((unsigned int)271304271304);
	//srand((unsigned int)time(NULL));

	// Core init

	core::configLoader.load("config.txt");

	core::simpleWindow.initWindow(window_width, window_height, (char *)app_build.c_str());

	core::simpleWindow.initOGL();

	core::renderer.init();

	// Timers init

	fpsCounter.start();

	fpsGovernor.setLimit(30);
	fpsGovernor.start();

	logger::logSystemInfo();
	logger::msg("Initializing done");
}

void MainApplication::release()
{
	logger::msg("Exiting ...");


	core::simpleWindow.closeWindow();

	core::renderer.release();


	logger::release();

	exit(EXIT_SUCCESS);
}

void MainApplication::input()
{
	glfwPollEvents();

	core::inputHandler.process_input();

	if (core::simpleWindow.shouldClose())
		run = false;
}

void MainApplication::update()
{
	core::renderer.update();
}

void MainApplication::render()
{
	core::renderer.draw();

	core::simpleWindow.swapBuffer();
}

void MainApplication::timer()
{
	fpsCounter.frameTick();
	fpsGovernor.frameTick();

	//logger::msg("Fps = " + std::to_string(fpsCounter.getFPS()));
	//printf("FPS = %lf\n", fpsCounter.getFPS());

	//sleep(33);
}