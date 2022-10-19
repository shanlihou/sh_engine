#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include <string>
#include <vector>
#include <utility>
#include <memory>
#include "Shader.h"
#include "Texture2D.h"


class Material {
public:
    Material() {};
    void parse(std::string &);

public:
    std::shared_ptr<Shader> shader_;
    std::vector<std::pair<std::string, std::shared_ptr<Texture2D>>> textures_;
};

#endif
