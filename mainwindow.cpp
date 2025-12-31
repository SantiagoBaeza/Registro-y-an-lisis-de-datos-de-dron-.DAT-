#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include "muParser.h"
#include <QDebug>
#include <QPen>
#include <QBrush>
#include <cmath>
#include <cstdio>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->botonIniciar, &QPushButton::clicked, this, [this](){
        iniciar();
    });
    connect(ui->botonCompute, &QPushButton::clicked, this, [this](){
        compute();
    });
    connect(ui->botonValuar, &QPushButton::clicked, this, [this](){
        valuar();
    });
}
void MainWindow::iniciar(){

    //aca abro una ventana de dialogo para seleccionar el archivo que quiero
    QString fileName= QFileDialog::getOpenFileName(this, "abrir archivo binario", "","Binary file(*.DAT)");
    if(fileName.isEmpty())
        return; //por si el usuario no selecciona nada se corta la ejecucion

    //esto nos dio la ruta del archivo, ahora tengo que pasarla a cost char*
    std::string path = fileName.toStdString();
    const char* cpath = path.c_str();

    //ahora ya puedo implementar lo de antes
    FILE* f = fopen(cpath, "rb");
    if (!f) {
        qDebug() << "No pude abrir el archivo";
        return;
    }

    //aca comienzo a usar el archivo...
    fseek(f, 0, SEEK_END);
    int bytes= ftell(f); //me fui hasta el final del archivo y registre el paso en "bytes"
    fseek(f, 0, SEEK_SET);
    int contFloat= bytes/ sizeof(float); //divido la cantidad de bytes por la cant de float, asi se cuantos hay
    int N= contFloat/4;
    varx.resize(N);
    vary.resize(N);
    time.resize(N);
    bateria.resize(N);

    for(int i=0; i<N; i++){
        float x, y, t, b;

        //leo el archivo
        fread(&x, sizeof(float),1,f);
        fread(&y, sizeof(float),1,f);
        fread(&t, sizeof(float),1,f);
        fread(&b, sizeof(float),1,f);

        //paso de float a double asi la grafica puede usarlos
        varx[i]= static_cast<double>(x);
        vary[i]= static_cast<double>(y);
        time[i]= static_cast<double>(t);
        bateria[i]= static_cast<double>(b);
    }
    fclose(f); //y ya tenemos todo guardado en nuestros cuatro vectores

    ui->plotx->clearGraphs();
    ui->ploty->clearGraphs();
    ui->plotb->clearGraphs();

    //grafica para x
    ui->plotx->addGraph();
    ui->plotx->graph(0)->setData(time, varx); //lo que antes era x,y
    ui->plotx->rescaleAxes();
    //config_grafica(ui->plotx); //esta es la funcion que esta al final del codigo
    ui->plotx->replot();

    //grafica para y
    ui->ploty->addGraph();
    ui->ploty->graph(0)->setData(time, vary);
    ui->ploty->rescaleAxes();
    //config_grafica(ui->ploty);
    ui->ploty->replot();

    //grafica para bateria
    ui->plotb->addGraph();
    ui->plotb->graph(0)->setData(time, bateria);
    ui->plotb->rescaleAxes();
    //config_grafica(ui->plotb);
    ui->plotb->replot();
}

void MainWindow::compute(){
    int N= time.size(); //pongo el valor del tiempo en la variable N
    if(N<2){
        ui->lcdEnergy->display(0);
    }
    double tmin= ui->Tmin->text().toDouble(); //asigno los valores ingresados en los lineEdits
    double tmax= ui->Tmax->text().toDouble();

    //verifico que sean valores logicos
    if(tmin< time[0] || tmax> time[N-1]){
        ui->lcdEnergy->display(0);
    }

    //busco los indices
    int i_min= 0;
    int i_max= N-1;
    for(int i=0; i<N; i++){
        if(time[i]<= tmin && tmin<= time[i+1]){
            i_min= i;
        }
        if(time[i]<=tmax && tmax<=time[i+1]){
            i_max= i;
        }
    }

    //integro
    double integral= 0.0;
    for(int i= i_min; i<= i_max; i++){
        double dt= time[i] - time[i-1]; //esto seria x
        double b_avg= (bateria[i]+ bateria[i-1])* 0.5; //esto seria y
        integral= integral+ dt* b_avg;
    }
    //interpolo
    {
        double t1= time[i_min];
        double t2= time[i_min+1];
        double aux= (tmin- t1)/ (t2-t1);
        double bmin= bateria[i_min] + aux * (bateria[i_min+1] - bateria[i_min]);

        double dt= time[i_min+1] - tmin;
        double b_avg= 0.5 * (bmin + bateria[i_min+1]);
        integral= integral + dt*b_avg;
    }
    {
        double t1= time[i_max];
        double t2= time[i_max+1];
        double aux= (tmax - t1)/(t2-t1);
        double bmax= bateria[i_max] + aux*(bateria[i_max+1]- bateria[i_max]);

        double dt= tmax-time[i_max];
        double b_avg= 0.5*(bmax+ bateria[i_max]);
        integral= integral + dt*b_avg;
    }
    ui->lcdEnergy->display(integral);
}

void MainWindow::valuar(){
    int N = time.size();
    double tiempo= ui->lineEditTiempo->text().toDouble();

    //me aseguro de que el valor este dentro del rango
    if(tiempo <=time[0]  || tiempo>= time[N-1]){
        ui->lcdX->display(0);
        ui->lcdY->display(0);
        ui->lcdBat->display(0);
    }

    int i=0;
    for(int k=0; k<=N-1;k++){ //recorro todo el qvector time[] buscando el intervalo que voy a interpolar
        if(tiempo>=time[k] && tiempo<=time[k+1]){
            //si estamos aca significa que este es el intervalo a interpolar
            i=k;
        }

    }
    double t1= time[i];
    double t2= time[i+1];
    double fac= (tiempo-t1)/(t2-t1);

    //interpolacion
    double x_val= varx[i]+fac*(varx[i+1]-varx[i]);
    double y_val= vary[i]+fac*(vary[i+1]-vary[i]);
    double b_val= bateria[i]+fac*(bateria[i+1]-bateria[i]);

    //muestro los valores
    ui->lcdX->display(x_val);
    ui->lcdY->display(y_val);
    ui->lcdBat->display(b_val);
}

MainWindow::~MainWindow()
{
    delete ui;
}
