#pragma once
#include "pch.h"
#include "StepTimer.h"
#include "DeviceResources.h"
#include "midi-controller/MidiController.h"

//------------------------------------------------------------------------------
struct Texture
{
	DirectX::XMVECTOR origin;
	int width	= 0;
	int height = 0;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

	void CreateFromFile(ID3D11Device* d3dDevice, const wchar_t* fileName);
};

//------------------------------------------------------------------------------
struct AppResources
{
	// Random Generators
	std::random_device randDevice;
	std::default_random_engine randEngine;

	DX::StepTimer m_timer;

	std::unique_ptr<DX::DeviceResources> m_deviceResources;
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	DirectX::Keyboard::KeyboardStateTracker kbTracker;
	std::unique_ptr<DirectX::Mouse> m_mouse;
	DirectX::Mouse::ButtonStateTracker mouseTracker;

	std::unique_ptr<DirectX::AudioEngine> audioEngine;
	midi::MidiController midiController;
	midi::MidiControllerTracker midiTracker;

	std::unique_ptr<DirectX::CommonStates> m_states;

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> font8pt;
	std::unique_ptr<DirectX::SpriteFont> font16pt;
	std::unique_ptr<DirectX::SpriteFont> font32pt;
	std::unique_ptr<DirectX::SpriteFont> fontMono8pt;
	std::unique_ptr<DirectX::SpriteFont> fontMono16pt;
	std::unique_ptr<DirectX::SpriteFont> fontMono32pt;

	std::unique_ptr<DX::DebugBatchType> m_batch;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_debugInputLayout;
	std::unique_ptr<DirectX::BasicEffect> m_debugEffect;

	std::unique_ptr<DirectX::EffectFactory> m_effectFactory;
	std::shared_ptr<DirectX::BasicEffect> m_debugBoundEffect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_debugBoundInputLayout;
	std::unique_ptr<DirectX::GeometricPrimitive> m_debugBound;

	AppResources()
			: randEngine(randDevice())
			, m_keyboard(std::make_unique<DirectX::Keyboard>())
			, m_mouse(std::make_unique<DirectX::Mouse>())
	{
	}
};

//------------------------------------------------------------------------------
