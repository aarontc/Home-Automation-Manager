#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	signals:
		void ReceiverCommand(QByteArray command);

	public slots:
		void ReceiverStatus(QByteArray line1, QByteArray line2, QByteArray icons);

	private slots:
		void on_pushButton_clicked();

		void on_pushButton_2_clicked();

		void on_pushButton_3_clicked();

		void on_pushButton_4_clicked();

	private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
