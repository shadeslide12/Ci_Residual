#ifndef QTTEST_CIPHERRUNNER_H
#define QTTEST_CIPHERRUNNER_H

#include <QObject>
#include <QProcess>
#include <QTimer>

class CipherRunner: public QObject{
Q_OBJECT

public:
    explicit CipherRunner(QWidget* parent= nullptr);

    void runCipher();
    void updateLogger();
    void recordError();
    void updateResidual();
signals:
    void messageToLog(const QByteArray& message);
    void errorToLog(const QByteArray& error);
    void finished();
    void s_UpdateResidual(const QVector<double>& iteration,
                          const QVector<double>& convergence1,
                          const QVector<double>& convergence2);
private:
    QProcess* pro_cipher;
    QTimer* timer;
};


#endif //QTTEST_CIPHERRUNNER_H
