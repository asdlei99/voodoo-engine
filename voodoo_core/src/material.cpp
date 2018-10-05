#include "voodoo/material.h"
#include "voodoo/image_manager.h"

namespace voodoo
{
	bool Material::Init(std::string vs_path, std::string ps_path, std::string texture_path, bool light)
	{
		shader_ = std::make_shared<Shader>();
		if (!shader_->Init(vs_path, ps_path, light)) {
			return false;
		}

		texture_ = std::make_shared<Texture>(ImageManager::Get().Retrieve(texture_path));

		return true;
	}

	bool Material::Update(
		const Matrix4x4<float>& world_matrix,
		const Matrix4x4<float>& view_matrix,
		const Matrix4x4<float>& projection_matrix)
	{
		if (!shader_->Update(world_matrix, view_matrix, projection_matrix, texture_->srv)) {
			return false;
		}

		return true;
	}
}