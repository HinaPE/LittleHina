#include "platform.h"
#include <imterm/terminal.hpp>
#include <imterm/terminal_helpers.hpp>
#include "GLFW/glfw3.h"
#include <vector>
#include <thread>

struct Helper
{
	bool should_close = false;
};

struct TerminalCommands : public ImTerm::basic_terminal_helper<TerminalCommands, Helper>
{
	TerminalCommands() = default;

	static void echo(argument_type &) {}
	static void ls(argument_type &) {}
	static void cd(argument_type &) {}
	static void exit(argument_type &) {
		// 先维护一个线程池
		std::thread thread;
		thread.join(); // 类似于这样，每次调用exit的时候就把线程join到主线程上。
	}
	static void help(argument_type &) {}

};

static int i = 0;

auto main() -> int
{
	Kasumi::Platform platform(1920, 1080);
	std::vector<ImTerm::terminal<TerminalCommands> *> other_terminals;

	Helper default_helper;
	ImTerm::terminal<TerminalCommands> default_terminal(default_helper);
	platform._key_callbacks.emplace_back(
			[&](int key, int scancode, int action, int mods) -> void
			{
				if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
				{
					Helper helper;
					auto terminal = new ImTerm::terminal<TerminalCommands>(helper);
					other_terminals.emplace_back(terminal);
				}
			}
	);

	platform.launch(
			[&]() -> int
			{
				default_terminal.show("Window 1");

				for (auto &terminal: other_terminals)
					terminal->show("Terminal" + std::to_string(i));
				return 0;
			}
	);
	return 0;
}
