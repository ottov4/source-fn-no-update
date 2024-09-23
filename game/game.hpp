#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <dwmapi.h>
#include "../auth/keyauth.hpp"
#include "../security/SkCrypt.hpp"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"
#include "cheats/aimbot/aimbot.hpp"
#include "cheats/visuals/visuals.hpp"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dwmapi.lib")

IDirect3D9Ex* p_object = NULL;
IDirect3DDevice9Ex* p_device = NULL;
D3DPRESENT_PARAMETERS p_params = { NULL };
MSG messager = { NULL };
HWND my_wnd = NULL;
HWND game_wnd = NULL;

int getFps()
{
	MASK
	using namespace std::chrono;
	static int count = 0;
	static auto last = high_resolution_clock::now();
	auto now = high_resolution_clock::now();
	static int fps = 0;

	count++;

	if (duration_cast<milliseconds>(now - last).count() > 1000)
	{
		fps = count;
		count = 0;
		last = now;
	}

	return fps;
}

HRESULT directx_init()
{
	MASK
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_object))) exit(3);

	ZeroMemory(&p_params, sizeof(p_params));
	p_params.Windowed = TRUE;
	p_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_params.hDeviceWindow = my_wnd;
	p_params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_params.BackBufferWidth = settings::width;
	p_params.BackBufferHeight = settings::height;
	p_params.EnableAutoDepthStencil = TRUE;
	p_params.AutoDepthStencilFormat = D3DFMT_D16;
	p_params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(p_object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, my_wnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_params, 0, &p_device)))
	{
		p_object->Release();
		exit(4);
	}

	ImGui::CreateContext();
	ImGui_ImplWin32_Init(my_wnd);
	ImGui_ImplDX9_Init(p_device);

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImFontAtlas* fontAtlas = io.Fonts;
	ImFontConfig arialConfig;
	arialConfig.FontDataOwnedByAtlas = false;
	ImFont* arialFont = fontAtlas->AddFontFromFileTTF("c:\\Windows\\Fonts\\Bahnschrift.ttf", 14.0f, &arialConfig);
	io.Fonts = fontAtlas;
	io.IniFilename = 0;

	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.FrameRounding = 3.0f;
	style.DisabledAlpha = 1.0f;
	style.WindowPadding = ImVec2(12.0f, 12.0f);
	style.WindowRounding = 8.0f;
	style.WindowBorderSize = 0.0f;
	style.WindowMinSize = ImVec2(20.0f, 20.0f);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_None;
	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 0.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(6.0f, 6.0f);
	style.FrameRounding = 0.0f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(12.0f, 6.0f);
	style.ItemInnerSpacing = ImVec2(6.0f, 3.0f);
	style.CellPadding = ImVec2(12.0f, 6.0f);
	style.IndentSpacing = 20.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 12.0f;
	style.GrabRounding = 0.0f;
	style.TabRounding = 3.0f;
	style.TabBorderSize = 0.0f;
	style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.2745098173618317f, 0.3176470696926117f, 0.4509803950786591f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5372549295425415f, 0.5529412031173706f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.5215686559677124f, 0.6000000238418579f, 0.7019608020782471f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.03921568766236305f, 0.9803921580314636f, 0.9803921580314636f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.2901960909366608f, 0.5960784554481506f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.9960784316062927f, 0.4745098054409027f, 0.6980392336845398f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);

	p_object->Release();
	return S_OK;
}

void create_overlay()
{
	MASK
	WNDCLASSEXA wcex = {
		sizeof(WNDCLASSEXA),           
		0,                             
		DefWindowProcA,                 
		0,                            
		0,                             
		GetModuleHandleA(nullptr),      
		LoadIcon(nullptr, IDI_APPLICATION),   
		LoadCursor(nullptr, IDC_ARROW), 
		nullptr,                        
		nullptr,                       
		"Desi",                       
		LoadIcon(nullptr, IDI_APPLICATION)    
	};

	ATOM classAtom = RegisterClassExA(&wcex);
	if (!classAtom) {
		MessageBoxA(nullptr, "Failed to register window class!", "Error", MB_ICONERROR | MB_OK);
		return;
	}


	RECT desktopRect;
	if (!GetWindowRect(GetDesktopWindow(), &desktopRect)) {
		MessageBoxA(nullptr, "Failed to get desktop window rect!", "Error", MB_ICONERROR | MB_OK);
		return;
	}

	my_wnd = gui::create_window_in_band(
		0,                          
		classAtom,                  
		L"Desi",                    
		WS_POPUP,                  
		desktopRect.left,          
		desktopRect.top,            
		desktopRect.right - desktopRect.left,  
		desktopRect.bottom - desktopRect.top,  
		nullptr,                    
		nullptr,                    
		wcex.hInstance,            
		nullptr,                    
		gui::ZBID_UIACCESS          
	);

	if (!my_wnd) {
		MessageBoxA(nullptr, "Failed to create overlay window!", "Error", MB_ICONERROR | MB_OK);
		return;
	}

	
	SetWindowLong(my_wnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);

	
	SetLayeredWindowAttributes(my_wnd, RGB(0, 0, 0), 255, LWA_ALPHA);

	
	MARGINS margins = { -1 };
	if (FAILED(DwmExtendFrameIntoClientArea(my_wnd, &margins))) {
		MessageBoxA(nullptr, "Failed to extend frame into client area!", "Error", MB_ICONERROR | MB_OK);
		return;
	}

	
	ShowWindow(my_wnd, SW_SHOWDEFAULT);
	UpdateWindow(my_wnd);
}


// OLD OVERALY dont add it back if this work correct (for now is better)


//void create_overlay()
//{
//	WNDCLASSEXA wcex = {
//		sizeof(WNDCLASSEXA),
//		0,
//		DefWindowProcA,
//		0,
//		0,
//		0,
//		LoadIcon(0, IDI_APPLICATION),
//		LoadCursor(0, IDC_ARROW),
//		0,
//		0,
//		"Desi",
//		LoadIcon(0, IDI_APPLICATION)
//	};
//	ATOM rce = RegisterClassExA(&wcex);
//	RECT rect;
//	GetWindowRect(GetDesktopWindow(), &rect);
//	my_wnd = gui::create_window_in_band(0, rce, L"Desi", WS_POPUP, rect.left, rect.top, rect.right, rect.bottom, 0, 0, wcex.hInstance, 0, gui::ZBID_UIACCESS);
//	SetWindowLong(my_wnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
//	RECT desktopRect;
//	if (!GetWindowRect(GetDesktopWindow(), &desktopRect)) {
//		MessageBoxA(nullptr, "Failed to get desktop window rect!", "Error", MB_ICONERROR | MB_OK);// TEST I MAKING DONT CARE ABOUT THIS
//		return;
//	}
//	SetLayeredWindowAttributes(my_wnd, RGB(0, 0, 0), 255, LWA_ALPHA);
//	MARGINS margin = { -1 };
//	DwmExtendFrameIntoClientArea(my_wnd, &margin);
//	ShowWindow(my_wnd, SW_SHOWDEFAULT);
//	UpdateWindow(my_wnd);
//}



void features()
{
	MASK
	if (settings::aimbot::enable)
	{
		if (settings::aimbot::mouseAim && GetAsyncKeyState(settings::aimbot::current_key))
		{
			mouseAim(cache::closest_mesh);
		}

		if (settings::aimbot::silentAim && GetAsyncKeyState(settings::aimbot::current_key))
		{
			silentAim(cache::closest_mesh);
		}

		if (settings::aimbot::crosshair)
		{
			//ImGui::GetForegroundDrawList()->AddLine(ImVec2(GetSystemMetrics(0) / 2 - 8, GetSystemMetrics(1) / 2), ImVec2(GetSystemMetrics(0) / 2 + 8, GetSystemMetrics(1) / 2), ImColor(0, 0, 0), 2.0f);
			//ImGui::GetForegroundDrawList()->AddLine(ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2 - 8), ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2 + 8), ImColor(0, 0, 0), 2.0f);
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(GetSystemMetrics(0) / 2 - 8, GetSystemMetrics(1) / 2), ImVec2(GetSystemMetrics(0) / 2 + 8, GetSystemMetrics(1) / 2), settings::colors::icCrosshairColor, 1.0f);
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2 - 8), ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2 + 8), settings::colors::icCrosshairColor, 1.0f);
		}

		if (settings::aimbot::show_fov)
		{
			//ImGui::GetForegroundDrawList()->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), settings::aimbot::fov, ImColor(0, 0, 0), 120, 2.0f);
			ImGui::GetForegroundDrawList()->AddCircle(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), settings::aimbot::fov, settings::colors::icFovColor, 120, 1.0f);
		}
	}

	actorLoop();

	//if (settings::visuals::radar)
	//{
	//	// Define window flags based on the current state of settings::show_menu
	//	int windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
	//		ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
	//	if (!settings::show_menu)
	//	{
	//		windowFlags |= ImGuiWindowFlags_NoMove; // Add NoMove flag if menu is not shown
	//	}

	//	// Set the size of the radar window
	//	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Always);

	//	// Start a new ImGui window with the specified flags
	//	if (ImGui::Begin("Radar", nullptr, windowFlags))
	//	{
	//		ImVec2 windowPos = ImGui::GetWindowPos();
	//		ImVec2 windowSize = ImGui::GetWindowSize();
	//		ImDrawList* drawList = ImGui::GetWindowDrawList();

	//		// Calculate center of the radar
	//		ImVec2 center(windowPos.x + windowSize.x * 0.5f, windowPos.y + windowSize.y * 0.5f);

	//		// Draw radar background lines
	//		drawList->AddLine(ImVec2(center.x, windowPos.y), ImVec2(center.x, windowPos.y + windowSize.y), ImColor(25, 25, 25), 1.0f);
	//		drawList->AddLine(ImVec2(windowPos.x, center.y), ImVec2(windowPos.x + windowSize.x, center.y), ImColor(25, 25, 25), 1.0f);
	//		drawList->AddLine(center, ImVec2(windowPos.x, windowPos.y), ImColor(25, 25, 25), 1.0f);
	//		drawList->AddLine(center, ImVec2(windowPos.x + windowSize.x, windowPos.y), ImColor(25, 25, 25), 1.0f);

	//		// Draw the center point
	//		drawList->AddCircleFilled(center, 5.0f, ImColor(255, 255, 255));

	//		// Draw radar points from cache
	//		for (const ImVec2& radarPos : cache::radarPoints)
	//		{
	//			ImVec2 pointPosition(windowPos.x + radarPos.x, windowPos.y + radarPos.y);
	//			drawList->AddCircleFilled(pointPosition, 5.0f, ImColor(255, 0, 0));
	//		}

	//		ImGui::End();
	//	}
	//}
}

void renderTabs(const char* tabLabels[], int tabCount, int& currentTab)
{
	float tabWidth = (ImGui::GetWindowWidth() - (ImGui::GetStyle().FramePadding.x) * (tabCount - 1)) / tabCount;

	for (int i = 0; i < tabCount; i++)
	{
		bool selected = currentTab == i;
		if (ImGui::customTab(tabLabels[i], selected, { tabWidth, 26 })) settings::tab = i;
		ImGui::SameLine(0, 0);
	}
}

void render_menu()
{
	MASK
	switch (settings::aimbot::current_aimkey)
	{
	case 0:
		settings::aimbot::current_key = VK_LBUTTON;
		break;
	case 1:
		settings::aimbot::current_key = VK_RBUTTON;
		break;
	case 2:
		settings::aimbot::current_key = VK_XBUTTON1;
		break;
	case 3:
		settings::aimbot::current_key = VK_XBUTTON2;
		break;
	case 4:
		settings::aimbot::current_key = VK_SHIFT;
		break;
	case 5:
		settings::aimbot::current_key = VK_CONTROL;
		break;
	case 6:
		settings::aimbot::current_key = VK_MENU;
		break;
	case 7:
		settings::aimbot::current_key = VK_CAPITAL;
		break;
	default:
		settings::aimbot::current_key = VK_LBUTTON; // default to left mouse button
		break;
	}

	char watermarkText[64];
	sprintf_s(watermarkText, "Payson Public | %.i FPS", getFps());
	ImVec2 wmTextSize = ImGui::CalcTextSize(watermarkText);
	ImVec2 rectSize = ImVec2(wmTextSize.x + 2 * 10.0f, wmTextSize.y + 2 * 5.0f);
	ImVec2 rectPos = ImVec2(5, 5);
	//ImGui::GetForegroundDrawList()->AddRectFilled(rectPos, ImVec2(rectPos.x + rectSize.x, rectPos.y + rectSize.y), ImColor(10, 10, 10), 0, 0);
	//ImGui::GetForegroundDrawList()->AddRectFilled(rectPos, ImVec2(rectPos.x + rectSize.x, rectPos.y + 2), ImColor(255, 0, 255), 0, 0);
	ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 14.0f, ImVec2(rectPos.x + (rectSize.x - wmTextSize.x) / 2, rectPos.y + (rectSize.y - wmTextSize.y) / 2), ImColor(255, 0, 255), watermarkText);

	if (GetAsyncKeyState(VK_INSERT) & 1) settings::show_menu = !settings::show_menu;
	if (settings::show_menu)
	{
		ImGui::SetNextWindowSize({ 800, 450 });
		ImGui::Begin("Payson Public - discord.gg/saturniv", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
		{
			if (ImGui::BeginTabBar("MainTabBar"))
			{
				if (ImGui::BeginTabItem("Aimbot"))
				{
					ImGui::Columns(2, nullptr, false);
					ImGui::SetColumnWidth(2, 550.0f / 2);
					float width = ImGui::GetColumnWidth() - 10.0f - ImGui::GetStyle().ChildBorderSize * 2;
					ImGui::BeginChild("##aimbot", ImVec2(width, 0), true);
					{
						ImGui::Text("Aimbot Toggles");
						ImGui::Separator();
						ImGui::Dummy(ImVec2(0, 1.0f));

						ImGui::Checkbox("Enable Aimbot", &settings::aimbot::enable);
						if (settings::aimbot::enable)
						{
							ImGui::Checkbox("Kernel Aim", &settings::aimbot::mouseAim);
							ImGui::Checkbox("Silent Aim", &settings::aimbot::silentAim);
							ImGui::Checkbox("Bullet Prediction", &settings::aimbot::bulletPrediction);
							ImGui::Checkbox("Crosshair", &settings::aimbot::crosshair);
							ImGui::Checkbox("Show FOV", &settings::aimbot::show_fov);
						}
					}
					ImGui::EndChild();
					ImGui::NextColumn();
					ImGui::BeginChild("##aimbotOptions", ImVec2(width, 0), true);
					{
						ImGui::Text("Aimbot Settings");
						ImGui::Separator();
						ImGui::Dummy(ImVec2(0, 1.0f));

						ImGui::SliderFloat("FOV", &settings::aimbot::fov, 50, 500, "%.f");
						ImGui::SliderFloat("Smoothness", &settings::aimbot::smoothness, 1, 25, "%.f%");
						ImGui::Combo("AimKey", &settings::aimbot::current_aimkey, settings::aimbot::aimkey, sizeof(settings::aimbot::aimkey) / sizeof(*settings::aimbot::aimkey));
						if (ImGui::BeginCombo("Hitbox", getHitboxTypeName(settings::aimbot::current_hitbox)))
						{
							for (auto hitboxType : hitboxValues)
							{
								if (ImGui::Selectable(getHitboxTypeName(hitboxType), settings::aimbot::current_hitbox == hitboxType)) settings::aimbot::current_hitbox = hitboxType;
							}
							ImGui::EndCombo();
						}
					}
					ImGui::EndChild();
					ImGui::Columns(1);
					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Visuals"))
				{
					ImGui::Columns(2, nullptr, false);
					ImGui::SetColumnWidth(2, 550.0f / 2);
					float width = ImGui::GetColumnWidth() - 10.0f - ImGui::GetStyle().ChildBorderSize * 2;
					ImGui::BeginChild("##visual", ImVec2(width, 0), true);
					{
						ImGui::Text("Visuals Toggles");
						ImGui::Separator();
						ImGui::Dummy(ImVec2(0, 1.0f));

						ImGui::Checkbox("Enable Visuals", &settings::visuals::enable);
						if (settings::visuals::enable)
						{
							ImGui::Checkbox("Box", &settings::visuals::box);
							ImGui::Checkbox("Skeleton", &settings::visuals::skeleton);
							ImGui::Checkbox("Line", &settings::visuals::line);
							ImGui::Checkbox("Device", &settings::visuals::platform);
							ImGui::Checkbox("Name", &settings::visuals::name);
							ImGui::Checkbox("Distance", &settings::visuals::distance);
							ImGui::Checkbox("Rank", &settings::visuals::rank);
						}
					}
					ImGui::EndChild();
					ImGui::NextColumn();
					ImGui::BeginChild("##visualsOptions", ImVec2(width, 0), true);
					{
						ImGui::Text("Visuals Settings");
						ImGui::Separator();
						ImGui::Dummy(ImVec2(0, 1.0f));

						ImGui::SliderFloat("Render Distance", &settings::visuals::renderDistance, 100, 3000, "%.fm");
						if (ImGui::BeginCombo("Box Type", getBoxTypeName(settings::visuals::boxType)))
						{
							for (auto boxType : boxValues)
							{
								if (ImGui::Selectable(getBoxTypeName(boxType), settings::visuals::boxType == boxType)) settings::visuals::boxType = boxType;
							}
							ImGui::EndCombo();
						}
					}
					ImGui::EndChild();
					ImGui::Columns(1);
					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Exploits"))
				{
					/*
					ImGui::Text("Crosshair");
					ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x);
					ImGui::ColorEdit3("##crosshair", reinterpret_cast<float*>(&settings::colors::icCrosshairColor));

					ImGui::Text("FOV");
					ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x);
					ImGui::ColorEdit3("##fov", reinterpret_cast<float*>(&settings::colors::icFovColor));

					ImGui::Text("Box Visible");
					ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x);
					ImGui::ColorEdit3("##boxVisible", reinterpret_cast<float*>(&settings::colors::icBoxColorVisible));

					ImGui::Text("Box Invisible");
					ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x);
					ImGui::ColorEdit3("##boxInsible", reinterpret_cast<float*>(&settings::colors::icBoxColorInvisible));

					ImGui::Text("Skeleton Visible");
					ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x);
					ImGui::ColorEdit3("##skeletonVisible", reinterpret_cast<float*>(&settings::colors::icSkeletonColorVisible));

					ImGui::Text("Skeleton Invisible");
					ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x);
					ImGui::ColorEdit3("##skeletonInvisible", reinterpret_cast<float*>(&settings::colors::icSkeletonColorInvisible));

					ImGui::Text("Line Visible");
					ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x);
					ImGui::ColorEdit3("##lineVisible", reinterpret_cast<float*>(&settings::colors::icTracerColorVisible));

					ImGui::Text("Line Invisible");
					ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x);
					ImGui::ColorEdit3("##lineInvisible", reinterpret_cast<float*>(&settings::colors::icTracerColorInvisible));
					*/
					ImGui::Checkbox("Spinbot", &settings::exploits::spinbot);
					ImGui::Checkbox("FOV Changer", &settings::exploits::fovchanger);
					ImGui::Checkbox("Aim While Jumping", &settings::exploits::aimwhilejumping);
					ImGui::Checkbox("Magic Bullet", &settings::exploits::magicbullet);
					ImGui::Checkbox("No Reload", &settings::exploits::noreload);
					ImGui::Checkbox("No Overheat", &settings::exploits::overheat);
					ImGui::Checkbox("CarFly", &settings::exploits::carfly);
					ImGui::SliderFloat("FOV Changer Value", &settings::exploits::fovchanger_value, 105, 360);
					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Info"))
				{
					ImGui::Columns(2, nullptr, false);
					ImGui::SetColumnWidth(2, 550.0f / 2);
					float width = ImGui::GetColumnWidth() - 10.0f - ImGui::GetStyle().ChildBorderSize * 2;
					ImGui::BeginChild("##info", ImVec2(width, 0), true);
					{
						ImGui::Text("Info");
						ImGui::Separator();
						ImGui::Dummy(ImVec2(0, 1.0f));

						ImGui::Text("Discord: ");
						ImGui::SameLine(0, 0);
						ImGui::TextColored(ImVec4(0, 1, 1, 1), "discord.gg/saturniv");
						ImGui::Text("Made By ");
						ImGui::SameLine(0, 0);
						ImGui::TextColored(ImVec4(1, 0, 1, 1), "github.com/paysonism");
					}
					ImGui::EndChild();
					ImGui::NextColumn();
					ImGui::BeginChild("##options", ImVec2(width, 0), true);
					{
						ImGui::Text("Options");
						ImGui::Separator();
						ImGui::Dummy(ImVec2(0, 1.0f));

						if (ImGui::Button("Unload Cheat", ImVec2(ImGui::GetContentRegionAvail().x, 32)))
						{
							exit(0);
						}
					}
					ImGui::EndChild();
					ImGui::Columns(1);
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
		}
		ImGui::End();
	}
}

HWND get_process_wnd(uint32_t pid)
{
	std::pair<HWND, uint32_t> params = { 0, pid };
	BOOL bresult = EnumWindows([](HWND hwnd, LPARAM lparam) -> BOOL
		{
			auto pparams = (std::pair<HWND, uint32_t>*)(lparam);
			uint32_t processid = 0;
			if (GetWindowThreadProcessId(hwnd, reinterpret_cast<LPDWORD>(&processid)) && processid == pparams->second)
			{
				SetLastError((uint32_t)-1);
				pparams->first = hwnd;
				return FALSE;
			}
			return TRUE;
		}, (LPARAM)&params);

	if (!bresult && GetLastError() == -1 && params.first) return params.first;

	return 0;
}

WPARAM render_loop()
{
	static RECT old_rc;

	bool running = true;
	while (running)
	{
		while (PeekMessage(&messager, my_wnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&messager);
			DispatchMessage(&messager);
			if (messager.message == WM_QUIT)
			{
				running = false;
			}
		}

		if (!running) break;

		if (game_wnd == NULL) exit(0);

		HWND active_wnd = GetForegroundWindow();
		if (active_wnd == game_wnd)
		{
			HWND target_wnd = GetWindow(active_wnd, GW_HWNDPREV);
			SetWindowPos(my_wnd, target_wnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		else
		{
			game_wnd = get_process_wnd(PaysonDRV::ProcessID);
			Sleep(250);
		}

		RECT rc;
		POINT xy;
		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		rc.left = xy.x;
		rc.top = xy.y;
		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = 1.0f / 60.0f;
		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(0x1))
		{
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
		{
			io.MouseDown[0] = false;
		}

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;
			settings::width = rc.right;
			settings::height = rc.bottom;
			p_params.BackBufferWidth = settings::width;
			p_params.BackBufferHeight = settings::height;
			SetWindowPos(my_wnd, (HWND)0, xy.x, xy.y, settings::width, settings::height, SWP_NOREDRAW);
			p_device->Reset(&p_params);
		}

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		{
			features();
			render_menu();
		}
		ImGui::EndFrame();
		ImGui::Render();

		p_device->SetRenderState(D3DRS_ZENABLE, false);
		p_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		p_device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
		p_device->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

		if (p_device->BeginScene() >= 0)
		{
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			p_device->EndScene();
		}

		HRESULT result = p_device->Present(0, 0, 0, 0);
		if (result == D3DERR_DEVICELOST && p_device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			p_device->Reset(&p_params);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (p_device != 0)
	{
		p_device->EndScene();
		p_device->Release();
	}

	if (p_object != 0) p_object->Release();

	DestroyWindow(my_wnd);

	return messager.wParam;
}
