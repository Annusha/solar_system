#ifndef MODEL
#define MODEL

#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>

#include <opencv2/opencv.hpp>

class Model
{
    public:
        /*  Model Data */
        vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        vector<Mesh> meshes;
        string directory;
        bool gammaCorrection;

        /*  Functions   */
        Model(char *path)
        {
            loadModel(path);
        }

        Model() {}

        void Draw(Shader shader);
    private:

        /*  Functions   */
        void loadModel(string path);

        void processNode(aiNode *node, const aiScene *scene);

        Mesh processMesh(aiMesh *mesh, const aiScene *scene);

        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                             string typeName);
};

#endif // MODEL

