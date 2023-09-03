#pragma once

#include <QWidget>
#include "ui_TalkWindowShell.h"

class TalkWindowShell : public QWidget
{
	Q_OBJECT

public:
	TalkWindowShell(QWidget *parent = nullptr);
	~TalkWindowShell();

private:
	Ui::TalkWindowShellClass ui;
};
