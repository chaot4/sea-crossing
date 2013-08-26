#include "material.h"


Material::~Material(void)
{
}

Material::Material(int in_id,GLSLProgram* prgm,Texture* diff,Texture* spec,Texture* roughness,Texture* normal) :
	id(in_id), shaderProgram(prgm), diffuseMap(diff), specularMap(spec), roughnessMap(roughness), normalMap(normal)
{
}


void Material::use()
{
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	shaderProgram->setUniform("diffuse_tx2D",0);
	diffuseMap->bindTexture();
	glActiveTexture(GL_TEXTURE1);
	shaderProgram->setUniform("specular_tx2D",1);
	specularMap->bindTexture();
	glActiveTexture(GL_TEXTURE2);
	shaderProgram->setUniform("roughness_tx2D",2);
	roughnessMap->bindTexture();
	glActiveTexture(GL_TEXTURE3);
	shaderProgram->setUniform("normal_tx2D",3);
	normalMap->bindTexture();
}