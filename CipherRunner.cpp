#include "CipherRunner.h"

#include <QStringList>
#include <QString>
#include <QFile>
#include <QTextStream>

CipherRunner::CipherRunner(QWidget *parent) :
        pro_cipher(new QProcess(this)),
        timer(new QTimer(this)){

    connect(pro_cipher,&QProcess::readyReadStandardOutput,this,&CipherRunner::updateLogger);
    connect(pro_cipher,&QProcess::readyReadStandardError,this,&CipherRunner::recordError);
    connect(pro_cipher,QOverload<int,QProcess::ExitStatus>::of(&QProcess::finished),
            [this](int exitCode,QProcess::ExitStatus exitStatus){
                timer->stop();
                emit s_Cal_Finished(exitCode, exitStatus);
            });
    connect(timer,&QTimer::timeout,this,&CipherRunner::updateResidual);
}


void CipherRunner::runCipher() {
    QStringList argument;
    argument << "-np" << "4" << "./cipher-1.0.5";
    pro_cipher->start("mpirun",argument);
    timer->start(1000);
}

void CipherRunner::updateLogger() {
    QByteArray message = pro_cipher ->readAllStandardOutput();
    emit s_MessageToLog(message);
}

void CipherRunner::recordError() {
    QByteArray errorMessage = pro_cipher -> readAllStandardError();
    emit s_ErrorToLog(QByteArray("[Error: ]") + errorMessage);
}

void CipherRunner::updateResidual() {
    QVector<double> iteration, convergence1,convergence2;

    QFile histFile("./hist.dat");
    if(histFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&histFile);

        while(!in.atEnd()){
            QString line = in.readLine();
            QStringList data = line.split(" ",Qt::SkipEmptyParts);

            if(data.size() >=4){
                iteration.append(data[1].toDouble());
                convergence1.append(data[2].toDouble());
                convergence2.append(data[3].toDouble());
            }
        }

        histFile.close();
    }
    emit s_UpdateResidual(iteration,convergence1,convergence2);
}

void CipherRunner::updateResult() {

}


