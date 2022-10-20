#include "Material.h"
#include <rapidxml/rapidxml.hpp>
#include "rapidxml/rapidxml_utils.hpp" 
#include "rapidxml/rapidxml_print.hpp"  

#include "Const.h"
#include "Utils.h"


void Material::parse(std::string &material_path) {

    auto _path = SHILY_UTILS::toResourcePath(material_path);

    rapidxml::file<> xml_file(_path.c_str());
    rapidxml::xml_document<> document;
    document.parse<0>(xml_file.data());
    //根节点
    rapidxml::xml_node<>* material_node = document.first_node("material");
    if(material_node == nullptr){
        return;
    }

    rapidxml::xml_attribute<>* material_shader_attribute = material_node->first_attribute("shader");
    if(material_shader_attribute == nullptr){
        return;
    }

    shader_ = ShaderManager::instance()->find(std::string(material_shader_attribute->value()));
    //解析Texture
    rapidxml::xml_node<>* material_texture_node = material_node->first_node("texture");
    while (material_texture_node != nullptr){
        rapidxml::xml_attribute<>* texture_name_attribute = material_texture_node->first_attribute("name");
        if(texture_name_attribute == nullptr){
            return;
        }
        rapidxml::xml_attribute<>* texture_image_attribute = material_texture_node->first_attribute("image");
        if(texture_image_attribute == nullptr){
            return;
        }
        std::string shader_property_name = texture_name_attribute->value();
        std::string image_path = texture_image_attribute->value();
        std::shared_ptr<Texture2D> _ptr(Texture2D::LoadFromFile(image_path));
        textures_.emplace_back(texture_name_attribute->value(), _ptr);
        material_texture_node = material_texture_node->next_sibling("texture");
    }
}
