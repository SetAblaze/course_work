#include <QApplication>
#include <mainwindow.h>
#include <dialog.h>


	int main(int argc, char* argv[]) {
		QApplication app(argc, argv);

		Dialog* logWindow = new Dialog();

		logWindow->show();

		return app.exec();
	}
