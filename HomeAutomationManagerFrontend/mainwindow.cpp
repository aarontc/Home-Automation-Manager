#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "HarmanKardonAVR645Receiver.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <xosd.h>


xosd *osd;


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	osd = xosd_create (2);
	if (osd == NULL)
	  {
		perror ("Could not create \"osd\"");
		exit (1);
	  }

}

MainWindow::~MainWindow()
{
	xosd_destroy (osd);
	delete ui;
}

void MainWindow::ReceiverStatus(QByteArray line1, QByteArray line2, QByteArray icons) {
	ui->lineEdit->setText(line1);
	ui->lineEdit_2->setText(line2);
	xosd_display (osd, 0, XOSD_string, "You have been R00ted");
}

void MainWindow::on_pushButton_clicked()
{
	emit(ReceiverCommand(HarmanKardonAVR645Receiver::COMMAND_POWER_ON));
}

void MainWindow::on_pushButton_2_clicked()
{
	emit(ReceiverCommand(HarmanKardonAVR645Receiver::COMMAND_POWER_OFF));
}

void MainWindow::on_pushButton_3_clicked()
{
	emit(ReceiverCommand(HarmanKardonAVR645Receiver::COMMAND_VOLUME_UP));
}

void MainWindow::on_pushButton_4_clicked()
{
	emit(ReceiverCommand(HarmanKardonAVR645Receiver::COMMAND_VOLUME_DOWN));
}
