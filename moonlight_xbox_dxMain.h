﻿#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\VideoRenderer.h"
#include "Content\LogRenderer.h"

// Renders Direct2D and 3D content on the screen.
namespace moonlight_xbox_dx
{
	class moonlight_xbox_dxMain : public DX::IDeviceNotify
	{
	public:
		moonlight_xbox_dxMain(const std::shared_ptr<DX::DeviceResources>& deviceResources, Windows::UI::Xaml::Controls::Button^ flyoutButton, Windows::UI::Core::CoreDispatcher ^dispatcher);
		~moonlight_xbox_dxMain();
		void CreateWindowSizeDependentResources();
		void TrackingUpdate(float positionX) { m_pointerLocationX = positionX; }
		void StartRenderLoop();
		void StopRenderLoop();
		void SetFlyoutOpened(bool value);
		Concurrency::critical_section& GetCriticalSection() { return m_criticalSection; }
		bool mouseMode = false;
		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

	private:
		void ProcessInput();
		void Update();
		bool Render();

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// TODO: Replace with your own content renderers.
		std::unique_ptr<VideoRenderer> m_sceneRenderer;
		std::unique_ptr<LogRenderer> m_fpsTextRenderer;

		Windows::Foundation::IAsyncAction^ m_renderLoopWorker;
		Windows::Foundation::IAsyncAction^ m_inputLoopWorker;
		Concurrency::critical_section m_criticalSection;

		// Rendering loop timer.
		DX::StepTimer m_timer;

		// Track current input pointer position.
		float m_pointerLocationX;
		bool insideFlyout = false;
		bool leftMouseButtonPressed = false;
		bool rightMouseButtonPressed = false;
		Windows::UI::Xaml::Controls::Button ^m_flyoutButton;
		Windows::UI::Core::CoreDispatcher ^m_dispatcher;
	};
}