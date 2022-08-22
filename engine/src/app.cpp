#include "precomp.h"
#include "app.h"

clan::ApplicationInstance<App> clanapp;

App::App()
{
#if defined(WIN32)
	clan::D3DTarget::set_current();
#else
	clan::OpenGLTarget::set_current();
#endif

	// set the window
	clan::DisplayWindowDescription desc;
	desc.set_title("Engine");

	desc.set_size(clan::Sizef(800, 600), true);
	desc.set_allow_resize(true);

	window = clan::DisplayWindow(desc);
	canvas = clan::Canvas(window);

	// connect the window close event
	//sc.connect(window.sig_window_close(), [&]() {_quit = true; });

	// connect a keyboard handler to on_key_up()
	//sc.connect(window.get_keyboard().sig_key_up(), clan::bind_member(this, &App::on_keyboard));

	// connect a mouse handler (only for example it is not used)
	//sc.connect(window.get_mouse().sig_key_down(), this, &App::on_mouse);
	//sc.connect(window.get_mouse().sig_key_dblclk(), this, &App::on_mouse);

	_quit = false;
	srand(static_cast<int>(time(0)));	// initialize random number generator

	init();		//initialize
}

bool App::update()
{
	// clear display with black background
	canvas.clear(clan::Colorf(0.0f, 0.0f, 0.0f));

	render();

	window.flip(1);

	return !_quit;
}

void App::init(void)
{
	
} // init

void App::render(void)
{
	
} // render

void App::compute()
{

} // compute
