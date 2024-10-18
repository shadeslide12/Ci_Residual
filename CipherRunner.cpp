#include "CipherRunner.h"

#include <QStringList>
#include <QString>

CipherRunner::CipherRunner(QWidget *parent) :
        pro_cipher(new QProcess(this)){

    connect(pro_cipher,&QProcess::readyReadStandardOutput,this,&CipherRunner::updateLogger);
    connect(pro_cipher,&QProcess::readyReadStandardError,this,&CipherRunner::recordError);
}


void CipherRunner::runCipher() {
    QStringList argument;
    argument << "-np" << "10" << "./cipher-1.0.5";
    pro_cipher->start("mpirun",argument);
}

void CipherRunner::updateLogger() {
    QByteArray message = pro_cipher ->readAllStandardOutput();
    emit messageToLog(message);
}

void CipherRunner::recordError() {
    QByteArray errorMessage = pro_cipher -> readAllStandardError();
    emit errorToLog(QByteArray("[Error: ]")+errorMessage);
}
