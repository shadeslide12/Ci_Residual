#include "CipherRunner.h"

#include <QStringList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
//
CipherRunner::CipherRunner(QWidget *parent) :
        pro_cipher(new QProcess(this)),
        timer(new QTimer(this)),
        lastResFilePos(0) {
    connect(pro_cipher,&QProcess::readyReadStandardOutput,this,&CipherRunner::updateLogger);
    connect(pro_cipher,&QProcess::readyReadStandardError,this,&CipherRunner::recordError);
    connect(pro_cipher,QOverload<int,QProcess::ExitStatus>::of(&QProcess::finished),
            [this](int exitCode,QProcess::ExitStatus exitStatus){
                timer->stop();
                lastResFilePos = 0;
                emit s_Cal_Finished(exitCode, exitStatus);
                dataFile.close();
            });
    connect(timer,&QTimer::timeout,this,&CipherRunner::updateResidual);
}


void CipherRunner::runCipher() {
    dataFile.setFileName("./hist.dat");
    if(! (dataFile.open(QIODevice::ReadOnly | QIODevice::Text) )) {
        qDebug() << "read dataFile failed";
        return;
    }
    lastResFilePos =0;
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

void CipherRunner:: updateResidual() {

    QTextStream in (&dataFile);
    in.seek(lastResFilePos);

    if(!in.atEnd() ){
        QString line = in.readLine();
        QStringList data  = line.split(" ",Qt::SkipEmptyParts);
        if(data.size()>= 4 ){
            int iteration = data[1].toInt();
            double convergence1 = data[2].toDouble();
            double convergence2 = data[3].toDouble();
            emit s_UpdateResidual(iteration,convergence1,convergence2);
        }
    }

    lastResFilePos = in.pos();

}

void CipherRunner::updateResult() {

}


