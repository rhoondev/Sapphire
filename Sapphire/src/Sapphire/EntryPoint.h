#pragma once

extern Sapphire::Application *Sapphire::CreateApplication();

int main(int argc, char **argv)
{
    Sapphire::Application *app = Sapphire::CreateApplication();
    app->Run();
    delete app;
}