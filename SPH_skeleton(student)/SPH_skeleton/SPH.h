#pragma once
#include "Particle.h"
#include <GL/glut.h>

using namespace std;
#define SPH_PI 3.1415926
#define GRIDSIZE  20
#define GRIDSIZEY 40

class SPH
{
public:
    GLuint Texture[3];
    vector<Particle*> particles;
    int index;				//particle index
    int MaxParticle;
    int iteration_n;
	bool onHOS;
private:
    double rest_density;	// rest density
    double mu;				// viscosity constant
    double h;				// kernel radius
    double k;				// gas constant

public:
    SPH();
    SPH(int numparticle);
    ~SPH();

    void resetParticle();
    void init();
    void damBreaking();
    void pouring();
    void update(float dt, vec3 gravity);
    void draw();
    void makeHashTable();
    void computeDensity();
    void computeForce();
    void integrate(double dt, vec3 gravity);

private:	//kernel functions for SPH
    double	poly6Kernel(vec3 rij, double h);
    vec3	spikygradientKernel(vec3 rij, double q);
    double	viscositylaplacianKernel(vec3 rij, double q);
private:
    vector<Particle*> hashGrid[GRIDSIZE][GRIDSIZEY][GRIDSIZE];
    vector<Particle*> getNeighbor(int gridx, int gridy, int gridz, double radius, vector<Particle*>& mine);

    void LoadTexture(const char* filename,int texturenum)
    {


        int width, height;

        unsigned char* data;

        FILE* file;

        file = fopen(filename, "rb");

        if (file == NULL) return;
        width = 420;
        height = 420;
        data = (unsigned char*)malloc(width * height * 3);
        fread(data, 54, 1, file);
        fread(data, width * height * 3, 1, file);
        fclose(file);

        for (int i = 0; i < width * height; ++i)
        {
            int index = i * 3;
            unsigned char B, R;
            B = data[index];
            R = data[index + 2];

            data[index] = R;
            data[index + 2] = B;

        }


        glGenTextures(1, &Texture[texturenum]);
        glBindTexture(GL_TEXTURE_2D, Texture[texturenum]);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
        free(data);

    }
};