#ifndef NIXIE_SHADER_H_
#define NIXIE_SHADER_H_

#pragma once

#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11shader.h>
#include <d3dcompiler.h>

#include "directx_manager.h"
#include "math/color.h"
#include "math/vector.h"
#include "math/matrix.h"


namespace nixie
{
	class Shader
	{
	private:
		struct ShaderBuffer
		{
			ShaderBuffer(unsigned int size) :
				data(new byte[size]),
				size(size)
			{}

			byte* data;
			unsigned int size;
		};

		struct MatrixBuffer
		{
			Matrix4x4<float> world_matrix;
			Matrix4x4<float> view_matrix;
			Matrix4x4<float> projection_matrix;
		};

		struct LightBuffer
		{
			Color diffuse_color;
			Color ambient_color;
			Vector3<float> direction;
			float padding;
		};

		struct PixelBuffer
		{
			Color color;
		};

	public:
		Shader();
		~Shader();

		bool Init(std::string vs_path, std::string ps_path, bool light);
		bool Update(
			const Matrix4x4<float>& world_matrix,
			const Matrix4x4<float>& view_matrix,
			const Matrix4x4<float>& projection_matrix,
			ID3D11ShaderResourceView* texture);

	private:
		bool CreateInputLayout(ShaderBuffer buffer);
		bool CreateMatrixBuffer();
		bool CreateSamplerState();
		bool CreateLightBuffer();

		ShaderBuffer LoadFromFile(std::string file_path);

	private:
		std::shared_ptr<ID3D11Device> device_;
		std::shared_ptr<ID3D11DeviceContext> device_context_;

		ID3D11VertexShader* vertex_shader_;
		ID3D11PixelShader* pixel_shader_;
		ID3D11InputLayout* input_layout_;
		ID3D11SamplerState* sampler_state_;

		ID3D11Buffer* matrix_buffer_;
		ID3D11Buffer* light_buffer_;
		ID3D11Buffer* pixel_buffer_;

		bool light_;
	};
}

#endif