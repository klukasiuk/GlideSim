#include "main_app.h"
#include "core.h"

string app_name = "GlideSim";

int window_width  = 640;
int window_height = 480;

MainApplication::MainApplication()
{
	run = true;
}


void MainApplication::start()
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


void MainApplication::init()
{
	logger::init();

	srand((unsigned int)time(NULL));

	core::simpleWindow.initWindow(window_width, window_height, (char *)app_name.c_str());

	core::simpleWindow.initOGL();

	fpsCounter.Start();

	fpsGovernor.setLimit(30);
	fpsGovernor.Start();

	core::renderer.init();


	logger::logSystemInfo();

	logger::msg("Initializing done");
}

void MainApplication::release()
{
	logger::msg("Exiting ...", logger::info);

	core::simpleWindow.closeWindow();

	core::renderer.release();

	exit(EXIT_SUCCESS);
}

void MainApplication::input()
{
	glfwPollEvents();

	inputHandler.process_input();

	if (core::simpleWindow.shouldClose())
		run = false;
}

void MainApplication::update()
{
	fpsCounter.frameTick();
	fpsGovernor.frameTick();

	core::renderer.update();

	//logger::msg("Fps = " + std::to_string(fpsCounter.getFPS()));
	//printf("FPS = %lf\n", fpsCounter.getFPS());
}

void MainApplication::render()
{
	core::renderer.draw();

	core::simpleWindow.swapBuffer();
}

void MainApplication::timer()
{
	//sleep(33);
}