#include "ckpch.h"
#include "LayerStack.h"

namespace Cherenkov {

	LayerStack::LayerStack() {
	
		m_LayerInsert = m_Layers.begin();

	}

	LayerStack::~LayerStack() {

		for (Layer* layer : m_Layers) {delete layer;}

	}

	void LayerStack::PushLayer(Layer* layer) {
	
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	
	}

	void LayerStack::PopLayer(Layer* layer) {

		auto object = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (object != m_Layers.end()) {
		
			m_Layers.erase(object);
			m_LayerInsert--;
		}
	}

	void LayerStack::PushOverlay(Layer* overlay) {

		m_Layers.emplace_back(overlay);

	}

	void LayerStack::PopOverlay(Layer* overlay) {

		auto object = std::find(m_Layers.begin(), m_Layers.end(), overlay);

		if (object != m_Layers.end()) {

			m_Layers.erase(object);
		}
	}
}