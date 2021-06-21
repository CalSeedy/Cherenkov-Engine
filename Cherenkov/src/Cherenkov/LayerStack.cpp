#include "ckpch.h"
#include "LayerStack.h"

namespace Cherenkov {

	LayerStack::LayerStack() {
	}

	LayerStack::~LayerStack() {

		for (Layer* layer : m_Layers) {delete layer;}

	}

	void LayerStack::PushLayer(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIdx, layer);
		m_LayerInsertIdx++;
		layer->onAttach();
	}

	void LayerStack::PopLayer(Layer* layer) {

		auto object = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (object != m_Layers.end()) {
		
			layer->onDetach();
			m_Layers.erase(object);
			m_LayerInsertIdx--;
		}
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
		overlay->onAttach();
	}

	void LayerStack::PopOverlay(Layer* overlay) {

		auto object = std::find(m_Layers.begin(), m_Layers.end(), overlay);

		if (object != m_Layers.end()) {
			overlay->onDetach();
			m_Layers.erase(object);
		}
	}
}
