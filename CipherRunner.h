#ifndef QTTEST_CIPHERRUNNER_H
#define QTTEST_CIPHERRUNNER_H

#include <QObject>
#include <QProcess>
#include <QTimer>
#include <QFile>

class CipherRunner: public QObject{
Q_OBJECT

public:
    explicit CipherRunner(QWidget* parent= nullptr);

    void runCipher();
    void updateLogger();
    void recordError();
    void updateResidual();
    void updateResult();
signals:
    void s_MessageToLog(const QByteArray& message);
    void s_ErrorToLog(const QByteArray& error);
    void s_Cal_Finished(int exitCode , QProcess::ExitStatus exitStatus);
    void s_UpdateResidual(const int& iteration,const double& convergence1,const double& convergence2);
    void s_UpdateResult();

private:
    QProcess* pro_cipher;
    QTimer* timer;
    qint64 lastResFilePos;
    QFile dataFile;
};


#endif //QTTEST_CIPHERRUNNER_H
