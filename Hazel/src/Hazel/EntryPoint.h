#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::init();
	HZ_CORE_WARN("this is a warn");
	int a = 5;
	HZ_INFO("Hello var = {0}", a);

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif // HA_PLATFORM_WINDOWS
