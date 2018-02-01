#ifndef PARAMETRS
#define PARAMETRS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

glm::vec3 pos[] = {
    // sun
    glm::vec3( 0.0f,  0.0f,  0.0f),
    // earth
    glm::vec3( 5.0f,  0.0f, 5.0f),
    //moon
    glm::vec3(0.5f, 0.0f, 0.5f),
    //mars
    glm::vec3(7.0f, 7.0f, 7.0f),
    //saturn
    glm::vec3(1.0f) * 10.0f
};

glm::vec3 scales[] = {
    // sun
    glm::vec3( 1.5f,  1.5f,  1.5f),
    // earth
    glm::vec3( 0.3f,  0.3f, 0.3f),
    //moon
    glm::vec3(0.1f, 0.1f, 0.1f),
    //mars
    glm::vec3(0.4f, 0.4f, 0.4f),
    // saturn
    glm::vec3(1)
};


class movement {
public:
    glm::vec3 init_pos;
    double alpha;
    glm::vec3 rotate;
    virtual void update()=0;
};

class sun : public movement{
public:
    sun() {
        init_pos = pos[0];
        alpha = 0;
        rotate = glm::vec3(0);
    }

    void update() {
        init_pos = pos[0];
    }
};
sun *sun_s = new sun();

class earth : public movement {
public:
    double betta;
    earth() {
        init_pos = pos[1];
        alpha = 0;
        betta = 0;
        rotate = glm::vec3(0);
    }

    void update() {

        init_pos.x = pos[1].x * cos(alpha);
        init_pos.z = pos[1].z * sin(alpha);
        rotate.y = alpha;
        rotate.x = 0.05;
        alpha += 0.01;
    }
};
earth *earth_s = new earth();

class moon : public movement{
public:
    moon() {
        init_pos = pos[2];
        alpha = 0;
        rotate = glm::vec3(0);
    }
    void update() {
        init_pos.x = pos[2].x * cos(alpha);
        init_pos.z = pos[2].z * sin(alpha);
        init_pos += earth_s->init_pos;
        alpha += 0.05;
    }
};
moon *moon_s = new moon();

class mars : public movement{
public:
    glm::vec4 pos_o;
    glm::mat4 mat_m;
    mars() {
        pos_o = glm::vec4(pos[3].x, 0.0f, pos[3].z, 1.0f);
        init_pos = glm::vec3(0);
        alpha = 0;
        rotate = glm::vec3(0);
        mat_m = glm::rotate(mat_m, 270.0f, glm::vec3(0.0f, 0.0f, 1.0));

    }

    void update() {

        double radian_a = glm::radians(alpha);
        pos_o.x = -pos[3].x * sin(radian_a);
        pos_o.z = pos[3].z * cos(radian_a);
        init_pos = glm::vec3(mat_m * pos_o);
        rotate.y = alpha / 100;
        rotate.x = 0.1;
        alpha += 1;
    }
};
mars *mars_s = new mars();

class saturn : public movement{
public:
    glm::vec4 pos_o;
    glm::mat4 mat_m;
    saturn() {
        pos_o = glm::vec4(pos[4].x, 0.0f, pos[4].z, 1.0f);
        init_pos = glm::vec3(0);
        alpha = 0;
        rotate = glm::vec3(0);
        mat_m = glm::rotate(mat_m, 10.0f, glm::vec3(0.0f, 0.0f, 1.0));

    }

    void update() {

        double radian_a = glm::radians(alpha);
        pos_o.x = pos[4].x * sin(radian_a);
        pos_o.z = pos[4].z * cos(radian_a);
        init_pos = glm::vec3(mat_m * pos_o);
        alpha += 1.4f;

    }
};
saturn *saturn_s = new saturn();

std::vector<movement*> moves;

void init_move() {
    moves.push_back(sun_s);
    moves.push_back(earth_s);
    moves.push_back(moon_s);
    moves.push_back(mars_s);
    moves.push_back(saturn_s);
}

#endif // PARAMETRS

