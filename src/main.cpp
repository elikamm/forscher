#include "forscher.hpp"
using std::cout;
using std::cerr;
using std::runtime_error;
using httplib::Server;

void forscher_main();

int main()
{
	cout << "INFO: Server wird gestartet.\n";

	while (true) {
		try {
			forscher_main();
		}
		catch(runtime_error &error) {
			cerr << "ERROR: Ein Fehler ist aufgetreten: " << error.what() << '\n';
		}
		catch(...) {
			cerr << "ERROR: Ein unbekannter Fehler ist aufgetreten.\n";
		}

		cout << "INFO: Server wird neu gestartet.\n";
	}

	return 0;
}

void forscher_main() {
	Server server;

	server.Get("/", [](const httplib::Request &, httplib::Response &res) {
  		res.set_content((char *)src_web_index_html, src_web_index_html_len, "text/html");
	});

	cout << "INFO: Server lauscht unter http://localhost:" << SERVER_PORT << "/\n";
	server.listen("0.0.0.0", SERVER_PORT);
}
