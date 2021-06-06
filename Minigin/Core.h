#pragma once
struct SDL_Window;
namespace GameEngine
{
	class Core
	{
	public:
		void Initialize();
		virtual void LoadGame() const =0;
		void Cleanup();
		void Run();
		virtual ~Core() {};
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
	};
}