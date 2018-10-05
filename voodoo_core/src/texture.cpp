#include "voodoo/texture.h"

namespace voodoo
{
	Texture::Texture(std::shared_ptr<Image> image)
	{
		HRESULT hr;

		D3D11_TEXTURE2D_DESC texture_desc;
		memset(&texture_desc, 0, sizeof(texture_desc));
		texture_desc.Width = image->width;
		texture_desc.Height = image->height;
		texture_desc.MipLevels = 1;
		texture_desc.ArraySize = 1;
		texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		texture_desc.SampleDesc.Count = 1;
		texture_desc.Usage = D3D11_USAGE_DEFAULT;
		texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		texture_desc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subresource_data;
		subresource_data.pSysMem = image->data;
		subresource_data.SysMemPitch = texture_desc.Width * 4;
		subresource_data.SysMemSlicePitch = 0;

		hr = DirectXManager::Get()->GetDevice()->CreateTexture2D(
			&texture_desc, &subresource_data, &texture);
		if (FAILED(hr)) {
			throw std::runtime_error("Failed to create texture from memory");
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc;
		ZeroMemory(&srv_desc, sizeof(srv_desc));
		srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srv_desc.Texture2D.MipLevels = texture_desc.MipLevels;
		srv_desc.Texture2D.MostDetailedMip = 0;

		// Determine format by image color channels
		switch (image->channels) {
		case 1:
			srv_desc.Format = DXGI_FORMAT_R8_UNORM;
			break;
		case 2:
			srv_desc.Format = DXGI_FORMAT_R8G8_UNORM;
			break;
		default:
			srv_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			break;
		}

		hr = DirectXManager::Get()->GetDevice()->CreateShaderResourceView(
			texture, &srv_desc, &srv);
		if (FAILED(hr)) {
			throw std::runtime_error("Failed to create shader resource view from texture");
		}
	}

	Texture::~Texture()
	{
		if (texture) {
			texture->Release();
		}

		if (srv) {
			srv->Release();
		}
	}
}