#include "gui.hpp"

#include "lua/lua_manager.hpp"
#include "renderer/renderer.hpp"

namespace big
{
	gui::gui()
	{
		g_renderer->add_dx_callback(
		    [] {
			    if (g_lua_manager)
			    {
				    g_lua_manager->trigger_event<"EarlyDraw">();
			    }
		    },
		    -100'000);
		g_renderer->add_dx_callback(
		    [] {
			    if (g_lua_manager)
			    {
				    g_lua_manager->trigger_event<"Draw">();
			    }
		    },
		    -1);

		g_renderer->add_wndproc_callback([](HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
			if (g_lua_manager)
			{
				g_lua_manager->trigger_event<"Wndproc">(hwnd, msg, wparam, lparam);
			}
		});

		g_renderer->set_safe_to_render();
	}
}
