#pragma once

class App : public clan::Application
{
public:
	App();
	bool update() override;

private:
    void on_keyboard(const clan::InputEvent &key);
	void on_mouse(const clan::InputEvent &key);

    void init();
    void render();
    void compute();

    clan::SlotContainer sc;
	clan::DisplayWindow window;
	clan::Canvas canvas;
    
    bool _quit;
    class Map* _map;							// map of tiles
};
