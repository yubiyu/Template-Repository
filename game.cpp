#include "game.h"

bool Game::exit;
bool Game::redraw;

void Game::MainLoop()
{
    while(!exit)
    {
        al_wait_for_event(Event::eventQueue, &Event::event);

        if(Event::event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit = true;

        if(Event::event.type == ALLEGRO_EVENT_KEY_DOWN)
            Keyboard::InputKeydown();

        if(Event::event.type == ALLEGRO_EVENT_KEY_UP)
            Keyboard::InputKeyup();

        if(Event::event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
        {

        }

        if(Event::event.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY)
        {

        }

        if(Event::event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            Mouse::InputMouseXY();
            Mouse::InputMousewheel();
        }

        if(Event::event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            Mouse::InputMouseDown();

        if(Event::event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            Mouse::InputMouseUp();


        if(Event::event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;

            InputSwitchboard();
            LogicSwitchboard();

            Mouse::mouseAxesAltered = false;
        }

        if(redraw && al_is_event_queue_empty(Event::eventQueue))
        {
            DrawingSwitchboard();
        }
    }
}

bool Game::Initialize(char **argv)
{
    exit = false;
    redraw = true;

    srand(time(NULL));

    al_install_system(ALLEGRO_VERSION_INT,NULL);
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    Display::display = al_create_display(Display::WIDTH, Display::HEIGHT);
    Time::FPSTimer = al_create_timer(1.0/Time::FPS);
    Event::eventQueue = al_create_event_queue();

    al_register_event_source(Event::eventQueue, al_get_display_event_source(Display::display));
    al_register_event_source(Event::eventQueue, al_get_timer_event_source(Time::FPSTimer));
    al_register_event_source(Event::eventQueue, al_get_keyboard_event_source());
    al_register_event_source(Event::eventQueue, al_get_mouse_event_source());

    if(!Resource::Initialize(argv))
    {
        assert("Resource : Initialization failed");
        return false;
    }

    Palette::Initialize();
    Scene::Initialize();

    Camera::Initialize();
    Camera::SetCell(0, 0);
    Camera::WarpToDestination();

    al_start_timer(Time::FPSTimer);

    return true;
}

void Game::Uninitialize()
{

    Camera::Uninitialize();
    Resource::Uninitialize();

    al_uninstall_audio();
    al_destroy_display(Display::display);
    al_destroy_timer(Time::FPSTimer);
    al_destroy_event_queue(Event::eventQueue);
    al_uninstall_system();

}


void Game::InputSwitchboard()
{
    Keyboard::InputKeyHold();
    Mouse::InputMouseButtonHold();

    switch(Scene::inputContext)
    {
    case Scene::INPUT_CONTEXT_TESTING:
        TestingInput();
        break;
    case Scene::INPUT_CONTEXT_TITLE:
        TitleInput();
        break;
    case Scene::INPUT_CONTEXT_SETTINGS:
        SettingsInput();
        break;
    case Scene::INPUT_CONTEXT_OVERWORLD:
        OverworldInput();
        break;
    }
}

void Game::TestingInput()
{
    if(Mouse::mousewheelInput[Mouse::MOUSEWHEEL_UP])
    {
        al_set_mouse_z(0);
    }
    else if(Mouse::mousewheelInput[Mouse::MOUSEWHEEL_DOWN])
    {
        al_set_mouse_z(0);
    }
    else if(Mouse::mouseInput[Mouse::MOUSE_MIDDLE])
    {

    }

    if(Mouse::mouseButtonHoldTicks[Mouse::MOUSE_LEFT] == 1)
    {

    }

    if(Keyboard::keyHoldTicks[Keyboard::KEY_LEFT] >= 1)
    {
        Camera::xPosition -= 4;
    }
    if(Keyboard::keyHoldTicks[Keyboard::KEY_RIGHT] >= 1)
    {
        Camera::xPosition += 4;
    }
    if(Keyboard::keyHoldTicks[Keyboard::KEY_UP] >= 1)
    {
        Camera::yPosition -= 4;
    }
    if(Keyboard::keyHoldTicks[Keyboard::KEY_DOWN] >= 1)
    {
        Camera::yPosition += 4;
    }

    if(Keyboard::keyHoldTicks[Keyboard::KEY_J] == 1)
    {
        al_play_sample_instance(Resource::genericLaserShootSampleInstance);
    }

    if(Keyboard::keyHoldTicks[Keyboard::KEY_K] == 1)
    {
        if(al_get_sample_instance_playing(Resource::genericBgmSampleInstance))
            al_stop_sample_instance(Resource::genericBgmSampleInstance);
        else
        {
            al_set_sample_instance_playmode(Resource::genericBgmSampleInstance, ALLEGRO_PLAYMODE_LOOP);
            al_play_sample_instance(Resource::genericBgmSampleInstance);
        }
    }

    if(Keyboard::keyHoldTicks[Keyboard::KEY_ENTER] == 1)
    {
        Scene::ChangeScene(Scene::SCENE_TITLE);
    }
}

void Game::TitleInput()
{

}

void Game::SettingsInput()
{

}

void Game::OverworldInput()
{

}

void Game::LogicSwitchboard()
{
    switch(Scene::scene)
    {
    case Scene::SCENE_TESTING_NOSCENE:
        TestingNosceneLogic();
        break;
    case Scene::SCENE_TITLE:
        TitleSceneLogic();
        break;
    case Scene::SCENE_SETTINGS:
        SettingsSceneLogic();
        break;
    case Scene::SCENE_OVERWORLD:
        OverworldSceneLogic();
        break;
    }
}

void Game::TestingNosceneLogic()
{

}

void Game::TitleSceneLogic()
{

}

void Game::SettingsSceneLogic()
{

}

void Game::OverworldSceneLogic()
{

}

void Game::DrawingSwitchboard()
{
    Game::redraw = false;
    al_clear_to_color(COLKEY_BACKGROUND);

    switch(Scene::scene)
    {
    case Scene::SCENE_TESTING_NOSCENE:
        TestingNosceneDrawing();
        break;
    case Scene::SCENE_TITLE:
        TitleSceneDrawing();
        break;
    case Scene::SCENE_SETTINGS:
        SettingsSceneDrawing();
        break;
    case Scene::SCENE_OVERWORLD:
        OverworldSceneDrawing();
        break;
    }

    al_flip_display();
}

void Game::TestingNosceneDrawing()
{
    DrawDebugGrid();
    DrawDebugGridCameraCrosshair();
    DrawDebugGridText();

    al_draw_multiline_text(Resource::builtin8, COLKEY_TEXT_LIGHT, Display::WIDTH, 0, 600, 16, ALLEGRO_ALIGN_RIGHT,
                           "<Enter> to proceed to title.\n<UDLR> to test camera.\n<J> to test SFX.\n<K> to toggle test BGM.");
}

void Game::TitleSceneDrawing()
{

}

void Game::SettingsSceneDrawing()
{

}

void Game::OverworldSceneDrawing()
{

}

void Game::DrawDebugGrid()
{
    for(int x = 0; x <= Display::WIDTH / Tile::WIDTH; x++) //Columns
    {
        al_draw_line(x*Tile::WIDTH - (int)Camera::xPosition%(int)Tile::HEIGHT,
                     0,
                     x*Tile::WIDTH  - (int)Camera::xPosition%(int)Tile::HEIGHT,
                     Display::HEIGHT,
                     COLKEY_GRID,1);
    }

    for(int y = 0; y <= Display::HEIGHT / Tile::HEIGHT; y++) //Rows
    {
        al_draw_line(0,
                     y*Tile::WIDTH  - (int)Camera::yPosition%(int)Tile::HEIGHT,
                     Display::WIDTH,
                     y*Tile::WIDTH  - (int)Camera::yPosition%(int)Tile::HEIGHT,
                     COLKEY_GRID,1);
    }
}



void Game::DrawDebugGridCameraCrosshair()
{
    al_draw_line(Display::WIDTH/2, 0, Display::WIDTH/2, Display::HEIGHT, COLKEY_CAMERA_CROSSHAIR_LOCKED, 1);
    al_draw_line(0, Display::HEIGHT/2, Display::WIDTH, Display::HEIGHT/2, COLKEY_CAMERA_CROSSHAIR_LOCKED, 1);
}



void Game::DrawDebugGridText()//float mouseTransformedX, float mouseTransformedY
{
    int camXPos = Camera::xPosition;
    int camYPos = Camera::yPosition;

    int camXCell = std::round(camXPos/Tile::WIDTH);
    int camYCell = std::round(camYPos/Tile::HEIGHT);

    int zoomPercentage = Camera::zoomScale*100;

    std::string cameraPositionString = "Crosshair position: (" + std::to_string(camXPos) + ", " + std::to_string(camYPos) + ") : ("
                                       + std::to_string(camXCell) + ", " + std::to_string(camYCell) + ") "
                                       + std::to_string(zoomPercentage) + "% zoom";

    Hax::string_al_draw_text(Resource::builtin8,COLKEY_CAMERA_CROSSHAIR_LOCKED,0,0,ALLEGRO_ALIGN_LEFT,cameraPositionString);

}
