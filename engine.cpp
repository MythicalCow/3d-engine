
#include <SFML/Graphics.hpp>
#include <random>
#include <unistd.h>
#include <iostream>
#include <math.h>
#define PI 3.14159265



using namespace sf;
using namespace std;
RenderWindow window(VideoMode(800, 800), "test");
int REFRESH_MICRO = 20000; //refreshrate of display in microseconds


class point{
    public:
        float c, d;
};


point rotate(float a, float b, float angle){
    float angle_rad = angle*(PI/180);
    float cos_val = cos(angle_rad); 
    float sin_val = sin(angle_rad);
    point vals;
    vals.c = a*cos_val - b*sin_val;
    vals.d = a*sin_val + b*cos_val;
    return vals;
}



int main()
{

    float vr = 0.f;
    float hr = 0.f;
    float moveF = 0.f;
    float moveS = 0.f;
    // float b = 1.f;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(Color::Black);
        // z += 0.01;
        //viewpoint

        //poly
        float points[3][3] = {{1.f,0.f,1.f},{2.f,0.f,1.f},{1.f,2.f,1.f}};
        float camera[6] = {2.f+moveS,0.f,-2.f+moveF,0.f+hr,0.f+vr,0.f};
        for(int vertex=0; vertex<3; vertex++){
             //Adjusted for Camera
            points[vertex][0] -= camera[0]; points[vertex][1] -= camera[1]; points[vertex][2] -= camera[2]; 
            
            
            //Sideways Rotation
            point vals = rotate(points[vertex][0],points[vertex][2],camera[3]);
            points[vertex][0] = vals.c; points[vertex][2] = vals.d;
            //Vertical Rotation
            vals = rotate(points[vertex][1],points[vertex][2],camera[4]);
            points[vertex][1] = vals.c; points[vertex][2] = vals.d;
            //Rotary Rotation
            vals = rotate(points[vertex][0],points[vertex][1],camera[5]);
            points[vertex][0] = vals.c; points[vertex][1] = vals.d;

            //Scaled Depth
            points[vertex][0] /= points[vertex][2]; points[vertex][1] /= points[vertex][2];

        }

        //Debug
        // cout << points[0][0] << " " << points[0][1] << endl;
        // cout << points[1][0] << " " << points[1][1] << endl;
        // cout << points[2][0] << " " << points[2][1] << endl;

        points[0][0] = points[0][0]*400.f + 400.f; points[0][1] = -1.f*points[0][1]*400.f + 400.f;
        points[1][0] = points[1][0]*400.f + 400.f; points[1][1] = -1.f*points[1][1]*400.f + 400.f;
        points[2][0] = points[2][0]*400.f + 400.f; points[2][1] = -1.f*points[2][1]*400.f + 400.f;

        VertexArray triangle(Triangles, 3);
        triangle[0].position = Vector2f(points[0][0],points[0][1]);
        triangle[1].position = Vector2f(points[1][0],points[1][1]);
        triangle[2].position = Vector2f(points[2][0],points[2][1]);
       
        // //Debug
        // cout << triangle[0].position.x << " " << triangle[0].position.y << endl;
        // cout << triangle[1].position.x << " " << triangle[1].position.y << endl;
        // cout << triangle[2].position.x << " " << triangle[2].position.y << endl;
        
        //Color :)
        triangle[0].color = Color::Red;
        triangle[1].color = Color::Blue;
        triangle[2].color = Color::Green;
        if (points[0][2] > 0) {

            window.draw(triangle);
        }


        if(Keyboard::isKeyPressed(Keyboard::D)){
            hr += 2.f;
        }
        if(Keyboard::isKeyPressed(Keyboard::A)){
            hr -= 2.f;
        }
        if(Keyboard::isKeyPressed(Keyboard::W)){
            vr += 2.f;
        }
        if(Keyboard::isKeyPressed(Keyboard::S)){
            vr -= 2.f;
        }

        if(Keyboard::isKeyPressed(Keyboard::Up)){
            moveF += .05;
        }
        if(Keyboard::isKeyPressed(Keyboard::Down)){
            moveF -= .05;
        }

        if(Keyboard::isKeyPressed(Keyboard::Right)){
            moveS += .05;
        }
        if(Keyboard::isKeyPressed(Keyboard::Left)){
            moveS -= .05;
        }



        // end the current frame
        usleep(REFRESH_MICRO);
        window.display();
    }

    return 0;
}