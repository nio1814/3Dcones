#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "generator.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	m_generator(new Generator)
{
	ui->setupUi(this);
	ui->trajectoryComboBox->addItem("Spiral", Generator::Spiral);

//	connect(ui->trajectoryComboBox, SIGNAL(currentIndexChanged(int)), m_generator, SLOT(setTrajectory(TrajectoryType)));
	connect(ui->trajectoryComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateFieldOfViewDisplay()));
//	connect(ui->trajectoryComboBox, SIGNAL(currentIndexChanged(int)), [=](int index){
//		Generator::TrajectoryType type = ui->trajectoryComboBox->currentData().value<Generator::TrajectoryType>();
//		m_generator->setTrajectory(type);
//	});
	connect(ui->trajectoryComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index){
		Generator::TrajectoryType type = ui->trajectoryComboBox->currentData().value<Generator::TrajectoryType>();
		m_generator->setTrajectory(type);
	});

	updateFieldOfViewDisplay();

	m_fieldOfViewSlider[0] = ui->fieldOfViewXSlider;
	m_fieldOfViewSlider[1] = ui->fieldOfViewYSlider;
	m_fieldOfViewSlider[2] = ui->fieldOfViewZSlider;
	m_fieldOfViewSpinBox[0] = ui->fieldOfViewXSpinBox;
	m_fieldOfViewSpinBox[1] = ui->fieldOfViewYSpinBox;
	m_fieldOfViewSpinBox[2] = ui->fieldOfViewZSpinBox;

	for (int n=0; n<3; n++)
	{
		m_fieldOfViewSlider[n]->setMinimum(5);
		m_fieldOfViewSlider[n]->setMaximum(50);
		m_fieldOfViewSpinBox[n]->setMinimum(m_fieldOfViewSlider[n]->minimum());
		m_fieldOfViewSpinBox[n]->setMaximum(m_fieldOfViewSlider[n]->maximum());
		connect(m_fieldOfViewSlider[n], &QSlider::valueChanged, [=](int value){
			setFieldOfView(value, n);
		});
		connect(m_fieldOfViewSpinBox[n], &QSpinBox::editingFinished, [=]{
			setFieldOfView(m_fieldOfViewSpinBox[n]->value(), n);
		});
		m_fieldOfViewSlider[n]->setValue(28);
	}

	m_spatialResolutionSlider[0] = ui->spatialResolutionXSlider;
	m_spatialResolutionSlider[1] = ui->spatialResolutionYSlider;
	m_spatialResolutionSlider[2] = ui->spatialResolutionZSlider;
	m_spatialResolutionSpinBox[0] = ui->spatialResolutionXDoubleSpinBox;
	m_spatialResolutionSpinBox[1] = ui->spatialResolutionYDoubleSpinBox;
	m_spatialResolutionSpinBox[2] = ui->spatialResolutionZDoubleSpinBox;

	for (int n=0; n<3; n++)
	{
		m_spatialResolutionSpinBox[n]->setMinimum(.3);
		m_spatialResolutionSpinBox[n]->setMaximum(12);
		m_spatialResolutionSlider[n]->setMinimum(m_spatialResolutionSpinBox[n]->minimum()*m_spatialResolutionSliderScale);
		m_spatialResolutionSlider[n]->setMaximum(m_spatialResolutionSpinBox[n]->maximum()*m_spatialResolutionSliderScale);

		connect(m_spatialResolutionSlider[n], &QSlider::valueChanged, [=](int value){
			setSpatialResolution(value/m_spatialResolutionSliderScale, n);
		});
		connect(m_spatialResolutionSpinBox[n], &QSpinBox::editingFinished, [=]{
			setSpatialResolution(m_spatialResolutionSpinBox[n]->value(), n);
		});
		m_spatialResolutionSpinBox[n]->setValue(2);
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::updateFieldOfViewDisplay()
{
	QWidget* layout;
	switch(m_generator->trajectoryType())
	{
		case Generator::Spiral:
//			layout = qobject_cast<QWidget*>(ui->fieldOfViewYLayout);
//			layout->hide();
			break;
	}
}

void MainWindow::setFieldOfView(float fieldOfView, int axis)
{
	m_fieldOfViewSlider[axis]->setValue(fieldOfView);
	m_fieldOfViewSpinBox[axis]->setValue(fieldOfView);
}

void MainWindow::setSpatialResolution(float spatialResolution, int axis)
{
	m_spatialResolutionSlider[axis]->setValue(m_spatialResolutionSliderScale*spatialResolution);
	m_spatialResolutionSpinBox[axis]->setValue(spatialResolution);
}
