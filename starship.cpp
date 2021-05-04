//
//  main.cpp
//  spaceshipshooter
//
//  Created by Logan Hoelscher on 12/2/19.
//  Copyright © 2019 Logan Hoelscher. All rights reserved.
//

#include <iostream>

// GLEW
#define GLEW_STATIC
#include <glew.h>

// GLFW
#include <glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "gtc/type_ptr.hpp"



// Other includes
#include "Shader.h"
#include "Camera.h"
#include "matrix.hpp"
#include "vec3.hpp"
#include "mat4x4.hpp"

void drawStuff();


// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

glm::vec3 carPos(0.0f, 3.0f, 0.0f);
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));


// The MAIN function, from here we start the application and run the game loop
int main()
{
    // Init GLFW
    glfwInit();

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Space Ship Racer", nullptr, nullptr);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);

    





    


    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        carPos.y -= 0.03f;

        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        //glUniformMatrix4fv(objectToWorldUniformLocation, 1, GL_FALSE, glm::value_ptr(mvp));

       // Render
       // Clear the colorbuffer
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawStuff();

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    // Properly de-allocate all resources once they've outlived their purpose
   // glDeleteVertexArrays(1, &VAO);
   // glDeleteBuffers(1, &VBO);


    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();

    return EXIT_SUCCESS;
}

void drawStuff()
{
    // Build and compile our shader program
    Shader ourShader("core.vert", "core.frag");
    Shader lightingShader("lightingShader.vert", "lightingShader.frag");
    Shader lampShader("lampShader.vert", "lampShader.frag");

    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] =
    {
        // Positions         // Colors
        0.2f, -0.8f, 0.0f,   0.4f, 0.4f, 0.4f,  // Bottom Right
        -0.2f, -0.8f, 0.0f,   0.4f, 0.4f, 0.4f,  // Bottom Left
        0.0f,  -0.4f, 0.0f,   1.0f, 1.0f, 1.0f,   // Top

        -0.2f, -0.8f, 0.0f,     0.35f, 0.35f, 0.67f,
        -0.1f, -1.0f, 0.0f,     1.0f, 1.0f, 1.0f,
        0.0f, -0.8f, 0.0f,      0.35f, 0.35f, 0.67f,

        0.0f, -0.8f, 0.0f,     0.35f, 0.35f, 0.67f,
        0.1f, -1.0f, 0.0f,      1.0f, 1.0f, 1.0f,
        0.2f, -0.8f, 0.0f,      0.35f, 0.35f, 0.67f

    };

    GLfloat walls[] =
    {
        //left wall
        -0.6f, 1.0f, 0.0f,    0.2f, 0.2f, 0.2f,
        -0.6f, -1.0f, 0.0f,     0.5f, 0.5f, 0.5f,
        -2.0f, -1.0f, 0.0f,     0.5f, 0.5f, 0.5f,

        -2.0f, -1.0f, 0.0f,     0.5f, 0.5f, 0.5f,
        -2.0f, 1.0f, 0.0f,    0.2f, 0.5f, 0.5f,
        -0.6f, 1.0f, 0.0f,    0.2f, 0.2f, 0.2f,

        //right wall
        0.6f, 1.0f, 0.0f,    0.2f, 0.2f, 0.2f,
        0.6f, -1.0f, 0.0f,     0.5f, 0.5f, 0.5f,
        2.0f, -1.0f, 0.0f,     0.5f, 0.5f, 0.5f,

        2.0f, -1.0f, 0.0f,     0.5f, 0.5f, 0.5f,
        2.0f, 1.0f, 0.0f,    0.2f, 0.2f, 0.2f,
        0.6f, 1.0f, 0.0f,    0.2f, 0.2f, 0.2f


    };

    //wave 1
    GLfloat car[] =
    {
        0.0f, 3.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        -0.1f, 3.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.1f, 3.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    GLfloat car1[] =
    {
        -0.4f, 3.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        -0.5f, 3.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        -0.3f, 3.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    //wave 2
    GLfloat car2[] =
    {
        0.0f, 4.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        -0.1f, 4.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.1f, 4.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    GLfloat car3[] =
    {
        0.4f, 4.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        0.5f, 4.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.3f, 4.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    // wave 3
    GLfloat car4[] =
    {
        -0.4f, 5.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        -0.5f, 5.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        -0.3f, 5.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    GLfloat car5[] =
    {
        0.4f, 5.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        0.5f, 5.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.3f, 5.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    //wave 4
    GLfloat car6[] =
    {
        0.0f, 6.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        -0.1f, 6.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.1f, 6.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    //wave 5
    GLfloat car7[] =
    {
        -0.4f, 7.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        -0.5f, 7.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        -0.3f, 7.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    //wave 6
    GLfloat car8[] =
    {
        0.4f, 8.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        0.5f, 8.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.3f, 8.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    //wave 7
    GLfloat car9[] =
    {
        0.0f, 9.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        -0.1f, 9.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.1f, 9.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    GLfloat car10[] =
    {
        -0.4f, 9.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        -0.5f, 9.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        -0.3f, 9.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    //wave 8
    GLfloat car11[] =
    {
        0.0f, 10.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        -0.1f, 10.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.1f, 10.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    GLfloat car12[] =
    {
        0.4f, 10.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        0.5f, 10.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.3f, 10.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    //wave 9
    GLfloat car13[] =
    {
        -0.4f, 11.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        -0.5f, 11.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        -0.3f, 11.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    GLfloat car14[] =
    {
        0.4f, 11.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        0.5f, 11.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.3f, 11.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    //wave 10
    GLfloat car15[] =
    {
        0.0f, 12.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        -0.1f, 12.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.1f, 12.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    //wave 11
    GLfloat car16[] =
    {
        0.0f, 13.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        -0.1f, 13.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.1f, 13.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    GLfloat car17[] =
    {
        0.4f, 13.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        0.5f, 13.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.3f, 13.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    //wave 12
    GLfloat car18[] =
    {
        -0.4f, 14.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        -0.5f, 14.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        -0.3f, 14.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };
    GLfloat car19[] =
    {
        0.0f, 14.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        -0.1f, 14.2f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.1f, 14.2f, 0.0f,    0.0f, 0.0f, 1.0f
    };

    GLfloat fin[] =
    {
        -0.6f, 15.0f, 0.0f,      0.0f, 0.0f, 1.0f,
        -0.6f, 15.4f, 0.0f,      0.0f, 0.0f, 1.0f,
        0.6f, 15.0f, 0.0f,       0.0f, 0.0f, 1.0f,

        -0.6f, 15.4f, 0.0f,      0.0f, 0.0f, 1.0f,
        0.6f, 15.4f, 0.0f,      0.0f, 0.0f, 1.0f,
        0.6f, 15.0f, 0.0f,       0.0f, 0.0f, 1.0f

    };



    glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);



    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint wallVBO, wallVAO;
    glGenVertexArrays(1, &wallVAO);
    glGenBuffers(1, &wallVBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(wallVAO);

    glBindBuffer(GL_ARRAY_BUFFER, wallVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(walls), walls, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint carVBO, carVAO;
    glGenVertexArrays(1, &carVAO);
    glGenBuffers(1, &carVBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(carVAO);

    glBindBuffer(GL_ARRAY_BUFFER, carVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car), car, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car1VBO, car1VAO;
    glGenVertexArrays(1, &car1VAO);
    glGenBuffers(1, &car1VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car1VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car1VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car1), car1, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car2VBO, car2VAO;
    glGenVertexArrays(1, &car2VAO);
    glGenBuffers(1, &car2VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car2VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car2VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car2), car2, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car3VBO, car3VAO;
    glGenVertexArrays(1, &car3VAO);
    glGenBuffers(1, &car3VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car3VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car3VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car3), car3, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car4VBO, car4VAO;
    glGenVertexArrays(1, &car4VAO);
    glGenBuffers(1, &car4VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car4VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car4VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car4), car4, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car5VBO, car5VAO;
    glGenVertexArrays(1, &car5VAO);
    glGenBuffers(1, &car5VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car5VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car5VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car5), car5, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car6VBO, car6VAO;
    glGenVertexArrays(1, &car6VAO);
    glGenBuffers(1, &car6VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car6VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car6VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car6), car6, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car7VBO, car7VAO;
    glGenVertexArrays(1, &car7VAO);
    glGenBuffers(1, &car7VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car7VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car7VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car7), car7, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car8VBO, car8VAO;
    glGenVertexArrays(1, &car8VAO);
    glGenBuffers(1, &car8VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car8VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car8VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car8), car8, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car9VBO, car9VAO;
    glGenVertexArrays(1, &car9VAO);
    glGenBuffers(1, &car9VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car9VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car9VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car9), car9, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car10VBO, car10VAO;
    glGenVertexArrays(1, &car10VAO);
    glGenBuffers(1, &car10VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car10VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car10VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car10), car10, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car11VBO, car11VAO;
    glGenVertexArrays(1, &car11VAO);
    glGenBuffers(1, &car11VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car11VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car11VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car11), car11, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car12VBO, car12VAO;
    glGenVertexArrays(1, &car12VAO);
    glGenBuffers(1, &car12VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car12VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car12VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car12), car12, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car13VBO, car13VAO;
    glGenVertexArrays(1, &car13VAO);
    glGenBuffers(1, &car13VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car13VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car13VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car13), car13, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car14VBO, car14VAO;
    glGenVertexArrays(1, &car14VAO);
    glGenBuffers(1, &car14VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car14VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car14VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car14), car14, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car15VBO, car15VAO;
    glGenVertexArrays(1, &car15VAO);
    glGenBuffers(1, &car15VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car15VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car15VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car15), car15, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car16VBO, car16VAO;
    glGenVertexArrays(1, &car16VAO);
    glGenBuffers(1, &car16VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car16VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car16VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car16), car16, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint car17VBO, car17VAO;
    glGenVertexArrays(1, &car17VAO);
    glGenBuffers(1, &car17VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(car17VAO);

    glBindBuffer(GL_ARRAY_BUFFER, car17VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(car17), car17, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    GLuint finVBO, finVAO;
    glGenVertexArrays(1, &finVAO);
    glGenBuffers(1, &finVBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(finVAO);

    glBindBuffer(GL_ARRAY_BUFFER, finVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fin), fin, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



     /***************************** original car ***********************************/
        // Use cooresponding shader when setting uniforms/drawing objects
    lightingShader.Use();
    GLint objectColorLoc = glGetUniformLocation(lightingShader.Program, "objectColor");
    GLint lightColorLoc = glGetUniformLocation(lightingShader.Program, "lightColor");
    GLint carPosLoc = glGetUniformLocation(lightingShader.Program, "carPos");
    GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
    glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
    glUniform3f(lightColorLoc, 1.0f, 0.0f, 0.0f);
    glUniform3f(carPosLoc, carPos.x, carPos.y, carPos.z);
    glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

    // Create camera transformations
    glm::mat4 view;
    view = camera.GetViewMatrix();

    // Get the uniform locations
    GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
    GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
    GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

    // Pass the matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Draw the container (using container's vertex attributes)
    glBindVertexArray(carVAO);
    glm::mat4 model;
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);


    // Also draw the lamp object, again binding the appropriate shader
    lampShader.Use();
    // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
    modelLoc = glGetUniformLocation(lampShader.Program, "model");
    viewLoc = glGetUniformLocation(lampShader.Program, "view");
    projLoc = glGetUniformLocation(lampShader.Program, "projection");
    // Set matrices
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    model = glm::mat4(0.5f);
    model = glm::translate(model, carPos);
    model = glm::scale(model, glm::vec3(2.3f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


    // Draw the car
    glBindVertexArray(carVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    /******************** end original car **********************/

    // Draw the car1
    glBindVertexArray(car1VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the car2
    glBindVertexArray(car2VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the car3
    glBindVertexArray(car3VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the car4
    glBindVertexArray(car4VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the car5
    glBindVertexArray(car5VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the car6
    glBindVertexArray(car6VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the car7
    glBindVertexArray(car7VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the car8
    glBindVertexArray(car8VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the car9
    glBindVertexArray(car9VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the car10
    glBindVertexArray(car10VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the car11
    glBindVertexArray(car11VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the car12
    glBindVertexArray(car12VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the car13
    glBindVertexArray(car13VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the car14
    glBindVertexArray(car14VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the car15
    glBindVertexArray(car15VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the car16
    glBindVertexArray(car16VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the car17
    glBindVertexArray(car17VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Draw the finish line
    glBindVertexArray(finVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);




    // Draw the triangle
    ourShader.Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 9);
    glBindVertexArray(0);

    // Draw the walls
    ourShader.Use();
    glBindVertexArray(wallVAO);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glBindVertexArray(0);



    int state = glfwGetKey(window, GLFW_KEY_LEFT);
    if (state == GLFW_PRESS)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        GLfloat vertices1[] =
        {
            // Positions         // Colors
            -0.2f, -0.8f, 0.0f,   0.4f, 0.4f, 0.4f,  // Bottom Right
            -0.6f, -0.8f, 0.0f,   0.4f, 0.4f, 0.4f,  // Bottom Left
            -0.4f,  -0.4f, 0.0f,   1.0f, 1.0f, 1.0f,   // Top

            -0.6f, -0.8f, 0.0f,     0.35f, 0.35f, 0.67f,
            -0.5f, -1.0f, 0.0f,     1.0f, 1.0f, 1.0f,
            -0.4f, -0.8f, 0.0f,     0.35f, 0.35f, 0.67f,

            -0.2f, -0.8f, 0.0f,     0.35f, 0.35f, 0.67f,
            -0.3f, -1.0f, 0.0f,     1.0f, 1.0f, 1.0f,
            -0.4f, -0.8f, 0.0f,     0.35f, 0.35f, 0.67f
        };

        GLuint VBO1, VAO1;
        glGenVertexArrays(1, &VAO1);
        glGenBuffers(1, &VBO1);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(VAO1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0); // Unbind VAO


        // Draw the triangle
        ourShader.Use();
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 9);
        glBindVertexArray(0);

        // Draw the walls
        ourShader.Use();
        glBindVertexArray(wallVAO);
        glDrawArrays(GL_TRIANGLES, 0, 12);
        glBindVertexArray(0);



        // Use cooresponding shader when setting uniforms/drawing objects
        lightingShader.Use();
        GLint objectColorLoc = glGetUniformLocation(lightingShader.Program, "objectColor");
        GLint lightColorLoc = glGetUniformLocation(lightingShader.Program, "lightColor");
        GLint carPosLoc = glGetUniformLocation(lightingShader.Program, "carPos");
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
        glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
        glUniform3f(carPosLoc, carPos.x, carPos.y, carPos.z);
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        // Create camera transformations
        glm::mat4 view;
        view = camera.GetViewMatrix();

        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Draw the container (using container's vertex attributes)
        glBindVertexArray(carVAO);
        glm::mat4 model;
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // Also draw the lamp object, again binding the appropriate shader
        lampShader.Use();
        // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
        modelLoc = glGetUniformLocation(lampShader.Program, "model");
        viewLoc = glGetUniformLocation(lampShader.Program, "view");
        projLoc = glGetUniformLocation(lampShader.Program, "projection");
        // Set matrices
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        model = glm::mat4(0.5f);
        model = glm::translate(model, carPos);
        model = glm::scale(model, glm::vec3(2.3f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


        // Draw the car
        glBindVertexArray(carVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car1
        glBindVertexArray(car1VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car2
        glBindVertexArray(car2VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car3
        glBindVertexArray(car3VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car4
        glBindVertexArray(car4VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car5
        glBindVertexArray(car5VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car6
        glBindVertexArray(car6VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car7
        glBindVertexArray(car7VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car8
        glBindVertexArray(car8VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car9
        glBindVertexArray(car9VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car10
        glBindVertexArray(car10VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car11
        glBindVertexArray(car11VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car12
        glBindVertexArray(car12VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car13
        glBindVertexArray(car13VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car14
        glBindVertexArray(car14VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car15
        glBindVertexArray(car15VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car16
        glBindVertexArray(car16VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car17
        glBindVertexArray(car17VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the finish line
        glBindVertexArray(finVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

    }

    int state2 = glfwGetKey(window, GLFW_KEY_RIGHT);
    if (state2 == GLFW_PRESS)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        GLfloat vertices2[] =
        {
            // Positions         // Colors
            0.6f, -0.8f, 0.0f,   0.4f, 0.4f, 0.4f,  // Bottom Right
            0.2f, -0.8f, 0.0f,   0.4f, 0.4f, 0.4f,  // Bottom Left
            0.4f,  -0.4f, 0.0f,   1.0f, 1.0f, 1.0f,   // Top

            0.6f, -0.8f, 0.0f,     0.35f, 0.35f, 0.67f,
            0.5f, -1.0f, 0.0f,     1.0f, 1.0f, 1.0f,
            0.4f, -0.8f, 0.0f,     0.35f, 0.35f, 0.67f,

            0.2f, -0.8f, 0.0f,     0.35f, 0.35f, 0.67f,
            0.3f, -1.0f, 0.0f,     1.0f, 1.0f, 1.0f,
            0.4f, -0.8f, 0.0f,     0.35f, 0.35f, 0.67f
        };

        GLuint VBO2, VAO2;
        glGenVertexArrays(1, &VAO2);
        glGenBuffers(1, &VBO2);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(VAO2);

        glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0); // Unbind VAO


        // Draw the triangle
        ourShader.Use();
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 9);
        glBindVertexArray(0);

        // Draw the walls
        ourShader.Use();
        glBindVertexArray(wallVAO);
        glDrawArrays(GL_TRIANGLES, 0, 12);
        glBindVertexArray(0);


        // Use cooresponding shader when setting uniforms/drawing objects
        lightingShader.Use();
        GLint objectColorLoc = glGetUniformLocation(lightingShader.Program, "objectColor");
        GLint lightColorLoc = glGetUniformLocation(lightingShader.Program, "lightColor");
        GLint carPosLoc = glGetUniformLocation(lightingShader.Program, "carPos");
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
        glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
        glUniform3f(carPosLoc, carPos.x, carPos.y, carPos.z);
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        // Create camera transformations
        glm::mat4 view;
        view = camera.GetViewMatrix();

        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Draw the container (using container's vertex attributes)
        glBindVertexArray(carVAO);
        glm::mat4 model;
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // Also draw the lamp object, again binding the appropriate shader
        lampShader.Use();
        // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
        modelLoc = glGetUniformLocation(lampShader.Program, "model");
        viewLoc = glGetUniformLocation(lampShader.Program, "view");
        projLoc = glGetUniformLocation(lampShader.Program, "projection");
        // Set matrices
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        model = glm::mat4(0.5f);
        model = glm::translate(model, carPos);
        model = glm::scale(model, glm::vec3(2.3f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


        // Draw the car
        glBindVertexArray(carVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car1
        glBindVertexArray(car1VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car2
        glBindVertexArray(car2VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car3
        glBindVertexArray(car3VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car4
        glBindVertexArray(car4VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car5
        glBindVertexArray(car5VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car6
        glBindVertexArray(car6VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car7
        glBindVertexArray(car7VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car8
        glBindVertexArray(car8VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car9
        glBindVertexArray(car9VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car10
        glBindVertexArray(car10VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car11
        glBindVertexArray(car11VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car12
        glBindVertexArray(car12VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car13
        glBindVertexArray(car13VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car14
        glBindVertexArray(car14VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car15
        glBindVertexArray(car15VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car16
        glBindVertexArray(car16VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the car17
        glBindVertexArray(car17VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Draw the finish line
        glBindVertexArray(finVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

    }