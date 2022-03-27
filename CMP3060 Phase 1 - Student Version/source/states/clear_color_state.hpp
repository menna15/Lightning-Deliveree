#pragma once

#include <application.hpp>

class ClearColorState : public our::State
{
// those variables will be used within the class methods only.
private:
    GLfloat r = 0.0;
    GLfloat g = 0.0;
    GLfloat b = 0.0;
    GLfloat a = 0.0;
    
public:
    // onInitialize() function is called once before the state starts
    void onInitialize() override
    {
        // TODO: Read the color from the configuration file and use it to set the clear color for the window
        // HINT: you can the configuration for the whole application using "getApp()->getConfig()"
        // To see how the clear color is written in the json files, see "config/blue-screen.json"
        // To know how read data from a nlohmann::json object,
        // look at the following documentation: https://json.nlohmann.me/features/element_access/

        const nlohmann::json &clearColor = getApp()->getConfig().at("scene").at("clear-color");  // read the clear color from app.config 
        // store each channel value in its specified variable.
        r = clearColor.at("r");  
        g = clearColor.at("g");
        b = clearColor.at("b");
        a = clearColor.at("a");
    }

    // onDraw(deltaTime) function is called every frame
    void onDraw(double deltaTime) override
    {
        // At the start of frame we want to clear the screen. Otherwise we would still see the results from the previous frame.
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }
};