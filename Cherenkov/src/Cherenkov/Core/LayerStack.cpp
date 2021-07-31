#include "ckpch.h"
#include "Cherenkov/Core/LayerStack.h"

namespace Cherenkov {

	LayerStack::~LayerStack() {

		for (Layer* layer : m_Layers) {
			layer->onDetach();
			delete layer;
		}

	}

	void LayerStack::pushLayer(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIdx, layer);
		m_LayerInsertIdx++;
	}

	void LayerStack::popLayer(Layer* layer) {

		auto object = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIdx, layer);

		if (object != m_Layers.begin() + m_LayerInsertIdx) {
		
			layer->onDetach();
			m_Layers.erase(object);
			m_LayerInsertIdx--;
		}
	}

	void LayerStack::pushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::popOverlay(Layer* overlay) {

		auto object = std::find(m_Layers.begin() + m_LayerInsertIdx, m_Layers.end(), overlay);

		if (object != m_Layers.end()) {
			overlay->onDetach();
			m_Layers.erase(object);
		}
	}
}
