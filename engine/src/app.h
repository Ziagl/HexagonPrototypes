#pragma once

class App : public clan::Application
{
public:
	App();
	bool update() override;

private:
    void init();
    void render();
    void compute();

	clan::DisplayWindow window;
	clan::Canvas canvas;
    bool _quit;
};
