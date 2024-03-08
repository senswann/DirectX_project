#pragma once

#include "Moteur/pch.h"
#include "wrl/client.h"
#include "Tools/Singelton.h"

namespace AYCDX {
	class AYCPipelineHandler3D : public Tools::Singelton<AYCPipelineHandler3D> {
	private:
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_pipelineStateDesc3D;
	
	public:
		bool Init(ID3D12RootSignature* InRootSignature3D, const class Shader* InVertexShader3D, const Shader* InPixelShader3D);
		inline const D3D12_GRAPHICS_PIPELINE_STATE_DESC& GetStateDesc3D() const { return m_pipelineStateDesc3D; }
		void Shutdown();
	};
}