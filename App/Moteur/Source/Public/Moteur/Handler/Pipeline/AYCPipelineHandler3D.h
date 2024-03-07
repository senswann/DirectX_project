#pragma once

#include "Moteur/pch.h"
#include "wrl/client.h"
#include "Tools/Singelton.h"

namespace AYCDX {
	class AYCPipelineHandler3D : public Tools::Singelton<AYCPipelineHandler3D> {
	private:
		D3D12_GRAPHICS_PIPELINE_STATE_DESC m_pipelineStateDesc3D;
	public:
		bool Init();
		void Shutdown();

	};
}